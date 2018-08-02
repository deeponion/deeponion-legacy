//
//

#include "themeoriginallight.h"


ThemeOriginalLight::ThemeOriginalLight() 
	: Theme()
{
	init();
}

void ThemeOriginalLight::init() 
{
    themeStyleSheet = "QComboBox {color: white; background-color: #2A2937; height: 26px;} \
                        QComboBox:hover {background-color: #FFFFFF; color: #2A2937;  height: 26px;} \
                        QWidget {color: #2A2937; background-color: #bdc9db;} \
                        QMenu {color: #2A2937; background-color: #bdc9db; border-color: #bdc9db;} \
                        QMenu::item:selected{background-color: #6b6b6b;}\
                        QMenuBar {color: #2A2937; background-color: #bdc9db;} \
                        QMenuBar::item {color: #2A2937; background-color: #bdc9db;} \
                        QMenuBar::item:hover {color: #2A2940; background-color: #F9F9F9;} \
                        QMenuBar::item:selected {color: #2A2937; font-weight: bold; background-color: #bdc9db;}\
                        QMainWindow {background-color: #FFFFFF; border:none;font-family:'Helvetica Neue';} \
                        QHeaderView::section {color:#2A2937; background-color: #d8d8d8; } \
                        QPlainTextEdit {color: #2B2B37; background-color: #D8D8D8; selection-background-color: #79a6d2; font-size: 13px; font-family: 'Helvetica Neue';} \
                        QPlainTextEdit:ContextMenu {height: 200px;}\
                        QTextEdit {color: #2B2B37; background-color: #D8D8D8; selection-background-color: #79a6d2; font-size: 13px; font-family: 'Helvetica Neue';} \
                        QLineEdit {border: 1px solid #7A7A7A; background-color: #bdc9db; color: #2B2B37; selection-background-color: #79a6d2; font-size: 13px; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px;}\
                        QLineEdit:hover {border: 1px solid #7A7A7A; background-color: #bdc9db; color: #2B2B37; selection-background-color: #79a6d2; font-size: 13px; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px;}\
                        QLineEdit:ContextMenu {height: 200px;}\
                        QTabWidget {color:#2A2937; background-color: #bdc9db;} \
                        QTabWidget::pane {color:#2A2937; background-color: #bdc9db; border: 1px solid #393947;} \
                        QTabBar::tab {color: #2A2937; background-color: #D8D8D8; border: 1px solid #393947; padding: 3px; border-top-left-radius: 4px; border-top-right-radius: 4px;} \
                        QTabBar::tab:selected, QTabBar::tab:hover {background-color: #bdc9db; color: #2A2937} \
                        QDialog {color:#2A2937; background-color: #bdc9db;} \
                        QCheckBox {color:#2A2937; background-color: #bdc9db;} \
                        QLabel {color:#2A2937; background-color: #bdc9db; font-family:'Helvetica Neue';} \
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
                        QToolBar {color:white; background-color: #ffffff; border: 0px;}\
                        QToolBar QToolButton {width: 180px; border:0; height:40px; padding-left: 15px;text-align:left; color:#486EBA; background-color: #FFFFFF} \
                        QToolBar QToolButton:pressed {border:0; height:40px; padding-left: 15px;text-align:left; color:white; background-color: #486EBA} \
                        QToolBar QToolButton:checked {border:0; height:40px; padding-left: 15px;text-align:left; color:white; background-color: #486EBA} \
                        QTreeView { color: #2B2B37; background-color:#c2c2ce; alternate-background-color: #538cc6;} \
                        QTreeView::item {color: #2B2B37; background-color: #c2c2ce; border: 1px solid #c2c2ce;} \
                        QTreeView::item:hover {color: #2B2B37; background-color: #79a6d2; border: 1px solid #c2c2ce;} \
                        QToolButton {color:#2A2937; background-color: #bdc9db; padding: 3px; border: none;} \
                        QDialogButtonBox {color:#2A2937; background-color: #bdc9db; padding: 3px;} \
                        QToolTip {color: #2A2937; border: 0px; background-color: #bdc9db; opacity: 225;} \
                        QPushButton {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #bdc9db; color: #2A2937; padding: 8px;}\
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

    centralWidgetStyle = "background: #bdc9db";

    mainMenuOverviewNormalBtnIco = ":/icons/overview";
    mainMenuSendcoinsNormalBtnIco = ":/icons/send";
    mainMenuReceiveCoinsNormalBtnIco = ":/icons/receiving_addresses";
    mainMenuTransactionsNormalBtnIco = ":/icons/history";
    mainMenuAddressBookNormalBtnIco = ":/icons/address-book";
    mainMenuMessagesNormalBtnIco = ":/icons/messaging";
    mainMenuExportNormalBtnIco = ":/icons/export";
    mainMenuUnlockWalletNormalBtnIco = ":/icons/lock_open";
    mainMenuLockWalletNormalBtnIco = ":/icons/lock_closed";
    
    mainMenuOverviewSelectedBtnIco = ":/icons/OverviewS";
    mainMenuSendcoinsSelectedBtnIco = ":/icons/SendCoinsS";
    mainMenuReceiveCoinsSelectedBtnIco = ":/icons/ReceiveCoinsS";
    mainMenuTransactionsSelectedBtnIco = ":/icons/TransactionsS";
    mainMenuAddressBookSelectedBtnIco = ":/icons/AddressBookS";
    mainMenuMessagesSelectedBtnIco = ":/icons/MessagesS";
    mainMenuExportSelectedBtnIco = ":/icons/ExportUS";
    mainMenuUnlockWalletSelectedBtnIco = ":/icons/lock_open";
    mainMenuLockWalletSelectedBtnIco = ":/icons/lock_closed";

    mainMenuExportDeactivatedBtnIco = ":/icons/export_disabled";
    
    qFrameGeneralStyle = "background-color: #FFFFFF;";
    qFrameSecondaryMenuGeneralStyle = "background-color: #93a3bb; padding: 8px;";
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
    qLineEdit = "QLineEdit {background-color: #bdc9db; color: #2B2B37; selection-background-color: #d7e6ff; font-size: 13px; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px; border: 1px solid #c2c2c2;} QLineEdit:ContextMenu {height: 200px;}";
    qLineEditPassword = "QLineEdit {background-color: #D8D8DB; color: #2B2B37; selection-background-color: #d7e6ff; font-size: 13px; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px; border: 1px solid #c2c2c2; } QLineEdit:ContextMenu {height: 200px;}";
    payAmountStyle = "background-color: #bdc9db; color: #2B2B37; selection-background-color: #d7e6ff; font-size: 13px; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px; border: 1px solid #c2c2c2;";
    iconTextButtonStyle = "QPushButton, QPushButton:hover {color: #486EBA; border: none; background-color: rgba(255, 255, 255, 10);}";
    informationIco = ":/icons/information-blue";
    informationBtnStyle = "background-color: #FFFFFF; border: none";
    qComboboxTransactionsFilteringStyle = "QComboBox { background-color: #FFFFFF; color: #486EBA; font-size: 14px; font-family: 'Helvetica Neue';\
                        padding-left: 8px; padding-top: 14px; padding-bottom: 14px; border: none; }\
                        QComboBox::drop-down {border: none; background: #486EBA; width: 30px;}\
                        QComboBox::down-arrow { width: 14px; height: 14px; image: url(:/icons/arrow_down_white);}";
    qComboboxDateRangeStyle = "background-color: #FFFFFF; color: #486EBA; font-size: 12px; font-family: 'Helvetica Neue';\
                        border: none; QComboBox::drop-down {border: none}";
    qToolBtnStyle = "{color:#2A2937; background-color: #bdc9db; padding: 3px; border: none;}";
    qPushBtnStyle = "QPushButton {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #bdc9db; color: #2A2937; padding: 8px}\
                        QPushButton:pressed {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #FFFFFF; color: #486EBA}\
                        QPushButton:hover {font-family:'Helvetica Neue'; border: 1px solid #65676b; background-color: #FFFFFF; color: #486EBA}";
    aboutImg = ":/images/about_light";
    fontBiggerIco = ":/icons/fontbigger_light";
    fontSmallerIco = ":/icons/fontsmaller_light";
    qTreeWidget = "QTreeView { color: #2B2B37; background-color:#c2c2ce; alternate-background-color: #538cc6;} \
                        QTreeView::item {color: #2B2B37; background-color: #c2c2ce; border: 1px solid #c2c2ce;} \
                        QTreeView::item:hover {color: #2B2B37; background-color: #79a6d2; border: 1px solid #c2c2ce;}";
    statusBarBackgroundColor = "background-color: #f4f6f9;";
    progressBarStyle = "color: #3dc28b; padding-left: 10px;  background-color: #f4f6f9;";
    radioTextStyle = "color: #000000";
}
