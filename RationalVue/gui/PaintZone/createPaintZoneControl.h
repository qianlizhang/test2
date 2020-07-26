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
	//	void sendPointClicked(string);			//���ͻ�����ź�
		//void sendLineClicked(string);			//���ͻ�ֱ�ߵ��ź�
	//	void sendSectorClicked(string);		//���ͻ����ε��ź�
	//	void sendEllipseClicked(string);		//���ͻ���Բ���ź�
	void sendRectClicked(string);

public slots:
	void on_toolButton_clicked();			//�����εĵ���¼�
	void on_toolButton_2_clicked();		//�����������ߵĵ���¼�
	void on_toolButton_3_clicked();		//����ĵ���¼�
	void on_toolButton_4_clicked();		//��ֱ�ߵĵ���¼�
	void on_toolButton_5_clicked();		//�����ߵĵ���¼�
	void on_toolButton_6_clicked();		//��Բ�ĵ���¼�
	void on_toolButton_7_clicked();		//�����εĵ���¼�
	void on_toolButton_8_clicked();		//����Բ�ĵ���¼�
	void on_toolButton_9_clicked();		//��****�ĵ���¼�

	void on_toolButton_10_clicked();		//��Բ���ĵ���¼�

	void on_toolButton_16_clicked();	//�����¼�
	void on_toolButton_18_clicked();	//��Ե����¼�

private:

};

#endif // CREATEPAINTZONECONTROL_H
