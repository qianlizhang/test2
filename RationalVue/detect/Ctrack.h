///*****************************************************************
///  文件名称: 
///  简要描述:  
///  作者:  Dreamhigh
///  创建日期: 
///*****************************************************************
#pragma once
#include "opencv2/opencv.hpp"
#include <opencv/cv.h>
#include "CKalman.h"

class TKalmanFilter;

struct  CTrack
{
public:
	bool flag = false;//判断该条轨迹是否是需要追踪的

	size_t track_id;//追踪物体的编号
	std::vector<cv::Point2d> trace;//运动对象运动轨迹坐标
	std::vector<double> traceY;//记录运动对象的Y坐标
	std::vector<double> traceX;//记录运动对象的X坐标
	double num_frames;//对象出现的帧计数
	std::vector<double> frames_num;//记录运动对象的帧时间
	//std::vector<double> frame_num;//与程序的总帧数
	size_t skipped_frames;//跳过的视频帧
	cv::Point2f prediction;//预测位置
	TKalmanFilter* KF;//卡尔曼滤波器
	cv::Mat m_img;

	size_t NextTrackID;//下一个追踪对象的编号	
	size_t ptrack_id;
	size_t cam_id;

	int pre_num = 0;//记录有多少个点是预测得到的


	CTrack(cv::Point2f p, float dt, float Accel_noise_mag);
	~CTrack();


public:
	double width;
	double height;
	double area;
	double cir;//周长

	int flag1;// = 0;//运动是否变向
	int flag2;// = 1;//0为向上，1为向下
};
