#pragma once
#include"CommonData.h"
#include<QMainWindow>
class CBaseWidget : public QMainWindow
{
public:
	CCommonData m_commonData;
	CBaseWidget(QWidget* parent) :QMainWindow(parent) {}
	CBaseWidget() :QMainWindow() {}
};