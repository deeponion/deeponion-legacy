//
// Created by arcas on 4/30/2018.
//

#ifndef DEEPONION_THEMEADAPTER_H
#define DEEPONION_THEMEADAPTER_H

#include <QString>
#include <QSettings>


class ThemeAdapter
{

public:
    explicit ThemeAdapter();

private:
    QSettings settings;
    QString currentTheme;

public:
    void changeTheme(QString);
    QString getStyleSheet();
    QString getMainMenuPageStyle();
    QString getMainMenuNormalButtonStyle();
    QString getMainMenuSelectedButtonStyle();
    QString getMainMenuDeactivatedButtonStyle();

    QString getCentralWidgetStyle();
    QString getDockMainMenuStyle();

    QString getOverviewNormalBtnIcon();
    QString getOverviewSelectedBtnIcon();
    QString getSendCoinsNormalBtnIcon();
    QString getSendCoinsSelectedBtnIcon();
    QString getReceiveCoinsNormalBtnIcon();
    QString getReceiveCoinsSelectedBtnIcon();
    QString getTransactionsNormalBtnIcon();
    QString getTransactionsSelectedBtnIcon();
    QString getAddressBookNormalBtnIcon();
    QString getAddressBookSelectedBtnIcon();
    QString getMessagesNormalBtnIcon();
    QString getMessagesSelectedBtnIcon();
    QString getExportNormalBtnIcon();
    QString getExportSelectedBtnIcon();

    QString getQFrameGeneralStyle();

    QString getListAlternateRowsGeneralStyle();
    QString getListHeaderGeneralStyle();

    QString getQValidatedLineEditGeneralStyle();
};

#endif //DEEPONION_THEMEADAPTER_H
