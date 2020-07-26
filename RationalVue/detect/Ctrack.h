///*****************************************************************
///  �ļ�����: 
///  ��Ҫ����:  
///  ����:  Dreamhigh
///  ��������: 
///*****************************************************************
#pragma once
#include "opencv2/opencv.hpp"
#include <opencv/cv.h>
#include "CKalman.h"

class TKalmanFilter;

struct  CTrack
{
public:
	bool flag = false;//�жϸ����켣�Ƿ�����Ҫ׷�ٵ�

	size_t track_id;//׷������ı��
	std::vector<cv::Point2d> trace;//�˶������˶��켣����
	std::vector<double> traceY;//��¼�˶������Y����
	std::vector<double> traceX;//��¼�˶������X����
	double num_frames;//������ֵ�֡����
	std::vector<double> frames_num;//��¼�˶������֡ʱ��
	//std::vector<double> frame_num;//��������֡��
	size_t skipped_frames;//��������Ƶ֡
	cv::Point2f prediction;//Ԥ��λ��
	TKalmanFilter* KF;//�������˲���
	cv::Mat m_img;

	size_t NextTrackID;//��һ��׷�ٶ���ı��	
	size_t ptrack_id;
	size_t cam_id;

	int pre_num = 0;//��¼�ж��ٸ�����Ԥ��õ���


	CTrack(cv::Point2f p, float dt, float Accel_noise_mag);
	~CTrack();


public:
	double width;
	double height;
	double area;
	double cir;//�ܳ�

	int flag1;// = 0;//�˶��Ƿ����
	int flag2;// = 1;//0Ϊ���ϣ�1Ϊ����
};
