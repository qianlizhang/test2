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
//	brief	: Ŀ�����㷨����
//	author	: ZZH
//***********************************************************************

class CObjectDetection : public QObject {
	Q_OBJECT;

protected:


	// ���ֳ�ʼ������
	CParams parameter;

public:


	// ���ò���
	virtual void SetParameter(CParams InputParam);

	// ������ж���  ����mat�� ���������������ؿ���Ϣ
	virtual void DetectObjects(cv::Mat frame, cv::Mat * background, CObjectRect & tarobj) ;

signals:
	void Detect_end_Sig();
};
