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
//	@biref		:	����洢�������ͼ����Ϣ���࣬�����ɼ���ͼ����У���main������ʵ����
//					ָ�봫���Ӧ������
//	@author		:	Zeng
//	@version	:	9.22.2017
//===============================================================================

class CDocument {

public:
	CDocument();
	~CDocument();
	//����
	CParams par_all;




	////��� ���� ���ٿ�
	//CObjectRect tarobj;

	//// �����ȡ��ͼƬ����
	//CBlockingQueue<cv::Mat> cameraImage;

	//// �� �����ȡ��ͼƬ���� ��Ӧ�� ���ٽ���� ����
	//CBlockingQueue<CObjectRect> objQueue;

	//�߿�������������
	std::vector<DetectResults> mDetectObjects;
	//���ٵõ������˿�
	//std::vector<CvRect> track_rect;

	//CNetTransmission mNetTransmission;

	//CBlockingQueue<CNetTransmission> pNetTransmissions;
	////�켣�ع�����ʾ����
	//CBlockingQueue<CNetTransmission> showFrames;
	////�������
	//CBlockingQueue<cv::Mat> BufferQueue;
	////���紫�����
	//CBlockingQueue<CNetTransmission> TransmissionQueue;

	//��Ƶ��ǰ֡
	cv::Mat nowframe;
	cv::Mat nowframe1;
	//����
	//cv::Mat testimg;
	cv::VideoCapture capture;
	QString VedioPath;

	cv::VideoCapture capture1;
	//������շ�����Ϣ

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
