/*
 * @Description: 
 * @Author: szq
 * @Github: https://github.com/MrQqqq
 * @Date: 2020-07-11 15:59:50
 * @LastEditors: szq
 * @LastEditTime: 2020-07-11 18:28:28
 * @FilePath: \QTCreateByCMake\GUI\StatusBarZone\statusBarZone.cpp
 */ 
#include "statusBarZone.h"
#include <QTextEdit>
#include <QLabel>
#include <QListView>
#include <QStatusBar>
#include <QDebug>
#include <QComboBox>
CStatusBarZone::CStatusBarZone(CCommonData *commondata, QWidget *parent):
    QStatusBar(parent), CCommonData(commondata)
{
    m_pPushButton_1 = new QPushButton;
    m_pPushButton_2 = new QPushButton;
    m_pPushButton_3 = new QPushButton;
    m_pPushButton_4 = new QPushButton;
    m_pPushButton_5 = new QPushButton;
    m_pPushButton_6 = new QPushButton;
    m_pComboBox_1 = new QComboBox;
    m_pComboBox_2 = new QComboBox;
    m_pComboBox_3 = new QComboBox;
    m_pComboBox_4 = new QComboBox;
    m_pComboBox_5 = new QComboBox;
    m_pBlank = new QLabel("         ");
    m_pPushButton_1->setFixedSize(20,20);
    m_pPushButton_2->setFixedSize(20,20);
    m_pPushButton_3->setFixedSize(20,20);
    m_pPushButton_4->setFixedSize(20,20);
    m_pPushButton_5->setFixedSize(20,20);
    m_pPushButton_6->setFixedSize(20,20);
    m_pComboBox_1->setFixedSize(115,20);
    m_pComboBox_2->setFixedSize(115,20);
    m_pComboBox_3->setFixedSize(115,20);
    m_pComboBox_4->setFixedSize(115,20);
    m_pComboBox_5->setFixedSize(135,20);
    m_pBlank->setFixedWidth(115);
    m_pPushButton_1->setStyleSheet("QPushButton {background-color: rgb(151,150,156);border: 2px solid gray;border-radius: 3px;}");
    m_pPushButton_2->setStyleSheet("QPushButton {background-color: rgb(151,150,156);border: 2px solid gray;border-radius: 3px;}");
    m_pPushButton_3->setStyleSheet("QPushButton {background-color: rgb(151,150,156);border: 2px solid gray;border-radius: 3px;}");
    m_pPushButton_4->setStyleSheet("QPushButton {background-color: rgb(151,150,156);border: 2px solid gray;border-radius: 3px;}");
    m_pPushButton_5->setStyleSheet("QPushButton {background-color: rgb(151,150,156);border: 2px solid gray;border-radius: 3px;}");
    m_pPushButton_6->setStyleSheet("QPushButton {background-color: rgb(151,150,156);border: 2px solid gray;border-radius: 3px;}");
    m_pPushButton_6->setIcon(QIcon(":/light.png"));
    m_pComboBox_1->setStyleSheet("QComboBox {border: 2px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;background-color: rgb(213,212,217);font: 9pt 'Arial Narrow';} "
                           "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 18px;border-left-width: 1px;border-left-color: darkgray;border-left-style: solid;background-color: rgb(130,130,137);}"
                           "QComboBox::down-arrow {image: url(':/jiantou.png');}"
                           "QComboBox QAbstractItemView{font-size: 15px;font-family: 'Arial Narrow';outline: 0px;}"
                           "QComboBox QAbstractItemView::item {height: 18px;background-color: rgb(213,212,217);}"
                           "QComboBox QAbstractItemView::item:selected{background-color: rgb(49,106,197);}");
    m_pComboBox_2->setStyleSheet("QComboBox {border: 2px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;background-color: rgb(213,212,217);font: 9pt 'Arial Narrow';} "
                           "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 18px;border-left-width: 1px;border-left-color: darkgray;border-left-style: solid;background-color: rgb(130,130,137);}"
                           "QComboBox::down-arrow {image: url(':/jiantou.png');}"
                           "QComboBox QAbstractItemView{font-size: 15px;font-family: 'Arial Narrow';outline: 0px;}"
                           "QComboBox QAbstractItemView::item {height: 18px;background-color: rgb(213,212,217);}"
                           "QComboBox QAbstractItemView::item:selected{background-color: rgb(49,106,197);}");
    m_pComboBox_3->setStyleSheet("QComboBox {border: 2px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;background-color: rgb(213,212,217);font: 9pt 'Arial Narrow';} "
                           "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 18px;border-left-width: 1px;border-left-color: darkgray;border-left-style: solid;background-color: rgb(130,130,137);}"
                           "QComboBox::down-arrow {image: url(':/jiantou.png');}"
                           "QComboBox QAbstractItemView{font-size: 15px;font-family: 'Arial Narrow';outline: 0px;}"
                           "QComboBox QAbstractItemView::item {height: 18px;background-color: rgb(213,212,217);}"
                           "QComboBox QAbstractItemView::item:selected{background-color: rgb(49,106,197);}");
    m_pComboBox_4->setStyleSheet("QComboBox {border: 2px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;background-color: rgb(213,212,217);font: 9pt 'Arial Narrow';} "
                           "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 18px;border-left-width: 1px;border-left-color: darkgray;border-left-style: solid;background-color: rgb(130,130,137);}"
                           "QComboBox::down-arrow {image: url(':/jiantou.png');}"
                           "QComboBox QAbstractItemView{font-size: 15px;font-family: 'Arial Narrow';outline: 0px;}"
                           "QComboBox QAbstractItemView::item {height: 18px;background-color: rgb(213,212,217);}"
                           "QComboBox QAbstractItemView::item:selected{background-color: rgb(49,106,197);}");
    m_pComboBox_5->setStyleSheet("QComboBox {border: 2px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;background-color: rgb(213,212,217);font: 9pt 'Arial Narrow';} "
                           "QComboBox::drop-down {subcontrol-origin: padding;subcontrol-position: top right;width: 20px;border-top-right-radius: 3px;border-bottom-right-radius: 3px;border-left-width: 1px;border-left-color: darkgray;border-left-style: solid;background-color: rgb(130,130,137);}"
                           "QComboBox::down-arrow {image: url(':/probe.png');}"
                           "QComboBox QAbstractItemView{font-size: 15px;font-family: 'Arial Narrow';outline: 0px;}"
                           "QComboBox QAbstractItemView::item {height: 18px;background-color: rgb(213,212,217);}"
                           "QComboBox QAbstractItemView::item:selected{background-color: rgb(49,106,197);}");
    this->setStyleSheet("QStatusBar {background-color: rgb(88,88,94);}"
                                 "QStatusBar::item {border-width: 0;border-color: darkkhaki;border-style: solid;border-radius: 2;}");
    this->addPermanentWidget(m_pComboBox_1);
    this->addPermanentWidget(m_pComboBox_2);
    this->addPermanentWidget(m_pComboBox_3);
    this->addPermanentWidget(m_pComboBox_4);
    this->addPermanentWidget(m_pBlank);
    this->addPermanentWidget(m_pComboBox_5);
    this->addPermanentWidget(m_pPushButton_1);
    this->addPermanentWidget(m_pPushButton_2);
    this->addPermanentWidget(m_pPushButton_3);
    this->addPermanentWidget(m_pPushButton_4);
    this->addPermanentWidget(m_pPushButton_5);
    this->addPermanentWidget(m_pPushButton_6);
    m_pComboBox_1->addItem("No Projection");
    m_pComboBox_1->addItem("PCS XY Plane");
    m_pComboBox_2->addItem("Millimeter");
    m_pComboBox_2->addItem("Inch");
    m_pComboBox_2->addItem("Meter");
    m_pComboBox_2->addItem("Feet");
    m_pComboBox_2->addItem("Centimeter");
    m_pComboBox_3->addItem("Degree");
    m_pComboBox_3->addItem("Radian");
    m_pComboBox_3->addItem("DD:MM:SS");
    m_pComboBox_4->addItem("Cart");
    m_pComboBox_4->addItem("Pol-XY");
    m_pComboBox_4->addItem("Pol-YZ");
    m_pComboBox_4->addItem("Pol-ZX");
    m_pComboBox_5->addItem("CCD1X1");
    m_pComboBox_1->setView(new QListView());
    m_pComboBox_2->setView(new QListView());
    m_pComboBox_3->setView(new QListView());
    m_pComboBox_4->setView(new QListView());
    m_pComboBox_5->setView(new QListView());

	//qDebug() << QString::fromStdString("leftdataDockWidget:" + m_solution->m_strSolutionName);
	connect(this->m_pComboBox_1, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeValue()));
	

}

void CStatusBarZone::changeValue()
{
	if(this->m_pComboBox_1->currentIndex() == 0) qDebug() << QString::fromStdString("statusbar:" + m_solution->m_strSolutionName);
	else if(this->m_pComboBox_1->currentIndex() == 1) qDebug() << QString::fromStdString("statusbar:" + m_solution->m_strDesignerName);
}

CStatusBarZone::~CStatusBarZone()
{
    
}
