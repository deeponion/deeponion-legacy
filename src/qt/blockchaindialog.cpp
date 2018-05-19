#include "blockchaindialog.h"
#include "ui_blockchaindialog.h"
#include "util.h"
#include "walletmodel.h"


BlockchainDialog::BlockchainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlockchainDialog)
{
    ui->setupUi(this);
}

BlockchainDialog::~BlockchainDialog()
{
    delete ui;
}

void BlockchainDialog::on_buttonBox_accepted()
{
    close();
}


void BlockchainDialog::setLabelText(WalletModel* walletModel)
{
	ui->label->setText(walletModel->getBlockchainStatusDetailsText());
	ui->label->setStyleSheet(walletModel->getBlockchainTextStylesheet());
}