#ifndef _HKCAMERA_H
#define _HKCAMERA_H

#include "common.h"
#include <mutex>
#include <map>
#include <QTimer>
#include <opencv2\opencv.hpp>
#include "common.h"
#include "HCNetSDK.h"
#include "plaympeg4.h"

class Camera:public CBaseProcessLogic {
public:
	enum FrameFormat { BGR, GRAY };
public:
	Camera(string ip, string username, string pwd, int id, WORD port = 8000)
		: ip_(ip), username_(username), password_(pwd), id_(id), port_(port)
	{
		char id_str[3] = {0};
		sprintf(id_str, "%2d", id);
		tag_ = "Camera@" + string(id_str);
	}
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;
	virtual ~Camera() = default;

	virtual bool isOpened() const = 0;

	virtual bool get(cv::Mat& frame, FrameFormat format) = 0;

	virtual void close() = 0;

	int id() const { return id_; }
	string tag() const { return tag_;  }

	int LowFloor_ = -1;
	int HighFloor_ = -1;

protected:
	string ip_;
	string username_;
	string password_;
	WORD port_;

	string tag_;

	int id_ = -1;

	int rows_ = 0;
	int cols_ = 0;
	int chs_ = 0;
	int fps_ = 0;
};

/**
 * @berif Camera 实现类
 */
class HKWin64_Camera : public Camera {
public:
	HKWin64_Camera(string ip, string username, string pwd, int id, WORD port = 8000);
	virtual ~HKWin64_Camera() override { delete timer_; }

	// 
	bool isOpened() const override { return is_opened_; }

	// 开始预览
	bool startRealPlay();

	// 注册回调函数，自行处理数据流
	bool enableDataStream();

	// 关闭预览
	void stopRealPlay();

	// 获取图像
	bool get(cv::Mat& frame, FrameFormat format) override;

	// 关闭(登出)摄像头
	void close();

	// 播放窗口的句柄
	HWND hwnd_ = nullptr;

private:
	// 登录
	bool login();

	static void CALLBACK ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser);
	static void CALLBACK DecodeCallback(LONG nPort, char * pBuf, LONG, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2);
	static void CALLBACK RealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser);

	long realplay_handle_ = -1;

	long user_id_ = -1;

	bool is_opened_ = false;

	bool has_new_gray_frame_ = false;
	bool has_new_bgr_frame_ = false;

	time_t last_time_;

	cv::Mat buf_;
	cv::Mat frame_bgr_;
	cv::Mat frame_gray_;
	std::mutex mtx_;

	std::mutex mtx_g_;
	std::mutex mtx_c_;

	LONG realplay_port_ = 0;

	QTimer * timer_ = nullptr;

	// (port, handle)
	static std::map<long, long> realplay_handles_;

	// (port, camera)
	static std::map<long, HKWin64_Camera *> cameras_;
};

class RTSPCamera : public Camera {
public:
	RTSPCamera(string ip, string username, string pwd, int id, WORD port = 8000)
		: Camera(ip, username, pwd, id, port)
	{
		rtsp_ = "rtsp://" + username_ + ":" + password_ + "@" + ip_ + "/Streaming/Channels/101";
		camera_.open(rtsp_, cv::CAP_FFMPEG);
		cols_ = camera_.get(cv::CAP_PROP_FRAME_WIDTH);
		rows_ = camera_.get(cv::CAP_PROP_FRAME_HEIGHT);
		fps_ = camera_.get(cv::CAP_PROP_FPS);
	}

	bool isOpened() const override { return camera_.isOpened(); }
	bool get(cv::Mat& frame, FrameFormat format) override;

	void close() override { camera_.release(); }

private:
	cv::VideoCapture camera_;
	string rtsp_;

	int counter_ = 0;
};

#endif // !_HKCAMERA_H