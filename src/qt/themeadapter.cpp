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