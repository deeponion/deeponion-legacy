#include "overviewpage.h"
#include "ui_overviewpage.h"

#include "walletmodel.h"
#include "bitcoinunits.h"
#include "optionsmodel.h"
#include "transactiontablemodel.h"
#include "transactionfilterproxy.h"
#include "guiutil.h"
#include "guiconstants.h"
#include "askpassphrasedialog.h"
#include "util.h"
#include "themeadapter.h"

#include <QAbstractItemDelegate>
#include <QPainter>

#define DECORATION_SIZE 64
#define NUM_ITEMS 6

class TxViewDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    TxViewDelegate(): QAbstractItemDelegate(), unit(BitcoinUnits::BTC)
    {

    }

    inline void paint(QPainter *painter, const QStyleOptionViewItem &option,
                      const QModelIndex &index ) const
    {
        painter->save();

        QIcon icon = qvariant_cast<QIcon>(index.data(Qt::DecorationRole));
        QRect mainRect = option.rect;
        QRect decorationRect(mainRect.topLeft(), QSize(DECORATION_SIZE, DECORATION_SIZE));
        int xspace = DECORATION_SIZE + 8;
        int ypad = 6;
        int halfheight = (mainRect.height() - 2*ypad)/2;
        QRect amountRect(mainRect.left() + xspace, mainRect.top()+ypad, mainRect.width() - xspace, halfheight);
        QRect addressRect(mainRect.left() + xspace, mainRect.top()+ypad+halfheight, mainRect.width() - xspace, halfheight);
        icon.paint(painter, decorationRect);

        QDateTime date = index.data(TransactionTableModel::DateRole).toDateTime();
        QString address = index.data(Qt::DisplayRole).toString();
        qint64 amount = index.data(TransactionTableModel::AmountRole).toLongLong();
        bool confirmed = index.data(TransactionTableModel::ConfirmedRole).toBool();
        QVariant value = index.data(Qt::ForegroundRole);
        QColor foreground = option.palette.color(QPalette::Text);
        if(value.canConvert(QMetaType::QColor))
        {
            foreground = qvariant_cast<QColor>(value);
        }

        painter->setPen(foreground);
        painter->drawText(addressRect, Qt::AlignLeft|Qt::AlignVCenter, address);

        if(amount < 0)
        {
            foreground = COLOR_NEGATIVE;
        }
        else if(!confirmed)
        {
            foreground = COLOR_UNCONFIRMED;
        }
        else
        {
            foreground = option.palette.color(QPalette::Text);
        }
        painter->setPen(foreground);
        QString amountText = BitcoinUnits::formatWithUnit(unit, amount, true);
        if(!confirmed)
        {
            amountText = QString("[") + amountText + QString("]");
        }
        painter->drawText(amountRect, Qt::AlignRight|Qt::AlignVCenter, amountText);

        painter->setPen(option.palette.color(QPalette::Text));
        painter->drawText(amountRect, Qt::AlignLeft|Qt::AlignVCenter, GUIUtil::dateTimeStr(date));

        painter->restore();
    }

    inline QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        return QSize(DECORATION_SIZE, DECORATION_SIZE);
    }

    int unit;

};
#include "overviewpage.moc"

OverviewPage::OverviewPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OverviewPage),
    currentBalance(-1),
    currentStake(0),
    currentUnconfirmedBalance(-1),
    currentImmatureBalance(-1),
    txdelegate(new TxViewDelegate()),
    filter(0)
{
    ui->setupUi(this);
    ui->wallet_summary->setStyleSheet(ThemeAdapter::getQFrameGeneralStyle());

    // Recent transactions
    //ui->listTransactions->setItemDelegate(txdelegate);
    //ui->listTransactions->setIconSize(QSize(DECORATION_SIZE, DECORATION_SIZE));
    //ui->listTransactions->setMinimumHeight(NUM_ITEMS * (DECORATION_SIZE + 2));
    //ui->listTransactions->setAttribute(Qt::WA_MacShowFocusRect, false);

    connect(ui->listTransactions, SIGNAL(clicked(QModelIndex)), this, SLOT(handleTransactionClicked(QModelIndex)));

    // init "out of sync" warning labels
    ui->labelWalletStatus->setText("(" + tr("out of sync") + ")");
    //ui->labelTransactionsStatus->setText("(" + tr("out of sync") + ")");

    // start with displaying the "out of sync" warnings
    showOutOfSyncWarning(true);
    //DD: we no longer add our logo on the overview page
    //ui->wallet_logo_lbl->setPixmap(QPixmap(":images/wallet_logo"));
}

void OverviewPage::handleTransactionClicked(const QModelIndex &index)
{
    if(filter)
        emit transactionClicked(filter->mapToSource(index));
}

OverviewPage::~OverviewPage()
{
    delete ui;
}

void OverviewPage::setBalance(qint64 balance, qint64 stake, qint64 unconfirmedBalance, qint64 immatureBalance)
{
    int unit = model->getOptionsModel()->getDisplayUnit();

    currentBalance = balance;
    currentStake = stake;
    currentUnconfirmedBalance = unconfirmedBalance;
    currentImmatureBalance = immatureBalance;

    // Removing ONION unit from the Wallet Summary Section. Unfortunately there is no space for that.
    ui->labelBalance->setText(BitcoinUnits::formatWithoutUnit(unit, balance));
    ui->labelStake->setText(BitcoinUnits::formatWithoutUnit(unit, stake));
    ui->labelUnconfirmed->setText(BitcoinUnits::formatWithoutUnit(unit, unconfirmedBalance));
    ui->labelImmature->setText(BitcoinUnits::formatWithoutUnit(unit, immatureBalance));
    ui->labelTotal->setText(BitcoinUnits::formatWithoutUnit(unit, balance + stake + unconfirmedBalance + immatureBalance));

    // only show immature (newly mined) balance if it's non-zero, so as not to complicate things
    // for the non-mining users
    bool showImmature = immatureBalance != 0;
    ui->labelImmature->setVisible(showImmature);
    ui->labelImmatureText->setVisible(showImmature);


}


void OverviewPage::unlockWallet()
{
    if(model->getEncryptionStatus() == WalletModel::Locked)
    {
        AskPassphraseDialog dlg(AskPassphraseDialog::Unlock, this);
        dlg.setModel(model);
        if(dlg.exec() == QDialog::Accepted)
        {
//            ui->unlockWalletButton->setText(QString("Lock Wallet"));
        }
    }
    else
    {
        model->setWalletLocked(true);
//        ui->unlockWalletButton->setText(QString("Unlock Wallet"));
    }
}

void OverviewPage::setModel(WalletModel *model)
{
    this->model = model;
    if(model && model->getOptionsModel())
    {
        // Set up transaction list
        filter = new TransactionFilterProxy();
        filter->setSourceModel(model->getTransactionTableModel());
        filter->setDynamicSortFilter(true);
        filter->setLimit(NUM_ITEMS);
        filter->setSortRole(Qt::EditRole);
        filter->setShowInactive(false);
        //filter->sort(TransactionTableModel::Status, Qt::DescendingOrder);

        ui->listTransactions->setModel(filter);
        ui->listTransactions->setAlternatingRowColors(true);
        ui->listTransactions->setStyleSheet(ThemeAdapter::getQTableGeneralStyle());
        ui->listTransactions->setSortingEnabled(true);
        ui->listTransactions->sortByColumn(TransactionTableModel::Status, Qt::DescendingOrder);
        ui->listTransactions->verticalHeader()->hide();

        ui->listTransactions->horizontalHeader()->resizeSection(
                TransactionTableModel::Status, 28);
        ui->listTransactions->horizontalHeader()->resizeSection(
                TransactionTableModel::Date, 120);
        ui->listTransactions->horizontalHeader()->resizeSection(
                TransactionTableModel::Type, 120);
        ui->listTransactions->horizontalHeader()->setSectionResizeMode(TransactionTableModel::ToAddress, QHeaderView::Stretch);
        ui->listTransactions->horizontalHeader()->resizeSection(
                TransactionTableModel::Amount, 100);
        ui->listTransactions->horizontalHeader()->setStyleSheet(ThemeAdapter::getQTableHeaderGeneralStyle());



        //ui->listTransactions->setModelColumn(TransactionTableModel::ToAddress);

        // Keep up to date with wallet
        setBalance(model->getBalance(), model->getStake(), model->getUnconfirmedBalance(), model->getImmatureBalance());
        connect(model, SIGNAL(balanceChanged(qint64, qint64, qint64, qint64)), this, SLOT(setBalance(qint64, qint64, qint64, qint64)));

        connect(model->getOptionsModel(), SIGNAL(displayUnitChanged(int)), this, SLOT(updateDisplayUnit()));

        // Unlock wallet button
        WalletModel::EncryptionStatus status = model->getEncryptionStatus();
        if(status == WalletModel::Unencrypted)
        {
//            ui->unlockWalletButton->setDisabled(true);
//            ui->unlockWalletButton->setText(QString("Wallet is not encrypted!"));

        }

        else
        {
//            ui->unlockWalletButton->setText(QString("Unlock wallet"));
        }
//        connect(ui->unlockWalletButton, SIGNAL(clicked()), this, SLOT(unlockWallet()));
    }

    // update the display unit, to not use the default ("BTC")
    updateDisplayUnit();
}

void OverviewPage::updateDisplayUnit()
{
    if(model && model->getOptionsModel())
    {
        if(currentBalance != -1)
            setBalance(currentBalance, model->getStake(), currentUnconfirmedBalance, currentImmatureBalance);

        // Update txdelegate->unit with the current unit
        txdelegate->unit = model->getOptionsModel()->getDisplayUnit();

        ui->listTransactions->update();
    }
}

void OverviewPage::showOutOfSyncWarning(bool fShow)
{
    ui->labelWalletStatus->setVisible(fShow);
    //ui->labelTransactionsStatus->setVisible(fShow);
}

void OverviewPage::refreshStyle() {
    ui->wallet_summary->setStyleSheet(ThemeAdapter::getQFrameGeneralStyle());
    ui->listTransactions->setStyleSheet(ThemeAdapter::getQTableGeneralStyle());
    ui->listTransactions->horizontalHeader()->setStyleSheet(ThemeAdapter::getQTableHeaderGeneralStyle());
}
