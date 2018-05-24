//
// Created by arcas on 5/18/2018.
//

#include "thememanager.h"
#include <QString>

ThemeManager::ThemeManager()
{
    // default use dark
    Theme* t = new Theme();
    t->init(0);
    allThemes[0] = t;
    current = t;
    currentType = 0;

    t = new Theme();
    t->init(1);
    allThemes[1] = t;
}

void ThemeManager::switchTheme(QString newTypeS)
{
    int newType;
    if (newTypeS.compare("light", Qt::CaseSensitive) == 0) {
        newType = 1;
    } else {
        newType = 0;
    }


    if(newType == currentType)
        return;

    currentType = newType;
    current = allThemes.at(newType);
}

Theme* ThemeManager::getCurrent() {
    return current;
}