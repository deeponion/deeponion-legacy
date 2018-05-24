//
// Created by arcas on 5/18/2018.
//

#include "theme.h"

void Theme::init(int type) {
    switch (type) {
        case 0:
            themeStyleSheet = "QComboBox {color: white; background-color: #2A2937;  height: 26px;} \
                                QComboBox:hover {background-color: #1b202f; height: 26px;} \
                                QWidget {color:white; background-color: #393947;} \
                                QMenu {color: white; background-color: #2A2937; border-color: #2A2937;} \
                                QMenu::item:selected {background-color: #1C1B15;}\
                                QMainWindow {background-color: #393947; border:none;font-family:'Helvetica Neue';} \
                                QTableView {color:white;} \
                                QHeaderView::section {color:white; background-color: #474757; } \
                                QPlainTextEdit {color: white; background-color: #2b2b37; selection-background-color: #79a6d2; font-size: 13px; font-family: 'Helvetica Neue';} \
                                QTextEdit {color: white; background-color: #2b2b37; selection-background-color: #79a6d2; font-size: 13px; font-family: 'Helvetica Neue';} \
                                QLineEdit {background-color: #2b2b37; color: #FFFFFF; selection-background-color: #79a6d2; font-size: 13px; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px;} \
                                QLineEdit:hover {border: 1px solid gray; background-color: #2b2b37; color: #FFFFFF; selection-background-color: #79a6d2; font-size: 13px; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px;} \
                                QTabWidget {color:white; background-color: #393947;} \
                                QTabWidget::pane {color:white; background-color: #393947; border: 1px solid #2b2b37;} \
                                QTabBar::tab {color:white; background-color: #474757; border: 1px solid #393947; padding: 3px; border-top-left-radius: 4px; border-top-right-radius: 4px;} \
                                QTabBar::tab:selected, QTabBar::tab:hover {color:white; background-color: #7272a3; border: 1px solid #393947; padding: 3px; border-top-left-radius: 4px; border-top-right-radius: 4px;} \
                                QDialog {color:white; background-color: #393947;} \
                                QLabel {color:#FFFFFF; background-color: #393947; font-family:'Helvetica Neue';} \
                                QLabel#labelTotalText {color: #898994;}\
                                QLabel#labelTotal {color: #FFFFFF;}\
                                QLabel#labelBalanceText {color: #898994;}\
                                QLabel#labelBalance {color: #FFFFFF;}\
                                QLabel#labelStakeText {color: #898994;}\
                                QLabel#labelStake {color: #FFFFFF;}\
                                QLabel#labelUnconfirmedText {color: #898994;}\
                                QLabel#labelUnconfirmed {color: #FFFFFF;}\
                                QLabel#labelImmatureText {color: #898994;}\
                                QLabel#labelImmature {color: #FFFFFF;}\
                                QToolBar {color:white; background-color: #191921;} \
                                QTreeView { color: #2A2937; background-color:#393947; alternate-background-color: #538cc6;} \
                                QTreeView::item {color: #2A2937; background-color: #393947; border: 1px solid #393947;} \
                                QTreeView::item:hover {color: #2A2937; background-color: #79a6d2; border: 1px solid #393947;} \
                                QToolButton {color:white; background-color: #393947; padding: 3px; border: none;} \
                                QDialogButtonBox {color:white; background-color: #393947; padding: 3px;} \
                                QMenuBar {background-color: #2A2937;} \
                                QToolTip {color: white; border: 0px; background-color: #2A2937; opacity: 225;} \
                                QMenuBar::item {color: white; background-color: #2A2937;} \
                                QMenuBar::item:selected {color: white; font-weight: bold; background-color: #2A2937;}\
                                QPushButton {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #2b2b37; color: #e9e8e8; padding: 8px}\
                                QPushButton:pressed {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #22222b; color: #e9e8e8}\
                                QPushButton:hover {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #22222b; color: #e9e8e8}\
                                QStatusBar::item { border: 0px}\
                                QProgressBar::chunk { background-color:#3dc28b;}\
                                QScrollBar:vertical {border: 2px solid grey;background: #32CC99;height: 15px;margin: 0px 20px 0 20px;}";
            break;
        case 1:
            themeStyleSheet = "QComboBox {color: white; background-color: #2A2937; height: 26px;} \
                                QComboBox:hover {background-color: #FFFFFF; color: #2A2937;  height: 26px;} \
                                QWidget {color: #2A2937; background-color: #F7F7F7;} \
                                QMenu {color: #2A2937; background-color: #F7F7F7; border-color: #F7F7F7;} \
                                QMenu::item:selected{background-color: #6b6b6b;}\
                                QMenuBar {color: #2A2937; background-color: #F7F7F7;} \
                                QMenuBar::item {color: #2A2937; background-color: #F7F7F7;} \
                                QMenuBar::item:hover {color: #2A2940; background-color: #F9F9F9;} \
                                QMenuBar::item:selected {color: #2A2937; font-weight: bold; background-color: #F7F7F7;}\
                                QMainWindow {background-color: #FFFFFF; border:none;font-family:'Helvetica Neue';} \
                                QTableView {color:#565656;} \
                                QHeaderView::section {color:#2A2937; background-color: #d8d8d8; } \
                                QPlainTextEdit {color: #2B2B37; background-color: #D8D8D8; selection-background-color: #79a6d2; font-size: 13px; font-family: 'Helvetica Neue';} \
                                QTextEdit {color: #2B2B37; background-color: #D8D8D8; selection-background-color: #79a6d2; font-size: 13px; font-family: 'Helvetica Neue';} \
                                QLineEdit { background-color: #D8D8D8; color: #2B2B37; selection-background-color: #79a6d2; font-size: 13px; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px;}\
                                QLineEdit:hover {border: 1px solid gray; background-color: #D8D8D8; color: #2B2B37; selection-background-color: #79a6d2; font-size: 13px; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px;}\
                                QTabWidget {color:#2A2937; background-color: #F7F7F7;} \
                                QTabWidget::pane {color:#2A2937; background-color: #F7F7F7; border: 1px solid #393947;} \
                                QTabBar::tab {color: #2A2937; background-color: #D8D8D8; border: 1px solid #393947; padding: 3px; border-top-left-radius: 4px; border-top-right-radius: 4px;} \
                                QTabBar::tab:selected, QTabBar::tab:hover {background-color: #F7F7F7; color: #2A2937} \
                                QDialog {color:#2A2937; background-color: #F7F7F7;} \
                                QLabel {color:#2A2937; background-color: #F7F7F7; font-family:'Helvetica Neue';} \
                                QLabel#labelTotalText {color: #486EBA;}\
                                QLabel#labelTotal {color: #4D4D4D;}\
                                QLabel#labelBalanceText {color: #486EBA;}\
                                QLabel#labelBalance {color: #4D4D4D;}\
                                QLabel#labelStakeText {color: #486EBA;}\
                                QLabel#labelStake {color: #4D4D4D;}\
                                QLabel#labelUnconfirmedText {color: #486EBA;}\
                                QLabel#labelUnconfirmed {color: #4D4D4D;}\
                                QLabel#labelImmatureText {color: #486EBA;}\
                                QLabel#labelImmature {color: #4D4D4D;}\
                                QToolBar {color:white; background-color: #191921;}\
                                QTreeView { color: #2B2B37; background-color:#c2c2ce; alternate-background-color: #538cc6;} \
                                QTreeView::item {color: #2B2B37; background-color: #c2c2ce; border: 1px solid #c2c2ce;} \
                                QTreeView::item:hover {color: #2B2B37; background-color: #79a6d2; border: 1px solid #c2c2ce;} \
                                QToolButton {color:#2A2937; background-color: #F7F7F7; padding: 3px; border: none;} \
                                QDialogButtonBox {color:#2A2937; background-color: #F7F7F7; padding: 3px;} \
                                QToolTip {color: #2A2937; border: 0px; background-color: #F7F7F7; opacity: 225;} \
                                QPushButton {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #F7F7F7; color: #2A2937; padding: 8px}\
                                QPushButton:pressed {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #FFFFFF; color: #486EBA}\
                                QPushButton:hover {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #FFFFFF; color: #486EBA}\
                                QStatusBar::item { border: 0px}\
                                QProgressBar::chunk { background-color:#3dc28b;}\
                                QScrollBar:horizontal {border: 2px solid grey;background: #486EBA; color: white; height: 15px;margin: 0px 20px 0 20px;}";
            break;
    }
}

QString Theme::getStyleSheet() {
    return themeStyleSheet;
}