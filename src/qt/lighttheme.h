//
// Created by arcas on 4/30/2018.
//

#ifndef DEEPONION_LIGHTTHEME_H
#define DEEPONION_LIGHTTHEME_H

#include <QString>

    static QString LIGHT_THEME_STYLESHEET = "QComboBox {color: white; background-color: #2A2937;} \
        QComboBox:hover {background-color: #1b202f;} \
		QWidget {color:white; background-color: #F7F7F7;} \
		QMenu {color: white; background-color: #2A2937; border-color: #2A2937;} \
        QMainWindow {background-color: #393947; border:none;font-family:'Helvetica Neue';} \
		QTableView {color:white; background-color: transparent; alternate-background-color: rgb(50, 50, 50);} \
		QHeaderView::section {color:white; background-color: #F7F7F7; } \
		QPlainTextEdit {color: white; background-color: #F7F7F7; selection-background-color: #d7e6ff; font-size: 13px; font-family: Helvetica Neue} \
		QLineEdit {color: white; background-color: #F7F7F7; border: none; selection-background-color: #d7e6ff; font-size: 13px; font-family: Helvetica Neue} \
		QTabWidget {color:white; background-color: #F7F7F7;} \
		QTabWidget::pane {color:white; background-color: #F7F7F7; border: 1px solid #393947;} \
		QTabBar::tab {color:white; background-color: #2A2937; border: 1px solid #393947; padding: 3px; border-top-left-radius: 4px; border-top-right-radius: 4px;} \
		QTabBar::tab:selected, QTabBar::tab:hover {background-color: #1b202f;} \
		QDialog {color:white; background-color: #F7F7F7;} \
		QLabel {color:white; background-color: #F7F7F7; font-family:'Helvetica Neue';} \
		QToolBar {color:white; background-color: #191921;} \
		QTreeView { color: white; background-color:#393947; alternate-background-color: #538cc6;} \
		QTreeView::item {color: white; background-color: #393947; border: 1px solid #393947;} \
		QTreeView::item:hover {color: white; background-color: #79a6d2; border: 1px solid #393947;} \
		QToolButton {color:white; background-color: #1b202f; padding: 3px;} \
		QDialogButtonBox {color:white; background-color: #1b202f; padding: 3px;} \
		QMenuBar {background-color: #2A2937;} \
		QToolTip {color: white; border: 0px; background-color: #2A2937; opacity: 225;} \
		QMenuBar::item {color: white; background-color: #2A2937;} \
		QMenuBar::item:selected {color: white; font-weight: bold; background-color: #2A2937;}\
        QPushButton {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #F7F7F7; color: #e9e8e8; padding: 8px}\
        QPushButton:pressed {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #22222b; color: #e9e8e8}\
        QPushButton:hover {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #22222b; color: #e9e8e8}\
        QStatusBar::item { border: 0px}\
        QProgressBar::chunk { background-color:#3dc28b;}";

    static QString LT_MAIN_MENU_PAGE_STYLE = "border-style: none; background-color: #FFFFFF";
    static QString LT_MAIN_MENU_NORMAL_BUTTON_STYLE = "border:0; height: 60px;padding-left: 15px;text-align:left;color: #486EBA; background-color: #FFFFFF";
    static QString LT_MAIN_MENU_SELECTED_BUTTON_STYLE = "border:0; height: 60px;padding-left: 15px;text-align:left;color: white;background-color: #486EBA";
    static QString LT_MAIN_MENU_DEACTIVATED_BUTTON_STYLE = "border:0; height: 60px;padding-left: 15px;text-align:left;color: #787878;background-color: #FFFFFF";

#endif //DEEPONION_LIGHTTHEME_H
