#pragma once
#include<vector>
#include <opencv2\opencv.hpp>


//==============================================================================
//	@name		:	ObjectRect
//	@biref		:	�����ⷵ�صľ��ο�
//	@author		:	
//===============================================================================

class CObjectRect
{
public:

	//�˶�������õ��Ľ��
	std::vector<CvRect> detectrects;  //��⵽�Ķ����
	std::vector<cv::Point2f> detections;  //��⵽���������ĵ�
	std::vector<double>width;
	std::vector<double>height;
	double frame_num;

	//�������õ��ı������������������
	std::vector< std::vector<double> > Cost;
	std::vector< std::vector<double> > Cost2;
	std::vector<int> assignment;
	std::vector<int> not_assigned_tracks;


	int frame_height = 0;
	int frame_width = 0;

};
