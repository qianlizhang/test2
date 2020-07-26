#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "SARibbonMainWindow.h"
#include "dataZoneLeft.h"
#include "dataZoneRight.h"
#include "dimensionReportZone.h"
#include "graphiceZone.h"
#include "createLightControl.h"
#include "machineStatusZone.h"
#include "createoperationzoneright.h"
#include "createOperationZoneLeftControl.h"
#include "createPaintZoneControl.h"
#include "statusBarZone.h"
#include<fstream>
#include"CommonData.h"
using namespace std;
class SARibbonCategory;
class SARibbonContextCategory;
class QTextEdit;
class MainWindow : public SARibbonMainWindow,CCommonData
{
	Q_OBJECT
public:
	void static loadTranslate();
	static QString tr_file;
	MainWindow(CCommonData *commondata = nullptr, QWidget* par = nullptr);
	void readSettingsDefault();
	void readSettingsBefore();
	void initMenu();
	void initDockWidget();
	void addImportCADChildMenu();
	void addExportCADChildMenu();
	void addImportFeaturesChildMenu();
	void addExportChildMenu();
	void addOptionsChildMenu();
	void addWindowChildMenu();
	void addLanguageChildMenu();
	void addHelpChildMenu();
	void addRecentChildMenu();
signals:
	void switchLanToEn(string lan);
	void switchLanToCh(string lan);
protected:
	void closeEvent(QCloseEvent *event);
private slots:
	void onShowContextCategory(bool on);
	void onWpsStyle(bool on);
private:
	void createCategoryMain(SARibbonCategory* page);
	void createCategoryOther(SARibbonCategory* page);
private slots:
	void onMenuButtonPopupCheckableTest(bool b);
	void onInstantPopupCheckableTest(bool b);
	void onDelayedPopupCheckableTest(bool b);

	void onMenuButtonPopupCheckabletriggered(bool b);
	void onInstantPopupCheckabletriggered(bool b);
	void onDelayedPopupCheckabletriggered(bool b);
	void selectLanguageEn();
	void selectLanguageCh();
	void switchLanguage(string lan);
public:
	CCreatDataZoneRight *m_pDataZoneRightDockWidget;
	CDimensionReportZoneDockWidget *m_pDimensionReportZone;
	CGraphiceZoneDockWidget *m_pGraphiceZoneDockWidget;
	CStatusBarZone *m_pStatusBarZone;

	CCreateMachineStatusZone *m_pMachineStatusZone;
	CCreateDataZoneLeftControl *m_pDataZoneLeftControl;
	CCreateLightControlDockWidget *m_pLightControl;
	CCreateOperationZoneLeftControl *m_pOperationZoneLeftControl;
	CCreateOperationZoneRight *m_pOperationZoneRightControl;
	CCreatePaintZoneControl *m_pPaintZoneControl;
private:
	SARibbonContextCategory* m_contextCategory;
	QTextEdit* m_edit;

	QMenu *p_fileMenu;
	QAction *p_fileMenu_new;
	QAction *p_fileMenu_open;
	QAction *p_fileMenu_save;
	QAction *p_fileMenu_saveas;
	QAction *p_fileMenu_solutionFunLock;
	QAction *p_fileMenu_importCAD;
	QAction *p_fileMenu_exportCAD;
	QAction *p_fileMenu_importFeatures;
	QAction *p_fileMenu_export;
	QAction *p_fileMenu_options;
	QAction *p_fileMenu_window;
	QAction *p_fileMenu_language;
	QAction *p_fileMenu_help;
	QAction *p_fileMenu_recent;
	QAction *p_fileMenu_exit;

	QAction *p_fileMenu_draw;//

	QMenu *p_childfileMenu_importCAD;
	QAction *p_action_iges;
	QAction *p_action_dxf;
	QAction *p_action_step;
	QAction *p_action_parasolid;
	QAction *p_action_catia;
	QAction *p_action_ug;
	QAction *p_action_proe;
	QAction *p_action_solidwork;
	QAction *p_action_jt3d;
	QAction *p_action_inventor;
	QAction *p_action_solidedge;
	QAction *p_action_drill;
	QMenu *p_childfileMenu_exportCAD;
	QAction *p_action_exportCAD_igse;
	QAction *p_action_exportCAD_dxf;
	QAction *p_action_exportCAD_includeNom;
	QAction *p_action_exportCAD_includeAct;
	QAction *p_action_exportCAD_includeMea;
	QAction *p_action_exportCAD_export;

	QMenu *p_childfileMenu_importFeatures;
	QAction *p_action_fromText;
	QAction *p_action_fromDXF;
	QAction *p_action_with;
	QAction *p_action_importCircle;
	QAction *p_action_importLine;
	QAction *p_action_importCurve;

	QMenu *p_childfileMenu_export;
	QAction *p_action_exportAsQ;

	//options子菜单
	QMenu *p_childfileMenu_options;
	QAction *p_action_App;
	QAction *p_action_Imp;
	QAction *p_action_Exp;

	QMenu *p_childfileMenu_window;
	QAction *p_action_Restore;
	QAction *p_action_SwitchI;
	QAction *p_action_SwitchG;
	QAction *p_action_SwitchD;
	QAction *p_action_IO;
	QAction *p_action_Shortcut;

	QMenu *p_childfileMenu_language;
	QAction *p_action_lanzh;
	QAction *p_action_lanen;

	//help子菜单
	QMenu *p_childfileMenu_help;
	QAction *p_action_help;
	QAction *p_action_ShowL;
	QAction *p_action_ShowA;
	QAction *p_action_tools;
	QAction *p_action_about;
	QMenu *p_childfileMenu_recent;


};

#endif // MAINWINDOW_H