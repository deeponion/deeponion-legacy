//
//

#include "themeoriginaldark.h"


ThemeOriginalDark::ThemeOriginalDark() 
	: Theme()
{
	init();
}

void ThemeOriginalDark::init() 
{
    themeStyleSheet = "QMenu {color: white; background-color: #2A2937; border-color: #2A2937;} \
    	QMenu::item:selected {background-color: #1C1B15;}\
   		QMainWindow {background-color: #393947; border:none;font-family:'Helvetica Neue';} \
   		QHeaderView::section {color:white; background-color: #474757; } \
    	QPlainTextEdit {color: white; background-color: #2b2b37; selection-background-color: #79a6d2; font-size: 13px; font-family: 'Helvetica Neue';} \
        QPlainTextEdit:ContextMenu {height: 200px;}\
        QTextEdit {color: white; background-color: #2b2b37; selection-background-color: #79a6d2; font-size: 13px; font-family: 'Helvetica Neue';} \
        QLineEdit {border: 1px solid gray; background-color: #2b2b37; color: #FFFFFF; selection-background-color: #79a6d2; font-size: 13px; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px;} \
        QLineEdit:hover {border: 1px solid gray; background-color: #2b2b37; color: #FFFFFF; selection-background-color: #79a6d2; font-size: 13px; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px;} \
        QLineEdit:ContextMenu {height: 200px;}\
        QTabWidget {color:white; background-color: #393947;} \
        QTabWidget::pane {color:white; background-color: #393947; border: 1px solid #2b2b37;} \
        QTabBar::tab {color:white; background-color: #474757; border: 1px solid #393947; padding: 3px; border-top-left-radius: 4px; border-top-right-radius: 4px;} \
        QTabBar::tab:selected, QTabBar::tab:hover {color:white; background-color: #7272a3; border: 1px solid #393947; padding: 3px; border-top-left-radius: 4px; border-top-right-radius: 4px;} \
        QDialog {color:white; background-color: #393947;} \
        QCheckBox {color:white; background-color: #393947;} \
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
        QToolBar {color:white; background-color: #393947; border: 0px;} \
        QToolBar QToolButton {width: 180px; border:0; height:40px; padding-left: 15px; text-align:left; color:white; background-color: #393947} \
        QToolBar QToolButton:pressed {border:0; height:40px; padding-left: 15px; text-align:left; color:white; background-color: #486EBA} \
        QToolBar QToolButton:checked {border:0; height:40px; padding-left: 15px; text-align:left; color:white; background-color: #486EBA} \
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

	centralWidgetStyle = "background: #2B2B37";
             
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
	qLineEdit = "QLineEdit {background-color: #2b2b37; color: #FFFFFF; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px;}  QLineEdit:ContextMenu {height: 200px;}";
	qLineEditPassword = "QLineEdit {background-color: #2b2b37; color: #FFFFFF; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px;}  QLineEdit:ContextMenu {height: 200px;}";
	payAmountStyle = "background-color: #2b2b37; color: #FFFFFF; padding-left: 5px; font-family: 'Helvetica Neue'; height: 32px;";
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
	statusBarBackgroundColor = "background-color: #1A1A21;";
	progressBarStyle = "color: #3dc28b; padding-left: 10px;  background-color: #1A1A21;";
	radioTextStyle = "color: #FFFFFF";
}
