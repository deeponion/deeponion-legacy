//
// Created by arcas on 4/30/2018.
//

#ifndef DEEPONION_THEMEADAPTER_H
#define DEEPONION_THEMEADAPTER_H

#include <QString>
#include <QSettings>

#include "darktheme.h"
#include "lighttheme.h"


class ThemeAdapter
{

public:
    explicit ThemeAdapter();

private:
    QSettings settings;
    QString currentTheme;

    // ------------------- theme components ----------------------------------------
    QString styleSheet = DARK_THEME_STYLESHEET;

public:
    void changeTheme(QString);
    QString getStyleSheet();
};

#endif //DEEPONION_THEMEADAPTER_H
