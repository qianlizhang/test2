#pragma once
#include <QtCore/QCoreApplication> 
#include <QtCore/QObject> 
#include <QtCore/QThread> 
#include <QtCore/QDebug> 
#include <opencv2\opencv.hpp>

#include<CParams.h>
#include<CFeature.h>
#include <DetectResults.h>
#include "CObjectRect.h"

#include<vector>

//***********************************************************************
//	name	: CTracking
//	brief	: Ŀ��׷���㷨����
//	author	: ZZH
//***********************************************************************

class CTracking : public QObject {
	Q_OBJECT

protected:
	// ��ǰ֡ͼ��
	//cv::Mat currentFrame;
	// ��ʼ��
	//cv::Rect InputRect;
	// �����
	//cv::Rect OutputRect;
	// ��������
	//cv::Point centerPoint;
	// ModelFeature
	//CFeature ModelFeature;

	//��һ��׷��Ŀ����
	size_t NextTrackID;

	//��ʼ�����ֲ���
	CParams parameter;

	//�м����
	//CObjectRect var;
	//�켣�Ľṹ��
	//�켣����s
	//vector<Trail> trail;


public :

	//��ʼ���������

	//��ô洢�켣������
	//virtual vector<Trail> getTrail();

	//virtual void GetFrame();

	//virtual void UpdateModel(vector<Point2f>& detections, vector<Mat>imgs, double frame_num){ cout << 0 << endl; };

	virtual void UpdateModel(CObjectRect &var, cv::Mat frame) ;
	virtual void UpdateModel4(CObjectRect &var, cv::Mat frame) ;
	virtual void UpdateModel6(CObjectRect &var, cv::Mat frame) ;
	//virtual void UpdateModel2(vector<int> assignment, vector<int> not_assigned_tracks, vector< vector<double> > Cost){};
	virtual void UpdateModel2(CObjectRect var, std::vector<DetectResults> &mDetectObjects) ;
	virtual void UpdateModel5(CObjectRect var, std::vector<DetectResults> &mDetectObjects) ;
	virtual void UpdateModel7(CObjectRect var, std::vector<DetectResults> &mDetectObjects) ;
	virtual void UpdateModel3(CObjectRect var, cv::Mat frame, CvRect &track_rect, std::vector<DetectResults> &mDetectObjects) = 0;
	//virtual void ExtractRectFea();

	//virtual void RectMatching();

	//virtual void GetCurrentRect();

	// ��ȡ���ĵ�
	//virtual void GetCenterPoint();

signals:

	void UpdateModel_end_Sig();
	void UpdateModel2_end_Sig();
	void UpdateModel3_end_Sig();
};