//
// Created by arcas on 4/30/2018.
//

#ifndef DEEPONION_THEMEADAPTER_H
#define DEEPONION_THEMEADAPTER_H

#include <QString>
#include <QSettings>

//struct Theme {
//    QString THEME_STYLESHEET;
//};


class ThemeAdapter
{
public:
    static void initThemes();
    static QString getStyleSheetNew();
    static void changeTheme(QString);
    static QString getStyleSheet();
    static QString getMainMenuNormalButtonStyle();
    static QString getMainMenuSelectedButtonStyle();
    static QString getMainMenuDeactivatedButtonStyle();

    static QString getCentralWidgetStyle();
    static QString getDockMainMenuStyle();

    static QString getOverviewNormalBtnIcon();
    static QString getOverviewSelectedBtnIcon();
    static QString getSendCoinsNormalBtnIcon();
    static QString getSendCoinsSelectedBtnIcon();
    static QString getReceiveCoinsNormalBtnIcon();
    static QString getReceiveCoinsSelectedBtnIcon();
    static QString getTransactionsNormalBtnIcon();
    static QString getTransactionsSelectedBtnIcon();
    static QString getAddressBookNormalBtnIcon();
    static QString getAddressBookSelectedBtnIcon();
    static QString getMessagesNormalBtnIcon();
    static QString getMessagesSelectedBtnIcon();
    static QString getExportNormalBtnIcon();
    static QString getExportSelectedBtnIcon();

    static QString getQFrameGeneralStyle();
    static QString getQFrameSecondaryMenuGeneralStyle();

    static QString getQListAlternateRowsGeneralStyle();
    static QString getQListHeaderGeneralStyle();

    static QString getQLabelGeneralStyle();
    static QString getQLineEditGeneralStyle();

    static QString getIconTextButtonStyle();

    static QString getInformationIcon();
    static QString getInformationBtnStyle();

    static QString getQComboboxTransactionsFilteringStyle();
    static QString getQComboboxDateRangeStyle();

    static QString getQToolButtonStyle();
    static QString getQPushButtonStyle();

    static QString getAboutImage();

    static QString getFontBiggerIcon();
    static QString getFontSmallerIcon();

    static QString getTreeWidgetStyle();
};

#endif //DEEPONION_THEMEADAPTER_H
