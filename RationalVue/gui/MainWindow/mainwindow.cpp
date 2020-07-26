#include "mainwindow.h"
#include <QTextEdit>
#include <QAbstractButton>
#include "SARibbonBar.h"
#include "SARibbonCategory.h"
#include <QPushButton>
#include "SARibbonPannel.h"
#include "SARibbonToolButton.h"
#include <QAction>
#include <QMenu>
#include <QDebug>
#include <QElapsedTimer>
#include "SARibbonMenu.h"
#include "SARibbonComboBox.h"
#include "SARibbonLineEdit.h"
#include "SARibbonGallery.h"
#include "SARibbonCheckBox.h"
#include "SARibbonQuickAccessBar.h"
#include "SARibbonButtonGroupWidget.h"

#include "qsettings.h"
#include<QSplitter>
#include<QMessageBox>
#include<fstream>
#include <quiloader.h>

QString globalmPickupModel; //声明一个全局变量用于窗体间传值,用于判断选择什么样的图形来画图；

//翻译语言对应的文件
map<string, string> language = {
	{"Chinese",":mainResource/gui/MainWindow/zh.qm"},
	{"English",":mainResource/gui/MainWindow/en.qm"},
};

//翻译设置文件的地址
string tr_file_path = "../gui/MainWindow/translation.txt";


//初始化静态变量tr_file
QString MainWindow::tr_file = QString::fromStdString(language["English"]);

//加载翻译文件，读设置文件
void MainWindow::loadTranslate() {
	std::ifstream input;
	input.open(tr_file_path, std::ios::in | std::ios::binary);
	if (!input.is_open()) {
		qDebug() << "file open failed!";
	}
	else {
		qDebug() << "file open success!";
		char line[512];
		input.getline(line, 512, '\n');
		input.close();
		std::string line_content = std::string(line);
		int index = line_content.find('=');
		string lan = line_content.substr(index + 1);
		tr_file = QString::fromStdString(language[lan]);
		input.close();
	}

}


//添加importCAD子菜单
void MainWindow::addImportCADChildMenu() {
	//import CAD的子菜单
	p_childfileMenu_importCAD = new QMenu(this);
	p_action_iges = new QAction("IGES...", p_childfileMenu_importCAD);
	p_action_dxf = new QAction("DXF...", p_childfileMenu_importCAD);
	p_action_step = new QAction("STEP", p_childfileMenu_importCAD);
	p_action_parasolid = new QAction("ParaSolid XT...", p_childfileMenu_importCAD);
	p_action_catia = new QAction("CATIA...", p_childfileMenu_importCAD);
	p_action_ug = new QAction("UG...", p_childfileMenu_importCAD);
	p_action_proe = new QAction("ProE...", p_childfileMenu_importCAD);
	p_action_solidwork = new QAction("SolidWorks...", p_childfileMenu_importCAD);
	p_action_jt3d = new QAction("JT3D...", p_childfileMenu_importCAD);
	p_action_inventor = new QAction("Inventor 3D", p_childfileMenu_importCAD);
	p_action_solidedge = new QAction("SolidEdge...", p_childfileMenu_importCAD);
	p_action_drill = new QAction("Drill...", p_childfileMenu_importCAD);
	p_fileMenu_importCAD->setMenu(p_childfileMenu_importCAD);
	p_childfileMenu_importCAD->addAction(p_action_iges);
	p_childfileMenu_importCAD->addAction(p_action_dxf);
	p_childfileMenu_importCAD->addAction(p_action_step);
	p_childfileMenu_importCAD->addAction(p_action_parasolid);
	p_childfileMenu_importCAD->addAction(p_action_catia);
	p_childfileMenu_importCAD->addAction(p_action_ug);
	p_childfileMenu_importCAD->addAction(p_action_proe);
	p_childfileMenu_importCAD->addAction(p_action_solidwork);
	p_childfileMenu_importCAD->addAction(p_action_jt3d);
	p_childfileMenu_importCAD->addAction(p_action_inventor);
	p_childfileMenu_importCAD->addAction(p_action_solidedge);
	p_childfileMenu_importCAD->addAction(p_action_drill);
}

//添加exportCAD子菜单
void MainWindow::addExportCADChildMenu() {
	p_childfileMenu_exportCAD = new QMenu(this);
	p_action_exportCAD_igse = new QAction("IGES...", p_childfileMenu_exportCAD);
	p_childfileMenu_exportCAD->addAction(p_action_exportCAD_igse);
	p_action_exportCAD_dxf = new QAction("DXF...", p_childfileMenu_exportCAD);
	p_childfileMenu_exportCAD->addAction(p_action_exportCAD_dxf);
	p_childfileMenu_exportCAD->addSeparator();
	p_action_exportCAD_includeNom = new QAction("Include Nom Features", p_childfileMenu_exportCAD);
	p_childfileMenu_exportCAD->addAction(p_action_exportCAD_includeNom);
	p_action_exportCAD_includeAct = new QAction("Include Act Features", p_childfileMenu_exportCAD);
	p_childfileMenu_exportCAD->addAction(p_action_exportCAD_includeAct);
	p_action_exportCAD_includeMea = new QAction("IGES...", p_childfileMenu_exportCAD);
	p_childfileMenu_exportCAD->addAction(p_action_exportCAD_includeMea);
	p_action_exportCAD_export = new QAction("Export measurement points only", p_childfileMenu_exportCAD);
	p_childfileMenu_exportCAD->addAction(p_action_exportCAD_export);

	p_fileMenu_exportCAD->setMenu(p_childfileMenu_exportCAD);
}

//添加import features子菜单
void MainWindow::addImportFeaturesChildMenu() {
	p_childfileMenu_importFeatures = new QMenu(this);
	p_action_fromText = new QAction("From Text File...", p_childfileMenu_importFeatures);
	p_action_fromDXF = new QAction("From DXF...", p_childfileMenu_importFeatures);
	p_action_with = new QAction("With Graphics", p_childfileMenu_importFeatures);
	p_action_importCircle = new QAction("Import Circle", p_childfileMenu_importFeatures);
	p_action_importLine = new QAction("Import Line", p_childfileMenu_importFeatures);
	p_action_importCurve = new QAction("Import Curve", p_childfileMenu_importFeatures);

	p_childfileMenu_importFeatures->addAction(p_action_fromText);
	p_childfileMenu_importFeatures->addAction(p_action_fromDXF);
	p_childfileMenu_importFeatures->addAction(p_action_with);
	p_childfileMenu_importFeatures->addAction(p_action_importCircle);
	p_childfileMenu_importFeatures->addAction(p_action_importLine);
	p_childfileMenu_importFeatures->addAction(p_action_importCurve);
	p_fileMenu_importFeatures->setMenu(p_childfileMenu_importFeatures);
}

//添加export子菜单
void MainWindow::addExportChildMenu() {
	p_childfileMenu_export = new QMenu(this);
	p_action_exportAsQ = new QAction("Export as Q-Das");
	p_childfileMenu_export->addAction(p_action_exportAsQ);
	p_fileMenu_export->setMenu(p_childfileMenu_export);
}

//添加options子菜单
void MainWindow::addOptionsChildMenu() {
	p_childfileMenu_options = new QMenu(this);
	p_action_App = new QAction("Application Setting", p_childfileMenu_options);
	p_action_Imp = new QAction("Import Application Setup", p_childfileMenu_options);
	p_action_Exp = new QAction("Export Application Setup", p_childfileMenu_options);

	p_childfileMenu_options->addAction(p_action_App);
	p_childfileMenu_options->addAction(p_action_Imp);
	p_childfileMenu_options->addAction(p_action_Exp);
	p_fileMenu_options->setMenu(p_childfileMenu_options);
}

void MainWindow::addWindowChildMenu() {
	p_childfileMenu_window = new QMenu(this);
	p_action_Restore = new QAction("Restore default window position", p_childfileMenu_window);
	p_action_Restore->setShortcut(QKeySequence(QLatin1String("Ctrl+R")));
	p_action_SwitchI = new QAction("Switch image tool window position", p_childfileMenu_window);
	p_action_SwitchG = new QAction("Switch graphics tool window position", p_childfileMenu_window);
	p_action_SwitchD = new QAction("Switch data window position", p_childfileMenu_window);
	p_action_SwitchD->setShortcut(QKeySequence(QLatin1String("Ctrl+E")));
	p_action_IO = new QAction("I/O monitor window", p_childfileMenu_window);
	p_action_Shortcut = new QAction("Shortcut window", p_childfileMenu_window);
	p_action_Shortcut->setShortcut(QKeySequence(QLatin1String("Ctrl*2")));

	p_childfileMenu_window->addAction(p_action_Restore);
	p_childfileMenu_window->addAction(p_action_SwitchI);
	p_childfileMenu_window->addAction(p_action_SwitchG);
	p_childfileMenu_window->addAction(p_action_SwitchD);
	p_childfileMenu_window->addSeparator();
	p_childfileMenu_window->addAction(p_action_IO);
	p_childfileMenu_window->addAction(p_action_Shortcut);
	p_fileMenu_window->setMenu(p_childfileMenu_window);
}

void MainWindow::addLanguageChildMenu() {
	p_childfileMenu_language = new QMenu(this);
	p_action_lanzh = new QAction("Chinese", p_childfileMenu_language);
	p_action_lanen = new QAction("English", p_childfileMenu_language);
	p_childfileMenu_language->addAction(p_action_lanzh);
	p_childfileMenu_language->addAction(p_action_lanen);
	p_fileMenu_language->setMenu(p_childfileMenu_language);
	connect(p_action_lanzh, &QAction::triggered, this, &MainWindow::selectLanguageCh);
	connect(this, SIGNAL(switchLanToCh(string)), this, SLOT(switchLanguage(string)));
	connect(p_action_lanen, &QAction::triggered, this, &MainWindow::selectLanguageEn);
	connect(this, SIGNAL(switchLanToEn(string)), this, SLOT(switchLanguage(string)));

}

void MainWindow::addRecentChildMenu() {
	p_childfileMenu_recent = new QMenu(this);
	p_fileMenu_recent->setMenu(p_childfileMenu_recent);
}

void MainWindow::addHelpChildMenu() {
	p_childfileMenu_help = new QMenu(this);
	p_action_help = new QAction("Help", p_childfileMenu_help);
	p_action_ShowL = new QAction("Show License Agreement", p_childfileMenu_help);
	p_action_ShowA = new QAction("Show App Log Viewer", p_childfileMenu_help);
	p_action_tools = new QAction("Support Tools", p_childfileMenu_help);
	p_action_about = new QAction("About RationalVue...", p_childfileMenu_help);
	p_childfileMenu_help->addAction(p_action_help);
	p_childfileMenu_help->addAction(p_action_ShowL);
	p_childfileMenu_help->addAction(p_action_ShowA);
	p_childfileMenu_help->addAction(p_action_tools);
	p_childfileMenu_help->addAction(p_action_about);

	p_fileMenu_help->setMenu(p_childfileMenu_help);
}
//添加画图子菜单


void MainWindow::initMenu() {
#if 1
	QElapsedTimer cost;
	int lastTimes = 0;
	cost.start();
	setWindowTitle(QStringLiteral("RationalVue"));
	SARibbonBar* ribbon = ribbonBar();
	QFont f = ribbon->font();
	f.setFamily("微软雅黑");
	ribbon->setFont(f);
	ribbon->applitionButton()->setText(QStringLiteral("File"));
	SARibbonCategory* categoryMain = ribbon->addCategoryPage(QStringLiteral("Main"));

	createCategoryMain(categoryMain);

	SARibbonCategory* categoryOther = ribbon->addCategoryPage(QStringLiteral("Other"));
	createCategoryOther(categoryOther);
	m_contextCategory = ribbon->addContextCategory(QStringLiteral("context"), Qt::red, 1);
	SARibbonCategory* contextCategoryPage1 = m_contextCategory->addCategoryPage(QStringLiteral("Page1"));
	SARibbonCategory* contextCategoryPage2 = m_contextCategory->addCategoryPage(QStringLiteral("Page1"));
#endif
	//添加菜单
	p_fileMenu = new QMenu(this);
	setStyleSheet("QMenu::item:selected {background-color: #654321;}QMenu{background-color: #88777E;}");
	p_fileMenu_new = new QAction(p_fileMenu);
	p_fileMenu_open = new QAction(p_fileMenu);
	p_fileMenu_save = new QAction(p_fileMenu);
	p_fileMenu_saveas = new QAction(p_fileMenu);
	p_fileMenu_solutionFunLock = new QAction(p_fileMenu);
	p_fileMenu_importCAD = new QAction(p_fileMenu);
	p_fileMenu_exportCAD = new QAction(p_fileMenu);
	p_fileMenu_importFeatures = new QAction(p_fileMenu);
	p_fileMenu_export = new QAction(p_fileMenu);
	p_fileMenu_options = new QAction(p_fileMenu);
	p_fileMenu_window = new QAction(p_fileMenu);
	p_fileMenu_language = new QAction(p_fileMenu);
	p_fileMenu_help = new QAction(p_fileMenu);
	p_fileMenu_recent = new QAction(p_fileMenu);
	p_fileMenu_exit = new QAction(p_fileMenu);
	p_fileMenu_draw = new QAction(p_fileMenu);

	//设置action文字
	p_fileMenu_new->setText(tr("New"));
	p_fileMenu_new->setShortcut(QKeySequence(QLatin1String("Ctrl+N")));
	p_fileMenu_open->setText(tr("Open Solution"));
	p_fileMenu_save->setText(tr("Save Solution"));
	p_fileMenu_save->setShortcut(QKeySequence(QLatin1String("Ctrl+S")));
	p_fileMenu_saveas->setText(tr("Save Solution As"));
	p_fileMenu_solutionFunLock->setText(tr("Solution Function Lock"));
	p_fileMenu_importCAD->setText(tr("Import CAD"));
	p_fileMenu_exportCAD->setText(tr("Export CAD"));
	p_fileMenu_importFeatures->setText(tr("Import Features"));
	p_fileMenu_export->setText(tr("Export"));
	p_fileMenu_options->setText(tr("Options"));
	p_fileMenu_window->setText(tr("Window"));
	p_fileMenu_language->setText(tr("Language"));
	p_fileMenu_help->setText(tr("Help"));
	p_fileMenu_recent->setText(tr("Recent"));
	p_fileMenu_exit->setText(tr("Exit"));
	p_fileMenu_draw->setText(tr("Draw"));

	p_fileMenu->addAction(p_fileMenu_new);
	p_fileMenu->addAction(p_fileMenu_open);
	p_fileMenu->addAction(p_fileMenu_save);
	p_fileMenu->addAction(p_fileMenu_saveas);
	p_fileMenu->addAction(p_fileMenu_solutionFunLock);
	p_fileMenu->addSeparator();
	p_fileMenu->addAction(p_fileMenu_importCAD);
	p_fileMenu->addAction(p_fileMenu_exportCAD);
	p_fileMenu->addSeparator();
	p_fileMenu->addAction(p_fileMenu_importFeatures);
	p_fileMenu->addAction(p_fileMenu_export);
	p_fileMenu->addSeparator();
	p_fileMenu->addAction(p_fileMenu_options);
	p_fileMenu->addAction(p_fileMenu_window);
	p_fileMenu->addAction(p_fileMenu_language);
	p_fileMenu->addAction(p_fileMenu_help);
	p_fileMenu->addSeparator();
	p_fileMenu->addAction(p_fileMenu_recent);
	p_fileMenu->addAction(p_fileMenu_exit);
	p_fileMenu->addSeparator();
	p_fileMenu->addAction(p_fileMenu_draw);



	//添加子菜单
	addImportCADChildMenu();

	//exportCAD子菜单
	addExportCADChildMenu();
	//import Features子菜单
	addImportFeaturesChildMenu();

	//export子菜单
	addExportChildMenu();

	//options子菜单
	addOptionsChildMenu();

	//Window子菜单
	addWindowChildMenu();

	//language子菜单
	addLanguageChildMenu();
	//help子菜单
	addHelpChildMenu();

	//recent solutions子菜单
	addRecentChildMenu();


	QAction *p_action_quickAccess = new QAction(QIcon(":/icon/icon/chartDataManager.png"), "action1", this);
	p_action_quickAccess->setMenu(p_fileMenu);
	ribbon->quickAccessBar()->addButton(p_action_quickAccess);
	ribbon->quickAccessBar()->addButton(new QAction(QIcon(":/icon/icon/figureIcon.png"), "action2", this));
	ribbon->quickAccessBar()->addButton(new QAction(QIcon(":/icon/icon/information.png"), "action3", this));
	ribbon->quickAccessBar()->addButton(new QAction(QIcon(":/icon/icon/inRangDataRemove.png"), "action4", this));

}

MainWindow::MainWindow(CCommonData *commondata, QWidget *par):CCommonData(commondata), SARibbonMainWindow(par)
{
	initMenu();
	qDebug() << QString::fromStdString("MainWindow:" + m_solution->m_strSolutionName);
	m_solution->m_strSolutionName = "FirstSolution";
	initDockWidget();
}

//读取上次的布局
void MainWindow::readSettingsBefore()
{
	QSettings settings("config.ini", QSettings::IniFormat);
	restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("state").toByteArray());
}

//读取默认布局
void MainWindow::readSettingsDefault()
{
	QSettings settings("../default.ini", QSettings::IniFormat);
	restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("state").toByteArray());
}

//保存界面布局到到State.ini
void MainWindow::closeEvent(QCloseEvent *event)
{
	QSettings settings("config.ini", QSettings::IniFormat);
	settings.setIniCodec("UTF8");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("state", saveState());
}

void MainWindow::initDockWidget()
{
	//创建所有子窗口
	CDimensionReportZoneDockWidget *m_pDimensionReportZone = new CDimensionReportZoneDockWidget();
	CGraphiceZoneDockWidget *m_pGraphiceZoneDockWidget = new CGraphiceZoneDockWidget();
	CStatusBarZone *m_pStatusBarZone = new CStatusBarZone(this);

	CCreateMachineStatusZone *m_pMachineStatusZone = new CCreateMachineStatusZone(this);
	CCreatDataZoneRight *m_pDataZoneRight = new CCreatDataZoneRight(this);
	CCreateDataZoneLeftControl *m_pDataZoneLeftControl = new CCreateDataZoneLeftControl(this);
	CCreateLightControlDockWidget *m_pLightControl = new CCreateLightControlDockWidget(this);
	CCreateOperationZoneLeftControl *m_pOperationZoneLeftControl = new CCreateOperationZoneLeftControl(this);
	CCreateOperationZoneRight *m_pOperationZoneRightControl = new CCreateOperationZoneRight(this);
	CCreatePaintZoneControl *m_pPaintZoneControl = new CCreatePaintZoneControl(this);

	//connect(m_pPaintZoneDockWidget, SIGNAL(sendPointClicked(string)), m_celementpickupscene, SLOT(receivepPointEvent(string)));
	//connect(m_pPaintZoneDockWidget, SIGNAL(sendLineClicked(string)), m_pGraphiceZoneDockWidget, SLOT(receivePickupModel()));
	//connect(m_pPaintZoneDockWidget, SIGNAL(sendSectorClicked(string)), m_celementpickupscene, SLOT(receiveSectorEvent(string)));
	//connect(m_pPaintZoneDockWidget, SIGNAL(sendEllipseClicked(string)), m_celementpickupscene, SLOT(receiveEllipseEvent(string)));
	//传递打开文件按钮信号到CGraphiceZoneDockWidget类中
	connect(p_action_iges, &QAction::triggered, m_pGraphiceZoneDockWidget, &CGraphiceZoneDockWidget::receivePickupModel);

	connect(p_fileMenu_draw, &QAction::triggered, m_pDimensionReportZone, &CDimensionReportZoneDockWidget::receiveShow);

	//DockWidget初始化
	setDockNestingEnabled(true);
	m_pDataZoneLeftControl->m_pDataZoneLeftDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
	m_pDataZoneRight->m_pDataZoneRightDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
	m_pDimensionReportZone->setFeatures(QDockWidget::AllDockWidgetFeatures);
	m_pGraphiceZoneDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
	m_pMachineStatusZone->m_pMachineStatusZoneDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
	m_pOperationZoneLeftControl->m_pOperationZoneLeftDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
	m_pOperationZoneRightControl->m_pOperationZoneRightDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
	m_pPaintZoneControl->m_pPaintZoneDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
	m_pLightControl->m_pLightControlDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);

	addDockWidget(Qt::LeftDockWidgetArea, m_pDimensionReportZone);
	splitDockWidget(m_pDimensionReportZone, m_pGraphiceZoneDockWidget, Qt::Horizontal);
	splitDockWidget(m_pGraphiceZoneDockWidget, m_pPaintZoneControl->m_pPaintZoneDockWidget, Qt::Horizontal);
	splitDockWidget(m_pDimensionReportZone, m_pDataZoneLeftControl->m_pDataZoneLeftDockWidget, Qt::Vertical);
	splitDockWidget(m_pDataZoneLeftControl->m_pDataZoneLeftDockWidget, m_pDataZoneRight->m_pDataZoneRightDockWidget, Qt::Horizontal);
	splitDockWidget(m_pGraphiceZoneDockWidget, m_pOperationZoneLeftControl->m_pOperationZoneLeftDockWidget, Qt::Vertical);
	splitDockWidget(m_pOperationZoneLeftControl->m_pOperationZoneLeftDockWidget, m_pOperationZoneRightControl->m_pOperationZoneRightDockWidget, Qt::Horizontal);
	splitDockWidget(m_pPaintZoneControl->m_pPaintZoneDockWidget, m_pLightControl->m_pLightControlDockWidget, Qt::Vertical);
	splitDockWidget(m_pLightControl->m_pLightControlDockWidget, m_pMachineStatusZone->m_pMachineStatusZoneDockWidget, Qt::Vertical);

	//设置状态栏
	this->setStatusBar(m_pStatusBarZone);
	//读取默认布局
	readSettingsDefault();

//	readSettingsBefore();
}

void MainWindow::onShowContextCategory(bool on)
{
	ribbonBar()->setContextCategoryVisible(m_contextCategory, on);
}

void MainWindow::onWpsStyle(bool on)
{
	if (on)
		ribbonBar()->setRibbonStyle(SARibbonBar::WpsLiteStyle);
	else
		ribbonBar()->setRibbonStyle(SARibbonBar::OfficeStyle);
	update();
}

void MainWindow::createCategoryMain(SARibbonCategory *page)
{
	QElapsedTimer cost;
	cost.start();
	SARibbonToolButton * btn;
	SARibbonMenu* menu = new SARibbonMenu(this);
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("1111111"));
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("1"));
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("11"));
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("111"));
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("11111"));
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("1111111"));
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("11111111"));
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("1111111111"));
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("1111111111111"));
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("1111111111111111111111111111"));

	int lastTimes = 0;
	SARibbonPannel* pannel = page->addPannel(QStringLiteral("Panel 1"));

	QAction* act = new QAction(this);
	act->setIcon(QIcon(":/icon/icon/save.png"));
	act->setText(QStringLiteral("SAve"));
	pannel->addLargeAction(act);
	connect(act, &QAction::triggered, this, [this](bool b) {
		this->m_edit->append("action clicked");
	});

	act = new QAction(this);
	act->setIcon(QIcon(":/icon/icon/save.png"));
	act->setText(QStringLiteral("hide ribbon"));
	act->setCheckable(true);
	pannel->addSmallAction(act);
	connect(act, &QAction::triggered, this, [this](bool b) {
		this->ribbonBar()->setHideMode(b);
	});

	act = new QAction(this);
	act->setIcon(QIcon(":/icon/icon/save.png"));
	act->setText(QStringLiteral("show hide button"));
	act->setCheckable(true);
	pannel->addSmallAction(act);
	connect(act, &QAction::triggered, this, [this](bool b) {
		this->ribbonBar()->showHideModeButton(b);
	});

	act = new QAction(this);
	act->setIcon(QIcon(":/icon/icon/filter.png"));
	act->setText(QStringLiteral("use wps style"));
	act->setCheckable(true);
	act->setChecked(false);
	btn = pannel->addSmallAction(act);
	connect(act, SIGNAL(triggered(bool)), this, SLOT(onWpsStyle(bool)));

	act = new QAction(this);
	act->setIcon(QIcon(":/icon/icon/folder.png"));
	act->setText(QStringLiteral("test 3"));
	act->setMenu(menu);
	btn = pannel->addSmallAction(act);
	btn->setPopupMode(QToolButton::MenuButtonPopup);

	act = new QAction(this);
	act->setIcon(QIcon(":/icon/icon/folder.png"));
	act->setText(QStringLiteral("test 4"));
	act->setMenu(menu);
	btn = pannel->addSmallAction(act);
	btn->setPopupMode(QToolButton::InstantPopup);

	pannel->addSeparator();




	act = new QAction(this);
	act->setIcon(QIcon(":/icon/icon/folder.png"));
	act->setText(QStringLiteral("DelayedPopup"));
	act->setMenu(menu);
	btn = pannel->addLargeAction(act);
	btn->setPopupMode(QToolButton::DelayedPopup);
	btn->setObjectName("SA_DelayedPopup");
	connect(act, &QAction::triggered, this, &MainWindow::onDelayedPopupCheckabletriggered);

	act = new QAction(this);
	act->setIcon(QIcon(":/icon/icon/folder.png"));
	act->setText(QStringLiteral("MenuButtonPopup"));
	act->setMenu(menu);
	btn = pannel->addLargeAction(act);
	btn->setObjectName(QStringLiteral("MenuButtonPopup"));
	btn->setPopupMode(QToolButton::MenuButtonPopup);
	connect(act, &QAction::triggered, this, &MainWindow::onMenuButtonPopupCheckabletriggered);

	act = new QAction(this);
	act->setIcon(QIcon(":/icon/icon/Graph-add.png"));
	act->setText(QStringLiteral("InstantPopup"));
	act->setMenu(menu);
	btn = pannel->addLargeAction(act);
	btn->setObjectName("buttonInstantPopup");
	btn->setPopupMode(QToolButton::InstantPopup);
	connect(act, &QAction::triggered, this, &MainWindow::onInstantPopupCheckabletriggered);

	act = new QAction(this);
	act->setCheckable(true);
	act->setIcon(QIcon(":/icon/icon/folder.png"));
	act->setText(QStringLiteral("DelayedPopup"));
	act->setMenu(menu);
	btn = pannel->addLargeAction(act);
	btn->setPopupMode(QToolButton::DelayedPopup);
	btn->setCheckable(true);
	connect(act, &QAction::triggered, this, &MainWindow::onDelayedPopupCheckableTest);

	act = new QAction(this);
	act->setCheckable(true);
	act->setIcon(QIcon(":/icon/icon/folder.png"));
	act->setText(QStringLiteral("MenuButtonPopup\n checkable"));
	act->setMenu(menu);
	btn = pannel->addLargeAction(act);
	btn->setPopupMode(QToolButton::MenuButtonPopup);
	btn->setCheckable(true);
	connect(act, &QAction::triggered, this, &MainWindow::onMenuButtonPopupCheckableTest);

	act = new QAction(this);
	act->setCheckable(true);
	act->setIcon(QIcon(":/icon/icon/Graph-add.png"));
	act->setText(QStringLiteral("InstantPopup"));
	act->setMenu(menu);
	btn = pannel->addLargeAction(act);
	btn->setCheckable(true);
	btn->setPopupMode(QToolButton::InstantPopup);
	connect(act, &QAction::triggered, this, &MainWindow::onInstantPopupCheckableTest);

	SARibbonPannel* panne2 = page->addPannel(QStringLiteral("pannel 2"));
	act = new QAction(this);
	act->setCheckable(true);
	act->setIcon(QIcon(":/icon/icon/Graph-add.png"));
	act->setText(QStringLiteral("show\nContext"));
	btn = panne2->addLargeAction(act);
	btn->setCheckable(true);
	//btn->setPopupMode(QToolButton::InstantPopup);
	connect(act, &QAction::triggered, this, [this](bool on) {
		if (on)
			this->ribbonBar()->showContextCategory(this->m_contextCategory);
		else
			this->ribbonBar()->hideContextCategory(this->m_contextCategory);
	});

	act = new QAction(this);
	act->setCheckable(true);
	act->setIcon(QIcon(":/icon/icon/Graph-add.png"));
	act->setText(QStringLiteral("unactive"));
	act->setMenu(menu);
	btn = panne2->addLargeAction(act);
	btn->setCheckable(true);
	btn->setPopupMode(QToolButton::InstantPopup);
	btn->setEnabled(false);


	SARibbonComboBox* com = new SARibbonComboBox(this);
	com->setSizePolicy(QSizePolicy::Expanding,
		QSizePolicy::Fixed);
	com->setWindowIcon(QIcon(":/icon/icon/Graph-add.png"));
	com->setWindowTitle("ComboBox");
	for (int i = 0; i < 40; ++i)
		com->addItem("SARibbonComboBox test");
	com->setEditable(true);
	pannel->addWidget(com);

	com = new SARibbonComboBox(this);
	com->setSizePolicy(QSizePolicy::Expanding,
		QSizePolicy::Fixed);
	com->setWindowIcon(QIcon(":/icon/icon/folder.png"));
	com->setWindowTitle("ComboBox Editable");
	for (int i = 0; i < 40; ++i)
		com->addItem("111111111111");
	pannel->addWidget(com);

	SARibbonLineEdit* lineEdit = new SARibbonLineEdit(this);
	lineEdit->setSizePolicy(QSizePolicy::Expanding,
		QSizePolicy::Fixed);
	lineEdit->setWindowIcon(QIcon(":/icon/icon/folder.png"));
	lineEdit->setWindowTitle("Line Edit");
	lineEdit->setText("SARibbonLineEdit");
	pannel->addWidget(lineEdit);
	QWidget* w = lineEdit->parentWidget();
	while (w)
	{
		qDebug() << w->metaObject()->className();
		w = w->parentWidget();
	}
	SARibbonCheckBox* checkBox = new SARibbonCheckBox(this);
	checkBox->setSizePolicy(QSizePolicy::Expanding,
		QSizePolicy::Fixed);
	checkBox->setWindowIcon(QIcon(":/icon/icon/folder.png"));
	checkBox->setText("checkBox");
	pannel->addWidget(checkBox);

	pannel->setExpanding();
	QAction* optAct = new QAction(this);
	pannel->addOptionAction(optAct);
}

void MainWindow::createCategoryOther(SARibbonCategory *page)
{
	SARibbonMenu* menu = new SARibbonMenu(this);
	QAction * item = menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("1111111"));
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("1111111"));
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("1111111"));
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("1111111"));
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("1111111"));
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("1111111"));
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("1111111"));
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("1111111"));
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("1111111"));
	menu->addAction(QIcon(":/icon/icon/folder.png"), QStringLiteral("1111111"));

	SARibbonPannel* pannel = page->addPannel(QStringLiteral("pannel 1"));
	SARibbonButtonGroupWidget* btnGroup = new SARibbonButtonGroupWidget(pannel);
	btnGroup->setFrameShape(QFrame::Box);
	btnGroup->addButton(new QAction(QIcon(":/icon/icon/figureIcon.png"), "", this));
	btnGroup->addButton(new QAction(QIcon(":/icon/icon/information.png"), "", this));
	pannel->addWidget(btnGroup, 0, 3);

	SARibbonToolButton* btn;
	btn = pannel->addLargeAction(item);
	btn->setIcon(QIcon(":/icon/icon/folder.png"));
	btn->setText(QStringLiteral("un format\nicon"));
	btn->setPopupMode(QToolButton::DelayedPopup);
	btn->setFixedHeight(78);
	btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	btn->setMenu(menu);
	pannel->addWidget(btn);

	btn = pannel->addLargeAction(item);
	btn->setIcon(QIcon(":/icon/icon/folder.png"));
	btn->setText(QStringLiteral("change page\ntest"));
	btn->setPopupMode(QToolButton::MenuButtonPopup);
	btn->setFixedHeight(78);
	btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	btn->setMenu(menu);
	pannel->addWidget(btn);

	btn = pannel->addLargeAction(item);
	btn->setIcon(QIcon(":/icon/icon/folder.png"));
	btn->setText(QStringLiteral("LargeBtn"));
	btn->setPopupMode(QToolButton::InstantPopup);
	btn->setFixedHeight(78);
	btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	btn->setMenu(menu);
	pannel->addWidget(btn);

	SARibbonGallery* gallery = pannel->addGallery();
	SARibbonGalleryGroup*group = gallery->addGalleryGroup();
	for (int i = 0; i < 100; ++i)
	{
		group->addItem(QIcon(":/icon/icon/folder.png"));
	}
	QAction* optAct = new QAction(this);
	pannel->addOptionAction(optAct);
	pannel->setObjectName("debug");

}

void MainWindow::onMenuButtonPopupCheckableTest(bool b)
{
	m_edit->append(QStringLiteral("MenuButtonPopupCheckableTest : %1").arg(b));
}

void MainWindow::onInstantPopupCheckableTest(bool b)
{
	m_edit->append(QStringLiteral("InstantPopupCheckableTest : %1").arg(b));
}

void MainWindow::onDelayedPopupCheckableTest(bool b)
{
	m_edit->append(QStringLiteral("DelayedPopupCheckableTest : %1").arg(b));
}

void MainWindow::onMenuButtonPopupCheckabletriggered(bool b)
{
	m_edit->append(QStringLiteral("MenuButtonPopupCheckabletriggered : %1").arg(b));
}

void MainWindow::onInstantPopupCheckabletriggered(bool b)
{
	m_edit->append(QStringLiteral("InstantPopupCheckabletriggered : %1").arg(b));
}

void MainWindow::onDelayedPopupCheckabletriggered(bool b)
{
	m_edit->append(QStringLiteral("DelayedPopupCheckabletriggered : %1").arg(b));
}

//切换系统语言
void MainWindow::switchLanguage(string lan) {

	std::ofstream output;
	output.open(tr_file_path, std::ios::out | std::ios::binary);
	if (output.is_open()) {
		qDebug() << "file open success";

		output << "language=" + lan;
		output.close();
	}
	else {
		qDebug() << "file open success";
	}
	int result = QMessageBox::question(this, QStringLiteral("修改程序语言"), QStringLiteral("立即重启程序？"), QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Cancel);
	if (result == QMessageBox::Yes) {
		exit(-1);
	}
}

//选择中文的槽函数，触发切换到中文的信号
void MainWindow::selectLanguageCh() {
	emit switchLanToCh("Chinese");
}
//选择英文的槽函数，触发切换到英文的信号
void MainWindow::selectLanguageEn() {
	emit switchLanToEn("English");
}
