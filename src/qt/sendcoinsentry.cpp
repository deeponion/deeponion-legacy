// Copyright (c) 2018 The DeepOnion Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "sendcoinsentry.h"
#include "ui_sendcoinsentry.h"
#include "guiutil.h"
#include "bitcoinunits.h"
#include "addressbookpage.h"
#include "wallet.h"
#include "walletmodel.h"
#include "optionsmodel.h"
#include "addresstablemodel.h"
#include "stealth.h"
#include "thememanager.h"

#include <QApplication>
#include <QClipboard>

extern ThemeManager *themeManager;

SendCoinsEntry::SendCoinsEntry(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SendCoinsEntry),
    model(0)
{
    ui->setupUi(this);

#ifdef Q_OS_MAC
    ui->payToLayout->setSpacing(4);
#endif
#if QT_VERSION >= 0x040700
    /* Do not move this to the XML file, Qt before 4.7 will choke on it */
    ui->addAsLabel->setPlaceholderText(tr("Enter a label for this address to add it to your address book"));
    ui->payTo->setPlaceholderText(tr("Enter a DeepOnion address"));
#endif
    setStyleSheet(themeManager->getCurrent()->getQFrameGeneralStyle());

    ui->addAsNarration->setPlaceholderText(tr("Enter a short note to send with payment (max 24 characters) - only available for payment to Stealth Address"));
    ui->addAsNarration->setMaxLength(MAX_STEALTH_NARRATION_SIZE_PLAINTEXT);

    ui->addAsNarration->setStyleSheet(themeManager->getCurrent()->getQLineEdit());
    ui->payTo->setStyleSheet(themeManager->getCurrent()->getQLineEdit());
    ui->addAsLabel->setStyleSheet(themeManager->getCurrent()->getQLineEdit());
    ui->payAmount->setStyleSheet(themeManager->getCurrent()->getPayAmountStyle());

    ui->label_5->setStyleSheet(themeManager->getCurrent()->getQLabelGeneralStyle());
    ui->label_2->setStyleSheet(themeManager->getCurrent()->getQLabelGeneralStyle());
    ui->label_4->setStyleSheet(themeManager->getCurrent()->getQLabelGeneralStyle());
    ui->label->setStyleSheet(themeManager->getCurrent()->getQLabelGeneralStyle());

    setFocusPolicy(Qt::TabFocus);
    setFocusProxy(ui->payTo);

    GUIUtil::setupAddressWidget(ui->payTo, this);
}

SendCoinsEntry::~SendCoinsEntry()
{
    delete ui;
}

void SendCoinsEntry::on_pasteButton_clicked()
{
    // Paste text from clipboard into recipient field
    ui->payTo->setText(QApplication::clipboard()->text());
}

void SendCoinsEntry::on_addressBookButton_clicked()
{
    if(!model)
        return;
    AddressBookPage dlg(AddressBookPage::ForSending, AddressBookPage::SendingTab, this, AddressBookPage::FromSendCoinsEntry);
    dlg.setModel(model->getAddressTableModel());
    if(dlg.exec())
    {
        ui->payTo->setText(dlg.getReturnValue());
        ui->payAmount->setFocus();
    }
}

void SendCoinsEntry::on_payTo_textChanged(const QString &address)
{
    if(!model)
        return;
    // Fill in label from address book, if address has an associated label
    QString associatedLabel = model->getAddressTableModel()->labelForAddress(address);
    if(!associatedLabel.isEmpty())
        ui->addAsLabel->setText(associatedLabel);
    
    if(address.length() > 0)
    {
    	setRemoveEnabled(true);
    }
    else
    {
    	setRemoveEnabled(false);
    }
    
    if(address.length() > STEALTH_LENGTH_TRESHOLD)
    {
        ui->addAsNarration->setEnabled(true);
    }
    else
    {
        ui->addAsNarration->setText("");
        ui->addAsNarration->setEnabled(false);
    }        
}

void SendCoinsEntry::setModel(WalletModel *model)
{
    this->model = model;

    if(model && model->getOptionsModel())
        connect(model->getOptionsModel(), SIGNAL(displayUnitChanged(int)), this, SLOT(updateDisplayUnit()));

    connect(ui->payAmount, SIGNAL(textChanged()), this, SIGNAL(payAmountChanged()));

    clear();
}

void SendCoinsEntry::setRemoveEnabled(bool enabled)
{
    ui->deleteButton->setEnabled(enabled);
}

void SendCoinsEntry::clear()
{
    ui->payTo->clear();
    ui->addAsLabel->clear();
    ui->addAsNarration->clear();
    ui->payAmount->clear();
    ui->payTo->setFocus();
    // update the display unit, to not use the default ("BTC")
    updateDisplayUnit();
}

void SendCoinsEntry::on_deleteButton_clicked()
{
	ui->payTo->clear();
    // emit removeEntry(this);
}

bool SendCoinsEntry::validate()
{
    // Check input validity
    bool retval = true;

    if(!ui->payAmount->validate())
    {
        retval = false;
    }
    else
    {
        if(ui->payAmount->value() <= 0)
        {
            // Cannot send 0 coins or less
            ui->payAmount->setValid(false);
            retval = false;
        }
    }

    if(!ui->payTo->hasAcceptableInput() ||
       (model && !model->validateAddress(ui->payTo->text())))
    {
        ui->payTo->setValid(false);
        retval = false;
    }

    return retval;
}

SendCoinsRecipient SendCoinsEntry::getValue()
{
    SendCoinsRecipient rv;

    rv.address = ui->payTo->text();
    rv.label = ui->addAsLabel->text();
    rv.amount = ui->payAmount->value();
    
    if (rv.address.length() > STEALTH_LENGTH_TRESHOLD 
        && IsStealthAddress(rv.address.toStdString()))
    {
        rv.typeInd = AddressTableModel::AT_Stealth;
        rv.narration = ui->addAsNarration->text();
        
        // limit max 24 characters only, this as a safety measure
        if(rv.narration.size() > MAX_STEALTH_NARRATION_SIZE_PLAINTEXT)
        {
            rv.narration = rv.narration.left(MAX_STEALTH_NARRATION_SIZE_PLAINTEXT);
        }
    } else {
        rv.typeInd = AddressTableModel::AT_Normal;
    }

    return rv;
}

QWidget *SendCoinsEntry::setupTabChain(QWidget *prev)
{
    QWidget::setTabOrder(prev, ui->payTo);
    QWidget::setTabOrder(ui->payTo, ui->addressBookButton);
    QWidget::setTabOrder(ui->addressBookButton, ui->pasteButton);
    QWidget::setTabOrder(ui->pasteButton, ui->deleteButton);
    QWidget::setTabOrder(ui->deleteButton, ui->addAsLabel);
    QWidget::setTabOrder(ui->addAsLabel, ui->addAsNarration);
    return ui->payAmount->setupTabChain(ui->addAsNarration);
}

void SendCoinsEntry::setValue(const SendCoinsRecipient &value)
{
    ui->payTo->setText(value.address);
    ui->addAsLabel->setText(value.label);
    ui->addAsNarration->setText(value.narration);
    ui->payAmount->setValue(value.amount);
}

bool SendCoinsEntry::isClear()
{
    return ui->payTo->text().isEmpty();
}

void SendCoinsEntry::setFocus()
{
    ui->payTo->setFocus();
}

void SendCoinsEntry::updateDisplayUnit()
{
    if(model && model->getOptionsModel())
    {
        // Update payAmount with the current unit
        ui->payAmount->setDisplayUnit(model->getOptionsModel()->getDisplayUnit());
    }
}
