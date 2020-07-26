// 该文件定义了公用的全局量，包括全局宏定义和全局变量等

// 防止Qt乱码
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

#define ERRDETECTTIME 30 //用于判断当前相机检测到的抛物是否是从上方楼层抛下，单位秒
#define ERRDETECTDISTANCE 20  //单位像素

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

	//测试视频
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

	 int perFloor = 3;          //每层楼的高度
     float distance = 15; //相机安装与大楼的距离
	 double CaHeight = 3; //相机安装高度
	 std::map<int, int>ID2Channel; //相机ID-通道号
	 static std::map<int,vector<windows>>Windows;//窗户的坐标信息及楼层、房间号
//	  int frameHeight = 2560; //??
};




using std::string;
using std::vector;

// 摄像机采集彩色图像，注释掉后采集灰度图像
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