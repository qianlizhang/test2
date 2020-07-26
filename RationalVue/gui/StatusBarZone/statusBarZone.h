/*
 * @Description: 
 * @Author: szq
 * @Github: https://github.com/MrQqqq
 * @Date: 2020-07-11 15:59:26
 * @LastEditors: szq
 * @LastEditTime: 2020-07-11 18:27:05
 * @FilePath: \QTCreateByCMake\GUI\StatusBarZone\statusBarZone.h
 */ 
#ifndef CStatusBatZone_H
#define CStatusBatZone_H

#include <QStatusBar>
#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include "CommonData.h"
class CStatusBarZone : public QStatusBar, public CCommonData
{
    Q_OBJECT

public:
    explicit CStatusBarZone(CCommonData *commondata, QWidget *parent = 0);
    ~CStatusBarZone();

    QPushButton *m_pPushButton_1;
    QPushButton *m_pPushButton_2;
    QPushButton *m_pPushButton_3;
    QPushButton *m_pPushButton_4;
    QPushButton *m_pPushButton_5;
    QPushButton *m_pPushButton_6;

    QComboBox *m_pComboBox_1;
    QComboBox *m_pComboBox_2;
    QComboBox *m_pComboBox_3;
    QComboBox *m_pComboBox_4;
    QComboBox *m_pComboBox_5;

    QLabel *m_pBlank;

public slots:
	void changeValue();

};

#endif // CStatusBatZone_H
