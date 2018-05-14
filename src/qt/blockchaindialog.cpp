#include "blockchaindialog.h"
#include "ui_blockchaindialog.h"
#include "util.h"


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
