// Copyright (c) 2018 The DeepOnion Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include "menupage.h"
#include "ui_menupage.h"
#include "clientmodel.h"
#include "walletmodel.h"
#include "bitcoingui.h"
#include "themeadapter.h"

#include "overviewpage.h"


#include "guiutil.h"
#include "guiconstants.h"

#include <QAbstractItemDelegate>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>

#define DECORATION_SIZE 64
#define NUM_ITEMS 3

MenuPage::MenuPage(QWidget *parent, BitcoinGUI *gui) :
  QWidget(parent),
  ui(new Ui::MenuPage),
  clientModel(0),
  walletModel(0),
  gui(gui)
{
    ui->setupUi(this);
    //QWidget::setStyleSheet(gui->getThemeAdapter()->getMainMenuPageStyle());
    QWidget::setStyleSheet("background: #F8CF8B;");

    connect(ui->Overview, SIGNAL(pressed()), this, SLOT(ClickedItem()));
    connect(ui->SendCoins, SIGNAL(pressed()), this, SLOT(ClickedItem()));
    connect(ui->ReceiveCoins, SIGNAL(pressed()), this, SLOT(ClickedItem()));
    connect(ui->Transactions, SIGNAL(pressed()), this, SLOT(ClickedItem()));
    connect(ui->AddressBook, SIGNAL(pressed()), this, SLOT(ClickedItem()));
    connect(ui->Messages, SIGNAL(pressed()), this, SLOT(ClickedItem()));
    connect(ui->Export, SIGNAL(pressed()), this, SLOT(ClickedItem()));
    //Change style to clicked to Dashboard button
    ui->Overview->setStyleSheet(gui->getThemeAdapter()->getMainMenuSelectedButtonStyle());

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

    ui->Overview->setIcon(QIcon(gui->getThemeAdapter()->getOverviewNormalBtnIcon()));
    ui->SendCoins->setIcon(QIcon(gui->getThemeAdapter()->getSendCoinsNormalBtnIcon()));
    ui->ReceiveCoins->setIcon(QIcon(gui->getThemeAdapter()->getReceiveCoinsNormalBtnIcon()));
    ui->Transactions->setIcon(QIcon(gui->getThemeAdapter()->getTransactionsNormalBtnIcon()));
    ui->AddressBook->setIcon(QIcon(gui->getThemeAdapter()->getAddressBookNormalBtnIcon()));
    ui->Messages->setIcon(QIcon(gui->getThemeAdapter()->getMessagesNormalBtnIcon()));
    ui->Export->setIcon(QIcon(gui->getThemeAdapter()->getExportNormalBtnIcon()));

    ui->Overview->setStyleSheet(gui->getThemeAdapter()->getMainMenuNormalButtonStyle());
    ui->SendCoins->setStyleSheet(gui->getThemeAdapter()->getMainMenuNormalButtonStyle());
    ui->ReceiveCoins->setStyleSheet(gui->getThemeAdapter()->getMainMenuNormalButtonStyle());
    ui->Transactions->setStyleSheet(gui->getThemeAdapter()->getMainMenuNormalButtonStyle());
    ui->AddressBook->setStyleSheet(gui->getThemeAdapter()->getMainMenuNormalButtonStyle());
    ui->Messages ->setStyleSheet(gui->getThemeAdapter()->getMainMenuNormalButtonStyle());
    ui->Export->setStyleSheet(gui->getThemeAdapter()->getMainMenuDeactivatedButtonStyle());

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
            ui->Overview->setStyleSheet(gui->getThemeAdapter()->getMainMenuSelectedButtonStyle());
            ui->Overview->setIcon(QIcon(gui->getThemeAdapter()->getOverviewSelectedBtnIcon()));
        break;
    case 1:
            ui->SendCoins->setCheckable(true);
            ui->SendCoins->setStyleSheet(gui->getThemeAdapter()->getMainMenuSelectedButtonStyle());
            ui->SendCoins->setIcon(QIcon(gui->getThemeAdapter()->getSendCoinsSelectedBtnIcon()));
        break;
    case 2:
            ui->ReceiveCoins->setCheckable(true);
            ui->ReceiveCoins->setStyleSheet(gui->getThemeAdapter()->getMainMenuSelectedButtonStyle());
            ui->ReceiveCoins->setIcon(QIcon(gui->getThemeAdapter()->getReceiveCoinsSelectedBtnIcon()));
        break;
    case 3:
            ui->Transactions->setCheckable(true);
            ui->Transactions->setStyleSheet(gui->getThemeAdapter()->getMainMenuSelectedButtonStyle());
            ui->Transactions->setIcon(QIcon(gui->getThemeAdapter()->getTransactionsSelectedBtnIcon()));
        break;
    case 4:
            ui->AddressBook->setCheckable(true);
            ui->AddressBook->setStyleSheet(gui->getThemeAdapter()->getMainMenuSelectedButtonStyle());
            ui->AddressBook->setIcon(QIcon(gui->getThemeAdapter()->getAddressBookSelectedBtnIcon()));
        break;
    case 5:
            ui->Messages->setCheckable(true);
            ui->Messages->setStyleSheet(gui->getThemeAdapter()->getMainMenuSelectedButtonStyle());
            ui->Messages->setIcon(QIcon(gui->getThemeAdapter()->getMessagesSelectedBtnIcon()));
        break;
    case 6:
            ui->Export->setCheckable(true);
            ui->Export->setStyleSheet(gui->getThemeAdapter()->getMainMenuSelectedButtonStyle());
            ui->Export->setIcon(QIcon(gui->getThemeAdapter()->getExportSelectedBtnIcon()));
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
