//
// Created by arcas on 4/30/2018.
//

#ifndef DEEPONION_DARKTHEME_H
#define DEEPONION_DARKTHEME_H

#include <QString>

    static QString DARK_THEME_STYLESHEET = "QWidget {color:white; background-color: #393947;} \
		QMenu {color: white; background-color: #2A2937; border-color: #2A2937;} \
        QMenu::item:selected {background-color: #1C1B15;}\
        QMainWindow {background-color: #393947; border:none;font-family:'Helvetica Neue';} \
		QHeaderView::section {color:white; background-color: #474757; } \
		QPlainTextEdit {color: white; background-color: #2b2b37; selection-background-color: #79a6d2; font-size: 13px; font-family: 'Helvetica Neue';} \
        QTextEdit {color: white; background-color: #2b2b37; selection-background-color: #79a6d2; font-size: 13px; font-family: 'Helvetica Neue';} \
		QLineEdit {background-color: #2b2b37; color: #FFFFFF; selection-background-color: #79a6d2; font-size: 13px; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px;} \
        QLineEdit:hover {border: 0px solid gray; background-color: #2b2b37; color: #FFFFFF; selection-background-color: #79a6d2; font-size: 13px; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px;} \
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
		QTreeView { color: #FFFFFF; background-color:#393947; alternate-background-color: #538cc6;} \
		QTreeView::item {color: #FFFFFF; background-color: #393947; border: 1px solid #393947;} \
		QTreeView::item:hover {color: #FFFFFF; background-color: #79a6d2; border: 1px solid #393947;} \
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
        QProgressBar::chunk { background-color:#3dc28b;}";

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
    static QString DT_QFRAME_SECONDARY_MENU_GENERAL_STYLE = "background-color: #22222B; padding: 8px;";
    static QString DT_QLABEL_GENERAL_STYLE = "color: #FFFFFF";
    static QString DT_TABLE_GENERAL_STYLE = "QTableView {color: #D5D5D9; alternate-background-color: #474758; background-color: #393848;} \
            QScrollBar:vertical {border: 1px solid #2B2B37; background: #2B2B37; width: 24px; margin: 5px 5px 5px 5px;} \
            QScrollBar::handle:vertical {border-radius: 4px; background: #C1C1C1; min-height: 25px; max-width: 12px; } \
            QScrollBar::add-line:vertical { background: #474758; height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;} \
            QScrollBar::sub-line:vertical { background: #474758; height: 0px; subcontrol-position: top; subcontrol-origin: margin;}";

    static QString DT_LIST_HEADER_GENERAL_STYLE = "QHeaderView::section {background-color: #486EBA; color: #FFFFFF; border: none; \
                                                                        font-size: 14px; font-family: Helvetica Neue; \
                                                                        padding-left: 8px; padding-right: 8px; \
                                                                        padding-top: 14px; padding-bottom: 14px;}";
    static QString DT_LINE_EDIT = "background-color: #2b2b37; color: #FFFFFF; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px;";
    static QString DT_ICON_TEXT_BUTTON_STYLE = "QPushButton, QPushButton:hover {color: #FFFFFF; border: none; background-color: rgba(255, 255, 255, 0);}";

    static QString DT_INFORMATION_ICO = ":/icons/information";
    static QString DT_INFORMATION_BTN_STYLE = "background-color: #393947; border: none";

    static QString DT_QCOMBOBOX_TRANSACTIONS_FILTERING_STYLE = "QComboBox { background-color: #393947; color: #FFFFFF; font-size: 14px; font-family: 'Helvetica Neue';\
                                        padding-left: 8px; padding-top: 14px; padding-bottom: 14px; border: none; }\
                                        QComboBox::drop-down {border: none; background: #486EBA; width: 30px;}\
                                        QComboBox::down-arrow { width: 14px; height: 14px; image: url(:/icons/arrow_down_white);}";
    static QString DT_QCOMBOBOX_DATE_RANGE_STYLE = "background-color: #393947; color: #FFFFFF; font-size: 14px; font-family: 'Helvetica Neue';\
                                        border: none; QComboBox::drop-down {border: none}";
    static QString DT_QTOOL_BTN_STYLE = "{color:white; background-color: #393947; padding: 3px; border: none;}";

    static QString DT_QPUSH_BTN_STYLE = "QPushButton {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #2b2b37; color: #e9e8e8; padding: 8px}\
        QPushButton:pressed {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #22222b; color: #e9e8e8}\
        QPushButton:hover {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #22222b; color: #e9e8e8}";

    static QString DT_ABOUT_IMG = ":/images/about_dark";
    static QString DT_FONTBIGGER_ICO = ":/icons/fontbigger_dark";
    static QString DT_FONTSMALLER_ICO = ":/icons/fontsmaller_dark";

    static QString DT_TREE_WIDGET = "QTreeView { color: #FFFFFF; background-color:#393947; alternate-background-color: #538cc6;} \
		QTreeView::item {color: #FFFFFF; background-color: #393947; border: 1px solid #393947;} \
		QTreeView::item:hover {color: #FFFFFF; background-color: #79a6d2; border: 1px solid #393947;}";

#endif //DEEPONION_DARKTHEME_H
