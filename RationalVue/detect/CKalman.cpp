#pragma once
#include "CKalman.h"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>

//---------------------------------------------------------------------------
// 构造卡尔曼滤波器
//---------------------------------------------------------------------------
TKalmanFilter::TKalmanFilter(cv::Point2f pt, float dt, float Accel_noise_mag)
{

	deltatime = dt; //0.2

	//完整构造KalmanFilter对象
	kalman = new cv::KalmanFilter(4, 2, 0);//状态的维度：4、测量的维度:2、控制量的维度
	//转移矩阵
	kalman->transitionMatrix = (cv::Mat_<float>(4, 4) << 1, 0, deltatime, 0, 0, 1, 0, deltatime, 0, 0, 1, 0, 0, 0, 0, 1);

	LastResult = pt;
	//预测状态
	kalman->statePre.at<float>(0) = pt.x; // x
	kalman->statePre.at<float>(1) = pt.y; // y

	kalman->statePre.at<float>(2) = 0;
	kalman->statePre.at<float>(3) = 0;

	//系统的初始状态
	kalman->statePost.at<float>(0) = pt.x;
	kalman->statePost.at<float>(1) = pt.y;

	//定义测量矩阵
	setIdentity(kalman->measurementMatrix);

	//定义过程噪声
	kalman->processNoiseCov = (cv::Mat_<float>(4, 4) <<
		pow(deltatime, 4.0) / 4.0, 0, pow(deltatime, 3.0) / 2.0, 0,
		0, pow(deltatime, 4.0) / 4.0, 0, pow(deltatime, 3.0) / 2.0,
		pow(deltatime, 3.0) / 2.0, 0, pow(deltatime, 2.0), 0,
		0, pow(deltatime, 3.0) / 2.0, 0, pow(deltatime, 2.0));
	kalman->processNoiseCov *= Accel_noise_mag;

	//定义测量噪声
	setIdentity(kalman->measurementNoiseCov, cv::Scalar::all(0.1));

	//定义最小均方误差
	setIdentity(kalman->errorCovPost, cv::Scalar::all(.1));

}

//
//析构卡尔曼滤波器
TKalmanFilter::~TKalmanFilter()
{
	delete kalman;
}


cv::Point2f TKalmanFilter::GetPrediction()
{
	cv::Mat prediction = kalman->predict();
	LastResult = cv::Point2f(prediction.at<float>(0), prediction.at<float>(1));
	return LastResult;
}

//*
//  跟新卡尔曼滤波模型
//*
cv::Point2f TKalmanFilter::Update(cv::Point2f p, bool DataCorrect)
{
	cv::Mat measurement(2, 1, CV_32FC1);
	if (!DataCorrect)
	{
		measurement.at<float>(0) = LastResult.x;
		measurement.at<float>(1) = LastResult.y;
	}
	else
	{
		measurement.at<float>(0) = p.x;
		measurement.at<float>(1) = p.y;
	}

	cv::Mat estimated = kalman->correct(measurement);
	LastResult.x = estimated.at<float>(0);
	LastResult.y = estimated.at<float>(1);
	return LastResult;
}

