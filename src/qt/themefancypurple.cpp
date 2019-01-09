//
//

#include "themefancypurple.h"


ThemeFancyPurple::ThemeFancyPurple()
	: Theme()
{
	init();
}

void ThemeFancyPurple::init()
{
	QString title_background = "#7d50cf";
    QString status_bar_background = "#1A1A21";
    QString widgets_background = "#282a3e";
    QString menu_background = "#2A2937";
    QString input_background = "#222435";
    QString frame_background = "#282a3e";
    QString font_family = "'Helvetica Neue'";
    QString selected_item_background = "#79a6d2";
    QString text_color = "#FFFFFF";
    QString alternate_background = "#36384a";
    QString tab_background = "#474757";
    QString selected_tab_background = "#7272a3";
    QString secondary_label_color = "#898994";
    QString push_button_text_color = "#e9e8e8";
    QString push_button_border_color = "#65676b";
    QString push_button_background = "#22222b";
    QString selected_menu_item_background = "#1C1B15";
    QString tree_item_alternate_background = "#538cc6";
    QString progress_bar_background = "#3dc28b";
    QString tableview_text_color = "#D5D5D9";
    QString scrollbar_handle_color = "#C1C1C1";
    QString disabled_text_color = "#e1e1ea";
    
    themeStyleSheet = "QMenu {color: " + text_color + "; background-color: " + menu_background + "; border-color: " + menu_background + ";} \
    	QMenu::item:selected {background-color: " + selected_menu_item_background + ";}\
   		QMainWindow {background-color: " + frame_background + "; border:none;font-family:" + font_family + ";} \
   		QHeaderView::section {color: " + text_color + "; background-color: " + tab_background + "; } \
    	QPlainTextEdit {color: " + text_color + "; background-color: " + input_background + "; selection-background-color: " + selected_item_background + "; font-size: 13px; font-family: " + font_family + ";} \
        QPlainTextEdit:ContextMenu {height: 200px;}\
        QTextEdit {color: " + text_color + "; background-color: " + input_background + "; selection-background-color: " + selected_item_background + "; font-size: 13px; font-family: " + font_family + ";} \
        QLineEdit {border: 1px solid gray; background-color: " + input_background + "; color: " + text_color + "; selection-background-color: " + selected_item_background + "; font-size: 13px; padding-left: 5px; font-family: " + font_family + "; height: 32px;} \
        QLineEdit:hover {border: 1px solid gray; background-color: " + input_background + "; color: " + text_color + "; selection-background-color: " + selected_item_background + "; font-size: 13px; padding-left: 5px; font-family: " + font_family + "; height: 32px;} \
        QLineEdit:ContextMenu {height: 200px;}\
        QTabWidget {color: " + text_color + "; background-color: " + frame_background + ";} \
        QTabWidget::pane {color: " + text_color + "; background-color: " + frame_background + "; border: 1px solid " + input_background + ";} \
        QTabBar::tab {color: " + text_color + "; background-color: " + tab_background + "; border: 1px solid " + frame_background + "; padding: 3px; border-top-left-radius: 4px; border-top-right-radius: 4px;} \
        QTabBar::tab:selected, QTabBar::tab:hover {color:" + text_color + "; background-color: " + selected_tab_background + "; border: 1px solid " + frame_background + "; padding: 3px; border-top-left-radius: 4px; border-top-right-radius: 4px;} \
        QDialog {color: " + text_color + "; background-color: " + frame_background + ";} \
        QCheckBox {color: " + text_color + "; background-color: " + frame_background + ";} \
        QLabel {color: " + text_color + "; background-color: " + frame_background + "; font-family:" + font_family + ";} \
        QLabel#labelTotalText {color: " + secondary_label_color + ";}\
        QLabel#labelTotal {color: " + text_color + ";}\
        QLabel#labelBalanceText {color: " + secondary_label_color + ";}\
        QLabel#labelBalance {color: " + text_color + ";}\
        QLabel#labelStakeText {color: " + secondary_label_color + ";}\
        QLabel#labelStake {color: " + text_color + ";}\
        QLabel#labelUnconfirmedText {color: " + secondary_label_color + ";}\
        QLabel#labelUnconfirmed {color: " + text_color + ";}\
        QLabel#labelImmatureText {color: " + secondary_label_color + ";}\
        QLabel#labelImmature {color: " + text_color + ";}\
        QToolBar {color: " + text_color + "; background-color: " + frame_background + "; border: 0px;} \
        QToolBar QToolButton {width: 180px; border:0; height:40px; padding-left: 15px; text-align:left; color: " + text_color + "; background-color: " + frame_background + "} \
        QToolBar QToolButton:pressed {border:0; height:40px; padding-left: 15px; text-align:left; color: " + text_color + "; background-color: " + title_background + "} \
        QToolBar QToolButton:checked {border:0; height:40px; padding-left: 15px; text-align:left; color: " + text_color + "; background-color: " + title_background + "} \
        QTreeView { color: " + text_color + "; background-color:" + frame_background + "; alternate-background-color: " + tree_item_alternate_background + ";} \
        QTreeView::item {color: " + text_color + "; background-color: " + frame_background + "; border: 1px solid " + frame_background + ";} \
        QTreeView::item:hover {color: " + text_color + "; background-color: " + selected_item_background + "; border: 1px solid " + frame_background + ";} \
        QToolButton {color: " + text_color + "; background-color: " + frame_background + "; padding: 3px; border: none;} \
        QDialogButtonBox {color: " + text_color + "; background-color: " + frame_background + "; padding: 3px;} \
        QMenuBar {background-color: " + menu_background + ";} \
        QToolTip {color: " + text_color + "; border: 0px; background-color: " + menu_background + "; opacity: 225;} \
        QMenuBar::item {color: " + text_color + "; background-color: " + menu_background + " ;} \
        QMenuBar::item:selected {color: " + text_color + "; font-weight: bold; background-color: " + menu_background + ";}\
        QPushButton {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + input_background + "; color: " + push_button_text_color + "; padding: 8px}\
        QPushButton:pressed {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + push_button_background + "; color: " + push_button_text_color + "}\
        QPushButton:hover {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + push_button_background + "; color: " + push_button_text_color + "}\
		QPushButton:disabled {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + push_button_background + "; color: " + disabled_text_color + ";}\
        QStatusBar::item { border: 0px}\
        QProgressBar::horizontal { text-align: middle;}\
        QProgressBar::chunk { background-color:" + progress_bar_background + ";}\
        QTableView {color: " + tableview_text_color + "; alternate-background-color: " + alternate_background + "; background-color: " + widgets_background + ";}\
        QScrollBar:vertical {border: 1px solid " + input_background + "; background: " + input_background + "; width: 24px; margin: 5px 5px 5px 5px;}\
        QScrollBar::handle:vertical {border-radius: 4px; background: " + scrollbar_handle_color + "; min-height: 25px; max-width: 12px; }\
        QScrollBar::add-line:vertical { background: " + alternate_background + "; height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;}\
        QScrollBar::sub-line:vertical { background: " + alternate_background + "; height: 0px; subcontrol-position: top; subcontrol-origin: margin;}\
        QScrollBar:horizontal {border: 1px solid " + input_background + "; background: " + input_background + "; width: 24px; margin: 5px 5px 5px 5px;}\
        QScrollBar::handle:horizontal {border-radius: 4px; background: " + scrollbar_handle_color + "; min-height: 25px; max-width: 12px; }\
        QScrollBar::add-line:horizontal { background: " + alternate_background + "; height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;}\
        QScrollBar::sub-line:horizontal { background: " + alternate_background + "; height: 0px; subcontrol-position: top; subcontrol-origin: margin;}";

	centralWidgetStyle = "background: " + input_background + "";
             
	mainMenuOverviewNormalBtnIco = ":/icons/OverviewS";
	mainMenuSendcoinsNormalBtnIco = ":/icons/SendCoinsS";
    mainMenuReceiveCoinsNormalBtnIco = ":/icons/ReceiveCoinsS";
    mainMenuTransactionsNormalBtnIco = ":/icons/TransactionsS";
    mainMenuAddressBookNormalBtnIco = ":/icons/AddressBookS";
    mainMenuMessagesNormalBtnIco = ":/icons/MessagesS";
    mainMenuExportNormalBtnIco = ":/icons/ExportUS";
    mainMenuUnlockWalletNormalBtnIco = ":/icons/lock_open_s";
    mainMenuLockWalletNormalBtnIco = ":/icons/lock_closed_s";
            
   	mainMenuOverviewSelectedBtnIco = ":/icons/OverviewS";
   	mainMenuSendcoinsSelectedBtnIco = ":/icons/SendCoinsS";
   	mainMenuReceiveCoinsSelectedBtnIco = ":/icons/ReceiveCoinsS";
  	mainMenuTransactionsSelectedBtnIco = ":/icons/TransactionsS";
  	mainMenuAddressBookSelectedBtnIco = ":/icons/AddressBookS";
  	mainMenuMessagesSelectedBtnIco = ":/icons/MessagesS";
  	mainMenuExportSelectedBtnIco = ":/icons/ExportUS";
  	mainMenuUnlockWalletSelectedBtnIco = ":/icons/lock_open_s";
   	mainMenuLockWalletSelectedBtnIco = ":/icons/lock_closed_s";

	mainMenuExportDeactivatedBtnIco = ":/icons/export_disabled";
            
	qFrameGeneralStyle = "background-color: " + frame_background + ";";
	qFrameSecondaryMenuGeneralStyle = "background-color: " + push_button_background + "; padding: 8px;";
	qLabelGeneralStyle = "color: " + text_color + "";
	qTableGeneralStyle = "QTableView {color: " + tableview_text_color + "; alternate-background-color: " + alternate_background + "; background-color: " + widgets_background + ";} \
		QScrollBar:vertical {border: 1px solid " + input_background + "; background: " + input_background + "; width: 24px; margin: 5px 5px 5px 5px;} \
		QScrollBar::handle:vertical {border-radius: 4px; background: " + scrollbar_handle_color + "; min-height: 25px; max-width: 12px; } \
		QScrollBar::add-line:vertical { background: " + alternate_background + "; height: 0px; subcontrol-position: bottom; subcontrol-origin: margin;} \
		QScrollBar::sub-line:vertical { background: " + alternate_background + "; height: 0px; subcontrol-position: top; subcontrol-origin: margin;}";
	qListHeaderGeneralStyle = "QHeaderView::section {background-color: " + title_background + "; color: " + text_color + "; border: none; \
		font-size: 14px; font-family: Helvetica Neue; \
		padding-left: 8px; padding-right: 8px; \
		padding-top: 14px; padding-bottom: 14px;}";
	qLineEdit = "QLineEdit {background-color: " + input_background + "; color: " + text_color + "; padding-left: 5px; font-family: " + font_family + "; height: 32px;}  QLineEdit:ContextMenu {height: 200px;}";
	qLineEditPassword = "QLineEdit {background-color: " + input_background + "; color: " + text_color + "; padding-left: 5px; font-family: " + font_family + "; height: 32px;}  QLineEdit:ContextMenu {height: 200px;}";
	payAmountStyle = "background-color: " + input_background + "; color: " + text_color + "; padding-left: 5px; font-family: " + font_family + "; height: 32px;";
	iconTextButtonStyle = "QPushButton, QPushButton:hover {color: " + text_color + "; border: none; background-color: rgba(255, 255, 255, 0);}";
	informationIco = ":/icons/information";
	informationBtnStyle = "background-color: " + frame_background + "; border: none";
	qComboboxTransactionsFilteringStyle = "QComboBox { background-color: " + frame_background + "; color: " + text_color + "; font-size: 14px; font-family: " + font_family + ";\
		padding-left: 8px; padding-top: 14px; padding-bottom: 14px; border: none; }\
		QComboBox::drop-down {border: none; background: " + title_background + "; width: 30px;}\
		QComboBox::down-arrow { width: 14px; height: 14px; image: url(:/icons/arrow_down_white);}";
	qComboboxDateRangeStyle = "background-color: " + frame_background + "; color: " + text_color + "; font-size: 14px; font-family: " + font_family + ";\
		border: none; QComboBox::drop-down {border: none}";
	qToolBtnStyle = "{color: " + text_color + "; background-color: " + frame_background + "; padding: 3px; border: none;}";
	qPushBtnStyle = "QPushButton {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + input_background + "; color: " + push_button_text_color + "; padding: 8px}\
		QPushButton:pressed {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + push_button_background + "; color: " + push_button_text_color + "}\
		QPushButton:hover {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + push_button_background + "; color: " + push_button_text_color + "}\
		QPushButton:disabled {font-family:" + font_family + "; border: 1px solid " + push_button_border_color + "; background-color: " + push_button_background + "; color: " + disabled_text_color + ";}";
	aboutImg = ":/images/about_dark_purple";
	fontBiggerIco = ":/icons/fontbigger_dark";
	fontSmallerIco = ":/icons/fontsmaller_dark";
	qTreeWidget = "QTreeView { color: " + text_color + "; background-color:" + frame_background + "; alternate-background-color: " + tree_item_alternate_background + ";} \
		QTreeView::item {color: " + text_color + "; background-color: " + frame_background + "; border: 1px solid " + frame_background + ";} \
		QTreeView::item:hover {color: " + text_color + "; background-color: " + selected_item_background + "; border: 1px solid " + frame_background + ";}";
	statusBarBackgroundColor = "background-color: " + status_bar_background + ";";
	progressBarStyle = "color: " + progress_bar_background + "; padding-left: 10px;  background-color: " + status_bar_background + ";";
	radioTextStyle = "color: " + text_color;
    mainHeaderStyle = "background-color: " + title_background + "; color: white; padding-right: 10px; font-size: 24px; font-weight: bold";
    menuHeaderStyle = "QToolBar {background: " + title_background + "; border: 0px;} \
        QToolBar QToolButton {background: " + title_background + "; padding-left: 15px; padding-top: 10px; text-align:left;}";
    subSectionTitleStyle = "padding-left: 10px; background-color: " + title_background + ";";
    roundedButtonStyle = "background-color: " + title_background + ";color: white;border-radius:14px;border-width:0px; margin-left: 8px;";
    deepOnionLogo = ":/icons/DeepOnionLogoPurple";
}
