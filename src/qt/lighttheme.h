//
// Created by arcas on 4/30/2018.
//

#ifndef DEEPONION_LIGHTTHEME_H
#define DEEPONION_LIGHTTHEME_H

#include <QString>

    static QString LIGHT_THEME_STYLESHEET = "QComboBox {color: white; background-color: #2A2937;} \
        QComboBox:hover {background-color: #1b202f;} \
		QWidget {color:white; background-color: #2B2B37;} \
		QMenu {color: white; background-color: #2A2937; border-color: #2A2937;} \
        QMainWindow {background-color: #FFFFFF; border:none;font-family:'Helvetica Neue';} \
		QTableView {color:#565656;} \
		QHeaderView::section {color:white; background-color: #F7F7F7; } \
		QPlainTextEdit {color: white; background-color: #2b2b37; selection-background-color: #d7e6ff; font-size: 13px; font-family: Helvetica Neue} \
		QLineEdit {color: white; background-color: #2b2b37; border: none; selection-background-color: #d7e6ff; font-size: 13px; font-family: Helvetica Neue} \
		QTabWidget {color:white; background-color: #2B2B37;} \
		QTabWidget::pane {color:white; background-color: #2B2B37; border: 1px solid #393947;} \
		QTabBar::tab {color:white; background-color: #2A2937; border: 1px solid #393947; padding: 3px; border-top-left-radius: 4px; border-top-right-radius: 4px;} \
		QTabBar::tab:selected, QTabBar::tab:hover {background-color: #1b202f;} \
		QDialog {color:white; background-color: #2B2B37;} \
		QLabel {color:white; background-color: #2B2B37; font-family:'Helvetica Neue';} \
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

    static QString LT_MAIN_MENU_PAGE_STYLE = "border-style: none; background-color: #FFFFFF";
    static QString LT_MAIN_MENU_NORMAL_BUTTON_STYLE = "border:0; height: 60px;padding-left: 15px;text-align:left;color: #486EBA; background-color: #FFFFFF";
    static QString LT_MAIN_MENU_SELECTED_BUTTON_STYLE = "border:0; height: 60px;padding-left: 15px;text-align:left;color: white;background-color: #486EBA";
    static QString LT_MAIN_MENU_DEACTIVATED_BUTTON_STYLE = "border:0; height: 60px;padding-left: 15px;text-align:left;color: #787878;background-color: #FFFFFF";
    static QString LT_CENTRAL_WIDGET_STYLE = "background: #F7F7F7";
    static QString LT_DOCK_MAIN_MENU_STYLE = "border: 0; background: #FFFFFF";

    static QString LT_MAIN_MENU_OVERVIEW_BTN_ICO = ":/icons/overview";
    static QString LT_MAIN_MENU_SENDCOINS_BTN_ICO = ":/icons/send";
    static QString LT_MAIN_MENU_RECEIVECOINS_BTN_ICO = ":/icons/receiving_addresses";
    static QString LT_MAIN_MENU_TRANSACTIONS_BTN_ICO = ":/icons/history";
    static QString LT_MAIN_MENU_ADDRESSBOOK_BTN_ICO = ":/icons/address-book";
    static QString LT_MAIN_MENU_MESSAGES_BTN_ICO = ":/icons/messaging";
    static QString LT_MAIN_MENU_EXPORT_BTN_ICO = ":/icons/export";

    static QString LT_MAIN_MENU_OVERVIEW_S_BTN_ICO = ":/icons/NewOverviewS";
    static QString LT_MAIN_MENU_SENDCOINS_S_BTN_ICO = ":/icons/NewSendCoinsS";
    static QString LT_MAIN_MENU_RECEIVECOINS_S_BTN_ICO = ":/icons/NewReceiveCoinsS";
    static QString LT_MAIN_MENU_TRANSACTIONS_S_BTN_ICO = ":/icons/NewTransactionsS";
    static QString LT_MAIN_MENU_ADDRESSBOOK_S_BTN_ICO = ":/icons/NewAddressBookS";
    static QString LT_MAIN_MENU_MESSAGES_S_BTN_ICO = ":/icons/NewMessagesS";
    static QString LT_MAIN_MENU_EXPORT_S_BTN_ICO = ":/icons/NewExportUS";

    static QString LT_QFRAME_GENERAL_STYLE = "background-color: #FFFFFF;";
    static QString LT_LIST_ALTERNATE_GENERAL_STYLE = "alternate-background-color: #D8D8D8; background-color: #FFFFFF;\
            border: none; margin: 0; padding: 0;";
    static QString LT_LIST_HEADER_GENERAL_STYLE = "QHeaderView::section {background-color: #486EBA; color: #FFFFFF; border: none; \
                                                                        font-size: 14px; font-family: Helvetica Neue; \
                                                                        padding-left: 8px; padding-right: 8px; \
                                                                        padding-top: 14px; padding-bottom: 14px;}";

#endif //DEEPONION_LIGHTTHEME_H
