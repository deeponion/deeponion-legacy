//
//

#include "themelightpurple.h"


ThemeLightPurple::ThemeLightPurple() 
	: Theme()
{
	init();
}

void ThemeLightPurple::init() 
{
    QString title_background = "#7d50cf";
    QString status_bar_background = "#f4f6f9";
    QString widgets_background = "#D8D8D8";
    QString menu_background = "#bdc9db";
    //QString input_background = ""; //unused
    QString frame_background = "#FFFFFF";
    QString font_family = "'Helvetica Neue'";
    QString selected_item_background = "#79a6d2";
    QString text_color = "#2B2B37";
    //QString alternate_background = ""; //unused
    //QString tab_background = ""; //unused
    //QString selected_tab_background = ""; //unused
    //QString secondary_label_color = ""; //unused
    QString push_button_text_color = "#2A2937";
    QString push_button_border_color = "#65676b";
    //QString push_button_background = ""; //unused
    QString selected_menu_item_background = "#6b6b6b";
    QString tree_item_alternate_background = "#538cc6";
    QString progress_bar_background = "#3dc28b";
    QString tableview_text_color = "#565656";
    QString scrollbar_handle_color = " rgba(255, 255, 255, 0%)";

    themeStyleSheet = "QComboBox {color: #FFFFFF; background-color: " + push_button_text_color + "; height: 26px;} \
                        QComboBox:hover {background-color: " + frame_background + "; color: " + push_button_text_color + ";  height: 26px;} \
                        QWidget {color: " + push_button_text_color + "; background-color: " + menu_background + ";} \
                        QMenu {color: " + push_button_text_color + "; background-color: " + menu_background + "; border-color: " + menu_background + ";} \
                        QMenu::item:selected{background-color: " + selected_menu_item_background + ";}\
                        QMenuBar {color: " + push_button_text_color + "; background-color: " + menu_background + ";} \
                        QMenuBar::item {color: " + push_button_text_color + "; background-color: " + menu_background + ";} \
                        QMenuBar::item:hover {color: #2A2940; background-color: #F9F9F9;} \
                        QMenuBar::item:selected {color: " + push_button_text_color + "; font-weight: bold; background-color: " + menu_background + ";}\
                        QMainWindow {background-color: " + frame_background + "; border:none;font-family:" + font_family + ";} \
                        QHeaderView::section {color:" + push_button_text_color + "; background-color: " + widgets_background + "; } \
                        QPlainTextEdit {color: " + text_color + "; background-color: " + widgets_background + "; selection-background-color: " + selected_item_background + "; font-size: 13px; font-family: " + font_family + ";} \
                        QPlainTextEdit:ContextMenu {height: 200px;}\
                        QTextEdit {color: " + text_color + "; background-color: " + widgets_background + "; selection-background-color: " + selected_item_background + "; font-size: 13px; font-family: " + font_family + ";} \
                        QLineEdit {border: 1px solid #7A7A7A; background-color: " + menu_background + "; color: " + text_color + "; selection-background-color: " + selected_item_background + "; font-size: 13px; padding-left: 5px; font-family: " + font_family + "; height: 32px;}\
                        QLineEdit:hover {border: 1px solid #7A7A7A; background-color: " + menu_background + "; color: " + text_color + "; selection-background-color: " + selected_item_background + "; font-size: 13px; padding-left: 5px; font-family: " + font_family + "; height: 32px;}\
                        QLineEdit:ContextMenu {height: 200px;}\
                        QTabWidget {color:" + push_button_text_color + "; background-color: " + menu_background + ";} \
                        QTabWidget::pane {color:" + push_button_text_color + "; background-color: " + menu_background + "; border: 1px solid #393947;} \
                        QTabBar::tab {color: " + push_button_text_color + "; background-color: " + widgets_background + "; border: 1px solid #393947; padding: 3px; border-top-left-radius: 4px; border-top-right-radius: 4px;} \
                        QTabBar::tab:selected, QTabBar::tab:hover {background-color: " + menu_background + "; color: " + push_button_text_color + "} \
                        QDialog {color:" + push_button_text_color + "; background-color: " + menu_background + ";} \
                        QCheckBox {color:" + push_button_text_color + "; background-color: " + menu_background + ";} \
                        QLabel {color:" + push_button_text_color + "; background-color: " + menu_background + "; font-family:" + font_family + ";} \
                        QLabel#labelTotalText {color: " + title_background + ";}\
                        QLabel#labelTotal {color: #4D4D4D;}\
                        QLabel#labelBalanceText {color: " + title_background + ";}\
                        QLabel#labelBalance {color: #4D4D4D;}\
                        QLabel#labelStakeText {color: " + title_background + ";}\
                        QLabel#labelStake {color: #4D4D4D;}\
                        QLabel#labelUnconfirmedText {color: " + title_background + ";}\
                        QLabel#labelUnconfirmed {color: #4D4D4D;}\
                        QLabel#labelImmatureText {color: " + title_background + ";}\
                        QLabel#labelImmature {color: #4D4D4D;}\
                        QToolBar {color:#FFFFFF; background-color: " + frame_background + "; border: 0px;}\
                        QToolBar QToolButton {width: 180px; border:0; height:40px; padding-left: 15px;text-align:left; color:" + title_background + "; background-color: " + frame_background + "} \
                        QToolBar QToolButton:pressed {border:0; height:40px; padding-left: 15px;text-align:left; color:#FFFFFF; background-color: " + title_background + "} \
                        QToolBar QToolButton:checked {border:0; height:40px; padding-left: 15px;text-align:left; color:#FFFFFF; background-color: " + title_background + "} \
                        QTreeView { color: " + text_color + "; background-color:#c2c2ce; alternate-background-color: " + tree_item_alternate_background + ";} \
                        QTreeView::item {color: " + text_color + "; background-color: #c2c2ce; border: 1px solid #c2c2ce;} \
                        QTreeView::item:hover {color: " + text_color + "; background-color: " + selected_item_background + "; border: 1px solid #c2c2ce;} \
                        QToolButton {color:" + push_button_text_color + "; background-color: " + menu_background + "; padding: 3px; border: none;} \
                        QDialogButtonBox {color:" + push_button_text_color + "; background-color: " + title_background + "; padding: 3px;} \
                        QToolTip {color: " + push_button_text_color + "; border: 0px; background-color: " + menu_background + "; opacity: 225;} \
                        QPushButton {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + menu_background + "; color: " + push_button_text_color + "; padding: 8px;}\
                        QPushButton:pressed {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + frame_background + "; color: " + title_background + ";}\
                        QPushButton:hover {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + frame_background + "; color: " + title_background + ";}\
                        QStatusBar::item { border: 0px}\
                        QProgressBar::chunk { background-color:" + progress_bar_background + ";}\
                        QTableView {color: " + tableview_text_color + "; alternate-background-color: " + widgets_background + "; background-color: " + frame_background + ";} \
                        QScrollBar:vertical {border: 1px solid #FFFFFF; background: " + scrollbar_handle_color + "; width: 24px; margin: 5px 5px 5px 5px;} \
                        QScrollBar::handle:vertical {border-radius: 4px; background: #C1C1C1; min-height: 25px; max-width: 12px; } \
                        QScrollBar::add-line:vertical { background: " + widgets_background + "; height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;} \
                        QScrollBar::sub-line:vertical { background: " + widgets_background + "; height: 0px; subcontrol-position: top; subcontrol-origin: margin;}\
                        QScrollBar:horizontal {border: 1px solid #FFFFFF; background: " + scrollbar_handle_color + "; width: 24px; margin: 5px 5px 5px 5px;} \
                        QScrollBar::handle:horizontal {border-radius: 4px; background: #C1C1C1; min-height: 25px; max-width: 12px; } \
                        QScrollBar::add-line:horizontal { background: " + widgets_background + "; height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;} \
                        QScrollBar::sub-line:horizontal { background: " + widgets_background + "; height: 0px; subcontrol-position: top; subcontrol-origin: margin;}";

    centralWidgetStyle = "background: " + menu_background + "";

    mainMenuOverviewNormalBtnIco = ":/icons/purple/overview";
    mainMenuSendcoinsNormalBtnIco = ":/icons/purple/send";
    mainMenuReceiveCoinsNormalBtnIco = ":/icons/purple/receiving_addresses";
    mainMenuTransactionsNormalBtnIco = ":/icons/purple/history";
    mainMenuAddressBookNormalBtnIco = ":/icons/purple/address-book";
    mainMenuMessagesNormalBtnIco = ":/icons/purple/messaging";
    mainMenuExportNormalBtnIco = ":/icons/purple/export";
    mainMenuUnlockWalletNormalBtnIco = ":/icons/purple/lock_open";
    mainMenuLockWalletNormalBtnIco = ":/icons/purple/lock_closed";
    
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
    
    qFrameGeneralStyle = "background-color: " + frame_background + ";";
    qFrameSecondaryMenuGeneralStyle = "background-color: #93a3bb; padding: 8px;";
    qLabelGeneralStyle = "color: " + title_background + "";
    qTableGeneralStyle = "QTableView {color: " + tableview_text_color + "; alternate-background-color: " + widgets_background + "; background-color: " + frame_background + ";} \
                        QScrollBar:vertical {border: 1px solid #FFFFFF; background: " + scrollbar_handle_color + "; width: 24px; margin: 5px 5px 5px 5px;} \
                        QScrollBar::handle:vertical {border-radius: 4px; background: #C1C1C1; min-height: 25px; max-width: 12px; } \
                        QScrollBar::add-line:vertical { background: " + widgets_background + "; height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;} \
                        QScrollBar::sub-line:vertical { background: " + widgets_background + "; height: 0px; subcontrol-position: top; subcontrol-origin: margin;}";
    qListHeaderGeneralStyle = "QHeaderView::section {background-color: " + title_background + "; color: #FFFFFF; border: none; \
                        font-size: 14px; font-family: Helvetica Neue; \
                        padding-left: 8px; padding-right: 8px; \
                        padding-top: 14px; padding-bottom: 14px;}";
    qLineEdit = "QLineEdit {background-color: " + menu_background + "; color: " + text_color + "; selection-background-color: #d7e6ff; font-size: 13px; padding-left: 5px; font-family: " + font_family + "; height: 32px; border: 1px solid #c2c2c2;} QLineEdit:ContextMenu {height: 200px;}";
    qLineEditPassword = "QLineEdit {background-color: #D8D8DB; color: " + text_color + "; selection-background-color: #d7e6ff; font-size: 13px; padding-left: 5px; font-family: " + font_family + "; height: 32px; border: 1px solid #c2c2c2; } QLineEdit:ContextMenu {height: 200px;}";
    payAmountStyle = "background-color: " + menu_background + "; color: " + text_color + "; selection-background-color: #d7e6ff; font-size: 13px; padding-left: 5px; font-family: " + font_family + "; height: 32px; border: 1px solid #c2c2c2;";
    iconTextButtonStyle = "QPushButton, QPushButton:hover {color: " + title_background + "; border: none; background-color: rgba(255, 255, 255, 10);}";
    informationIco = ":/icons/information-blue";
    informationBtnStyle = "background-color: " + frame_background + "; border: none";
    qComboboxTransactionsFilteringStyle = "QComboBox { background-color: " + frame_background + "; color: " + title_background + "; font-size: 14px; font-family: " + font_family + ";\
                        padding-left: 8px; padding-top: 14px; padding-bottom: 14px; border: none; }\
                        QComboBox::drop-down {border: none; background: " + title_background + "; width: 30px;}\
                        QComboBox::down-arrow { width: 14px; height: 14px; image: url(:/icons/arrow_down_white);}";
    qComboboxDateRangeStyle = "background-color: " + frame_background + "; color: " + title_background + "; font-size: 12px; font-family: " + font_family + ";\
                        border: none; QComboBox::drop-down {border: none}";
    qToolBtnStyle = "{color:" + push_button_text_color + "; background-color: " + menu_background + "; padding: 3px; border: none;}";
    qPushBtnStyle = "QPushButton {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + menu_background + "; color: " + push_button_text_color + "; padding: 8px}\
                        QPushButton:pressed {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + frame_background + "; color: " + title_background + "}\
                        QPushButton:hover {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + frame_background + "; color: " + title_background + "}";
    aboutImg = ":/images/about_light_purple";
    fontBiggerIco = ":/icons/fontbigger_light";
    fontSmallerIco = ":/icons/fontsmaller_light";
    qTreeWidget = "QTreeView { color: " + text_color + "; background-color:#c2c2ce; alternate-background-color: " + tree_item_alternate_background + ";} \
                        QTreeView::item {color: " + text_color + "; background-color: #c2c2ce; border: 1px solid #c2c2ce;} \
                        QTreeView::item:hover {color: " + text_color + "; background-color: " + selected_item_background + "; border: 1px solid #c2c2ce;}";
    statusBarBackgroundColor = "background-color: #" + status_bar_background + ";";
    progressBarStyle = "color: " + progress_bar_background + "; padding-left: 10px;  background-color: #" + status_bar_background + ";";
    radioTextStyle = "color: #000000";
    mainHeaderStyle = "background-color: " + title_background + "; color: white; padding-right: 10px; font-size: 24px; font-weight: bold";
    menuHeaderStyle = "QToolBar {background: " + title_background + "; border: 0px;} \
        QToolBar QToolButton {background: " + title_background + "; padding-left: 15px; padding-top: 10px; text-align:left;}";
    subSectionTitleStyle = "color: #FFFFFF; padding-left: 10px; background-color: " + title_background + ";";
    roundedButtonStyle = "background-color: " + title_background + ";color: white;border-radius:14px;border-width:0px; margin-left: 8px;";
    roundedButtonBoxStyle = "background: " + title_background + ";color: white;border-radius:14px;border-width:0px; margin-left: 8px;";

    deepOnionLogo = ":/icons/DeepOnionLogoPurple";
}
