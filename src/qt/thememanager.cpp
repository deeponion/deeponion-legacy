//
// Created by arcas on 5/18/2018.
//

#include <QSettings>
#include "thememanager.h"
#include "themeoriginaldark.h"
#include "themeoriginallight.h"


ThemeManager::ThemeManager()
{
	defaultTheme = THEME_ORIGINAL_DARK;
	
    allThemes[THEME_ORIGINAL_DARK] = new ThemeOriginalDark();
    allThemes[THEME_ORIGINAL_LIGHT] = new ThemeOriginalLight();
}

void ThemeManager::applyCurrentTheme() {
    QSettings settings;
    QString currentTheme = settings.value("theme", defaultTheme).toString();
    
    if(allThemes.find(currentTheme) != allThemes.end())
    	current = allThemes[currentTheme];
    else
    	current = allThemes[defaultTheme];
}

void ThemeManager::switchTheme(QString newTypeS)
{
    if(allThemes.find(newTypeS) != allThemes.end())
    	current = allThemes[newTypeS];
    else
    	current = allThemes[defaultTheme];
}

Theme* ThemeManager::getCurrent() {
    return current;
}

