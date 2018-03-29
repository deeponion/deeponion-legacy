// Copyright (c) 017 The Zoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#include "menupage.h"
#include "ui_menupage.h"
#include "clientmodel.h"
#include "walletmodel.h"
#include "bitcoingui.h"

#include "overviewpage.h"


#include "guiutil.h"
#include "guiconstants.h"

#include <QAbstractItemDelegate>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>

#define DECORATION_SIZE 64
#define NUM_ITEMS 3

MenuPage::MenuPage(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MenuPage),
  clientModel(0),
  walletModel(0)
{

   ui->setupUi(this);

   connect(ui->Overview, SIGNAL(pressed()), this, SLOT(ClickedItem()));
   connect(ui->SendCoins, SIGNAL(pressed()), this, SLOT(ClickedItem()));
   connect(ui->ReceiveCoins, SIGNAL(pressed()), this, SLOT(ClickedItem()));
   connect(ui->Transactions, SIGNAL(pressed()), this, SLOT(ClickedItem()));
   connect(ui->AddressBook, SIGNAL(pressed()), this, SLOT(ClickedItem()));
   connect(ui->Messages, SIGNAL(pressed()), this, SLOT(ClickedItem()));
   connect(ui->Export, SIGNAL(pressed()), this, SLOT(ClickedItem()));
   ui->Overview->setStyleSheet("color: rgb(75, 13, 149); border-left :5px solid rgb(74,14,149);height: 60px;padding-left: 5px; text-align:left;");

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

    ui->Overview->setStyleSheet("color: rgb(0, 0, 0); height: 60px;padding-left: 5px; text-align:left;");
    ui->SendCoins->setStyleSheet("color: rgb(0, 0, 0);height: 60px;padding-left: 5px; text-align:left;");
    ui->ReceiveCoins->setStyleSheet("color: rgb(0, 0, 0);height: 60px;padding-left: 5px; text-align:left;");
    ui->Transactions->setStyleSheet("color: rgb(0, 0, 0);height: 60px;padding-left: 5px; text-align:left;");
    ui->AddressBook->setStyleSheet("color: rgb(0, 0, 0);height: 60px;padding-left: 5px; text-align:left;");
    ui->Messages ->setStyleSheet("color: rgb(0, 0, 0);height: 60px;padding-left: 5px; text-align:left;");
    ui->Export->setStyleSheet("color: rgb(0, 0, 0);height: 60px;padding-left: 5px; text-align:left;");


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
        ui->Overview->setStyleSheet("color: rgb(75, 13, 149); border-left :5px solid rgb(74,14,149);height: 60px;padding-left: 5px; text-align:left;");
        break;
    case 1:
        ui->SendCoins->setCheckable(true);
        ui->SendCoins->setStyleSheet("color: rgb(75, 13, 149); border-left :5px solid rgb(74,14,149);height: 60px;padding-left: 5px; text-align:left;");
        break;
    case 2:
        ui->ReceiveCoins->setCheckable(true);
        ui->ReceiveCoins->setStyleSheet("color: rgb(75, 13, 149); border-left :5px solid rgb(74,14,149);height: 60px;padding-left: 5px; text-align:left;");
        break;
    case 3:
        ui->Transactions->setCheckable(true);
        ui->Transactions->setStyleSheet("color: rgb(75, 13, 149); border-left :5px solid rgb(74,14,149);height: 60px;padding-left: 5px; text-align:left;");
        break;
    case 4:
        ui->AddressBook->setCheckable(true);
        ui->AddressBook->setStyleSheet("color: rgb(75, 13, 149); border-left :5px solid rgb(74,14,149);height: 60px;padding-left: 5px; text-align:left;");
        break;
    case 5:
        ui->Messages->setCheckable(true);
        ui->Messages->setStyleSheet("color: rgb(75, 13, 149); border-left :5px solid rgb(74,14,149);height: 60px;padding-left: 5px; text-align:left;");
        break;
    case 6:
        ui->Export->setCheckable(true);
        ui->Export->setStyleSheet("color: rgb(75, 13, 149); border-left :5px solid rgb(74,14,149);height: 60px;padding-left: 5px; text-align:left;");
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
    connect(ui->Export, SIGNAL(pressed()), gui, SLOT(gotoZoinodePage()));
}

void MenuPage::ClickedItemNonSlot(int s){

    ui->Overview->setCheckable(false);
    ui->SendCoins->setCheckable(false);
    ui->ReceiveCoins->setCheckable(false);
    ui->Transactions->setCheckable(false);
    ui->AddressBook->setCheckable(false);
    ui->Messages->setCheckable(false);
    ui->Export->setCheckable(false);

    ui->Overview->setStyleSheet("color: rgb(0, 0, 0); height: 60px;padding-left: 5px; text-align:left;");
    ui->SendCoins->setStyleSheet("color: rgb(0, 0, 0);height: 60px;padding-left: 5px; text-align:left;");
    ui->ReceiveCoins->setStyleSheet("color: rgb(0, 0, 0);height: 60px;padding-left: 5px; text-align:left;");
    ui->Transactions->setStyleSheet("color: rgb(0, 0, 0);height: 60px;padding-left: 5px; text-align:left;");
    ui->AddressBook->setStyleSheet("color: rgb(0, 0, 0);height: 60px;padding-left: 5px; text-align:left;");
    ui->Messages->setStyleSheet("color: rgb(0, 0, 0);height: 60px;padding-left: 5px; text-align:left;");
    ui->Export->setStyleSheet("color: rgb(0, 0, 0);height: 60px;padding-left: 5px; text-align:left;");


    switch(s){
    case 0:
        ui->Overview->setCheckable(true);
        ui->Overview->setStyleSheet("color: rgb(75, 13, 149); border-left :5px solid rgb(74,14,149);height: 60px;padding-left: 5px; text-align:left;");
        break;
    case 1:
        ui->SendCoins->setCheckable(true);
        ui->SendCoins->setStyleSheet("color: rgb(75, 13, 149); border-left :5px solid rgb(74,14,149);height: 60px;padding-left: 5px; text-align:left;");
        break;
    case 2:
        ui->ReceiveCoins->setCheckable(true);
        ui->ReceiveCoins->setStyleSheet("color: rgb(75, 13, 149); border-left :5px solid rgb(74,14,149);height: 60px;padding-left: 5px; text-align:left;");
        break;
    case 3:
        ui->Transactions->setCheckable(true);
        ui->Transactions->setStyleSheet("color: rgb(75, 13, 149); border-left :5px solid rgb(74,14,149);height: 60px;padding-left: 5px; text-align:left;");
        break;
    case 4:
        ui->AddressBook->setCheckable(true);
        ui->AddressBook->setStyleSheet("color: rgb(75, 13, 149); border-left :5px solid rgb(74,14,149);height: 60px;padding-left: 5px; text-align:left;");
        break;
    case 5:
        ui->Messages->setCheckable(true);
        ui->Messages->setStyleSheet("color: rgb(75, 13, 149); border-left :5px solid rgb(74,14,149);height: 60px;padding-left: 5px; text-align:left;");
        break;
    case 6:
        ui->Export->setCheckable(true);
        ui->Export->setStyleSheet("color: rgb(75, 13, 149); border-left :5px solid rgb(74,14,149);height: 60px;padding-left: 5px; text-align:left;");
        break;
    default:
        break;

    }
}

void MenuPage::SimulateOverviewClick(){
    ClickedItemNonSlot(0);
}
void MenuPage::SimulateSendCoinsClick(){
    ClickedItemNonSlot(1);
}
void MenuPage::SimulateReceiveCoinsClick(){
    ClickedItemNonSlot(2);
}
void MenuPage::SimulateTransactionsClick(){
    ClickedItemNonSlot(3);
}
void MenuPage::SimulateAddressBookClick(){
    ClickedItemNonSlot(4);
}
void MenuPage::SimulateMessagesClick(){
    ClickedItemNonSlot(5);
}
void MenuPage::SimulateExportClick(){
    ClickedItemNonSlot(6);
}



