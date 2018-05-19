// Copyright (c) 2018 The DeepOnion Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "walletmodel.h"
#include "guiconstants.h"
#include "optionsmodel.h"
#include "addresstablemodel.h"
#include "transactiontablemodel.h"

#include "ui_interface.h"
#include "wallet.h"
#include "walletdb.h" // for BackupWallet
#include "base58.h"

#include <QSet>
#include <QTimer>

WalletModel::WalletModel(CWallet *wallet, OptionsModel *optionsModel, QObject *parent) :
    QObject(parent), wallet(wallet), optionsModel(optionsModel), addressTableModel(0),
    transactionTableModel(0),
    cachedBalance(0), cachedStake(0), cachedUnconfirmedBalance(0), cachedImmatureBalance(0),
    cachedNumTransactions(0),
    cachedEncryptionStatus(Unencrypted),
    cachedNumBlocks(0)
{
    addressTableModel = new AddressTableModel(wallet, this);
    transactionTableModel = new TransactionTableModel(wallet, this);

    // This timer will be fired repeatedly to update the balance
    pollTimer = new QTimer(this);
    connect(pollTimer, SIGNAL(timeout()), this, SLOT(pollBalanceChanged()));
    pollTimer->start(MODEL_UPDATE_DELAY);

    subscribeToCoreSignals();
}

WalletModel::~WalletModel()
{
    unsubscribeFromCoreSignals();
}

qint64 WalletModel::getBalance() const
{
    return wallet->GetBalance();
}

qint64 WalletModel::getUnconfirmedBalance() const
{
    return wallet->GetUnconfirmedBalance();
}

qint64 WalletModel::getStake() const
{
    return wallet->GetStake();
}

qint64 WalletModel::getImmatureBalance() const
{
    return wallet->GetImmatureBalance();
}

int WalletModel::getNumTransactions() const
{
    int numTransactions = 0;
    {
        LOCK(wallet->cs_wallet);
        numTransactions = wallet->mapWallet.size();
    }
    return numTransactions;
}

void WalletModel::updateStatus()
{
    EncryptionStatus newEncryptionStatus = getEncryptionStatus();

    if(cachedEncryptionStatus != newEncryptionStatus)
        emit encryptionStatusChanged(newEncryptionStatus);
}

void WalletModel::pollBalanceChanged()
{
    if(nBestHeight != cachedNumBlocks)
    {
        // Balance and number of transactions might have changed
        cachedNumBlocks = nBestHeight;
        checkBalanceChanged();
    }
}

void WalletModel::checkBalanceChanged()
{
    qint64 newBalance = getBalance();
    qint64 newStake = getStake();
    qint64 newUnconfirmedBalance = getUnconfirmedBalance();
    qint64 newImmatureBalance = getImmatureBalance();

    if(cachedBalance != newBalance || cachedStake != newStake || cachedUnconfirmedBalance != newUnconfirmedBalance || cachedImmatureBalance != newImmatureBalance)
    {
        cachedBalance = newBalance;
        cachedStake = newStake;
        cachedUnconfirmedBalance = newUnconfirmedBalance;
        cachedImmatureBalance = newImmatureBalance;
        emit balanceChanged(newBalance, newStake, newUnconfirmedBalance, newImmatureBalance);
    }
}

void WalletModel::updateTransaction(const QString &hash, int status)
{
    if(transactionTableModel)
        transactionTableModel->updateTransaction(hash, status);

    // Balance and number of transactions might have changed
    checkBalanceChanged();

    int newNumTransactions = getNumTransactions();
    if(cachedNumTransactions != newNumTransactions)
    {
        cachedNumTransactions = newNumTransactions;
        emit numTransactionsChanged(newNumTransactions);
    }
}

void WalletModel::updateAddressBook(const QString &address, const QString &label, bool isMine, int status)
{
    if(addressTableModel)
        addressTableModel->updateEntry(address, label, isMine, status);
}

bool WalletModel::validateAddress(const QString &address)
{
    std::string sAddr = address.toStdString();

    if (sAddr.length() > STEALTH_LENGTH_TRESHOLD)
    {
        if (IsStealthAddress(sAddr)) {
            return true;
        }
    }

    CBitcoinAddress addressParsed(sAddr);
    return addressParsed.IsValid();
}

WalletModel::SendCoinsReturn WalletModel::sendCoins(const QList<SendCoinsRecipient> &recipients, const CCoinControl *coinControl)
{
    qint64 total = 0;
    QSet<QString> setAddress;
    QString hex;

    if(recipients.empty())
    {
        return OK;
    }

    // Pre-check input data for validity
    foreach(const SendCoinsRecipient &rcp, recipients)
    {
        if(!validateAddress(rcp.address))
        {
            return InvalidAddress;
        }

        setAddress.insert(rcp.address);

        if(rcp.amount <= 0)
        {
            return InvalidAmount;
        }

        total += rcp.amount;
    }

    if (recipients.size() > setAddress.size())
        foreach(QString rcpAddr, setAddress)
            if(!IsStealthAddress(rcpAddr.toStdString()))
                return DuplicateAddress;

    int64_t nBalance = 0;
    std::vector<COutput> vCoins;
    wallet->AvailableCoins(vCoins, true, coinControl);

    BOOST_FOREACH(const COutput& out, vCoins)
        nBalance += out.tx->vout[out.i].nValue;

    if(total > nBalance)
        return AmountExceedsBalance;

    if((total + nTransactionFee) > nBalance)
        return SendCoinsReturn(AmountWithFeeExceedsBalance, nTransactionFee);

    std::map<int, std::string> mapStealthNarr;
    
    {
        LOCK2(cs_main, wallet->cs_wallet);

        CWalletTx wtx;

        // Sendmany
        std::vector<std::pair<CScript, int64_t> > vecSend;
        foreach(const SendCoinsRecipient &rcp, recipients)
        {
            std::string sAddr = rcp.address.toStdString();

            if (rcp.typeInd == AddressTableModel::AT_Stealth)
            {
                CStealthAddress sxAddr;
                if (sxAddr.SetEncoded(sAddr))
                {
                    ec_secret ephem_secret;
                    ec_secret secretShared;
                    ec_point pkSendTo;
                    ec_point ephem_pubkey;

                    if (GenerateRandomSecret(ephem_secret) != 0)
                    {
                        LogPrintf("GenerateRandomSecret failed.\n");
                        return Aborted;
                    }

                    if (StealthSecret(ephem_secret, sxAddr.scan_pubkey, sxAddr.spend_pubkey, secretShared, pkSendTo) != 0)
                    {
                        LogPrintf("Could not generate receiving public key.\n");
                        return Aborted;
                    }

                    CPubKey cpkTo(pkSendTo);
                    if (!cpkTo.IsValid())
                    {
                        LogPrintf("Invalid public key generated.\n");
                        return Aborted;
                    }

                    CBitcoinAddress addrTo(cpkTo.GetID());

                    if (SecretToPublicKey(ephem_secret, ephem_pubkey) != 0)
                    {
                        LogPrintf("Could not generate ephem public key.\n");
                        return Aborted;
                    }

                    if (fDebug)
                    {
                        LogPrintf("Stealth send to generated pubkey %u: %s\n", pkSendTo.size(), HexStr(pkSendTo).c_str());
                        LogPrintf("hash %s\n", addrTo.ToString().c_str());
                        LogPrintf("ephem_pubkey %u: %s\n", ephem_pubkey.size(), HexStr(ephem_pubkey).c_str());
                    }

                    CScript scriptPubKey;
                    scriptPubKey.SetDestination(addrTo.Get());

                    vecSend.push_back(make_pair(scriptPubKey, rcp.amount));

                    CScript scriptP = CScript() << OP_RETURN << ephem_pubkey;

                    if (rcp.narration.length() > 0)
                    {
                        std::string sNarr = rcp.narration.toStdString();

                        if (sNarr.length() > 24)
                        {
                            LogPrintf("Narration is too long.\n");
                            return NarrationTooLong;
                        }

                        std::vector<unsigned char> vchNarr;

                        SecMsgCrypter crypter;
                        crypter.SetKey(&secretShared.e[0], &ephem_pubkey[0]);

                        if (!crypter.Encrypt((uint8_t*)&sNarr[0], sNarr.length(), vchNarr))
                        {
                            LogPrintf("Narration encryption failed.\n");
                            return Aborted;
                        }

                        if (vchNarr.size() > 48)
                        {
                            LogPrintf("Encrypted narration is too long.\n");
                            return Aborted;
                        }

                        if (vchNarr.size() > 0)
                            scriptP = scriptP << OP_RETURN << vchNarr;

                        int pos = vecSend.size()-1;
                        mapStealthNarr[pos] = sNarr;
                    }

                    vecSend.push_back(std::make_pair(scriptP, 0));
                    continue;
                } // else drop through to normal
            }

            CScript scriptPubKey;
            scriptPubKey.SetDestination(CBitcoinAddress(sAddr).Get());
            vecSend.push_back(make_pair(scriptPubKey, rcp.amount));

            if (rcp.narration.length() > 0)
            {
                std::string sNarr = rcp.narration.toStdString();

                if (sNarr.length() > 24)
                {
                    LogPrintf("Narration is too long.\n");
                    return NarrationTooLong;
                }

                std::vector<uint8_t> vNarr(sNarr.c_str(), sNarr.c_str() + sNarr.length());
                std::vector<uint8_t> vNDesc;

                vNDesc.resize(2);
                vNDesc[0] = 'n';
                vNDesc[1] = 'p';

                CScript scriptN = CScript() << OP_RETURN << vNDesc << OP_RETURN << vNarr;

                vecSend.push_back(make_pair(scriptN, 0));
            }
        }

        CReserveKey keyChange(wallet);
        int64 nFeeRequired = 0;
        int nChangePos = -1;
        bool fCreated = wallet->CreateTransaction(vecSend, wtx, keyChange, nFeeRequired, nChangePos, coinControl);

        std::map<int, std::string>::iterator it;
        for (it = mapStealthNarr.begin(); it != mapStealthNarr.end(); ++it)
        {
            int pos = it->first;
            if (nChangePos > -1 && it->first >= nChangePos)
                pos++;
            
            char key[64];
            if (snprintf(key, sizeof(key), "n_%u", pos) < 1)
            {
                LogPrintf("CreateStealthTransaction(): Error creating narration key.");
                continue;
            }
            wtx.mapValue[key] = it->second;
        }

        if (!fCreated)
        {
            if ((total + nFeeRequired) > nBalance) // FIXME: could cause collisions in the future
                return SendCoinsReturn(AmountWithFeeExceedsBalance, nFeeRequired);

            return TransactionCreationFailed;
        }
        if (!uiInterface.ThreadSafeAskFee(nFeeRequired, tr("Sending...").toStdString()))
            return Aborted;

        if (!wallet->CommitTransaction(wtx, keyChange))
            return TransactionCommitFailed;

        hex = QString::fromStdString(wtx.GetHash().GetHex());

    } // cs_main, wallet->cs_wallet

    // Add addresses / update labels that we've sent to to the address book
    foreach(const SendCoinsRecipient &rcp, recipients)
    {
        if(rcp.label.isEmpty()) // Don't add addresses without labels...
            continue;

        std::string strAddress = rcp.address.toStdString();
        std::string strLabel = rcp.label.toStdString();
        {
            LOCK(wallet->cs_wallet);

            if (rcp.typeInd == AddressTableModel::AT_Stealth)
            {
                wallet->UpdateStealthAddress(strAddress, strLabel, true);
            } 
            else
            {
                CTxDestination dest = CBitcoinAddress(strAddress).Get();
                std::map<CTxDestination, std::string>::iterator mi = wallet->mapAddressBook.find(dest);

                // Check if we have a new address or an updated label
                if (mi == wallet->mapAddressBook.end() || mi->second != strLabel)
                    wallet->SetAddressBookName(dest, strLabel);
            }
        } // wallet->cs_wallet
    }

    return SendCoinsReturn(OK, 0, hex);
}

OptionsModel *WalletModel::getOptionsModel()
{
    return optionsModel;
}

AddressTableModel *WalletModel::getAddressTableModel()
{
    return addressTableModel;
}

TransactionTableModel *WalletModel::getTransactionTableModel()
{
    return transactionTableModel;
}

WalletModel::EncryptionStatus WalletModel::getEncryptionStatus() const
{
    if(!wallet->IsCrypted())
    {
        return Unencrypted;
    }
    else if(wallet->IsLocked())
    {
        return Locked;
    }
    else
    {
        return Unlocked;
    }
}

bool WalletModel::setWalletEncrypted(bool encrypted, const SecureString &passphrase)
{
    if(encrypted)
    {
        // Encrypt
        return wallet->EncryptWallet(passphrase);
    }
    else
    {
        // Decrypt -- TODO; not supported yet
        return false;
    }
}

bool WalletModel::setWalletLocked(bool locked, const SecureString &passPhrase)
{
    if(locked)
    {
        // Lock
        return wallet->Lock();
    }
    else
    {
        // Unlock
        return wallet->Unlock(passPhrase);
    }
}

bool WalletModel::changePassphrase(const SecureString &oldPass, const SecureString &newPass)
{
    bool retval;
    {
        LOCK(wallet->cs_wallet);
        wallet->Lock(); // Make sure wallet is locked before attempting pass change
        retval = wallet->ChangeWalletPassphrase(oldPass, newPass);
    }
    return retval;
}

bool WalletModel::backupWallet(const QString &filename)
{
    return BackupWallet(*wallet, filename.toLocal8Bit().data());
}

// Handlers for core signals
static void NotifyKeyStoreStatusChanged(WalletModel *walletmodel, CCryptoKeyStore *wallet)
{
    OutputDebugStringF("NotifyKeyStoreStatusChanged\n");
    QMetaObject::invokeMethod(walletmodel, "updateStatus", Qt::QueuedConnection);
}

static void NotifyAddressBookChanged(WalletModel *walletmodel, CWallet *wallet, const CTxDestination &address, const std::string &label, bool isMine, ChangeType status)
{
    if (address.type() == typeid(CStealthAddress)) {
        CStealthAddress sxAddr = boost::get<CStealthAddress>(address);
        std::string enc = sxAddr.Encoded();
        OutputDebugStringF("NotifyAddressBookChanged %s %s isMine=%i status=%i\n", enc.c_str(), label.c_str(), isMine, status);
        QMetaObject::invokeMethod(walletmodel, "updateAddressBook", Qt::QueuedConnection,
                                  Q_ARG(QString, QString::fromStdString(enc)),
                                  Q_ARG(QString, QString::fromStdString(label)),
                                  Q_ARG(bool, isMine),
                                  Q_ARG(int, status));
    } else {
        OutputDebugStringF("NotifyAddressBookChanged %s %s isMine=%i status=%i\n", CBitcoinAddress(address).ToString().c_str(), label.c_str(), isMine, status);
        QMetaObject::invokeMethod(walletmodel, "updateAddressBook", Qt::QueuedConnection,
                                  Q_ARG(QString, QString::fromStdString(CBitcoinAddress(address).ToString())),
                                  Q_ARG(QString, QString::fromStdString(label)),
                                  Q_ARG(bool, isMine),
                                  Q_ARG(int, status));
    }
}

static void NotifyTransactionChanged(WalletModel *walletmodel, CWallet *wallet, const uint256 &hash, ChangeType status)
{
    OutputDebugStringF("NotifyTransactionChanged %s status=%i\n", hash.GetHex().c_str(), status);
    QMetaObject::invokeMethod(walletmodel, "updateTransaction", Qt::QueuedConnection,
                              Q_ARG(QString, QString::fromStdString(hash.GetHex())),
                              Q_ARG(int, status));
}

void WalletModel::subscribeToCoreSignals()
{
    // Connect signals to wallet
    wallet->NotifyStatusChanged.connect(boost::bind(&NotifyKeyStoreStatusChanged, this, _1));
    wallet->NotifyAddressBookChanged.connect(boost::bind(NotifyAddressBookChanged, this, _1, _2, _3, _4, _5));
    wallet->NotifyTransactionChanged.connect(boost::bind(NotifyTransactionChanged, this, _1, _2, _3));
}

void WalletModel::unsubscribeFromCoreSignals()
{
    // Disconnect signals from wallet
    wallet->NotifyStatusChanged.disconnect(boost::bind(&NotifyKeyStoreStatusChanged, this, _1));
    wallet->NotifyAddressBookChanged.disconnect(boost::bind(NotifyAddressBookChanged, this, _1, _2, _3, _4, _5));
    wallet->NotifyTransactionChanged.disconnect(boost::bind(NotifyTransactionChanged, this, _1, _2, _3));
}

// WalletModel::UnlockContext implementation
WalletModel::UnlockContext WalletModel::requestUnlock()
{
    bool was_locked = getEncryptionStatus() == Locked;
    
    if ((!was_locked) && fWalletUnlockStakingOnly)
    {
       setWalletLocked(true);
       was_locked = getEncryptionStatus() == Locked;

    }
    if(was_locked)
    {
        // Request UI to unlock wallet
        emit requireUnlock();
    }
    // If wallet is still locked, unlock was failed or cancelled, mark context as invalid
    bool valid = getEncryptionStatus() != Locked;

    return UnlockContext(this, valid, was_locked && !fWalletUnlockStakingOnly);
}

WalletModel::UnlockContext::UnlockContext(WalletModel *wallet, bool valid, bool relock):
        wallet(wallet),
        valid(valid),
        relock(relock)
{
}

WalletModel::UnlockContext::~UnlockContext()
{
    if(valid && relock)
    {
        wallet->setWalletLocked(true);
    }
}

void WalletModel::UnlockContext::CopyFrom(const UnlockContext& rhs)
{
    // Transfer context; old object no longer relocks wallet
    *this = rhs;
    rhs.relock = false;
}

bool WalletModel::getPubKey(const CKeyID &address, CPubKey& vchPubKeyOut) const
{
    return wallet->GetPubKey(address, vchPubKeyOut);   
}

CWallet * WalletModel::getWallet()
{
    return wallet;
}

// returns a list of COutputs from COutPoints
void WalletModel::getOutputs(const std::vector<COutPoint>& vOutpoints, std::vector<COutput>& vOutputs)
{
    BOOST_FOREACH(const COutPoint& outpoint, vOutpoints)
    {
        if (!wallet->mapWallet.count(outpoint.hash)) continue;
        int nDepth = wallet->mapWallet[outpoint.hash].GetDepthInMainChain();
        if (nDepth < 0) continue;
        COutput out(&wallet->mapWallet[outpoint.hash], outpoint.n, nDepth);
        vOutputs.push_back(out);
    }
}

// AvailableCoins + LockedCoins grouped by wallet address (put change in one group with wallet address) 
void WalletModel::listCoins(std::map<QString, std::vector<COutput> >& mapCoins) const
{
    std::vector<COutput> vCoins;
    wallet->AvailableCoins(vCoins);
    std::vector<COutPoint> vLockedCoins;

    // add locked coins
    BOOST_FOREACH(const COutPoint& outpoint, vLockedCoins)
    {
        if (!wallet->mapWallet.count(outpoint.hash)) continue;
        int nDepth = wallet->mapWallet[outpoint.hash].GetDepthInMainChain();
        if (nDepth < 0) continue;
        COutput out(&wallet->mapWallet[outpoint.hash], outpoint.n, nDepth);
        vCoins.push_back(out);
    }

    BOOST_FOREACH(const COutput& out, vCoins)
    {
        COutput cout = out;

        while (wallet->IsChange(cout.tx->vout[cout.i]) && cout.tx->vin.size() > 0 && wallet->IsMine(cout.tx->vin[0]))
        {
            if (!wallet->mapWallet.count(cout.tx->vin[0].prevout.hash)) break;
            cout = COutput(&wallet->mapWallet[cout.tx->vin[0].prevout.hash], cout.tx->vin[0].prevout.n, 0);
        }

        CTxDestination address;
        if(!ExtractDestination(cout.tx->vout[cout.i].scriptPubKey, address)) continue;
        mapCoins[CBitcoinAddress(address).ToString().c_str()].push_back(out);
    }
}

bool WalletModel::isLockedCoin(uint256 hash, unsigned int n) const
{
    return false;
}

void WalletModel::lockCoin(COutPoint& output)
{
    return;
}

void WalletModel::unlockCoin(COutPoint& output)
{
    return;
}

void WalletModel::listLockedCoins(std::vector<COutPoint>& vOutpts)
{
    return;
}

void WalletModel::updateBlockchainStatus()
{
	if(blockchainStatus == -1)
		wallet->ScanBlockchainForHash();
}

QString WalletModel::getBlockchainStatusText()
{
	QString text;
	
	if(blockchainStatus == -1)
		text = QString("The DeepOnoion blockchain is not fully sychronized.");
	else if(blockchainStatus == 0)
		text = QString("The DeepOnoion blockchain sychronized, but it does not match the latest checkpoint hash at Block ")
			+ QString::number(CWallet::LAST_REGISTERED_BLOCK_HEIGHT) + QString(" (which is registered and guaranteed by the Bitcoin blockchain). ")
			+ QString("So you are most likely on a forked chain, please resync with official peers at https://deeponion.org.");
	else
		text = QString("The DeepOnoion blockchain is fully sychronized. It is authentic! It is guaranteed by Bitcoin blockchain ")
			+ QString("the most secure immuatble database in the world) up to Block ") 
			+ QString::number(CWallet::LAST_REGISTERED_BLOCK_HEIGHT) + QString(".");
	
	return text;
}


QString WalletModel::getBlockchainStatusDetailsText()
{
	QString text;
	
	if(blockchainStatus == -1)
		text = QString("We can't verify the DeepOnoion blockchain as it is not fully sychronized yet. ")
				+ QString("Please wait it fully synchronized and check back.");
	else if(blockchainStatus == 0)
		text = QString("The DeepOnoion blockchain sychronized, but it does not match the latest checkpoint hash at Block ")
			+ QString::number(CWallet::LAST_REGISTERED_BLOCK_HEIGHT) + QString(" (which is registered and guaranteed by the Bitcoin blockchain). ")
			+ QString("So you are most likely on a forked chain, please resync with official peers at https://deeponion.org.");
	else
		text = QString("The current DeepOnion blockchain you are using matches the hash registered in the Bitcoin blockchain at height ")
			+ QString::number(CWallet::LAST_REGISTERED_BTC_BLOCK_HEIGHT) + QString(". The matched hash is ") 
			+ QString::fromUtf8(CWallet::LAST_REGISTERED_BLOCKCHAIN_HASH.c_str()) + QString(", which is registered at Bitcoin blockchain at Block ")
			+ QString::number(CWallet::LAST_REGISTERED_BTC_BLOCK_HEIGHT) + QString(", with txid ")
			+ QString::fromUtf8(CWallet::LAST_REGISTERED_BTC_TX.c_str()) + QString(".");
	
	return text;
}


QString WalletModel::getBlockchainTextStylesheet()
{
	QString stylesheet;
	
	if(blockchainStatus == -1)
		stylesheet = "QLabel {font-weight: bold; color: blue;}";
	else if(blockchainStatus == 0)
		stylesheet = "QLabel {font-weight: bold; color: red;}";
	else
		stylesheet = "QLabel {font-weight: bold; color: green;}";

	return stylesheet;
}


bool WalletModel::needUpdateBlockchainStatusUI()
{
	if(blockchainStatusLast == blockchainStatus)
	{
		return false;
	}
	
	blockchainStatusLast = blockchainStatus;
	return true;
}
