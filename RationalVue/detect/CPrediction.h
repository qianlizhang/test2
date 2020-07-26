#pragma once
#include "opencv2/opencv.hpp"
#include <opencv/cv.h>
#include "Ctrack.h"

struct CTrack;

//struct CTrack
//{
//public:
//	size_t track_id;//׷������ı��
//	std::vector<cv::Point2d> trace;//�˶������˶��켣����
//	std::vector<double> traceY;//��¼�˶������Y����
//	std::vector<double> traceX;//��¼�˶������X����
//	double num_frames;//������ֵ�֡����
//	std::vector<double> frames_num;//��¼�˶������֡ʱ��
//	std::vector<double> frame_num;//��������֡��
//	size_t skipped_frames;//��������Ƶ֡
//	cv::Point2f prediction;//Ԥ��λ��
//	//TKalmanFilter* KF;//�������˲���
//	cv::Mat m_img;
//
//	size_t NextTrackID;//��һ��׷�ٶ���ı��	
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