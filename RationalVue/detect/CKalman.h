#pragma once
#include "opencv2/opencv.hpp"
#include <opencv/cv.h>
#include "CPrediction.h"


class TKalmanFilter //: public CPrediction
{
public:
	cv::Point2f LastResult;
	cv::KalmanFilter* kalman;
	cv::Mat m_img;
	double deltatime;

	TKalmanFilter(cv::Point2f p, float dt = 0.2, float Accel_noise_mag = 0.5);
	virtual ~TKalmanFilter();

	cv::Point2f GetPrediction();
	cv::Point2f Update(cv::Point2f p, bool DataCorrect);
	void UpdateModel3(std::vector<int> assignment, std::vector<cv::Point2f> detections, std::vector<CTrack*> tracks, std::vector<cv::Mat> imgs, int max_trace_length) {};
};
