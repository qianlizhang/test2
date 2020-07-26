#pragma once
#include <QtCore/QCoreApplication> 
#include <QtCore/QObject> 
#include <QtCore/QThread> 
#include <QtCore/QDebug> 
#include <opencv2\opencv.hpp>

#include"CParams.h"
#include"CObjectRect.h"
//***********************************************************************
//	name	: CObjectDetection
//	brief	: 目标检测算法基类
//	author	: ZZH
//***********************************************************************

class CObjectDetection : public QObject {
	Q_OBJECT;

protected:


	// 各种初始化参数
	CParams parameter;

public:


	// 设置参数
	virtual void SetParameter(CParams InputParam);

	// 检测所有对象：  输入mat， 输出背景，输出返回框信息
	virtual void DetectObjects(cv::Mat frame, cv::Mat * background, CObjectRect & tarobj) ;

signals:
	void Detect_end_Sig();
};
