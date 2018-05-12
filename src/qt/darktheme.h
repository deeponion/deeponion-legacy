//
// Created by arcas on 4/30/2018.
//

#ifndef DEEPONION_DARKTHEME_H
#define DEEPONION_DARKTHEME_H

#include <QString>

    static QString DARK_THEME_STYLESHEET = "QComboBox {color: white; background-color: #2A2937;} \
        QComboBox:hover {background-color: #1b202f;} \
		QWidget {color:white; background-color: #2B2B37;} \
		QMenu {color: white; background-color: #2A2937; border-color: #2A2937;} \
        QMainWindow {background-color: #393947; border:none;font-family:'Helvetica Neue';} \
		QTableView {color:white;} \
		QHeaderView::section {color:white; background-color: #F7F7F7; } \
		QPlainTextEdit {color: white; background-color: #2b2b37; selection-background-color: #d7e6ff; font-size: 13px; font-family: 'Helvetica Neue';} \
		QLineEdit {color: #FFFFFF; background-color: #2b2b37; padding-left: 5px;  border: none; selection-background-color: #d7e6ff; font-size: 13px; font-family: 'Helvetica Neue';} \
        QTabWidget {color:white; background-color: #2B2B37;} \
		QTabWidget::pane {color:white; background-color: #2B2B37; border: 1px solid #393947;} \
		QTabBar::tab {color:white; background-color: #2A2937; border: 1px solid #393947; padding: 3px; border-top-left-radius: 4px; border-top-right-radius: 4px;} \
		QTabBar::tab:selected, QTabBar::tab:hover {background-color: #1b202f;} \
		QDialog {color:white; background-color: #2B2B37;} \
		QLabel {color:white; background-color: #2B2B37; font-family:'Helvetica Neue';} \
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
		QTreeView { color: white; background-color:#393947; alternate-background-color: #538cc6;} \
		QTreeView::item {color: white; background-color: #393947; border: 1px solid #393947;} \
		QTreeView::item:hover {color: white; background-color: #79a6d2; border: 1px solid #393947;} \
		QToolButton {color:white; background-color: #1b202f; padding: 3px;} \
		QDialogButtonBox {color:white; background-color: #1b202f; padding: 3px;} \
		QMenuBar {background-color: #2A2937;} \
		QToolTip {color: white; border: 0px; background-color: #2A2937; opacity: 225;} \
		QMenuBar::item {color: white; background-color: #2A2937;} \
		QMenuBar::item:selected {color: white; font-weight: bold; background-color: #2A2937;}\
        QPushButton {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #2b2b37; color: #e9e8e8; padding: 8px}\
        QPushButton:pressed {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #22222b; color: #e9e8e8}\
        QPushButton:hover {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #22222b; color: #e9e8e8}\
        QStatusBar::item { border: 0px}\
        QProgressBar::chunk { background-color:#3dc28b;}";

    static QString DT_MAIN_MENU_PAGE_STYLE = "border-style: none; background-color: blue;";
    static QString DT_MAIN_MENU_NORMAL_BUTTON_STYLE = "border:0; height: 60px;padding-left: 15px;text-align:left;color: white;background-color: #393947";
    static QString DT_MAIN_MENU_SELECTED_BUTTON_STYLE = "border:0; height: 60px;padding-left: 15px;text-align:left;color: white;background-color: #486EBA";
    static QString DT_MAIN_MENU_DEACTIVATED_BUTTON_STYLE = "border:0; height: 60px;padding-left: 15px;text-align:left;color: #787878;background-color: #393947";
    static QString DT_CENTRAL_WIDGET_STYLE = "background: #2B2B37";
    static QString DT_DOCK_MAIN_MENU_STYLE = "border: 0; background: #393947";

    static QString DT_MAIN_MENU_OVERVIEW_BTN_ICO = ":/icons/NewOverviewS";
    static QString DT_MAIN_MENU_SENDCOINS_BTN_ICO = ":/icons/NewSendCoinsS";
    static QString DT_MAIN_MENU_RECEIVECOINS_BTN_ICO = ":/icons/NewReceiveCoinsS";
    static QString DT_MAIN_MENU_TRANSACTIONS_BTN_ICO = ":/icons/NewTransactionsS";
    static QString DT_MAIN_MENU_ADDRESSBOOK_BTN_ICO = ":/icons/NewAddressBookS";
    static QString DT_MAIN_MENU_MESSAGES_BTN_ICO = ":/icons/NewMessagesS";
    static QString DT_MAIN_MENU_EXPORT_BTN_ICO = ":/icons/NewExportUS";

    static QString DT_QFRAME_GENERAL_STYLE = "background-color: #393947;";
    static QString DT_LIST_ALTERNATE_GENERAL_STYLE = "alternate-background-color: #474757; background-color: #393947;\
            border: none; margin: 0; padding: 0;";
    static QString DT_LIST_HEADER_GENERAL_STYLE = "QHeaderView::section {background-color: #486EBA; color: #FFFFFF; border: none; \
                                                                        font-size: 14px; font-family: Helvetica Neue; \
                                                                        padding-left: 8px; padding-right: 8px; \
                                                                        padding-top: 14px; padding-bottom: 14px;}";

    static QString DT_QVALIDATED_LINE_EDIT = "QValidatedLineEdit {background-color: #2b2b37; color: #FFFFFF; padding-left: 5px; font-family: 'Helvetica Neue';}";

#endif //DEEPONION_DARKTHEME_H
