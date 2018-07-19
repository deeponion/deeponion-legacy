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
    std::string currentTheme = settings.value("theme", QString::fromStdString(defaultTheme)).toString().toStdString();
    
    if(allThemes.find(currentTheme) != allThemes.end())
    	current = allThemes[currentTheme];
    else
    	current = allThemes[defaultTheme];
}

void ThemeManager::switchTheme(QString newTypeS)
{
	std::string newType = newTypeS.toStdString();
    if(allThemes.find(newType) != allThemes.end())
    	current = allThemes[newType];
    else
    	current = allThemes[defaultTheme];
}

Theme* ThemeManager::getCurrent() {
    return current;
}

