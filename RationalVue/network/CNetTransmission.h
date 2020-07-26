#pragma once
#ifndef NETTRANSMISSION_H_
#define NETTRANSMISSION_H_

#include "DetectResults.h"
#include<vector>
#include <QDataStream>
#include <iostream>
//#include "Utils.h"

class CNetTransmission
{
public:
	int camera_ID;//����ı��
	long _time;//ʱ���
	cv::Mat frame;//ѹ������Ƶ֡ͼ��
	int height;
	std::vector<DetectResults> mDetectObjects;//�߿�������������\
	//std::vector<cv::Point2d> trace;//�˶������˶��켣����
	//cv::Point2d first_trace;//����߿��������ʼλ��
	CNetTransmission clone()
	{
		CNetTransmission a;
		a.camera_ID = this->camera_ID;
		a._time = this->_time;
		a.frame = this->frame.clone();
		a.mDetectObjects = this->mDetectObjects;
		return a;
	}

	~CNetTransmission() {
		frame.release();
		mDetectObjects.clear();
	}
};


inline QDataStream & operator<< (QDataStream & out, const CNetTransmission & msg)
{
	out << msg.height;
	out << msg.camera_ID;
	int resLen = msg.mDetectObjects.size();
	out << resLen;
	for (int i = 0; i < resLen; ++i) {
		out << msg.mDetectObjects[i];
	}
	return out;
}

inline QDataStream & operator>> (QDataStream & in, CNetTransmission & msg)
{
	in >> msg.height;
	in >> msg.camera_ID;
	int resLen;
	in >> resLen;
	msg.mDetectObjects.resize(resLen);
	for (int i = 0; i < resLen; ++i) {
		in >> msg.mDetectObjects[i];
	}
	return in;
}



#endif	// NETTRANSMISSION_H_