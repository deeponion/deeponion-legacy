/*
 * Qt4 bitcoin GUI.
 *
 * W.J. van der Laan 2011-2012
 * The Bitcoin Developers 2011-2012
 */

// Copyright (c) 2017-2018 The DeepOnion Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
 
#include "bitcoingui.h"
#include "transactiontablemodel.h"
#include "addressbookpage.h"
#include "sendcoinsdialog.h"
#include "sendmessagesdialog.h"
#include "signverifymessagedialog.h"
#include "optionsdialog.h"
#include "aboutdialog.h"
#include "clientmodel.h"
#include "walletmodel.h"
#include "messagemodel.h"
#include "editaddressdialog.h"
#include "optionsmodel.h"
#include "transactiondescdialog.h"
#include "addresstablemodel.h"
#include "transactionview.h"
#include "overviewpage.h"
#include "messagepage.h"
#include "bitcoinunits.h"
#include "guiconstants.h"
#include "askpassphrasedialog.h"
#include "notificator.h"
#include "guiutil.h"
#include "rpcconsole.h"
#include "wallet.h"
#include "init.h"
#include "net.h"
#include "thememanager.h"

#ifdef Q_OS_MAC
#include "macdockiconhandler.h"
#endif

#include <QFontDatabase>
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QIcon>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QLineEdit>
#include <QInputDialog>
#include <QPushButton>
#include <QToolButton>
#include <QLocale>
#include <QMessageBox>
#include <QMimeData>
#include <QProgressBar>
#include <QStackedWidget>
#include <QDateTime>
#include <QMovie>
#include <QFileDialog>
#include <QDesktopServices>
#include <QTimer>
#include <QDragEnterEvent>
#include <QUrl>
#include <QStyle>
#include <QStyleFactory>
#include <QTextStream>
#include <QTextDocument>
#include <QSettings>

#include <iostream>

extern CWallet *pwalletMain;
extern int64_t nLastCoinStakeSearchInterval;
extern unsigned int nStakeTargetSpacing;
double GetPoSKernelPS();

ThemeManager *themeManager = new ThemeManager();

BitcoinGUI::BitcoinGUI(QWidget *parent):
    QMainWindow(parent),
    clientModel(0),
    walletModel(0),
    messageModel(0),
    encryptWalletAction(0),
    changePassphraseAction(0),
    unlockWalletAction(0),
    lockWalletAction(0),
    aboutQtAction(0),
    trayIcon(0),
    notificator(0),
    rpcConsole(0),
    prevBlocks(0),
    spinnerFrame(0)
{

    GUIUtil::restoreWindowGeometry("nWindow", QSize(890, 600), this);

#ifdef Q_OS_MAC
    resize(960, 610);
    setWindowTitle(tr("DeepOnion wallet - Mac"));
#elif _WIN32
    resize(890, 600);
    setWindowTitle(tr("DeepOnion wallet - Windows"));
#else
    resize(1020, 650);
    setWindowTitle(tr("DeepOnion wallet - Linux"));
#endif

#ifndef Q_OS_MAC
    qApp->setWindowIcon(QIcon(":icons/bitcoin"));
    setWindowIcon(QIcon(":icons/bitcoin"));
#else
    setUnifiedTitleAndToolBarOnMac(true);
    QApplication::setAttribute(Qt::AA_DontShowIconsInMenus);
#endif

    themeManager->applyCurrentTheme();
    qApp->setStyleSheet(themeManager->getCurrent()->getStyleSheet());

    currentScreen = SCREEN_OVERVIEW;

    QFontDatabase::addApplicationFont(":/fonts/HelveticaNeue");
    // Accept D&D of URIs
    setAcceptDrops(true);

    // Create actions for the toolbar, menu bar and tray/dock icon
    createActions();

    // Create application menu bar
    createMenuBar();

    // Create the toolbars
    QToolBar *fakeToolbarForBlueLine = addToolBar(tr("Fake toolbar for blue line"));
    fakeToolbarForBlueLine->setFixedHeight(59);
    fakeToolbarForBlueLine->setMovable(false);
    fakeToolbarForBlueLine->setStyleSheet("background: #486EBA; border: 0px;");
    addToolBar(Qt::LeftToolBarArea, fakeToolbarForBlueLine);

    QToolBar *fakeToolbarForSpacing = addToolBar(tr("Fake toolbar for spacing"));
    fakeToolbarForSpacing->setFixedHeight(40);
    fakeToolbarForSpacing->setMovable(false);
    addToolBar(Qt::LeftToolBarArea, fakeToolbarForSpacing);

	toolbar = addToolBar(tr("Tabs toolbar"));
    // QToolBar *toolbar = QtGui.QToolBar(this);
    addToolBar(Qt::LeftToolBarArea, toolbar);
    toolbar->setOrientation(Qt::Vertical);
    toolbar->setFixedWidth(180);
    createToolBars();
    
    setContextMenuPolicy(Qt::NoContextMenu);

    // Create the tray icon (or setup the dock icon)
    createTrayIcon();
    /*
    QFile style(":/styles/res/styles/style.qss");
    style.open(QFile::ReadOnly);
    setStyleSheet(QString::fromUtf8(style.readAll()));
	*/

    /* don't override the background color of the toolbar on mac os x due to
       the whole component it resides on not being paintable
     */
#ifdef Q_OS_MAC
    toolbar->setStyleSheet("QToolBar { background-color: transparent; border: 0px solid black; padding: 3px; }");
#endif

    // Create tabs
    overviewPage = new OverviewPage();
    messagePage   = new MessagePage(this);
    transactionsPage = new QWidget(this);
    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->setContentsMargins(0,0,0,0);
    vbox->setSpacing(0);
    transactionView = new TransactionView(this);
    vbox->addWidget(transactionView);
    transactionsPage->setLayout(vbox);

    addressBookPage = new AddressBookPage(AddressBookPage::ForEditing, AddressBookPage::SendingTab);

    receiveCoinsPage = new AddressBookPage(AddressBookPage::ForEditing, AddressBookPage::ReceivingTab);

    sendCoinsPage = new SendCoinsDialog(this);

    signVerifyMessageDialog = new SignVerifyMessageDialog(this);

    centralWidget = new QStackedWidget(this);
    
    // DD adding this to remove the small border that separates left menu and central area
    centralWidget->layout()->setContentsMargins(0,0,0,0);
    layout()->setContentsMargins(0,0,0,0);
    setStyleSheet("QMainWindow::separator{ width: 0px; height: 0px; };");
    centralWidget->setStyleSheet(themeManager->getCurrent()->getCentralWidgetStyle());
    centralWidget->addWidget(overviewPage);;	
    centralWidget->addWidget(messagePage);
    centralWidget->addWidget(transactionsPage);
    centralWidget->addWidget(addressBookPage);
    centralWidget->addWidget(receiveCoinsPage);
    centralWidget->addWidget(sendCoinsPage);
    setCentralWidget(centralWidget);

    // Returns the status bar for the main window. Method from QWindow.
    statusBar();
    statusBar()->setSizeGripEnabled(false);

    // Status bar notification icons
    QFrame *frameBlocks = new QFrame();
    frameBlocks->setObjectName("frameBlocks");
    frameBlocks->setContentsMargins(0, 0, 0, 0);
    frameBlocks->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    frameBlocks->setStyleSheet("background-color: #1A1A21;");


    QHBoxLayout *frameBlocksLayout = new QHBoxLayout(frameBlocks);
    frameBlocksLayout->setContentsMargins(3, 0, 3, 0);
    frameBlocksLayout->setSpacing(3);
    int statusIconLabelHeight = 32;
    labelEncryptionIcon = new QLabel();
    labelEncryptionIcon->setStyleSheet("background-color: #1A1A21;");
    labelEncryptionIcon->setMinimumWidth(statusIconLabelHeight);
    labelEncryptionIcon->setMinimumHeight(statusIconLabelHeight);
    labelStakingIcon = new QLabel();
    labelStakingIcon->setStyleSheet("background-color: #1A1A21;");
    labelStakingIcon->setMinimumWidth(statusIconLabelHeight);
    labelStakingIcon->setMinimumHeight(statusIconLabelHeight);
    labelConnectionsIcon = new QLabel();
    labelConnectionsIcon->setStyleSheet("background-color: #1A1A21;");
    labelConnectionsIcon->setMinimumWidth(statusIconLabelHeight);
    labelConnectionsIcon->setMinimumHeight(statusIconLabelHeight);
	labelOnionIcon = new QLabel();
    labelOnionIcon->setStyleSheet("background-color: #1A1A21;");
    labelOnionIcon->setMinimumWidth(statusIconLabelHeight);
    labelOnionIcon->setMinimumHeight(statusIconLabelHeight);
    labelBlocksIcon = new QLabel();
    labelBlocksIcon->setStyleSheet("background-color: #1A1A21;");
    labelBlocksIcon->setMinimumWidth(statusIconLabelHeight);
    labelBlocksIcon->setMinimumHeight(statusIconLabelHeight);
    //frameBlocksLayout->addStretch();
    frameBlocksLayout->addWidget(labelEncryptionIcon);
    frameBlocksLayout->addStretch();
    frameBlocksLayout->addWidget(labelStakingIcon);
    frameBlocksLayout->addStretch();
    frameBlocksLayout->addWidget(labelOnionIcon);
    frameBlocksLayout->addStretch();
    frameBlocksLayout->addWidget(labelConnectionsIcon);
    frameBlocksLayout->addStretch();
    frameBlocksLayout->addWidget(labelBlocksIcon);
    frameBlocksLayout->addStretch();

    if (GetBoolArg("-staking", true))
    {
        QTimer *timerStakingIcon = new QTimer(labelStakingIcon);
        connect(timerStakingIcon, SIGNAL(timeout()), this, SLOT(updateStakingIcon()));
        timerStakingIcon->start(30 * 1000);
        updateStakingIcon();
    }

    if (fTorEnabled == 1)
    {
        QTimer *timerOnionIcon = new QTimer(labelOnionIcon);
        connect(timerOnionIcon, SIGNAL(timeout()), this, SLOT(updateOnionIcon()));
        timerOnionIcon->start(30 * 1000);
        updateOnionIcon();
    }

    // Progress bar and label for blocks download
    progressBarLabel = new QLabel();
    progressBarLabel->setVisible(false);
    progressBar = new QProgressBar();
    progressBar->setAlignment(Qt::AlignCenter);
    progressBar->setVisible(false);

    // Override style sheet for progress bar for styles that have a segmented progress bar,
    // as they make the text unreadable (workaround for issue #1071)
    // See https://qt-project.org/doc/qt-4.8/gallery.html
//    QString curStyle = qApp->style()->metaObject()->className();
//    if(curStyle == "QWindowsStyle" || curStyle == "QWindowsXPStyle")
//    {
//        progressBar->setStyleSheet("QProgressBar { background-color: #393947; border: none; padding: 1px; text-align: center; }\
//        QProgressBar::chunk { background: QLinearGradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #FF8000, stop: 1 orange); margin: 0px; }");
//    }

    progressBar->setStyleSheet("color: #486EBA; background-color: #393947;");
    progressBarLabel->setStyleSheet("color: #3dc28b; padding-left: 10px;  background-color: #1A1A21;");
    progressBarLabel->setFrameStyle(QFrame::NoFrame);
    statusBar()->addWidget(progressBarLabel);
    statusBar()->addWidget(progressBar);
    statusBar()->addPermanentWidget(frameBlocks);
    statusBar()->setStyleSheet("background-color: #1A1A21;");
    statusBar()->setMinimumHeight(56);
    statusBar()->setMaximumHeight(56);

    syncIconMovie = new QMovie(":/movies/update_spinner", "mng", this);

    // Clicking on a transaction on the overview page simply sends you to transaction history page
    connect(overviewPage, SIGNAL(transactionClicked(QModelIndex)), this, SLOT(gotoHistoryPage()));
    connect(overviewPage, SIGNAL(transactionClicked(QModelIndex)), transactionView, SLOT(focusTransaction(QModelIndex)));

    // Double-clicking on a transaction on the transaction history page shows details
    connect(transactionView, SIGNAL(doubleClicked(QModelIndex)), transactionView, SLOT(showDetails()));

    rpcConsole = new RPCConsole(this);
    connect(openRPCConsoleAction, SIGNAL(triggered()), rpcConsole, SLOT(show()));
    
    // Clicking on "Open configuration file" in "Settings" menu opens DeepOnion.conf file in the system default editor
    connect(openConfEditorAction, SIGNAL(triggered()), rpcConsole, SLOT(showConfEditor()));
    
    // Clicking on "Verify Message" in the address book sends you to the verify message tab
    connect(addressBookPage, SIGNAL(verifyMessage(QString)), this, SLOT(gotoVerifyMessageTab(QString)));
    // Clicking on "Sign Message" in the receive coins page sends you to the sign message tab
    connect(receiveCoinsPage, SIGNAL(signMessage(QString)), this, SLOT(gotoSignMessageTab(QString)));

    gotoOverviewPage();
}

BitcoinGUI::~BitcoinGUI()
{
    GUIUtil::saveWindowGeometry("nWindow", this);
    if (trayIcon) // Hide tray icon, as deleting will let it linger until quit (on Ubuntu)
        trayIcon->hide();
#ifdef Q_OS_MAC
    delete appMenuBar;
#endif
}

void BitcoinGUI::createActions()
{
    QActionGroup *tabGroup = new QActionGroup(this);

    overviewAction = new QAction(QIcon(themeManager->getCurrent()->getMainMenuOverviewNormalBtnIco()), tr("&Overview"), this);
    overviewAction->setToolTip(tr("Show general overview of wallet"));
    overviewAction->setCheckable(true);
    overviewAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_1));
    tabGroup->addAction(overviewAction);

    messageAction = new QAction(QIcon(themeManager->getCurrent()->getMainMenuMessagesNormalBtnIco()), tr("&Messages"), this);
    messageAction->setToolTip(tr("View and Send Encrypted messages"));
    messageAction->setCheckable(true);
    messageAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_7));
    tabGroup->addAction(messageAction);

    sendCoinsAction = new QAction(QIcon(themeManager->getCurrent()->getMainMenuSendcoinsNormalBtnIco()), tr("&Send coins"), this);
    sendCoinsAction->setToolTip(tr("Send coins to a DeepOnion address"));
    sendCoinsAction->setCheckable(true);
    sendCoinsAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_2));
    tabGroup->addAction(sendCoinsAction);

    receiveCoinsAction = new QAction(QIcon(themeManager->getCurrent()->getMainMenuReceiveCoinsNormalBtnIco()), tr("&Receive coins"), this);
    receiveCoinsAction->setToolTip(tr("Show the list of addresses for receiving payments"));
    receiveCoinsAction->setCheckable(true);
    receiveCoinsAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_3));
    tabGroup->addAction(receiveCoinsAction);

    historyAction = new QAction(QIcon(themeManager->getCurrent()->getMainMenuTransactionsNormalBtnIco()), tr("&Transactions"), this);
    historyAction->setToolTip(tr("Browse transaction history"));
    historyAction->setCheckable(true);
    historyAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_4));
    tabGroup->addAction(historyAction);

    addressBookAction = new QAction(QIcon(themeManager->getCurrent()->getMainMenuAddressBookNormalBtnIco()), tr("&Address Book"), this);
    addressBookAction->setToolTip(tr("Edit the list of stored addresses and labels"));
    addressBookAction->setCheckable(true);
    addressBookAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_5));
    tabGroup->addAction(addressBookAction);

    connect(overviewAction, SIGNAL(triggered()), this, SLOT(showNormalIfMinimized()));
    connect(overviewAction, SIGNAL(triggered()), this, SLOT(gotoOverviewPage()));
    connect(sendCoinsAction, SIGNAL(triggered()), this, SLOT(showNormalIfMinimized()));
    connect(sendCoinsAction, SIGNAL(triggered()), this, SLOT(gotoSendCoinsPage()));
    connect(receiveCoinsAction, SIGNAL(triggered()), this, SLOT(showNormalIfMinimized()));
    connect(receiveCoinsAction, SIGNAL(triggered()), this, SLOT(gotoReceiveCoinsPage()));
    connect(historyAction, SIGNAL(triggered()), this, SLOT(showNormalIfMinimized()));
    connect(historyAction, SIGNAL(triggered()), this, SLOT(gotoHistoryPage()));
    connect(addressBookAction, SIGNAL(triggered()), this, SLOT(showNormalIfMinimized()));
    connect(addressBookAction, SIGNAL(triggered()), this, SLOT(gotoAddressBookPage()));
    connect(messageAction, SIGNAL(triggered()), this, SLOT(showNormalIfMinimized()));
    connect(messageAction, SIGNAL(triggered()), this, SLOT(gotoMessagePage()));

    quitAction = new QAction(QIcon(":/icons/quit"), tr("E&xit"), this);
    quitAction->setToolTip(tr("Quit application"));
    quitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    quitAction->setMenuRole(QAction::QuitRole);
    aboutAction = new QAction(QIcon(":/icons/bitcoin"), tr("&About DeepOnion"), this);
    aboutAction->setToolTip(tr("Show information about DeepOnion"));
    aboutAction->setMenuRole(QAction::AboutRole);
#if QT_VERSION < 0x050000
    aboutQtAction = new QAction(QIcon(":/trolltech/qmessagebox/images/qtlogo-64.png"), tr("About &Qt"), this);
#else
    aboutQtAction = new QAction(QIcon(":/qt-project.org/qmessagebox/images/qtlogo-64.png"), tr("About &Qt"), this);
#endif
    aboutQtAction->setToolTip(tr("Show information about Qt"));
    aboutQtAction->setMenuRole(QAction::AboutQtRole);
    optionsAction = new QAction(QIcon(":/icons/options"), tr("&Options..."), this);
    optionsAction->setToolTip(tr("Modify configuration options for DeepOnion"));
    optionsAction->setMenuRole(QAction::PreferencesRole);
    toggleHideAction = new QAction(QIcon(":/icons/bitcoin"), tr("&Show / Hide"), this);
    encryptWalletAction = new QAction(QIcon(":/icons/new_lock_closed"), tr("&Encrypt Wallet..."), this);
    encryptWalletAction->setToolTip(tr("Encrypt or decrypt wallet"));
    encryptWalletAction->setCheckable(true);
    openConfEditorAction = new QAction(QIcon(":/icons/edit"), tr("Open configuration &file..."), this);
    openConfEditorAction->setToolTip(tr("Open the configuration file DeepOnion.conf"));
    backupWalletAction = new QAction(QIcon(":/icons/filesave"), tr("&Backup Wallet..."), this);
    backupWalletAction->setToolTip(tr("Backup wallet to another location"));
    changePassphraseAction = new QAction(QIcon(":/icons/key"), tr("&Change Passphrase..."), this);
    changePassphraseAction->setToolTip(tr("Change the passphrase used for wallet encryption"));
    unlockWalletAction = new QAction(QIcon(themeManager->getCurrent()->getMainMenuUnlockWalletNormalBtnIco()), tr("&Unlock Wallet..."), this);
    unlockWalletAction->setToolTip(tr("Unlock wallet"));
    lockWalletAction = new QAction(QIcon(themeManager->getCurrent()->getMainMenuLockWalletNormalBtnIco()), tr("&Lock Wallet"), this);
    lockWalletAction->setToolTip(tr("Lock wallet"));
    signMessageAction = new QAction(QIcon(":/icons/edit"), tr("Sign &message..."), this);
    verifyMessageAction = new QAction(QIcon(":/icons/transaction_0"), tr("&Verify message..."), this);

    exportAction = new QAction(QIcon(themeManager->getCurrent()->getMainMenuExportNormalBtnIco()), tr("&Export..."), this);
    exportAction->setToolTip(tr("Export the data in the current tab to a file"));
    openRPCConsoleAction = new QAction(QIcon(":/icons/debugwindow"), tr("&Debug window"), this);
    openRPCConsoleAction->setToolTip(tr("Open debugging and diagnostic console"));

    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutClicked()));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(optionsAction, SIGNAL(triggered()), this, SLOT(optionsClicked()));
    connect(toggleHideAction, SIGNAL(triggered()), this, SLOT(toggleHidden()));
    connect(encryptWalletAction, SIGNAL(triggered(bool)), this, SLOT(encryptWallet(bool)));
    connect(backupWalletAction, SIGNAL(triggered()), this, SLOT(backupWallet()));
    connect(changePassphraseAction, SIGNAL(triggered()), this, SLOT(changePassphrase()));
    connect(unlockWalletAction, SIGNAL(triggered()), this, SLOT(unlockWallet()));
    connect(lockWalletAction, SIGNAL(triggered()), this, SLOT(lockWallet()));
    connect(signMessageAction, SIGNAL(triggered()), this, SLOT(gotoSignMessageTab()));
    connect(verifyMessageAction, SIGNAL(triggered()), this, SLOT(gotoVerifyMessageTab()));
    
}

void BitcoinGUI::changeStyleSheet()
{
    setStyleSheet(QInputDialog::getText(this, "Change Stylesheet", "Sheet", QLineEdit::Normal, styleSheet()));
}

void BitcoinGUI::createMenuBar()
{
#ifdef Q_OS_MAC
    // Create a decoupled menu bar on Mac which stays even if the window is closed
    appMenuBar = new QMenuBar();
#else
    // Get the main window's menu bar on other platforms
    appMenuBar = menuBar();
#endif

    // Configure the menus
    QMenu *file = appMenuBar->addMenu(tr("&File"));
    file->addAction(backupWalletAction);
    file->addAction(exportAction);
    file->addAction(signMessageAction);
    file->addAction(verifyMessageAction);
    file->addSeparator();
    file->addAction(quitAction);

    QMenu *settings = appMenuBar->addMenu(tr("&Settings"));
    settings->addAction(encryptWalletAction);
    settings->addAction(changePassphraseAction);
    settings->addAction(unlockWalletAction);
    settings->addAction(lockWalletAction);
    settings->addSeparator();
    settings->addAction(openConfEditorAction);   
    settings->addAction(optionsAction);

    QMenu *help = appMenuBar->addMenu(tr("&Help"));
    help->addAction(openRPCConsoleAction);
    help->addSeparator();
    help->addAction(aboutAction);
    help->addAction(aboutQtAction);
}

void BitcoinGUI::createToolBars()
{
    toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolbar->setContextMenuPolicy(Qt::PreventContextMenu);
    toolbar->setMovable(false);
    
    toolbar->addAction(overviewAction);
    toolbar->addAction(sendCoinsAction);
    toolbar->addAction(receiveCoinsAction);
    toolbar->addAction(historyAction);
    toolbar->addAction(addressBookAction);
    toolbar->addAction(unlockWalletAction);
    toolbar->addAction(lockWalletAction);
    toolbar->addAction(messageAction);
    toolbar->addAction(exportAction);

    toolbar->setStyleSheet("QToolButton {font-family:'Helvetica'; font-size:16px;}");
}

void BitcoinGUI::setClientModel(ClientModel *clientModel)
{
    this->clientModel = clientModel;
    if (clientModel)
    {
        // Replace some strings and icons, when using the testnet
        if (clientModel->isTestNet())
        {
            setWindowTitle(windowTitle() + QString(" ") + tr("[testnet]"));
#ifndef Q_OS_MAC
            qApp->setWindowIcon(QIcon(":icons/bitcoin_testnet"));
            setWindowIcon(QIcon(":icons/bitcoin_testnet"));
#else
            MacDockIconHandler::instance()->setIcon(QIcon(":icons/bitcoin_testnet"));
#endif
            if (trayIcon)
            {
                trayIcon->setToolTip(tr("DeepOnion client") + QString(" ") + tr("[testnet]"));
                trayIcon->setIcon(QIcon(":/icons/toolbar_testnet"));
                toggleHideAction->setIcon(QIcon(":/icons/toolbar_testnet"));
            }

            aboutAction->setIcon(QIcon(":/icons/toolbar_testnet"));
        }

        // Keep up to date with client
        setNumConnections(clientModel->getNumConnections());
        connect(clientModel, SIGNAL(numConnectionsChanged(int)), this, SLOT(setNumConnections(int)));

        setNumBlocks(clientModel->getNumBlocks(), clientModel->getNumBlocksOfPeers());
        connect(clientModel, SIGNAL(numBlocksChanged(int, int)), this, SLOT(setNumBlocks(int, int)));

        // Report errors from network/worker thread
        connect(clientModel, SIGNAL(error(QString, QString, bool)), this, SLOT(error(QString, QString, bool)));

        rpcConsole->setClientModel(clientModel);
        addressBookPage->setOptionsModel(clientModel->getOptionsModel());
        receiveCoinsPage->setOptionsModel(clientModel->getOptionsModel());
    }
}

void BitcoinGUI::setWalletModel(WalletModel *walletModel)
{
    this->walletModel = walletModel;
    if (walletModel)
    {
        // Report errors from wallet thread
        connect(walletModel, SIGNAL(error(QString, QString, bool)), this, SLOT(error(QString, QString, bool)));

        // Put transaction list in tabs
        transactionView->setModel(walletModel);

        overviewPage->setModel(walletModel);
        addressBookPage->setModel(walletModel->getAddressTableModel());
        receiveCoinsPage->setModel(walletModel->getAddressTableModel());
        sendCoinsPage->setModel(walletModel);
        signVerifyMessageDialog->setModel(walletModel);

        setEncryptionStatus(walletModel->getEncryptionStatus());
        connect(walletModel, SIGNAL(encryptionStatusChanged(int)), this, SLOT(setEncryptionStatus(int)));

        // Balloon pop-up for new transaction
        connect(walletModel->getTransactionTableModel(), SIGNAL(rowsInserted(QModelIndex, int, int)),
                this, SLOT(incomingTransaction(QModelIndex, int, int)));

        // Ask for passphrase if needed
        connect(walletModel, SIGNAL(requireUnlock()), this, SLOT(unlockWallet()));
    }
}

void BitcoinGUI::setMessageModel(MessageModel *messageModel)
{
    this->messageModel = messageModel;
    if (messageModel)
    {
        // Report errors from message thread
        connect(messageModel, SIGNAL(error(QString, QString, bool)), this, SLOT(error(QString, QString, bool)));

        // Put transaction list in tabs
        messagePage->setModel(messageModel);

        // Balloon pop-up for new message
        connect(messageModel, SIGNAL(rowsInserted(QModelIndex, int, int)),
                this, SLOT(incomingMessage(QModelIndex, int, int)));
    }
}

void BitcoinGUI::createTrayIcon()
{
    QMenu *trayIconMenu;
#ifndef Q_OS_MAC
    trayIcon = new QSystemTrayIcon(this);
    trayIconMenu = new QMenu(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setToolTip(tr("DeepOnion client"));

    trayIcon->setIcon(QIcon(":/icons/toolbar"));

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    trayIcon->show();
#else
    // Note: On Mac, the dock icon is used to provide the tray's functionality.
    MacDockIconHandler *dockIconHandler = MacDockIconHandler::instance();
    dockIconHandler->setMainWindow((QMainWindow *)this);
    trayIconMenu = dockIconHandler->dockMenu();
#endif

    // Configuration of the tray icon (or dock icon) icon menu
    trayIconMenu->addAction(toggleHideAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(sendCoinsAction);
    trayIconMenu->addAction(receiveCoinsAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(signMessageAction);
    trayIconMenu->addAction(verifyMessageAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(optionsAction);
    trayIconMenu->addAction(openRPCConsoleAction);
    trayIconMenu->addAction(openConfEditorAction);
#ifndef Q_OS_MAC // This is built-in on Mac
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
#endif

    notificator = new Notificator(qApp->applicationName(), trayIcon);
}

#ifndef Q_OS_MAC
void BitcoinGUI::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
    {
        // Click on system tray icon triggers show/hide of the main window
        toggleHideAction->trigger();
    }
}
#endif

void BitcoinGUI::optionsClicked()
{
    if (!clientModel || !clientModel->getOptionsModel())
        return;
    OptionsDialog dlg;
    dlg.setModel(clientModel->getOptionsModel());
    connect(&dlg, SIGNAL(finished(int)), this, SLOT(optionsDialogFinished(int)));
    dlg.exec();
}

void BitcoinGUI::aboutClicked()
{
    AboutDialog dlg;
    dlg.setModel(clientModel);
    dlg.exec();
}

void BitcoinGUI::setNumConnections(int count)
{
    QString icon;
    switch (count)
    {
    	case 0: icon = ":/icons/new_connect_0"; 
    		break;
    	case 1: 
    	case 2: 
    	case 3: 
    		icon = ":/icons/new_connect_1"; 
    		break;
    	case 4: 
    	case 5: 
    	case 6: 
    		icon = ":/icons/new_connect_2"; 
    		break;
    	case 7: 
    	case 8: 
    	case 9: 
    		icon = ":/icons/new_connect_3"; 
    		break;
    	default: 
    		icon = ":/icons/new_connect_4"; 
    		break;
    }
    
    labelConnectionsIcon->setPixmap(QIcon(icon).pixmap(STATUSBAR_ICONSIZE, STATUSBAR_ICONSIZE));
    labelConnectionsIcon->setToolTip(tr("%n active connection(s) to DeepOnion network", "", count));

    if (fTorEnabled == 1)
    {
        updateOnionIcon();
    }
}

void BitcoinGUI::setNumBlocks(int count, int nTotalBlocks)
{
    // don't show / hide progress bar and its label if we have no connection to the network
    if (!clientModel || clientModel->getNumConnections() == 0)
    {
        progressBarLabel->setVisible(false);
        progressBar->setVisible(false);

        return;
    }

    QString strStatusBarWarnings = clientModel->getStatusBarWarnings();
    QString tooltip;

    if (count < nTotalBlocks)
    {
        int nRemainingBlocks = nTotalBlocks - count;
        float nPercentageDone = count / (nTotalBlocks * 0.01f);

        if (strStatusBarWarnings.isEmpty())
        {
            progressBarLabel->setText(tr("Synchronizing with network..."));
            progressBarLabel->setVisible(true);
            progressBar->setFormat(tr("~%n block(s) remaining", "", nRemainingBlocks));
            progressBar->setMaximum(nTotalBlocks);
            progressBar->setValue(count);
            progressBar->setVisible(true);
        }

        tooltip = tr("Downloaded %1 of %2 blocks of transaction history (%3% done).").arg(count).arg(nTotalBlocks).arg(nPercentageDone, 0, 'f', 2);
    }
    else
    {
        if (strStatusBarWarnings.isEmpty())
            progressBarLabel->setVisible(false);

        progressBar->setVisible(false);
        tooltip = tr("Downloaded %1 blocks of transaction history.").arg(count);
    }

    // Override progressBarLabel text and hide progress bar, when we have warnings to display
    if (!strStatusBarWarnings.isEmpty())
    {
        progressBarLabel->setText(strStatusBarWarnings);
        progressBarLabel->setVisible(true);
        progressBar->setVisible(false);
    }

    QDateTime lastBlockDate = clientModel->getLastBlockDate();
    int secs = lastBlockDate.secsTo(QDateTime::currentDateTime());
    QString text;

    // Represent time from last generated block in human readable text
    if (secs <= 0)
    {
        // Fully up to date. Leave text empty.
    }
    else if (secs < 60)
    {
        text = tr("%n second(s) ago", "", secs);
    }
    else if(secs < 3600) // 60 * 60
    {
        text = tr("%n minute(s) ago", "", secs / 60);
    }
    else if(secs < 86400) // 24*60*60
    {
        text = tr("%n hour(s) ago","",secs/3600);
    }
    else
    {
        text = tr("%n day(s) ago","",secs/86400);
    }


    // Set icon state: spinning if catching up, tick otherwise 5400 = 90*60
    if(secs < 5400 && count >= nTotalBlocks)
    {
        tooltip = tr("Up to date") + QString(".<br>") + tooltip;
        labelBlocksIcon->setPixmap(QIcon(":/icons/new_synced").pixmap(STATUSBAR_ICONSIZE, STATUSBAR_ICONSIZE));

        overviewPage->showOutOfSyncWarning(false);
        rpcConsole->updateBlockchainStatus();
    }
    else
    {
        tooltip = tr("Catching up...") + QString("<br>") + tooltip;
        //Old version using the movie, even though, I have never seen the movie so I doubt it works..
        //labelBlocksIcon->setMovie(syncIconMovie);
        //syncIconMovie->start();
        //labelBlocksIcon->setPixmap(QIcon(":/icons/new_notsynced").pixmap(STATUSBAR_ICONSIZE, STATUSBAR_ICONSIZE));
        if(count != prevBlocks) {
            labelBlocksIcon->setPixmap(QIcon(QString(":/movies/spinner-%1").arg(spinnerFrame, 3, 10, QChar('0'))).
                    pixmap(STATUSBAR_ICONSIZE, STATUSBAR_ICONSIZE));
            spinnerFrame = (spinnerFrame + 1) % SPINNER_FRAMES;
        }
        prevBlocks = count;
        overviewPage->showOutOfSyncWarning(true);
    }

    if (!text.isEmpty())
    {
        tooltip += QString("<br>");
        tooltip += tr("Last received block was generated %1.").arg(text);
    }

    // Don't word-wrap this (fixed-width) tooltip
    tooltip = QString("<nobr>") + tooltip + QString("</nobr>");

    labelBlocksIcon->setToolTip(tooltip);
    progressBarLabel->setToolTip(tooltip);
    progressBar->setToolTip(tooltip);
}

void BitcoinGUI::error(const QString &title, const QString &message, bool modal)
{
    // Report errors from network/worker thread
    if (modal)
    {
        QMessageBox::critical(this, title, message, QMessageBox::Ok, QMessageBox::Ok);
    }
    else
    {
        notificator->notify(Notificator::Critical, title, message);
    }
}

void BitcoinGUI::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
#ifndef Q_OS_MAC // Ignored on Mac
    if (e->type() == QEvent::WindowStateChange)
    {
        if (clientModel && clientModel->getOptionsModel()->getMinimizeToTray())
        {
            QWindowStateChangeEvent *wsevt = static_cast<QWindowStateChangeEvent *>(e);
            if (!(wsevt->oldState() & Qt::WindowMinimized) && isMinimized())
            {
                QTimer::singleShot(0, this, SLOT(hide()));
                e->ignore();
            }
        }
    }
#endif
}

void BitcoinGUI::closeEvent(QCloseEvent *event)
{
    if (clientModel)
    {
#ifndef Q_OS_MAC // Ignored on Mac
        if (!clientModel->getOptionsModel()->getMinimizeToTray() &&
            !clientModel->getOptionsModel()->getMinimizeOnClose())
        {
            qApp->quit();
        }
#endif
    }
    QMainWindow::closeEvent(event);
}

void BitcoinGUI::askFee(qint64 nFeeRequired, bool *payFee)
{
    QString strMessage =
        tr("This transaction is over the size limit.  You can still send it for a fee of %1, "
           "which goes to the nodes that process your transaction and helps to support the network.  "
           "Do you want to pay the fee?")
            .arg(
                BitcoinUnits::formatWithUnit(BitcoinUnits::BTC, nFeeRequired));
    QMessageBox::StandardButton retval = QMessageBox::question(
        this, tr("Confirm transaction fee"), strMessage,
        QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Yes);
    *payFee = (retval == QMessageBox::Yes);
}

void BitcoinGUI::incomingTransaction(const QModelIndex &parent, int start, int end)
{
    if (!walletModel || !clientModel)
        return;
    TransactionTableModel *ttm = walletModel->getTransactionTableModel();
    qint64 amount = ttm->index(start, TransactionTableModel::Amount, parent)
                        .data(Qt::EditRole)
                        .toULongLong();
    if (!clientModel->inInitialBlockDownload())
    {
        // On new transaction, make an info balloon
        // Unless the initial block download is in progress, to prevent balloon-spam
        QString date = ttm->index(start, TransactionTableModel::Date, parent)
                           .data()
                           .toString();
        QString type = ttm->index(start, TransactionTableModel::Type, parent)
                           .data()
                           .toString();
        QString address = ttm->index(start, TransactionTableModel::ToAddress, parent)
                              .data()
                              .toString();
        QIcon icon = qvariant_cast<QIcon>(ttm->index(start,
                                                     TransactionTableModel::ToAddress, parent)
                                              .data(Qt::DecorationRole));

        notificator->notify(Notificator::Information,
                            (amount) < 0 ? tr("Sent transaction") : tr("Incoming transaction"),
                            tr("Date: %1\n"
                               "Amount: %2\n"
                               "Type: %3\n"
                               "Address: %4\n")
                                .arg(date)
                                .arg(BitcoinUnits::formatWithUnit(walletModel->getOptionsModel()->getDisplayUnit(), amount, true))
                                .arg(type)
                                .arg(address),
                            icon);
    }
}

void BitcoinGUI::incomingMessage(const QModelIndex &parent, int start, int end)
{
    if (!messageModel)
        return;

    MessageModel *mm = messageModel;

    if (mm->index(start, MessageModel::TypeInt, parent).data().toInt() == MessageTableEntry::Received)
    {
        QString sent_datetime = mm->index(start, MessageModel::ReceivedDateTime, parent).data().toString();
        QString from_address = mm->index(start, MessageModel::FromAddress, parent).data().toString();
        QString to_address = mm->index(start, MessageModel::ToAddress, parent).data().toString();
        QString message = mm->index(start, MessageModel::Message, parent).data().toString();
        QTextDocument html;
        html.setHtml(message);
        QString messageText(html.toPlainText());
        notificator->notify(Notificator::Information,
                            tr("Incoming Secure Message"),
                            tr("Date: %1\n"
                               "From Address: %2\n"
                               "To Address: %3\n"
                               "Message: %4\n")
                                .arg(sent_datetime)
                                .arg(from_address)
                                .arg(to_address)
                                .arg(messageText));
    };
}

void BitcoinGUI::gotoOverviewPage()
{
    currentScreen = SCREEN_OVERVIEW;
    overviewAction->setChecked(true);
    updateWindowStyle(currentScreen);
    centralWidget->setCurrentWidget(overviewPage);
    exportAction->setEnabled(false);
    disconnect(exportAction, SIGNAL(triggered()), 0, 0);
}

void BitcoinGUI::gotoMessagePage()
{
    currentScreen = SCREEN_MESSAGES;
    messageAction->setChecked(true);
    updateWindowStyle(currentScreen);
    centralWidget->setCurrentWidget(messagePage);
    exportAction->setEnabled(true);
    disconnect(exportAction, SIGNAL(triggered()), 0, 0);
    connect(exportAction, SIGNAL(triggered()), messagePage, SLOT(exportClicked()));
}

void BitcoinGUI::gotoHistoryPage()
{
    currentScreen = SCREEN_TRANSACTIONS;
    historyAction->setChecked(true);
    updateWindowStyle(currentScreen);
    centralWidget->setCurrentWidget(transactionsPage);
    exportAction->setEnabled(true);
    disconnect(exportAction, SIGNAL(triggered()), 0, 0);
    connect(exportAction, SIGNAL(triggered()), transactionView, SLOT(exportClicked()));
}

void BitcoinGUI::gotoAddressBookPage()
{
    currentScreen = SCREEN_ADDRESSBOOK;
    addressBookAction->setChecked(true);
    updateWindowStyle(currentScreen);
    centralWidget->setCurrentWidget(addressBookPage);
    exportAction->setEnabled(true);
    disconnect(exportAction, SIGNAL(triggered()), 0, 0);
    connect(exportAction, SIGNAL(triggered()), addressBookPage, SLOT(exportClicked()));
}

void BitcoinGUI::gotoReceiveCoinsPage()
{
    currentScreen = SCREEN_RECEIVECOINS;
    receiveCoinsAction->setChecked(true);
    updateWindowStyle(currentScreen);
    centralWidget->setCurrentWidget(receiveCoinsPage);
    exportAction->setEnabled(true);
    disconnect(exportAction, SIGNAL(triggered()), 0, 0);
    connect(exportAction, SIGNAL(triggered()), receiveCoinsPage, SLOT(exportClicked()));
}

void BitcoinGUI::gotoSendCoinsPage()
{
    currentScreen = SCREEN_SENDCOINS;
    sendCoinsAction->setChecked(true);
    updateWindowStyle(currentScreen);
    centralWidget->setCurrentWidget(sendCoinsPage);
    exportAction->setEnabled(false);
    disconnect(exportAction, SIGNAL(triggered()), 0, 0);
}

void BitcoinGUI::gotoSignMessageTab(QString addr)
{
    // call show() in showTab_SM()
    signVerifyMessageDialog->showTab_SM(true);

    if (!addr.isEmpty())
        signVerifyMessageDialog->setAddress_SM(addr);
}

void BitcoinGUI::gotoVerifyMessageTab(QString addr)
{
    // call show() in showTab_VM()
    signVerifyMessageDialog->showTab_VM(true);

    if (!addr.isEmpty())
        signVerifyMessageDialog->setAddress_VM(addr);
}

void BitcoinGUI::dragEnterEvent(QDragEnterEvent *event)
{
    // Accept only URIs
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void BitcoinGUI::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        int nValidUrisFound = 0;
        QList<QUrl> uris = event->mimeData()->urls();
        foreach (const QUrl &uri, uris)
        {
            if (sendCoinsPage->handleURI(uri.toString()))
                nValidUrisFound++;
        }

        // if valid URIs were found
        if (nValidUrisFound)
            gotoSendCoinsPage();
        else
            notificator->notify(Notificator::Warning, tr("URI handling"), tr("URI can not be parsed! This can be caused by an invalid DeepOnion address or malformed URI parameters."));
    }

    event->acceptProposedAction();
}

void BitcoinGUI::handleURI(QString strURI)
{
    // URI has to be valid
    if (sendCoinsPage->handleURI(strURI))
    {
        showNormalIfMinimized();
        gotoSendCoinsPage();
    }
    else
        notificator->notify(Notificator::Warning, tr("URI handling"), tr("URI can not be parsed! This can be caused by an invalid DeepOnion address or malformed URI parameters."));
}

void BitcoinGUI::setEncryptionStatus(int status)
{
    switch (status)
    {
    case WalletModel::Unencrypted:
        labelEncryptionIcon->hide();
        encryptWalletAction->setChecked(false);
        changePassphraseAction->setEnabled(false);
        unlockWalletAction->setVisible(false);
        lockWalletAction->setVisible(false);
        encryptWalletAction->setEnabled(true);
        break;
    case WalletModel::Unlocked:
        labelEncryptionIcon->show();
        labelEncryptionIcon->setPixmap(QIcon(":/icons/new_lock_open").pixmap(STATUSBAR_ICONSIZE,STATUSBAR_ICONSIZE));
        labelEncryptionIcon->setToolTip(tr("Wallet is <b>encrypted</b> and currently <b>unlocked</b>"));
        encryptWalletAction->setChecked(true);
        changePassphraseAction->setEnabled(true);
        unlockWalletAction->setVisible(false);
        lockWalletAction->setVisible(true);
        encryptWalletAction->setEnabled(false); // TODO: decrypt currently not supported
        break;
    case WalletModel::Locked:
        labelEncryptionIcon->show();
        labelEncryptionIcon->setPixmap(QIcon(":/icons/new_lock_closed").pixmap(STATUSBAR_ICONSIZE,STATUSBAR_ICONSIZE));
        labelEncryptionIcon->setToolTip(tr("Wallet is <b>encrypted</b> and currently <b>locked</b>"));
        encryptWalletAction->setChecked(true);
        changePassphraseAction->setEnabled(true);
        unlockWalletAction->setVisible(true);
        lockWalletAction->setVisible(false);
        encryptWalletAction->setEnabled(false); // TODO: decrypt currently not supported
        break;
    }
}

void BitcoinGUI::encryptWallet(bool status)
{
    if (!walletModel)
        return;
    AskPassphraseDialog dlg(status ? AskPassphraseDialog::Encrypt : AskPassphraseDialog::Decrypt, this);
    dlg.setModel(walletModel);
    dlg.exec();

    setEncryptionStatus(walletModel->getEncryptionStatus());
}

void BitcoinGUI::backupWallet()
{
    QString saveDir = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation)[0];
    QString filename = QFileDialog::getSaveFileName(this, tr("Backup Wallet"), saveDir, tr("Wallet Data (*.dat)"));
    if (!filename.isEmpty())
    {
        if (!walletModel->backupWallet(filename))
        {
            QMessageBox::warning(this, tr("Backup Failed"), tr("There was an error trying to save the wallet data to the new location."));
        }
    }
}

void BitcoinGUI::changePassphrase()
{
    AskPassphraseDialog dlg(AskPassphraseDialog::ChangePass, this);
    dlg.setModel(walletModel);
    dlg.exec();
}

void BitcoinGUI::unlockWallet()
{
    if (!walletModel)
        return;
    // Unlock wallet when requested by wallet model
    if (walletModel->getEncryptionStatus() == WalletModel::Locked)
    {
        AskPassphraseDialog::Mode mode = sender() == unlockWalletAction ? AskPassphraseDialog::UnlockStaking : AskPassphraseDialog::Unlock;
        AskPassphraseDialog dlg(mode, this);
        dlg.setModel(walletModel);
        dlg.exec();
    }
}

void BitcoinGUI::lockWallet()
{
    if (!walletModel)
        return;

    walletModel->setWalletLocked(true);
}

void BitcoinGUI::showNormalIfMinimized(bool fToggleHidden)
{
    // activateWindow() (sometimes) helps with keyboard focus on Windows
    if (isHidden())
    {
        show();
        activateWindow();
    }
    else if (isMinimized())
    {
        showNormal();
        activateWindow();
    }
    else if (GUIUtil::isObscured(this))
    {
        raise();
        activateWindow();
    }
    else if (fToggleHidden)
        hide();
}

void BitcoinGUI::toggleHidden()
{
    showNormalIfMinimized(true);
}

void BitcoinGUI::updateStakingIcon()
{
    uint64_t nMinWeight = 0, nMaxWeight = 0, nWeight = 0;
    if (pwalletMain)
        pwalletMain->GetStakeWeight(*pwalletMain, nMinWeight, nMaxWeight, nWeight);

    if (nLastCoinStakeSearchInterval && nWeight)
    {
        uint64_t nNetworkWeight = GetPoSKernelPS();

        labelStakingIcon->setPixmap(QIcon(":/icons/new_staking_on").pixmap(STATUSBAR_ICONSIZE,STATUSBAR_ICONSIZE));
        labelStakingIcon->setToolTip(tr("Staking.<br>Your weight is %1<br>Network weight is %2").arg(nWeight).arg(nNetworkWeight));
    }
    else
    {
        labelStakingIcon->setPixmap(QIcon(":/icons/new_staking_off").pixmap(STATUSBAR_ICONSIZE,STATUSBAR_ICONSIZE));
        if (pwalletMain && pwalletMain->IsLocked())
            labelStakingIcon->setToolTip(tr("Not staking because wallet is locked"));
        else if (vNodes.empty())
            labelStakingIcon->setToolTip(tr("Not staking because wallet is offline"));
        else if (IsInitialBlockDownload())
            labelStakingIcon->setToolTip(tr("Not staking because wallet is syncing"));
        else if (!nWeight)
            labelStakingIcon->setToolTip(tr("Not staking because you don't have mature coins"));
        else
            labelStakingIcon->setToolTip(tr("Not staking"));
    }
}

void BitcoinGUI::updateOnionIcon()
{
	std::string ipaddress = addrSeenByPeer.ToStringIP();
	// printf(">>> addrSeenByPeer = %s\n", ipaddress.c_str());

	if (ipaddress == std::string("0.0.0.0"))
	{
		labelOnionIcon->setPixmap(QIcon(":/icons/new_tor_inactive").pixmap(STATUSBAR_ICONSIZE, STATUSBAR_ICONSIZE));
		labelOnionIcon->setToolTip(tr("Connecting over the Tor Network"));
	}
	else
	{
		std::string display = std::string("Connected over the Tor Network. IP: ") + ipaddress;
		labelOnionIcon->setPixmap(QIcon(":/icons/new_tor_active").pixmap(STATUSBAR_ICONSIZE, STATUSBAR_ICONSIZE));
		labelOnionIcon->setToolTip(tr(display.c_str()));
	}
}

void BitcoinGUI::optionsDialogFinished (int result)
{
    if(result != QDialog::Accepted){
        return;
    }
    themeManager->switchTheme(clientModel->getOptionsModel()->getTheme());
    refreshStyle();
}

void BitcoinGUI::refreshStyle()
{
    qApp->setStyleSheet(themeManager->getCurrent()->getStyleSheet());
    updateWindowStyle(currentScreen);
    centralWidget->setStyleSheet(themeManager->getCurrent()->getCentralWidgetStyle());
    overviewPage->refreshStyle();
    sendCoinsPage->refreshStyle();
    receiveCoinsPage->refreshStyle();
    addressBookPage->refreshStyle();
    transactionView->refreshStyle();
    messagePage->refreshStyle();
    signVerifyMessageDialog->refreshStyle();
    rpcConsole->refreshStyle();
}

void BitcoinGUI::updateWindowStyle(int screen)
{
	/*
	((QToolButton*)toolbar->widgetForAction(overviewAction))->setCheckable(false);
	((QToolButton*)toolbar->widgetForAction(sendCoinsAction))->setCheckable(false);
	((QToolButton*)toolbar->widgetForAction(receiveCoinsAction))->setCheckable(false);
	((QToolButton*)toolbar->widgetForAction(historyAction))->setCheckable(false);
	((QToolButton*)toolbar->widgetForAction(addressBookAction))->setCheckable(false);
	((QToolButton*)toolbar->widgetForAction(messageAction))->setCheckable(false);
	((QToolButton*)toolbar->widgetForAction(exportAction))->setCheckable(false);
	((QToolButton*)toolbar->widgetForAction(unlockWalletAction))->setCheckable(false);
	((QToolButton*)toolbar->widgetForAction(lockWalletAction))->setCheckable(false);
	*/

	((QToolButton*)toolbar->widgetForAction(overviewAction))->setIcon(QIcon(themeManager->getCurrent()->getMainMenuOverviewNormalBtnIco()));
	((QToolButton*)toolbar->widgetForAction(sendCoinsAction))->setIcon(QIcon(themeManager->getCurrent()->getMainMenuSendcoinsNormalBtnIco()));
	((QToolButton*)toolbar->widgetForAction(receiveCoinsAction))->setIcon(QIcon(themeManager->getCurrent()->getMainMenuReceiveCoinsNormalBtnIco()));
	((QToolButton*)toolbar->widgetForAction(historyAction))->setIcon(QIcon(themeManager->getCurrent()->getMainMenuTransactionsNormalBtnIco()));
	((QToolButton*)toolbar->widgetForAction(addressBookAction))->setIcon(QIcon(themeManager->getCurrent()->getMainMenuAddressBookNormalBtnIco()));
	((QToolButton*)toolbar->widgetForAction(messageAction))->setIcon(QIcon(themeManager->getCurrent()->getMainMenuMessagesNormalBtnIco()));
	((QToolButton*)toolbar->widgetForAction(exportAction))->setIcon(QIcon(themeManager->getCurrent()->getMainMenuExportNormalBtnIco()));
	((QToolButton*)toolbar->widgetForAction(unlockWalletAction))->setIcon(QIcon(themeManager->getCurrent()->getMainMenuUnlockWalletNormalBtnIco()));
	((QToolButton*)toolbar->widgetForAction(lockWalletAction))->setIcon(QIcon(themeManager->getCurrent()->getMainMenuLockWalletNormalBtnIco()));

	/*
	toolbar->widgetForAction(overviewAction)->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
	toolbar->widgetForAction(sendCoinsAction)->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
	toolbar->widgetForAction(receiveCoinsAction)->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
	toolbar->widgetForAction(historyAction)->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
	toolbar->widgetForAction(addressBookAction)->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
	toolbar->widgetForAction(messageAction)->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
	toolbar->widgetForAction(exportAction)->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
	toolbar->widgetForAction(unlockWalletAction)->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
	toolbar->widgetForAction(lockWalletAction)->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
	*/
	
    switch(screen) {
        case SCREEN_OVERVIEW:
        	// ((QToolButton*)toolbar->widgetForAction(overviewAction))->setCheckable(true);
        	((QToolButton*)toolbar->widgetForAction(overviewAction))->setIcon(QIcon(themeManager->getCurrent()->getMainMenuOverviewSelectedBtnIco()));
        	// toolbar->widgetForAction(overviewAction)->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            break;
            
        case SCREEN_SENDCOINS:
        	// ((QToolButton*)toolbar->widgetForAction(sendCoinsAction))->setCheckable(true);
        	((QToolButton*)toolbar->widgetForAction(sendCoinsAction))->setIcon(QIcon(themeManager->getCurrent()->getMainMenuSendcoinsSelectedBtnIco()));
        	// toolbar->widgetForAction(sendCoinsAction)->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            break;
            
        case SCREEN_RECEIVECOINS:
        	// ((QToolButton*)toolbar->widgetForAction(receiveCoinsAction))->setCheckable(true);
        	((QToolButton*)toolbar->widgetForAction(receiveCoinsAction))->setIcon(QIcon(themeManager->getCurrent()->getMainMenuReceiveCoinsSelectedBtnIco()));
        	// toolbar->widgetForAction(receiveCoinsAction)->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            break;
            
        case SCREEN_TRANSACTIONS:
        	// ((QToolButton*)toolbar->widgetForAction(historyAction))->setCheckable(true);
        	((QToolButton*)toolbar->widgetForAction(historyAction))->setIcon(QIcon(themeManager->getCurrent()->getMainMenuTransactionsSelectedBtnIco()));
        	// toolbar->widgetForAction(historyAction)->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            break;
            
        case SCREEN_ADDRESSBOOK:
        	// ((QToolButton*)toolbar->widgetForAction(addressBookAction))->setCheckable(true);
        	((QToolButton*)toolbar->widgetForAction(addressBookAction))->setIcon(QIcon(themeManager->getCurrent()->getMainMenuAddressBookSelectedBtnIco()));
        	// toolbar->widgetForAction(addressBookAction)->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            break;
            
        case SCREEN_MESSAGES:
        	// ((QToolButton*)toolbar->widgetForAction(messageAction))->setCheckable(true);
        	((QToolButton*)toolbar->widgetForAction(messageAction))->setIcon(QIcon(themeManager->getCurrent()->getMainMenuMessagesSelectedBtnIco()));
        	// toolbar->widgetForAction(messageAction)->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            break;
            
        case SCREEN_EXPORT:
        	// ((QToolButton*)toolbar->widgetForAction(exportAction))->setCheckable(true);
        	((QToolButton*)toolbar->widgetForAction(exportAction))->setIcon(QIcon(themeManager->getCurrent()->getMainMenuExportSelectedBtnIco()));
        	// toolbar->widgetForAction(exportAction)->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            break;
            
        case SCREEN_UNLOCKWALLET:
        	// ((QToolButton*)toolbar->widgetForAction(unlockWalletAction))->setCheckable(true);
        	((QToolButton*)toolbar->widgetForAction(unlockWalletAction))->setIcon(QIcon(themeManager->getCurrent()->getMainMenuUnlockWalletSelectedBtnIco()));
        	// toolbar->widgetForAction(unlockWalletAction)->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
        	// ((QToolButton*)toolbar->widgetForAction(lockWalletAction))->setCheckable(true);
        	((QToolButton*)toolbar->widgetForAction(lockWalletAction))->setIcon(QIcon(themeManager->getCurrent()->getMainMenuLockWalletSelectedBtnIco()));
        	// toolbar->widgetForAction(lockWalletAction)->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            break;
            
        default:
            break;
    }
}
