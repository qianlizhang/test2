#pragma once
#include<vector>
#include <opencv2\opencv.hpp>


//==============================================================================
//	@name		:	ObjectRect
//	@biref		:	对象检测返回的矩形框
//	@author		:	
//===============================================================================

class CObjectRect
{
public:

	//运动对象检测得到的结果
	std::vector<CvRect> detectrects;  //检测到的对象框
	std::vector<cv::Point2f> detections;  //检测到的物体中心点
	std::vector<double>width;
	std::vector<double>height;
	double frame_num;

	//跟踪中用到的变量（匈牙利的输出）
	std::vector< std::vector<double> > Cost;
	std::vector< std::vector<double> > Cost2;
	std::vector<int> assignment;
	std::vector<int> not_assigned_tracks;


	int frame_height = 0;
	int frame_width = 0;

};
