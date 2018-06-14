//
// Created by arcas on 5/18/2018.
//

#include "thememanager.h"
#include <QString>
#include <QSettings>

ThemeManager::ThemeManager()
{

    // Dark Theme
    Theme* t = new Theme();
    t->init(0);
    allThemes[0] = t;


    // Light Theme
    t = new Theme();
    t->init(1);
    allThemes[1] = t;

}

void ThemeManager::applyCurrentTheme() {
    QSettings settings;
    QString currentTheme = settings.value("theme", "dark").toString();

    if (currentTheme.compare("light", Qt::CaseSensitive) == 0) {
        current = allThemes[1];
        currentType = 1;
    } else {
        current = allThemes[0];
        currentType = 0;
    }
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