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
//	brief	: 目标追踪算法基类
//	author	: ZZH
//***********************************************************************

class CTracking : public QObject {
	Q_OBJECT

protected:
	// 当前帧图像
	//cv::Mat currentFrame;
	// 初始框
	//cv::Rect InputRect;
	// 输出框
	//cv::Rect OutputRect;
	// 中心坐标
	//cv::Point centerPoint;
	// ModelFeature
	//CFeature ModelFeature;

	//下一个追踪目标编号
	size_t NextTrackID;

	//初始化各种参数
	CParams parameter;

	//中间变量
	//CObjectRect var;
	//轨迹的结构体
	//轨迹向量s
	//vector<Trail> trail;


public :

	//初始化各类参数

	//获得存储轨迹的向量
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

	// 获取中心点
	//virtual void GetCenterPoint();

signals:

	void UpdateModel_end_Sig();
	void UpdateModel2_end_Sig();
	void UpdateModel3_end_Sig();
};