#include "createPaintZoneControl.h"
#include <quiloader.h>
#include <qfile.h>
#include <qtoolbutton.h>
#include <QDebug>
#include <QKeyEvent>

extern QString globalmPickupModel; //声明外部变量

CCreatePaintZoneControl::CCreatePaintZoneControl(CCommonData *commondata) :CCommonData(commondata)
{
	//----------------------测试CommonData-------------------------
	m_solution->m_bReadOnly = true;
	qDebug()<<QString::fromLocal8Bit("解决方案:")+QString::fromStdString(m_solution->m_strSolutionName)+ QString::fromLocal8Bit("设置m_solution->m_bReadOnly的值为:")+ m_solution->m_bReadOnly;
	
	//----------------------动态加载ui------------------------------
	QUiLoader loader;
	QFile file(":/ui/gui/PaintZone/paintZoneDockwidget.ui");
	file.open(QFile::ReadOnly);
	m_pPaintZoneDockWidget = static_cast<QDockWidget*>(loader.load(&file));
	file.close();

	QToolButton *btn_1 = m_pPaintZoneDockWidget->findChild<QToolButton*>("toolButton");
	connect(btn_1, SIGNAL(clicked()), this, SLOT(on_toolButton_clicked()));
	QToolButton *btn_2 = m_pPaintZoneDockWidget->findChild<QToolButton*>("toolButton_2");
	connect(btn_2, SIGNAL(clicked()), this, SLOT(on_toolButton_2_clicked()));
	QToolButton *btn_3 = m_pPaintZoneDockWidget->findChild<QToolButton*>("toolButton_3");
	connect(btn_3, SIGNAL(clicked()), this, SLOT(on_toolButton_3_clicked()));
	QToolButton *btn_4 = m_pPaintZoneDockWidget->findChild<QToolButton*>("toolButton_4");
	connect(btn_4, SIGNAL(clicked()), this, SLOT(on_toolButton_4_clicked()));
	QToolButton *btn_5 = m_pPaintZoneDockWidget->findChild<QToolButton*>("toolButton_5");
	connect(btn_5, SIGNAL(clicked()), this, SLOT(on_toolButton_5_clicked()));
	QToolButton *btn_6 = m_pPaintZoneDockWidget->findChild<QToolButton*>("toolButton_6");
	connect(btn_6, SIGNAL(clicked()), this, SLOT(on_toolButton_6_clicked()));
	QToolButton *btn_7 = m_pPaintZoneDockWidget->findChild<QToolButton*>("toolButton_7");
	connect(btn_7, SIGNAL(clicked()), this, SLOT(on_toolButton_7_clicked()));
	QToolButton *btn_8 = m_pPaintZoneDockWidget->findChild<QToolButton*>("toolButton_8");
	connect(btn_8, SIGNAL(clicked()), this, SLOT(on_toolButton_8_clicked()));
	QToolButton *btn_9 = m_pPaintZoneDockWidget->findChild<QToolButton*>("toolButton_9");
	connect(btn_9, SIGNAL(clicked()), this, SLOT(on_toolButton_9_clicked()));
	QToolButton *btn_10 = m_pPaintZoneDockWidget->findChild<QToolButton*>("toolButton_10");
	connect(btn_10, SIGNAL(clicked()), this, SLOT(on_toolButton_10_clicked()));
	QToolButton *btn_16 = m_pPaintZoneDockWidget->findChild<QToolButton*>("toolButton_16");
	connect(btn_16, SIGNAL(clicked()), this, SLOT(on_toolButton_16_clicked()));
	//18边缘检测
	QToolButton *btn_18 = m_pPaintZoneDockWidget->findChild<QToolButton*>("toolButton_18");
	connect(btn_18, SIGNAL(clicked()), this, SLOT(on_toolButton_18_clicked()));

}

QDockWidget* CCreatePaintZoneControl::init()
{
	return m_pPaintZoneDockWidget;
}

CCreatePaintZoneControl::~CCreatePaintZoneControl()
{
    
}

//画矩形的点击事件
void CCreatePaintZoneControl::on_toolButton_clicked()
{
	globalmPickupModel = "rect";
	emit sendRectClicked("rect");
	//qDebug() << "globalmPickupModel==========" << globalmPickupModel;
}
//画贝塞尔曲线的点击事件
void CCreatePaintZoneControl::on_toolButton_2_clicked()
{
	globalmPickupModel = "bezircurve";
	//qDebug() << "globalmPickupModel==========" << globalmPickupModel;
}
//画点的点击事件
void CCreatePaintZoneControl::on_toolButton_3_clicked()
{
	//qDebug() << "toolButton_3 clicked event============";
	//emit sendPointClicked("point");
	globalmPickupModel = "point";
	//qDebug() << "globalmPickupModel==========" << globalmPickupModel;
}
//画直线的点击事件
void CCreatePaintZoneControl::on_toolButton_4_clicked()
{
	//qDebug() << "toolButton_4 clicked event============";
	//emit sendLineClicked("line");
	globalmPickupModel = "line";
	//qDebug() << "globalmPickupModel==========" << globalmPickupModel;
}
//画曲线的点击事件
void CCreatePaintZoneControl::on_toolButton_5_clicked()
{
	globalmPickupModel = "path";
	//qDebug() << "globalmPickupModel==========" << globalmPickupModel;
}
//画圆的点击事件
void CCreatePaintZoneControl::on_toolButton_6_clicked()
{
	globalmPickupModel = "circle";
	//qDebug() << "globalmPickupModel==========" << globalmPickupModel;
}
//画扇形的点击事件
void CCreatePaintZoneControl::on_toolButton_7_clicked()
{
	//qDebug() << "toolButton_7 clicked event============";
	//emit sendSectorClicked("sector");
	globalmPickupModel = "sector";
	//qDebug() << "globalmPickupModel==========" << globalmPickupModel;
}
//画椭圆的点击事件
void CCreatePaintZoneControl::on_toolButton_8_clicked()
{
	//qDebug() << "toolButton_8 clicked event============";
	//emit sendEllipseClicked("ellipse");
	globalmPickupModel = "ellipse";
	//qDebug() << "globalmPickupModel==========" << globalmPickupModel;
}
//画****的点击事件
void CCreatePaintZoneControl::on_toolButton_9_clicked()
{
	globalmPickupModel = "*****";
}
//画圆弧的点击事件
void CCreatePaintZoneControl::on_toolButton_10_clicked()
{
	globalmPickupModel = "arc";
	//qDebug() << "globalmPickupModel==========" << globalmPickupModel;
}
//撤销事件
void CCreatePaintZoneControl::on_toolButton_16_clicked()
{
	globalmPickupModel = "nulll";
}
//边缘检测事件
void CCreatePaintZoneControl::on_toolButton_18_clicked()
{
	globalmPickupModel = "edge detection";
}