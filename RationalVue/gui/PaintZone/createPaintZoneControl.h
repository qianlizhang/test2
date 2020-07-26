#ifndef CREATEPAINTZONECONTROL_H
#define CREATEPAINTZONECONTROL_H

#include <QDockWidget>
#include "CommonData.h"
using namespace std;

class CCreatePaintZoneControl : public QWidget,CCommonData
//class CCreatePaintZoneControl : public QWidget
{
	Q_OBJECT

public:
	CCreatePaintZoneControl(CCommonData *commondata);
    ~CCreatePaintZoneControl();
	QDockWidget* init();
	QDockWidget* m_pPaintZoneDockWidget;

signals:
	//	void sendPointClicked(string);			//发送画点的信号
		//void sendLineClicked(string);			//发送画直线的信号
	//	void sendSectorClicked(string);		//发送画扇形的信号
	//	void sendEllipseClicked(string);		//发送画椭圆的信号
	void sendRectClicked(string);

public slots:
	void on_toolButton_clicked();			//画矩形的点击事件
	void on_toolButton_2_clicked();		//画贝塞尔曲线的点击事件
	void on_toolButton_3_clicked();		//画点的点击事件
	void on_toolButton_4_clicked();		//画直线的点击事件
	void on_toolButton_5_clicked();		//画曲线的点击事件
	void on_toolButton_6_clicked();		//画圆的点击事件
	void on_toolButton_7_clicked();		//画扇形的点击事件
	void on_toolButton_8_clicked();		//画椭圆的点击事件
	void on_toolButton_9_clicked();		//画****的点击事件

	void on_toolButton_10_clicked();		//画圆弧的点击事件

	void on_toolButton_16_clicked();	//撤销事件
	void on_toolButton_18_clicked();	//边缘检测事件

private:

};

#endif // CREATEPAINTZONECONTROL_H
