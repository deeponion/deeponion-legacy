//
// Created by arcas on 5/18/2018.
//

#include <QSettings>
#include "thememanager.h"
#include "themeoriginaldark.h"
#include "themeoriginallight.h"
#include "themefancypurple.h"

ThemeManager::ThemeManager()
{
    defaultTheme = THEME_FANCY_PURPLE;
    // printf(">> def theme = %d\n", defaultTheme);

    allThemes[THEME_ORIGINAL_DARK] = new ThemeOriginalDark();
    allThemes[THEME_ORIGINAL_LIGHT] = new ThemeOriginalLight();
    allThemes[THEME_FANCY_PURPLE] = new ThemeFancyPurple();

    themeTypeToName[THEME_ORIGINAL_DARK] = QString("Original Dark");
    themeTypeToName[THEME_ORIGINAL_LIGHT] = QString("Original Light");
    themeTypeToName[THEME_FANCY_PURPLE] = QString("Fancy Purple");
}

void ThemeManager::applyCurrentTheme() {
    QSettings settings;
    QString currentTheme = settings.value("theme", getThemeName(defaultTheme)).toString();
	// printf(">> currentTheme = %s\n", currentTheme.toStdString().c_str());

    ThemeType currentType = getThemeType(currentTheme);
    if(allThemes.find(currentType) != allThemes.end())
    	current = allThemes[currentType];
    else
    	current = allThemes[defaultTheme];
}

void ThemeManager::switchTheme(QString newTypeS)
{
    // printf(">> newtype = %s\n", newTypeS.toStdString().c_str());
    ThemeType currentType = getThemeType(newTypeS);	
    if(allThemes.find(currentType) != allThemes.end())
    	current = allThemes[currentType];
    else
    	current = allThemes[defaultTheme];
}

Theme* ThemeManager::getCurrent() {
    return current;
}

QString ThemeManager::getThemeName(ThemeType type) {
   QString str = themeTypeToName[defaultTheme];
   if(themeTypeToName.find(type) != themeTypeToName.end())
    	str = themeTypeToName[type];
    
    return str;
}

ThemeType ThemeManager::getThemeType(QString themeName) {
    ThemeType type = defaultTheme;
    std::map<ThemeType, QString>::iterator it;
    for (it = themeTypeToName.begin(); it != themeTypeToName.end(); ++it )
    {
    	if (it->second == themeName)
	{
        	type = it->first;
		break;
	}
    }
    return type;
}
