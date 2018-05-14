//
// Created by arcas on 4/30/2018.
//

#ifndef DEEPONION_LIGHTTHEME_H
#define DEEPONION_LIGHTTHEME_H

#include <QString>

    static QString LIGHT_THEME_STYLESHEET = "QComboBox {color: white; background-color: #2A2937;} \
        QComboBox:hover {background-color: #FFFFFF; color: #2A2937} \
		QWidget {color: #2A2937; background-color: #F7F7F7;} \
		QMenu {color: #2A2937; background-color: #F7F7F7; border-color: #F7F7F7;} \
        QMenuBar {color: #2A2937; background-color: #F7F7F7;} \
        QMenuBar::item {color: #2A2937; background-color: #F7F7F7;} \
        QMenuBar::item:hover {color: #2A2940; background-color: #F9F9F9;} \
        QMenuBar::item:selected {color: #2A2937; font-weight: bold; background-color: #F7F7F7;}\
        QMainWindow {background-color: #FFFFFF; border:none;font-family:'Helvetica Neue';} \
		QTableView {color:#565656;} \
		QHeaderView::section {color:white; background-color: #F7F7F7; } \
		QPlainTextEdit {color: #2B2B37; background-color: #D8D8D8; selection-background-color: #d7e6ff; font-size: 13px; font-family: 'Helvetica Neue';} \
		QLineEdit {color: #2B2B37; background-color: #D8D8D8; padding-left: 5px;  border: none; selection-background-color: #d7e6ff; font-size: 13px; font-family: 'Helvetica Neue';} \
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
		QTreeView { color: white; background-color:#393947; alternate-background-color: #538cc6;} \
		QTreeView::item {color: white; background-color: #393947; border: 1px solid #393947;} \
		QTreeView::item:hover {color: white; background-color: #79a6d2; border: 1px solid #393947;} \
		QToolButton {color:#2A2937; background-color: #F7F7F7; padding: 3px;} \
		QDialogButtonBox {color:#2A2937; background-color: #F7F7F7; padding: 3px;} \
		QToolTip {color: #2A2937; border: 0px; background-color: #F7F7F7; opacity: 225;} \
        QPushButton {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #F7F7F7; color: #2A2937; padding: 8px}\
        QPushButton:pressed {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #FFFFFF; color: #486EBA}\
        QPushButton:hover {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #FFFFFF; color: #486EBA}\
        QStatusBar::item { border: 0px}\
        QProgressBar::chunk { background-color:#3dc28b;}\
        QScrollBar:horizontal {border: 2px solid grey;background: #486EBA; color: white; height: 15px;margin: 0px 20px 0 20px;}";

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
    static QString LT_QFRAME_SECONDARY_MENU_GENERAL_STYLE = "background-color: #D8D8D8; padding: 8px;";
    static QString LT_QLABEL_GENERAL_STYLE = "color: #486EBA";
    static QString LT_LIST_ALTERNATE_GENERAL_STYLE = "alternate-background-color: #D8D8D8; background-color: #FFFFFF;\
            border: none; margin: 0; padding: 0;";
    static QString LT_LIST_HEADER_GENERAL_STYLE = "QHeaderView::section {background-color: #486EBA; color: #FFFFFF; border: none; \
                                                                        font-size: 14px; font-family: Helvetica Neue; \
                                                                        padding-left: 8px; padding-right: 8px; \
                                                                        padding-top: 14px; padding-bottom: 14px;}";
    static QString LT_LINE_EDIT = "background-color: #D8D8D8; color: #2B2B37; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px;";
    static QString LT_ICON_TEXT_BUTTON_STYLE = "QPushButton, QPushButton:hover {color: #486EBA; border: none; background-color: rgba(255, 255, 255, 10);} ";

    static QString LT_INFORMATION_ICO = ":/icons/information-blue";
    static QString LT_INFORMATION_BTN_STYLE = "background-color: #FFFFFF; border: none";

    static QString LT_QCOMBOBOX_TRANSACTIONS_FILTERING_STYLE = "background-color: #FFFFFF; color: #486EBA; font-size: 12px; font-family: 'Helvetica Neue';\
                                        padding-left: 8px; padding-top: 14px; padding-bottom: 14px; border: none;\
                                        QComboBox::drop-down {border: none}";
    static QString LT_QCOMBOBOX_DATE_RANGE_STYLE = "background-color: #FFFFFF; color: #486EBA; font-size: 12px; font-family: 'Helvetica Neue';\
                                        border: none; QComboBox::drop-down {border: none}";


#endif //DEEPONION_LIGHTTHEME_H
