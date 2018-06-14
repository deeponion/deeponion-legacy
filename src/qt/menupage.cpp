// Copyright (c) 2018 The DeepOnion Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include "menupage.h"
#include "ui_menupage.h"
#include "clientmodel.h"
#include "walletmodel.h"
#include "bitcoingui.h"
#include "thememanager.h"

#include "overviewpage.h"


#include "guiutil.h"
#include "guiconstants.h"

#include <QAbstractItemDelegate>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>

#define DECORATION_SIZE 64
#define NUM_ITEMS 3

extern ThemeManager *themeManager;

MenuPage::MenuPage(QWidget *parent, BitcoinGUI *gui) :
  QWidget(parent),
  ui(new Ui::MenuPage),
  clientModel(0),
  walletModel(0),
  gui(gui)
{
    ui->setupUi(this);

    connect(ui->Overview, SIGNAL(pressed()), this, SLOT(ClickedItem()));
    connect(ui->SendCoins, SIGNAL(pressed()), this, SLOT(ClickedItem()));
    connect(ui->ReceiveCoins, SIGNAL(pressed()), this, SLOT(ClickedItem()));
    connect(ui->Transactions, SIGNAL(pressed()), this, SLOT(ClickedItem()));
    connect(ui->AddressBook, SIGNAL(pressed()), this, SLOT(ClickedItem()));
    connect(ui->Messages, SIGNAL(pressed()), this, SLOT(ClickedItem()));
    connect(ui->Export, SIGNAL(pressed()), this, SLOT(ClickedItem()));
    //Change style to clicked to Dashboard button
    ui->Overview->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());

}

MenuPage::~MenuPage()
{
    delete ui;
}

void MenuPage::ClickedItem(){

    ui->Overview->setCheckable(false);
    ui->SendCoins->setCheckable(false);
    ui->ReceiveCoins->setCheckable(false);
    ui->Transactions->setCheckable(false);
    ui->AddressBook->setCheckable(false);
    ui->Messages->setCheckable(false);
    ui->Export->setCheckable(false);

    ui->Overview->setIcon(QIcon(themeManager->getCurrent()->getMainMenuOverviewNormalBtnIco()));
    ui->SendCoins->setIcon(QIcon(themeManager->getCurrent()->getMainMenuSendcoinsNormalBtnIco()));
    ui->ReceiveCoins->setIcon(QIcon(themeManager->getCurrent()->getMainMenuReceiveCoinsNormalBtnIco()));
    ui->Transactions->setIcon(QIcon(themeManager->getCurrent()->getMainMenuTransactionsNormalBtnIco()));
    ui->AddressBook->setIcon(QIcon(themeManager->getCurrent()->getMainMenuAddressBookNormalBtnIco()));
    ui->Messages->setIcon(QIcon(themeManager->getCurrent()->getMainMenuMessagesNormalBtnIco()));
    ui->Export->setIcon(QIcon(themeManager->getCurrent()->getMainMenuExportNormalBtnIco()));

    ui->Overview->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
    ui->SendCoins->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
    ui->ReceiveCoins->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
    ui->Transactions->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
    ui->AddressBook->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
    ui->Messages ->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
    ui->Export->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());

    int screen = 0;
    QObject *sender = QObject::sender();

    if(sender == ui->Overview)
        screen = 0;
    if(sender == ui->SendCoins)
        screen = 1;
    if(sender == ui->ReceiveCoins)
        screen = 2;
    if(sender == ui->Transactions)
        screen = 3;
    if(sender == ui->AddressBook)
        screen = 4;
    if(sender == ui->Messages)
        screen = 5;
    if(sender == ui->Export)
        screen = 6;

    switch(screen){
    case 0:
            ui->Overview->setCheckable(true);
            ui->Overview->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            ui->Overview->setIcon(QIcon(themeManager->getCurrent()->getMainMenuOverviewSelectedBtnIco()));
        break;
    case 1:
            ui->SendCoins->setCheckable(true);
            ui->SendCoins->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            ui->SendCoins->setIcon(QIcon(themeManager->getCurrent()->getMainMenuSendcoinsSelectedBtnIco()));
        break;
    case 2:
            ui->ReceiveCoins->setCheckable(true);
            ui->ReceiveCoins->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            ui->ReceiveCoins->setIcon(QIcon(themeManager->getCurrent()->getMainMenuReceiveCoinsSelectedBtnIco()));
        break;
    case 3:
            ui->Transactions->setCheckable(true);
            ui->Transactions->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            ui->Transactions->setIcon(QIcon(themeManager->getCurrent()->getMainMenuTransactionsSelectedBtnIco()));
        break;
    case 4:
            ui->AddressBook->setCheckable(true);
            ui->AddressBook->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            ui->AddressBook->setIcon(QIcon(themeManager->getCurrent()->getMainMenuAddressBookSelectedBtnIco()));
        break;
    case 5:
            ui->Messages->setCheckable(true);
            ui->Messages->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            ui->Messages->setIcon(QIcon(themeManager->getCurrent()->getMainMenuMessagesSelectedBtnIco()));
        break;
    case 6:
            ui->Export->setCheckable(true);
            ui->Export->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            ui->Export->setIcon(QIcon(themeManager->getCurrent()->getMainMenuExportSelectedBtnIco()));
        break;
    default:
        break;

    }
}


void MenuPage::ClickedItemAfterThemeChanged(int sender){

    ui->Overview->setCheckable(false);
    ui->SendCoins->setCheckable(false);
    ui->ReceiveCoins->setCheckable(false);
    ui->Transactions->setCheckable(false);
    ui->AddressBook->setCheckable(false);
    ui->Messages->setCheckable(false);
    ui->Export->setCheckable(false);

    ui->Overview->setIcon(QIcon(themeManager->getCurrent()->getMainMenuOverviewNormalBtnIco()));
    ui->SendCoins->setIcon(QIcon(themeManager->getCurrent()->getMainMenuSendcoinsNormalBtnIco()));
    ui->ReceiveCoins->setIcon(QIcon(themeManager->getCurrent()->getMainMenuReceiveCoinsNormalBtnIco()));
    ui->Transactions->setIcon(QIcon(themeManager->getCurrent()->getMainMenuTransactionsNormalBtnIco()));
    ui->AddressBook->setIcon(QIcon(themeManager->getCurrent()->getMainMenuAddressBookNormalBtnIco()));
    ui->Messages->setIcon(QIcon(themeManager->getCurrent()->getMainMenuMessagesNormalBtnIco()));
    ui->Export->setIcon(QIcon(themeManager->getCurrent()->getMainMenuExportNormalBtnIco()));

    ui->Overview->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
    ui->SendCoins->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
    ui->ReceiveCoins->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
    ui->Transactions->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
    ui->AddressBook->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
    ui->Messages ->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());
    ui->Export->setStyleSheet(themeManager->getCurrent()->getMainMenuNormalButtonStyle());

    int screen = sender;

    switch(screen){
        case 0:
            ui->Overview->setCheckable(true);
            ui->Overview->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            ui->Overview->setIcon(QIcon(themeManager->getCurrent()->getMainMenuOverviewSelectedBtnIco()));
            break;
        case 1:
            ui->SendCoins->setCheckable(true);
            ui->SendCoins->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            ui->SendCoins->setIcon(QIcon(themeManager->getCurrent()->getMainMenuSendcoinsSelectedBtnIco()));
            break;
        case 2:
            ui->ReceiveCoins->setCheckable(true);
            ui->ReceiveCoins->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            ui->ReceiveCoins->setIcon(QIcon(themeManager->getCurrent()->getMainMenuReceiveCoinsSelectedBtnIco()));
            break;
        case 3:
            ui->Transactions->setCheckable(true);
            ui->Transactions->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            ui->Transactions->setIcon(QIcon(themeManager->getCurrent()->getMainMenuTransactionsSelectedBtnIco()));
            break;
        case 4:
            ui->AddressBook->setCheckable(true);
            ui->AddressBook->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            ui->AddressBook->setIcon(QIcon(themeManager->getCurrent()->getMainMenuAddressBookSelectedBtnIco()));
            break;
        case 5:
            ui->Messages->setCheckable(true);
            ui->Messages->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            ui->Messages->setIcon(QIcon(themeManager->getCurrent()->getMainMenuMessagesSelectedBtnIco()));
            break;
        case 6:
            ui->Export->setCheckable(true);
            ui->Export->setStyleSheet(themeManager->getCurrent()->getMainMenuSelectedButtonStyle());
            ui->Export->setIcon(QIcon(themeManager->getCurrent()->getMainMenuExportSelectedBtnIco()));
            break;
        default:
            break;

    }
}

void MenuPage::LinkMenu(BitcoinGUI *gui){

    //connect(overviewAction, SIGNAL(triggered()), this, SLOT(showNormalIfMinimized()));
    connect(ui->Overview, SIGNAL(pressed()), gui, SLOT(gotoOverviewPage()));
    connect(ui->SendCoins, SIGNAL(pressed()), gui, SLOT(gotoSendCoinsPage()));
    connect(ui->ReceiveCoins, SIGNAL(pressed()), gui, SLOT(gotoReceiveCoinsPage()));
    connect(ui->Transactions, SIGNAL(pressed()), gui, SLOT(gotoHistoryPage()));
    connect(ui->AddressBook, SIGNAL(pressed()), gui, SLOT(gotoAddressBookPage()));
    connect(ui->Messages, SIGNAL(pressed()), gui, SLOT(gotoMessagePage()));
}
