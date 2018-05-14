#ifndef BLOCKCHAINDIALOG_H
#define BLOCKCHAINDIALOG_H

#include <QDialog>

namespace Ui {
    class BlockchainDialog;
}

/** "About" dialog box */
class BlockchainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BlockchainDialog(QWidget *parent = 0);
    ~BlockchainDialog();

private:
    Ui::BlockchainDialog *ui;

private slots:
    void on_buttonBox_accepted();
};

#endif // BLOCKCHAINDIALOG_H
