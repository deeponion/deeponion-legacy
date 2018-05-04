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

public:
    void changeTheme(QString);
    QString getStyleSheet();
    QString getMainMenuPageStyle();
    QString getMainMenuNormalButtonStyle();
    QString getMainMenuSelectedButtonStyle();
    QString getMainMenuDeactivatedButtonStyle();
};

#endif //DEEPONION_THEMEADAPTER_H
