//
// Created by arcas on 5/18/2018.
//

#ifndef DEEPONION_THEME_THEMEMANAGERX_H
#define DEEPONION_THEME_THEMEMANAGERX_H
#include <iostream>
#include <string>
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
    Theme* current;
    std::map<std::string, Theme*> allThemes;
    std::string defaultTheme;
};


#endif //DEEPONION_THEME_THEMEMANAGERX_H
