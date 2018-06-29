//
// Created by arcas on 5/18/2018.
//

#ifndef DEEPONION_THEME_THEME_H
#define DEEPONION_THEME_THEME_H

#include <QString>

class Theme {
public:
	
	enum Screen_Name
	{
	    ORIGINAL_DARK = 0,
	    ORIGINAL_LIGHT = 1
	};
	
    void init(int type);

    const QString getStyleSheet() const;

    const QString getMainMenuNormalButtonStyle() const;

    const QString getMainMenuSelectedButtonStyle() const;

    const QString getMainMenuDeactivatedButtonStyle() const;

    const QString getCentralWidgetStyle() const;

    const QString getQFrameGeneralStyle() const;

    const QString getQFrameSecondaryMenuGeneralStyle() const;

    const QString getQLabelGeneralStyle() const;

    const QString getQTableGeneralStyle() const;

    const QString getQListHeaderGeneralStyle() const;

    const QString getQLineEdit() const;

    const QString getIconTextButtonStyle() const;

    const QString getInformationIco() const;

    const QString getInformationBtnStyle() const;

    const QString getQComboboxTransactionsFilteringStyle() const;

    const QString getQComboboxDateRangeStyle() const;

    const QString getQToolBtnStyle() const;

    const QString getQPushBtnStyle() const;

    const QString getAboutImg() const;

    const QString getFontBiggerIco() const;

    const QString getFontSmallerIco() const;

    const QString getQTreeWidget() const;

    const QString getMainMenuOverviewNormalBtnIco() const;
    const QString getMainMenuSendcoinsNormalBtnIco() const;
    const QString getMainMenuReceiveCoinsNormalBtnIco() const;
    const QString getMainMenuTransactionsNormalBtnIco() const;
    const QString getMainMenuAddressBookNormalBtnIco() const;
    const QString getMainMenuMessagesNormalBtnIco() const;
    const QString getMainMenuExportNormalBtnIco() const;
    const QString getMainMenuUnlockWalletNormalBtnIco() const;
    const QString getMainMenuLockWalletNormalBtnIco() const;

    const QString getMainMenuOverviewSelectedBtnIco() const;
    const QString getMainMenuSendcoinsSelectedBtnIco() const;
    const QString getMainMenuReceiveCoinsSelectedBtnIco() const;
    const QString getMainMenuTransactionsSelectedBtnIco() const;
    const QString getMainMenuAddressBookSelectedBtnIco() const;
    const QString getMainMenuMessagesSelectedBtnIco() const;
    const QString getMainMenuExportSelectedBtnIco() const;
    const QString getMainMenuUnlockWalletSelectedBtnIco() const;
    const QString getMainMenuLockWalletSelectedBtnIco() const;
	const QString getStatusBarBackgroundColor() const;
    const QString getProgressBarStyle() const;

private:
    QString themeStyleSheet;
    QString mainMenuNormalButtonStyle;
    QString mainMenuSelectedButtonStyle;
    QString mainMenuDeactivatedButtonStyle;
    QString centralWidgetStyle;

    QString mainMenuOverviewNormalBtnIco;
    QString mainMenuSendcoinsNormalBtnIco;
    QString mainMenuReceiveCoinsNormalBtnIco;
    QString mainMenuTransactionsNormalBtnIco;
    QString mainMenuAddressBookNormalBtnIco;
    QString mainMenuMessagesNormalBtnIco;
    QString mainMenuExportNormalBtnIco;
    QString mainMenuUnlockWalletNormalBtnIco;
    QString mainMenuLockWalletNormalBtnIco;
    
    QString mainMenuOverviewSelectedBtnIco;
    QString mainMenuSendcoinsSelectedBtnIco;
    QString mainMenuReceiveCoinsSelectedBtnIco;
    QString mainMenuTransactionsSelectedBtnIco;
    QString mainMenuAddressBookSelectedBtnIco;
    QString mainMenuMessagesSelectedBtnIco;
    QString mainMenuExportSelectedBtnIco;
    QString mainMenuUnlockWalletSelectedBtnIco;
    QString mainMenuLockWalletSelectedBtnIco;
    
    QString qFrameGeneralStyle;
    QString qFrameSecondaryMenuGeneralStyle;
    QString qLabelGeneralStyle;
    QString qTableGeneralStyle;
    QString qListHeaderGeneralStyle;
    QString qLineEdit;
    QString iconTextButtonStyle;
    QString informationIco;
    QString informationBtnStyle;
    QString qComboboxTransactionsFilteringStyle;
    QString qComboboxDateRangeStyle;
    QString qToolBtnStyle;
    QString qPushBtnStyle;
    QString aboutImg;
    QString fontBiggerIco;
    QString fontSmallerIco;
    QString qTreeWidget;
	QString statusBarBackgroundColor;
    QString progressBarStyle;
};


#endif //DEEPONION_THEME_THEME_H
