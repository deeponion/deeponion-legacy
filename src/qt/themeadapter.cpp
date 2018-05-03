//
// Created by arcas on 4/30/2018.
//

#include "themeadapter.h"
#include <iostream>

ThemeAdapter::ThemeAdapter() {
    currentTheme = settings.value("theme", "dark").toString();
}

void ThemeAdapter::changeTheme(QString newTheme) {
    currentTheme = newTheme;
    if (currentTheme.compare("ligth", Qt::CaseSensitive) == 0) {
        styleSheet = LIGHT_THEME_STYLESHEET;
    } else {
        styleSheet = DARK_THEME_STYLESHEET;
    }
}

QString ThemeAdapter::getStyleSheet() {
    return styleSheet;
}