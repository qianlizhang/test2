#ifndef DATAZONELEFT_H
#define DATAZONELEFT_H

#include <QDockWidget>
#include<QWidget>
#include<QVBoxLayout>
#include<QString>
#include<QIcon>
#include<QToolButton>
#include<QCheckBox>
#include<QListWidget>
#include<QListWidgetItem>
#include<QMenu>
#include<QUiLoader>
#include<QFile>
#include <QtUiTools/QtUiTools>
#include "CommonData.h"
//namespace Ui {
//class CDataZoneLeft;
//}

class CCreateDataZoneLeftControl:CCommonData
{

public:
	CCreateDataZoneLeftControl(CCommonData *commondata);
    ~CCreateDataZoneLeftControl();


	QWidget *m_pWidget;
	QWidget *m_pWidget_1;
	QWidget *m_pWidget_2;


	QDockWidget *m_pDataZoneLeftDockWidget;

	QVBoxLayout *m_pVBoxLayout;
	QVBoxLayout *m_pVBoxLayout_2;

	QListWidget *m_pListWidget;

	QHBoxLayout *m_pHBoxLayout;

	QToolButton *m_pToolButton;
	QToolButton *m_pToolButton_2;
	QToolButton *m_pToolButton_3;
	QToolButton *m_pToolButton_4;
	QToolButton *m_pToolButton_5;
	QToolButton *m_pToolButton_6;
	QToolButton *m_pToolButton_7;
	QToolButton *m_pToolButton_8;
	QToolButton *m_pToolButton_9;

	QMenu *m_pMenu;

	QCheckBox *m_pCheckBox;
	QCheckBox *m_pCheckBox_2;
	QCheckBox *m_pCheckBox_3;
	QCheckBox *m_pCheckBox_4;
	QCheckBox *m_pCheckBox_5;
	QCheckBox *m_pCheckBox_6;
	QCheckBox *m_pCheckBox_7;
	QCheckBox *m_pCheckBox_8;
	QCheckBox *m_pCheckBox_9;

	QListWidgetItem * m_pItem;
	QListWidgetItem * m_pItem_2;
	QListWidgetItem * m_pItem_3;
	QListWidgetItem * m_pItem_4;
	QListWidgetItem * m_pItem_5;
	QListWidgetItem * m_pItem_6;
	QListWidgetItem * m_pItem_7;
	QListWidgetItem * m_pItem_8;
	QListWidgetItem * m_pItem_9;

private:
//    Ui::CDataZoneLeft *ui;
};

#endif // DATAZONELEFT_H
