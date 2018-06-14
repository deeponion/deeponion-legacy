//
// Created by arcas on 5/18/2018.
//

#ifndef DEEPONION_THEME_THEMEMANAGERX_H
#define DEEPONION_THEME_THEMEMANAGERX_H
#include <iostream>
#include <map>
#include "theme.h"
#include <QString>

class ThemeManager {
public:
    ThemeManager();
    void applyCurrentTheme();
    Theme* getCurrent();
    void switchTheme(QString newType);
private:
    int currentType;
    Theme* current;
    std::map<int, Theme*> allThemes;
};


#endif //DEEPONION_THEME_THEMEMANAGERX_H
