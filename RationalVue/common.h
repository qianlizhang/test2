// ���ļ������˹��õ�ȫ����������ȫ�ֺ궨���ȫ�ֱ�����

// ��ֹQt����
#pragma execution_character_set("utf-8")

#ifndef _COMMON_H
#define _COMMON_H

#include <string>
#include <vector>
#include <QLabel>
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog\logging.h>

#include <opencv2/opencv.hpp>
#include "CBlockingQueue.h"
#include"WindowNotation.h"

#define FRAMEMAX 2
#define FRAMECOLS 2560
#define FRAMEROWS 2160

#define ERRDETECTTIME 30 //�����жϵ�ǰ�����⵽�������Ƿ��Ǵ��Ϸ�¥�����£���λ��
#define ERRDETECTDISTANCE 20  //��λ����

class Camera;
class QProcess;
class DetectThread;
class QLabel;
class DetectAlgorithm;

struct App
{
	static std::vector<std::vector<QLabel *>> labels;
	static std::map<uint16_t, Camera *> cameras;
	static std::map<uint16_t, DetectThread *> threads;
	static std::map<uint16_t, DetectAlgorithm *> threads_;
	static QVector<QVector<QLabel*>> pShowEdit;

	static std::map<long, CBlockingQueue<cv::Mat>*> cameraImages;
	static std::map<int, long> id2handle;

	//������Ƶ
	static cv::VideoCapture cap;
	static QString CurrentUser;
};

class CMyBaseWidget : public QWidget
{
public:
	App* app;
	CMyBaseWidget(QWidget* parent) :QWidget(parent){}
	CMyBaseWidget():QWidget(){}
};

class CBaseProcessLogic : public QObject
{
public:
	App* app;
};

using std::vector;
class CommonData
{
public:
	CommonData() {
		ID2Channel[0] = 33;
		ID2Channel[1] = 34;
		ID2Channel[10] = 35;
		ID2Channel[11] = 36;
		ID2Channel[20] = 37;
		ID2Channel[30] = 38;
		ID2Channel[40] = 39;
		ID2Channel[41] = 40;
		ID2Channel[50] = 41;
		ID2Channel[51] = 42;
		ID2Channel[60] = 43;
		ID2Channel[61] = 44;
	}

	 int perFloor = 3;          //ÿ��¥�ĸ߶�
     float distance = 15; //�����װ���¥�ľ���
	 double CaHeight = 3; //�����װ�߶�
	 std::map<int, int>ID2Channel; //���ID-ͨ����
	 static std::map<int,vector<windows>>Windows;//������������Ϣ��¥�㡢�����
//	  int frameHeight = 2560; //??
};




using std::string;
using std::vector;

// ������ɼ���ɫͼ��ע�͵���ɼ��Ҷ�ͼ��
#define HKCAMERA_USE_BGR

// TCP
#define TCP_SERVER_DEFAULT_PROT		(3721)
#define TCP_SOCKET_BUFFER_SIZE		(1024 * 8 * 1)		// 8K

#define STR2JSON(X, Y)				do {											\
										try {										\
											Y = JSON::parse(X);						\
										}											\
										catch (JSON::parse_error& e) {				\
											Q_UNUSED(e);							\
											LOG(ERROR) << "Parse failed.";			\
										}											\
									} while(0)

#endif // !_COMMON_H