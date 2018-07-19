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

enum ThemeType
{
	THEME_ORIGINAL_DARK = 1,
	THEME_ORIGINAL_LIGHT = 2,
	THEME_FANCY_PURPLE = 3
};


class ThemeManager {
public:
    ThemeManager();
    void applyCurrentTheme();
    Theme* getCurrent();
    void switchTheme(QString newType);
    QString getThemeName(ThemeType type);
    ThemeType getThemeType(QString themeName);
    
private:
    Theme* current;
    std::map<ThemeType, Theme*> allThemes;
    ThemeType defaultTheme;
    std::map<ThemeType, QString> themeTypeToName;
};


#endif //DEEPONION_THEME_THEMEMANAGERX_H
