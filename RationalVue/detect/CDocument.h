#pragma once
//#include "CBlockingQueue.h"
#include <opencv2\opencv.hpp>
//#include <CFeature.h>
#include "CParams.h"
//#include <CObjectRect.h>
#include "DetectResults.h"
//#include "CNetTransmission.h"


//==============================================================================
//	@name		:	CImageDoc
//	@biref		:	负责存储相机拍摄图像信息的类，包括采集的图像队列，在main函数中实例化
//					指针传入对应的类中
//	@author		:	Zeng
//	@version	:	9.22.2017
//===============================================================================

class CDocument {

public:
	CDocument();
	~CDocument();
	//参数
	CParams par_all;




	////检测 人脸 跟踪框
	//CObjectRect tarobj;

	//// 相机读取的图片序列
	//CBlockingQueue<cv::Mat> cameraImage;

	//// 与 相机读取的图片序列 对应的 跟踪结果框 序列
	//CBlockingQueue<CObjectRect> objQueue;

	//高空抛物检测结果保存
	std::vector<DetectResults> mDetectObjects;
	//跟踪得到的老人框
	//std::vector<CvRect> track_rect;

	//CNetTransmission mNetTransmission;

	//CBlockingQueue<CNetTransmission> pNetTransmissions;
	////轨迹回归后的显示队列
	//CBlockingQueue<CNetTransmission> showFrames;
	////缓存队列
	//CBlockingQueue<cv::Mat> BufferQueue;
	////网络传输队列
	//CBlockingQueue<CNetTransmission> TransmissionQueue;

	//视频当前帧
	cv::Mat nowframe;
	cv::Mat nowframe1;
	//测试
	//cv::Mat testimg;
	cv::VideoCapture capture;
	QString VedioPath;

	cv::VideoCapture capture1;
	//网络接收发送信息

public:
	void DayOrNight() {
		QTime current_time = QTime::currentTime();
		int hour = current_time.hour();
		/*int minute = current_time.minute();
		int second = current_time.second();*/
		if ((hour >= 6 && hour < 18)) {
			par_all.is_day = true;
		}
		else {
			par_all.is_day = false;
		}
	}
};
