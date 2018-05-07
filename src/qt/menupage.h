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
    explicit MenuPage(QWidget *parent = NULL, BitcoinGUI *gui = NULL);

    ~MenuPage();
    void LinkMenu(BitcoinGUI *gui);
//private:
    BitcoinGUI *gui;
    Ui::MenuPage *ui;
    ClientModel *clientModel;
    WalletModel *walletModel;

    QLabel *progressBarLabel;
    QProgressBar *progressBar;
    QFrame *frameBlocks;

public Q_SLOTS:
    void ClickedItem();
};

#endif // MENUPAGE_H