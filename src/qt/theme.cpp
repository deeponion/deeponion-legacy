//
// Created by arcas on 5/18/2018.
//

#include "theme.h"

void Theme::init(int type) {
    switch (type) {
    
        case ORIGINAL_DARK:
        	
            themeStyleSheet = "QWidget {color:white; background-color: #393947;} \
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
                                QToolBar {color:white; background-color: #191921; width: 192px;} \
                                QToolBar QToolButton {width:180px; height:40px; font-family:'Helvetica Neue'; font-size:12px; border:1px solid #65676b; background-color:#2b2b37; color:#e9e8e8; padding:8px;} \
                                QToolBar QToolButton:hover {background-color: #001100; color: #e9e8e8;} \
                                QToolBar QToolButton:pressed {background-color: #110000; color: #e9e8e8;} \
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
                                QProgressBar::chunk { background-color:#3dc28b;}\
                                QTableView {color: #D5D5D9; alternate-background-color: #474758; background-color: #393848;}\
                                QScrollBar:vertical {border: 1px solid #2B2B37; background: #2B2B37; width: 24px; margin: 5px 5px 5px 5px;}\
                                QScrollBar::handle:vertical {border-radius: 4px; background: #C1C1C1; min-height: 25px; max-width: 12px; }\
                                QScrollBar::add-line:vertical { background: #474758; height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;}\
                                QScrollBar::sub-line:vertical { background: #474758; height: 0px; subcontrol-position: top; subcontrol-origin: margin;}\
                                QScrollBar:horizontal {border: 1px solid #2B2B37; background: #2B2B37; width: 24px; margin: 5px 5px 5px 5px;}\
                                QScrollBar::handle:horizontal {border-radius: 4px; background: #C1C1C1; min-height: 25px; max-width: 12px; }\
                                QScrollBar::add-line:horizontal { background: #474758; height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;}\
                                QScrollBar::sub-line:horizontal { background: #474758; height: 0px; subcontrol-position: top; subcontrol-origin: margin;}";
            
            mainMenuNormalButtonStyle = "border:0; height:40px; padding-left:15px; text-align:left; color:white; background-color: #393947";
            mainMenuSelectedButtonStyle = "border:0; height:40px; padding-left:15px; text-align:left; color:white; background-color: #486EBA";
            mainMenuDeactivatedButtonStyle = "border:0; height:40px; padding-left:15px; text-align:left; color:#787878; background-color: #393947";
            centralWidgetStyle = "background: #2B2B37";
             
            mainMenuOverviewNormalBtnIco = ":/icons/NewOverviewS";
            mainMenuSendcoinsNormalBtnIco = ":/icons/NewSendCoinsS";
            mainMenuReceiveCoinsNormalBtnIco = ":/icons/NewReceiveCoinsS";
            mainMenuTransactionsNormalBtnIco = ":/icons/NewTransactionsS";
            mainMenuAddressBookNormalBtnIco = ":/icons/NewAddressBookS";
            mainMenuMessagesNormalBtnIco = ":/icons/NewMessagesS";
            mainMenuExportNormalBtnIco = ":/icons/NewExportUS";
            mainMenuUnlockWalletNormalBtnIco = ":/icons/new_lock_open_s";
            mainMenuLockWalletNormalBtnIco = ":/icons/new_lock_closed_s";
            
            mainMenuOverviewSelectedBtnIco = ":/icons/NewOverviewS";
            mainMenuSendcoinsSelectedBtnIco = ":/icons/NewSendCoinsS";
            mainMenuReceiveCoinsSelectedBtnIco = ":/icons/NewReceiveCoinsS";
            mainMenuTransactionsSelectedBtnIco = ":/icons/NewTransactionsS";
            mainMenuAddressBookSelectedBtnIco = ":/icons/NewAddressBookS";
            mainMenuMessagesSelectedBtnIco = ":/icons/NewMessagesS";
            mainMenuExportSelectedBtnIco = ":/icons/NewExportUS";
            mainMenuUnlockWalletSelectedBtnIco = ":/icons/new_lock_open_s";
            mainMenuLockWalletSelectedBtnIco = ":/icons/new_lock_closed_s";
            
            qFrameGeneralStyle = "background-color: #393947;";
            qFrameSecondaryMenuGeneralStyle = "background-color: #22222B; padding: 8px;";
            qLabelGeneralStyle = "color: #FFFFFF";
            qTableGeneralStyle = "QTableView {color: #D5D5D9; alternate-background-color: #474758; background-color: #393848;} \
                                QScrollBar:vertical {border: 1px solid #2B2B37; background: #2B2B37; width: 24px; margin: 5px 5px 5px 5px;} \
                                QScrollBar::handle:vertical {border-radius: 4px; background: #C1C1C1; min-height: 25px; max-width: 12px; } \
                                QScrollBar::add-line:vertical { background: #474758; height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;} \
                                QScrollBar::sub-line:vertical { background: #474758; height: 0px; subcontrol-position: top; subcontrol-origin: margin;}";
            qListHeaderGeneralStyle = "QHeaderView::section {background-color: #486EBA; color: #FFFFFF; border: none; \
                                font-size: 14px; font-family: Helvetica Neue; \
                                padding-left: 8px; padding-right: 8px; \
                                padding-top: 14px; padding-bottom: 14px;}";
            qLineEdit = "background-color: #2b2b37; color: #FFFFFF; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px;";
            iconTextButtonStyle = "QPushButton, QPushButton:hover {color: #FFFFFF; border: none; background-color: rgba(255, 255, 255, 0);}";
            informationIco = ":/icons/information";
            informationBtnStyle = "background-color: #393947; border: none";
            qComboboxTransactionsFilteringStyle = "QComboBox { background-color: #393947; color: #FFFFFF; font-size: 14px; font-family: 'Helvetica Neue';\
                                padding-left: 8px; padding-top: 14px; padding-bottom: 14px; border: none; }\
                                QComboBox::drop-down {border: none; background: #486EBA; width: 30px;}\
                                QComboBox::down-arrow { width: 14px; height: 14px; image: url(:/icons/arrow_down_white);}";
            qComboboxDateRangeStyle = "background-color: #393947; color: #FFFFFF; font-size: 14px; font-family: 'Helvetica Neue';\
                                border: none; QComboBox::drop-down {border: none}";
            qToolBtnStyle = "{color:white; background-color: #393947; padding: 3px; border: none;}";
            qPushBtnStyle = "QPushButton {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #2b2b37; color: #e9e8e8; padding: 8px}\
                                QPushButton:pressed {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #22222b; color: #e9e8e8}\
                                QPushButton:hover {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #22222b; color: #e9e8e8}";
            aboutImg = ":/images/about_dark";
            fontBiggerIco = ":/icons/fontbigger_dark";
            fontSmallerIco = ":/icons/fontsmaller_dark";
            qTreeWidget = "QTreeView { color: #FFFFFF; background-color:#393947; alternate-background-color: #538cc6;} \
                                QTreeView::item {color: #FFFFFF; background-color: #393947; border: 1px solid #393947;} \
                                QTreeView::item:hover {color: #FFFFFF; background-color: #79a6d2; border: 1px solid #393947;}";
            break;
            
        case ORIGINAL_LIGHT:
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
                                QHeaderView::section {color:#2A2937; background-color: #d8d8d8; } \
                                QPlainTextEdit {color: #2B2B37; background-color: #D8D8D8; selection-background-color: #79a6d2; font-size: 13px; font-family: 'Helvetica Neue';} \
                                QTextEdit {color: #2B2B37; background-color: #D8D8D8; selection-background-color: #79a6d2; font-size: 13px; font-family: 'Helvetica Neue';} \
                                QLineEdit { background-color: #F7F7F7; color: #2B2B37; selection-background-color: #79a6d2; font-size: 13px; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px; border: 0px;}\
                                QLineEdit:hover {border: 0px solid d3d3d3; background-color: #F7F7F7; color: #2B2B37; selection-background-color: #79a6d2; font-size: 13px; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px;}\
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
                                QToolBar {color:white; background-color: #191921; width: 192px;}\
                                QToolBar QToolButton {width: 180px; height: 40px; font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #F7F7F7; color: #2A2937; padding: 8px;} \
                                QToolBar QToolButton:hover {background-color: #001100; color: #e9e8e8;} \
                                QToolBar QToolButton:pressed {background-color: #110000; color: #e9e8e8;} \
                                QTreeView { color: #2B2B37; background-color:#c2c2ce; alternate-background-color: #538cc6;} \
                                QTreeView::item {color: #2B2B37; background-color: #c2c2ce; border: 1px solid #c2c2ce;} \
                                QTreeView::item:hover {color: #2B2B37; background-color: #79a6d2; border: 1px solid #c2c2ce;} \
                                QToolButton {color:#2A2937; background-color: #F7F7F7; padding: 3px; border: none;} \
                                QDialogButtonBox {color:#2A2937; background-color: #F7F7F7; padding: 3px;} \
                                QToolTip {color: #2A2937; border: 0px; background-color: #F7F7F7; opacity: 225;} \
                                QPushButton {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #F7F7F7; color: #2A2937; padding: 8px;}\
                                QPushButton:pressed {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #FFFFFF; color: #486EBA;}\
                                QPushButton:hover {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #FFFFFF; color: #486EBA;}\
                                QStatusBar::item { border: 0px}\
                                QProgressBar::chunk { background-color:#3dc28b;}\
                                QTableView {color: #565656; alternate-background-color: #D8D8D8; background-color: #FFFFFF;} \
                                QScrollBar:vertical {border: 1px solid #FFFFFF; background: rgba(255, 255, 255, 0%); width: 24px; margin: 5px 5px 5px 5px;} \
                                QScrollBar::handle:vertical {border-radius: 4px; background: #C1C1C1; min-height: 25px; max-width: 12px; } \
                                QScrollBar::add-line:vertical { background: #D8D8D8; height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;} \
                                QScrollBar::sub-line:vertical { background: #D8D8D8; height: 0px; subcontrol-position: top; subcontrol-origin: margin;}\
                                QScrollBar:horizontal {border: 1px solid #FFFFFF; background: rgba(255, 255, 255, 0%); width: 24px; margin: 5px 5px 5px 5px;} \
                                QScrollBar::handle:horizontal {border-radius: 4px; background: #C1C1C1; min-height: 25px; max-width: 12px; } \
                                QScrollBar::add-line:horizontal { background: #D8D8D8; height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;} \
                                QScrollBar::sub-line:horizontal { background: #D8D8D8; height: 0px; subcontrol-position: top; subcontrol-origin: margin;}";

            mainMenuNormalButtonStyle = "border:0; height:40px; padding-left: 15px;text-align:left; color:#486EBA; background-color: #FFFFFF";
            mainMenuSelectedButtonStyle = "border:0; height:40px; padding-left: 15px;text-align:left; color:white; background-color: #486EBA";
            mainMenuDeactivatedButtonStyle = "border:0; height: 60px;padding-left: 15px;text-align:left;color: #787878;background-color: #FFFFFF";
            centralWidgetStyle = "background: #F7F7F7";

            mainMenuOverviewNormalBtnIco = ":/icons/overview";
            mainMenuSendcoinsNormalBtnIco = ":/icons/send";
            mainMenuReceiveCoinsNormalBtnIco = ":/icons/receiving_addresses";
            mainMenuTransactionsNormalBtnIco = ":/icons/history";
            mainMenuAddressBookNormalBtnIco = ":/icons/address-book";
            mainMenuMessagesNormalBtnIco = ":/icons/messaging";
            mainMenuExportNormalBtnIco = ":/icons/export";
            mainMenuUnlockWalletNormalBtnIco = ":/icons/new_lock_open";
            mainMenuLockWalletNormalBtnIco = ":/icons/new_lock_closed";
            
            mainMenuOverviewSelectedBtnIco = ":/icons/overview";
            mainMenuSendcoinsSelectedBtnIco = ":/icons/send";
            mainMenuReceiveCoinsSelectedBtnIco = ":/icons/receiving_addresses";
            mainMenuTransactionsSelectedBtnIco = ":/icons/history";
            mainMenuAddressBookSelectedBtnIco = ":/icons/address-book";
            mainMenuMessagesSelectedBtnIco = ":/icons/messaging";
            mainMenuExportSelectedBtnIco = ":/icons/export";
            mainMenuUnlockWalletSelectedBtnIco = ":/icons/new_lock_open";
            mainMenuLockWalletSelectedBtnIco = ":/icons/new_lock_closed";
            
            qFrameGeneralStyle = "background-color: #FFFFFF;";
            qFrameSecondaryMenuGeneralStyle = "background-color: #DFE9F7; padding: 8px;";
            qLabelGeneralStyle = "color: #486EBA";
            qTableGeneralStyle = "QTableView {color: #565656; alternate-background-color: #D8D8D8; background-color: #FFFFFF;} \
                                QScrollBar:vertical {border: 1px solid #FFFFFF; background: rgba(255, 255, 255, 0%); width: 24px; margin: 5px 5px 5px 5px;} \
                                QScrollBar::handle:vertical {border-radius: 4px; background: #C1C1C1; min-height: 25px; max-width: 12px; } \
                                QScrollBar::add-line:vertical { background: #D8D8D8; height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;} \
                                QScrollBar::sub-line:vertical { background: #D8D8D8; height: 0px; subcontrol-position: top; subcontrol-origin: margin;}";
            qListHeaderGeneralStyle = "QHeaderView::section {background-color: #486EBA; color: #FFFFFF; border: none; \
                                font-size: 14px; font-family: Helvetica Neue; \
                                padding-left: 8px; padding-right: 8px; \
                                padding-top: 14px; padding-bottom: 14px;}";
            qLineEdit = "background-color: #F7F7F7; color: #2B2B37; selection-background-color: #d7e6ff; font-size: 13px; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px;";
            iconTextButtonStyle = "QPushButton, QPushButton:hover {color: #486EBA; border: none; background-color: rgba(255, 255, 255, 10);}";
            informationIco = ":/icons/information-blue";
            informationBtnStyle = "background-color: #FFFFFF; border: none";
            qComboboxTransactionsFilteringStyle = "QComboBox { background-color: #FFFFFF; color: #486EBA; font-size: 14px; font-family: 'Helvetica Neue';\
                                padding-left: 8px; padding-top: 14px; padding-bottom: 14px; border: none; }\
                                QComboBox::drop-down {border: none; background: #486EBA; width: 30px;}\
                                QComboBox::down-arrow { width: 14px; height: 14px; image: url(:/icons/arrow_down_white);}";
            qComboboxDateRangeStyle = "background-color: #FFFFFF; color: #486EBA; font-size: 12px; font-family: 'Helvetica Neue';\
                                border: none; QComboBox::drop-down {border: none}";
            qToolBtnStyle = "{color:#2A2937; background-color: #F7F7F7; padding: 3px; border: none;}";
            qPushBtnStyle = "QPushButton {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #F7F7F7; color: #2A2937; padding: 8px}\
                                QPushButton:pressed {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #FFFFFF; color: #486EBA}\
                                QPushButton:hover {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #FFFFFF; color: #486EBA}";
            aboutImg = ":/images/about_light";
            fontBiggerIco = ":/icons/fontbigger_light";
            fontSmallerIco = ":/icons/fontsmaller_light";
            qTreeWidget = "QTreeView { color: #2B2B37; background-color:#c2c2ce; alternate-background-color: #538cc6;} \
                                QTreeView::item {color: #2B2B37; background-color: #c2c2ce; border: 1px solid #c2c2ce;} \
                                QTreeView::item:hover {color: #2B2B37; background-color: #79a6d2; border: 1px solid #c2c2ce;}";
            break;
    }
}

const QString Theme::getStyleSheet() const {
    return themeStyleSheet;
}

const QString Theme::getMainMenuNormalButtonStyle() const {
    return mainMenuNormalButtonStyle;
}

const QString Theme::getMainMenuSelectedButtonStyle() const {
    return mainMenuSelectedButtonStyle;
}

const QString Theme::getMainMenuDeactivatedButtonStyle() const {
    return mainMenuDeactivatedButtonStyle;
}

const QString Theme::getCentralWidgetStyle() const {
    return centralWidgetStyle;
}

const QString Theme::getQFrameGeneralStyle() const {
    return qFrameGeneralStyle;
}

const QString Theme::getQFrameSecondaryMenuGeneralStyle() const {
    return qFrameSecondaryMenuGeneralStyle;
}

const QString Theme::getQLabelGeneralStyle() const {
    return qLabelGeneralStyle;
}

const QString Theme::getQTableGeneralStyle() const {
    return qTableGeneralStyle;
}

const QString Theme::getQListHeaderGeneralStyle() const {
    return qListHeaderGeneralStyle;
}

const QString Theme::getQLineEdit() const {
    return qLineEdit;
}

const QString Theme::getIconTextButtonStyle() const {
    return iconTextButtonStyle;
}

const QString Theme::getInformationIco() const {
    return informationIco;
}

const QString Theme::getInformationBtnStyle() const {
    return informationBtnStyle;
}

const QString Theme::getQComboboxTransactionsFilteringStyle() const {
    return qComboboxTransactionsFilteringStyle;
}

const QString Theme::getQComboboxDateRangeStyle() const {
    return qComboboxDateRangeStyle;
}

const QString Theme::getQToolBtnStyle() const {
    return qToolBtnStyle;
}

const QString Theme::getQPushBtnStyle() const {
    return qPushBtnStyle;
}

const QString Theme::getAboutImg() const {
    return aboutImg;
}

const QString Theme::getFontBiggerIco() const {
    return fontBiggerIco;
}

const QString Theme::getFontSmallerIco() const {
    return fontSmallerIco;
}

const QString Theme::getQTreeWidget() const {
    return qTreeWidget;
}


const QString Theme::getMainMenuOverviewNormalBtnIco() const {
    return mainMenuOverviewNormalBtnIco;
}

const QString Theme::getMainMenuSendcoinsNormalBtnIco() const {
    return mainMenuSendcoinsNormalBtnIco;
}

const QString Theme::getMainMenuReceiveCoinsNormalBtnIco() const {
    return mainMenuReceiveCoinsNormalBtnIco;
}

const QString Theme::getMainMenuTransactionsNormalBtnIco() const {
    return mainMenuTransactionsNormalBtnIco;
}

const QString Theme::getMainMenuAddressBookNormalBtnIco() const {
    return mainMenuAddressBookNormalBtnIco;
}

const QString Theme::getMainMenuMessagesNormalBtnIco() const {
    return mainMenuMessagesNormalBtnIco;
}

const QString Theme::getMainMenuExportNormalBtnIco() const {
    return mainMenuExportNormalBtnIco;
}

const QString Theme::getMainMenuUnlockWalletNormalBtnIco() const {
    return mainMenuUnlockWalletNormalBtnIco;
}

const QString Theme::getMainMenuLockWalletNormalBtnIco() const {
    return mainMenuLockWalletNormalBtnIco;
}


const QString Theme::getMainMenuOverviewSelectedBtnIco() const {
    return mainMenuOverviewSelectedBtnIco;
}

const QString Theme::getMainMenuSendcoinsSelectedBtnIco() const {
    return mainMenuSendcoinsSelectedBtnIco;
}

const QString Theme::getMainMenuReceiveCoinsSelectedBtnIco() const {
    return mainMenuReceiveCoinsSelectedBtnIco;
}

const QString Theme::getMainMenuTransactionsSelectedBtnIco() const {
    return mainMenuTransactionsSelectedBtnIco;
}

const QString Theme::getMainMenuAddressBookSelectedBtnIco() const {
    return mainMenuAddressBookSelectedBtnIco;
}

const QString Theme::getMainMenuMessagesSelectedBtnIco() const {
    return mainMenuMessagesSelectedBtnIco;
}

const QString Theme::getMainMenuExportSelectedBtnIco() const {
    return mainMenuExportSelectedBtnIco;
}

const QString Theme::getMainMenuUnlockWalletSelectedBtnIco() const {
    return mainMenuUnlockWalletSelectedBtnIco;
}

const QString Theme::getMainMenuLockWalletSelectedBtnIco() const {
    return mainMenuLockWalletSelectedBtnIco;
}


