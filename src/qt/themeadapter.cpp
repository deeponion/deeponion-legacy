//
// Created by arcas on 4/30/2018.
//

#include "darktheme.h"
#include "lighttheme.h"
#include "themeadapter.h"
#include <iostream>

ThemeAdapter::ThemeAdapter() {
    currentTheme = settings.value("theme", "dark").toString();
}

void ThemeAdapter::changeTheme(QString newTheme) {
    currentTheme = newTheme;
}

QString ThemeAdapter::getStyleSheet() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LIGHT_THEME_STYLESHEET;
    } else {
        return DARK_THEME_STYLESHEET;
    }
}
QString ThemeAdapter::getMainMenuPageStyle() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_MAIN_MENU_PAGE_STYLE;
    } else {
        return DT_MAIN_MENU_PAGE_STYLE;
    }
}

QString ThemeAdapter::getMainMenuNormalButtonStyle() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_MAIN_MENU_NORMAL_BUTTON_STYLE;
    } else {
        return DT_MAIN_MENU_NORMAL_BUTTON_STYLE;
    }
}
QString ThemeAdapter::getMainMenuSelectedButtonStyle(){
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_MAIN_MENU_SELECTED_BUTTON_STYLE;
    } else {
        return DT_MAIN_MENU_SELECTED_BUTTON_STYLE;
    }
}
QString ThemeAdapter::getMainMenuDeactivatedButtonStyle() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_MAIN_MENU_DEACTIVATED_BUTTON_STYLE;
    } else {
        return DT_MAIN_MENU_DEACTIVATED_BUTTON_STYLE;
    }
}

QString ThemeAdapter::getCentralWidgetStyle() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_CENTRAL_WIDGET_STYLE;
    } else {
        return DT_CENTRAL_WIDGET_STYLE;
    }
}

QString ThemeAdapter::getDockMainMenuStyle() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_DOCK_MAIN_MENU_STYLE;
    } else {
        return DT_DOCK_MAIN_MENU_STYLE;
    }
}

QString ThemeAdapter::getOverviewNormalBtnIcon() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_MAIN_MENU_OVERVIEW_BTN_ICO;
    } else {
        return DT_MAIN_MENU_OVERVIEW_BTN_ICO;
    }
}

QString ThemeAdapter::getOverviewSelectedBtnIcon() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_MAIN_MENU_OVERVIEW_S_BTN_ICO;
    } else {
        return DT_MAIN_MENU_OVERVIEW_BTN_ICO;
    }
}

QString ThemeAdapter::getSendCoinsNormalBtnIcon() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_MAIN_MENU_SENDCOINS_BTN_ICO;
    } else {
        return DT_MAIN_MENU_SENDCOINS_BTN_ICO;
    }
}

QString ThemeAdapter::getSendCoinsSelectedBtnIcon() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_MAIN_MENU_SENDCOINS_S_BTN_ICO;
    } else {
        return DT_MAIN_MENU_SENDCOINS_BTN_ICO;
    }
}

QString ThemeAdapter::getReceiveCoinsNormalBtnIcon() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_MAIN_MENU_RECEIVECOINS_BTN_ICO;
    } else {
        return DT_MAIN_MENU_RECEIVECOINS_BTN_ICO;
    }
}

QString ThemeAdapter::getReceiveCoinsSelectedBtnIcon() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_MAIN_MENU_RECEIVECOINS_S_BTN_ICO;
    } else {
        return DT_MAIN_MENU_RECEIVECOINS_BTN_ICO;
    }
}

QString ThemeAdapter::getTransactionsNormalBtnIcon() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_MAIN_MENU_TRANSACTIONS_BTN_ICO;
    } else {
        return DT_MAIN_MENU_TRANSACTIONS_BTN_ICO;
    }
}

QString ThemeAdapter::getTransactionsSelectedBtnIcon() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_MAIN_MENU_TRANSACTIONS_S_BTN_ICO;
    } else {
        return DT_MAIN_MENU_TRANSACTIONS_BTN_ICO;
    }
}

QString ThemeAdapter::getAddressBookNormalBtnIcon() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_MAIN_MENU_ADDRESSBOOK_BTN_ICO;
    } else {
        return DT_MAIN_MENU_ADDRESSBOOK_BTN_ICO;
    }
}

QString ThemeAdapter::getAddressBookSelectedBtnIcon() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_MAIN_MENU_ADDRESSBOOK_S_BTN_ICO;
    } else {
        return DT_MAIN_MENU_ADDRESSBOOK_BTN_ICO;
    }
}

QString ThemeAdapter::getMessagesNormalBtnIcon() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_MAIN_MENU_MESSAGES_BTN_ICO;
    } else {
        return DT_MAIN_MENU_MESSAGES_BTN_ICO;
    }
}

QString ThemeAdapter::getMessagesSelectedBtnIcon() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_MAIN_MENU_MESSAGES_S_BTN_ICO;
    } else {
        return DT_MAIN_MENU_MESSAGES_BTN_ICO;
    }
}

QString ThemeAdapter::getExportNormalBtnIcon() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_MAIN_MENU_EXPORT_BTN_ICO;
    } else {
        return DT_MAIN_MENU_EXPORT_BTN_ICO;
    }
}

QString ThemeAdapter::getExportSelectedBtnIcon() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_MAIN_MENU_EXPORT_S_BTN_ICO;
    } else {
        return DT_MAIN_MENU_EXPORT_BTN_ICO;
    }
}

QString ThemeAdapter::getQFrameGeneralStyle() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_QFRAME_GENERAL_STYLE;
    } else {
        return DT_QFRAME_GENERAL_STYLE;
    }
}

QString getListHeaderAndTextGeneralStyle();

QString ThemeAdapter::getListAlternateRowsGeneralStyle() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_LIST_ALTERNATE_GENERAL_STYLE;
    } else {
        return DT_LIST_ALTERNATE_GENERAL_STYLE;
    }
}

QString ThemeAdapter::getListHeaderGeneralStyle() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_LIST_HEADER_GENERAL_STYLE;
    } else {
        return DT_LIST_HEADER_GENERAL_STYLE;
    }
}

QString ThemeAdapter::getQValidatedLineEditGeneralStyle() {
    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        return LT_QVALIDATED_LINE_EDIT;
    } else {
        return DT_QVALIDATED_LINE_EDIT;
    }
}