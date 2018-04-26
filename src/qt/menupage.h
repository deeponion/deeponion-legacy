// Copyright (c) 2017 The Zoin Developers
// Created by Matthew Tawil
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.


#ifndef MENUPAGE_H
#define MENUPAGE_H

#include <QWidget>

#include <QProgressBar>
#include <QLabel>
#include <QFrame>
#include "guiutil.h"
#include "bitcoingui.h"
//#include "walletview.h"



namespace Ui {
    class MenuPage;
}

class BitcoinGUI;
class ClientModel;
class WalletModel;

class MenuPage : public QWidget
{
    Q_OBJECT
public:
    explicit MenuPage(QWidget *parent = NULL);
    ~MenuPage();
    void LinkMenu(BitcoinGUI *gui);
//private:
    Ui::MenuPage *ui;
    ClientModel *clientModel;
    WalletModel *walletModel;

    QLabel *progressBarLabel;
    QProgressBar *progressBar;
    QFrame *frameBlocks;
    //WalletView *walletView;

    QString normalButtonStyle = "border:0; height: 60px;padding-left: 15px;text-align:left;color: white;background-color: #393848";
    QString deactivatedButtonStyle = "border:0; height: 60px;padding-left: 15px;text-align:left;color: #787878;background-color: #393848";
    QString selectedButtonStyle = "border:0; height: 60px;padding-left: 15px;text-align:left;color: white;background-color: #486EBA";

public Q_SLOTS:
    void ClickedItem();
};

#endif // MENUPAGE_H