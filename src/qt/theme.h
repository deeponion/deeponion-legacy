//
// Created by arcas on 5/18/2018.
//

#ifndef DEEPONION_THEME_THEME_H
#define DEEPONION_THEME_THEME_H

#include <QString>

class Theme {
public:
    void init(int type);
    QString getStyleSheet();

private:
    QString themeStyleSheet;
};


#endif //DEEPONION_THEME_THEME_H
