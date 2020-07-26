#pragma once
#include "CKalman.h"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>

//---------------------------------------------------------------------------
// ���쿨�����˲���
//---------------------------------------------------------------------------
TKalmanFilter::TKalmanFilter(cv::Point2f pt, float dt, float Accel_noise_mag)
{

	deltatime = dt; //0.2

	//��������KalmanFilter����
	kalman = new cv::KalmanFilter(4, 2, 0);//״̬��ά�ȣ�4��������ά��:2����������ά��
	//ת�ƾ���
	kalman->transitionMatrix = (cv::Mat_<float>(4, 4) << 1, 0, deltatime, 0, 0, 1, 0, deltatime, 0, 0, 1, 0, 0, 0, 0, 1);

	LastResult = pt;
	//Ԥ��״̬
	kalman->statePre.at<float>(0) = pt.x; // x
	kalman->statePre.at<float>(1) = pt.y; // y

	kalman->statePre.at<float>(2) = 0;
	kalman->statePre.at<float>(3) = 0;

	//ϵͳ�ĳ�ʼ״̬
	kalman->statePost.at<float>(0) = pt.x;
	kalman->statePost.at<float>(1) = pt.y;

	//�����������
	setIdentity(kalman->measurementMatrix);

	//�����������
	kalman->processNoiseCov = (cv::Mat_<float>(4, 4) <<
		pow(deltatime, 4.0) / 4.0, 0, pow(deltatime, 3.0) / 2.0, 0,
		0, pow(deltatime, 4.0) / 4.0, 0, pow(deltatime, 3.0) / 2.0,
		pow(deltatime, 3.0) / 2.0, 0, pow(deltatime, 2.0), 0,
		0, pow(deltatime, 3.0) / 2.0, 0, pow(deltatime, 2.0));
	kalman->processNoiseCov *= Accel_noise_mag;

	//�����������
	setIdentity(kalman->measurementNoiseCov, cv::Scalar::all(0.1));

	//������С�������
	setIdentity(kalman->errorCovPost, cv::Scalar::all(.1));

}

//
//�����������˲���
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
//  ���¿������˲�ģ��
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

