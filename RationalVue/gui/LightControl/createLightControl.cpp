#include "createLightControl.h"
#include "lightCircle.h"
//#include "ui_lightControl.h"
#include "qdesktopwidget.h"
#include<QDebug>
#include<qfile.h>
#include<qtoolbutton.h>
#include<quiloader.h>

CCreateLightControlDockWidget::CCreateLightControlDockWidget(CCommonData *commondata):CCommonData(commondata)
{
	//测试输出CCommonData数据
	qDebug() << QString::fromStdString( "测试:"+ m_solution->m_strSolutionName);
	qDebug() << QString::fromStdString("解决方案:"+m_solution->m_strSolutionName+ "读取到m_solution->m_bReadOnly的值为:")+ m_solution->m_bReadOnly;

	//动态加载ui文件
	QUiLoader loader;
	QFile file(":/ui/gui/LightControl/lightControlDockWidget.ui");
	file.open(QFile::ReadOnly);

	m_pLightControlDockWidget = static_cast<QDockWidget*>(loader.load(&file));

	//绘制灯光控制圆形控制台
	lightCircle* lcp = new lightCircle(m_pLightControlDockWidget->findChild<QWidget*>("lightCirclePanel"));
	lcp->setFixedSize(QSize(180,180));
		//lightCircle文件中可以自动获取qwidget的宽和高以此绘出控制台大小，但它并没有随窗口大小变化，现设定一个不能更改的大小
	
//	file.close();

}


QDockWidget* CCreateLightControlDockWidget::init() 
{

	return m_pLightControlDockWidget;
}


CCreateLightControlDockWidget::~CCreateLightControlDockWidget()
{
	delete m_pLightControlDockWidget;
}


