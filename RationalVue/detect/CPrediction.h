#pragma once
#include "opencv2/opencv.hpp"
#include <opencv/cv.h>
#include "Ctrack.h"

struct CTrack;

//struct CTrack
//{
//public:
//	size_t track_id;//追踪物体的编号
//	std::vector<cv::Point2d> trace;//运动对象运动轨迹坐标
//	std::vector<double> traceY;//记录运动对象的Y坐标
//	std::vector<double> traceX;//记录运动对象的X坐标
//	double num_frames;//对象出现的帧计数
//	std::vector<double> frames_num;//记录运动对象的帧时间
//	std::vector<double> frame_num;//与程序的总帧数
//	size_t skipped_frames;//跳过的视频帧
//	cv::Point2f prediction;//预测位置
//	//TKalmanFilter* KF;//卡尔曼滤波器
//	cv::Mat m_img;
//
//	size_t NextTrackID;//下一个追踪对象的编号	
//	size_t ptrack_id;
//	size_t cam_id;
//
//
//	CTrack(cv::Point2f p, float dt, float Accel_noise_mag);
//	~CTrack();
//};

class CPrediction {
protected:


public:
	CPrediction() {};
	~CPrediction() {};
	virtual cv::Point2f GetPrediction() { return 0; };
	virtual cv::Point2f Update(cv::Point2f p, bool DataCorrect) { return 0; };
	virtual void UpdateModel3(
		std::vector<int> assignment,
		std::vector<cv::Point2f> detections,
		std::vector<CTrack*> tracks,
		std::vector<cv::Mat> imgs,
		int max_trace_length) = 0;

};