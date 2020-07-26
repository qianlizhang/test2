#include "HKCamera.h"

std::map<long, long> HKWin64_Camera::realplay_handles_;
std::map<long, HKWin64_Camera *> HKWin64_Camera::cameras_;

// 回调函数，将传入的码流调用解码函数解码
void CALLBACK HKWin64_Camera::DecodeCallback(LONG nPort, char * pBuf, LONG nSize, FRAME_INFO * pFrameInfo, long nReserved1, long nReserved2)
{
	auto _this = cameras_[realplay_handles_[nPort]];

	if (pFrameInfo->nType == T_YV12) {
		
		if (_this->mtx_.try_lock()) {
			//if (_this->buf_.empty()) {
			//	_this->buf_.create(pFrameInfo->nHeight + pFrameInfo->nHeight / 2, pFrameInfo->nWidth, CV_8UC1);
			//}

			//memcpy(_this->buf_.data, pBuf, (pFrameInfo->nHeight * 3 / 2) * pFrameInfo->nWidth);

			if(_this->frame_gray_.empty())
				_this->frame_gray_.create(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC1);
			memcpy(_this->frame_gray_.data, pBuf, pFrameInfo->nHeight * pFrameInfo->nWidth);
			App::cameraImages[realplay_handles_[nPort]]->Put(_this->frame_gray_);
		//	LOG(INFO) << _this->tag_ << ", port@  " << nPort<<"   " <<App::cameraImages[realplay_handles_[nPort]]->m_pCount->getValue();


			_this->has_new_bgr_frame_ = true;
			_this->has_new_gray_frame_ = true;
			_this->mtx_.unlock();

			_this->last_time_ = time(nullptr);

		//	LOG(INFO) << _this->tag_ << ", port@" << nPort;
		}
	}

}

// 实时预览数据流的回调函数
void CALLBACK HKWin64_Camera::RealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, DWORD dwUser)
{
	auto _this = cameras_[lRealHandle];
	auto& port = _this->realplay_port_;

	switch (dwDataType)
	{
	case NET_DVR_SYSHEAD:
		if (!PlayM4_GetPort(&port)) {
			LOG(ERROR) << _this->tag_ << ":PlayM4_GetPort:" << PlayM4_GetLastError(port) << std::endl;
			break;
		}

		LOG(INFO) << _this->tag_ <<" ====> port@" << port;

		// (port, handle)
		realplay_handles_[port] = lRealHandle;

		if (!PlayM4_OpenStream(port, pBuffer, dwBufSize, 1024 * 1024 * 64)) {
			LOG(ERROR) << _this->tag_ << ": PlayM4_OpenStream@" << port << ":" << PlayM4_GetLastError(port);
			break;
		}

		if (!PlayM4_SetDecCallBack(port, DecodeCallback)) {
			LOG(ERROR) << _this->tag_ << ": PlayM4_SetDecCallBack@" << port << ":" << PlayM4_GetLastError(port);
			break;
		}

		if (!PlayM4_Play(port, nullptr)) {
			LOG(ERROR) << _this->tag_ << ": PlayM4_Play@" << port << ":" << PlayM4_GetLastError(port);
			break;
		}
		break;

	case NET_DVR_STREAMDATA:
		if (dwBufSize > 0 && port != -1) {
			if (!PlayM4_InputData(port, pBuffer, dwBufSize)) {
				//LOG(ERROR) << _this->tag_ << ": PlayM4_InputData@" << port << ":" << PlayM4_GetLastError(port);
				break;
			}
		}
		break;

	default:
		if (dwBufSize > 0 && port != -1) {
			if (!PlayM4_InputData(port, pBuffer, dwBufSize)) {
				LOG(ERROR) << _this->tag_ << ": PlayM4_InputData@" << port << ":" << PlayM4_GetLastError(port) << std::endl;
				break;
			}
		}
		break;
	}
}

void CALLBACK HKWin64_Camera::ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
	/*switch (dwType)
	{
	case EXCEPTION_RECONNECT: //预览时重连
		LOG(WARNING) << cameras_[lHandle]->tag_ << ": EXCEPTION_RECONNECT";
		break;

	case EXCEPTION_PREVIEW:
		LOG(WARNING) << cameras_[lHandle]->tag_ << ": EXCEPTION_PREVIEW";
		break;

	case PREVIEW_RECONNECTSUCCESS:
		LOG(WARNING) << cameras_[lHandle]->tag_ << ": PREVIEW_RECONNECTSUCCESS.";
		break;

	default:
		LOG(ERROR) << cameras_[lHandle]->tag_ << ": " << dwType;
		break;
	}*/
	LOG(WARNING) << "camera exception";
}

HKWin64_Camera::HKWin64_Camera(string ip, string username, string pwd, int id, WORD port)
	: Camera(ip, username, pwd, id, port)
{
	is_opened_ = login();// && startRealPlay() && enableDataStream();
	timer_ = new QTimer();
}

bool HKWin64_Camera::login()
{
	NET_DVR_Init();

	// 连接设置
	NET_DVR_SetConnectTime(2000, 1);
	NET_DVR_SetReconnect(5000, true);

	NET_DVR_USER_LOGIN_INFO login_info = { 0 };
	strncpy(login_info.sDeviceAddress, ip_.c_str(), ip_.size());
	strncpy(login_info.sUserName, username_.c_str(), username_.size());
	strncpy(login_info.sPassword, password_.c_str(), password_.size());
	login_info.wPort = port_;

	NET_DVR_DEVICEINFO_V40 device_info = { 0 };
	user_id_ = NET_DVR_Login_V40(&login_info, &device_info);

	NET_DVR_SetExceptionCallBack_V30(0, NULL, ExceptionCallBack, NULL);

	return !!(user_id_ >= 0);
}

bool HKWin64_Camera::startRealPlay()
{
	// 启动预览
	NET_DVR_PREVIEWINFO struPlayInfo = { 0 };

	struPlayInfo.hPlayWnd = hwnd_;		//需要 SDK 解码时句柄设为有效值，仅取流不解码时可设为空
	struPlayInfo.lChannel = 1;			//预览通道号
	struPlayInfo.dwStreamType = 0;		//0 - 主码流，		1 - 子码流，			2 - 码流 3，		3 - 码流	 4，	以此类推
	struPlayInfo.dwLinkMode = 0;		//0 - TCP 方式，		1 - UDP 方式，		2 - 多播方式，	3 - RTP 方式，	4-RTP/RTSP， 5 - RSTP/HTTP
	struPlayInfo.bBlocked = 1;			//0 - 非阻塞取流，	1 - 阻塞取流
	//struPlayInfo.dwDisplayBufNum = 1;

	// 实时预览
	realplay_handle_ = NET_DVR_RealPlay_V40(user_id_, &struPlayInfo, nullptr, nullptr);

	if (realplay_handle_ < 0) {
		LOG(FATAL) << tag_ << ": NET DVR Last Error: " << NET_DVR_GetLastError();
		close();
		return false;
	}

	cameras_[realplay_handle_] = this;
//	App::id2handle[id_] = realplay_handle_;

//	App::cameraImages[realplay_handle_] = new CBlockingQueue<cv::Mat>(64);

	app->id2handle[id_] = realplay_handle_;
	app->cameraImages[realplay_handle_] = new CBlockingQueue<cv::Mat>(64);

	return true;
}

bool HKWin64_Camera::enableDataStream()
{
	if (!NET_DVR_SetRealDataCallBack(realplay_handle_, RealDataCallBack, NULL)) {
		LOG(FATAL) << tag_ << "Register callback function failed.";
		return false;
	}

	QObject::connect(timer_, &QTimer::timeout, [this]() {
		auto current_time = time(nullptr);
		if (current_time - last_time_ > 5) {
		//	LOG(ERROR) << tag_ << ": disconnected.";

		//	LOG(ERROR) << tag_ << ": " << ctime(&last_time_) << " - " << ctime(&current_time);

			last_time_ = time(nullptr);
			
			/*LOG(ERROR) << tag_ << ": connecting...";

			if (enableDataStream()) {
				LOG(ERROR) << tag_ << ": connected.";
				this->last_time_ = time(nullptr);
			}*/
		}
	});
	timer_->start(1000);
	
	return true;
}

void HKWin64_Camera::stopRealPlay()
{
	if (!NET_DVR_StopRealPlay(realplay_handle_)) {
		LOG(ERROR) << tag_ << "Stop RealPlay failed!";
	}
	is_opened_ = false;
}

void HKWin64_Camera::close()
{
	stopRealPlay();
	hwnd_ = nullptr;
	
	NET_DVR_Logout(user_id_);
	NET_DVR_Cleanup();
	is_opened_ = false;
}

bool HKWin64_Camera::get(cv::Mat& _frame, FrameFormat format)
{
	switch (format) {
	case GRAY:
		if (has_new_gray_frame_) {
			if (_frame.cols != buf_.cols && _frame.rows != buf_.rows * 3 / 2) {
				_frame.create(buf_.rows * 2 / 3, buf_.cols, CV_8UC1);
			}

			mtx_.lock();
			memcpy(_frame.data, buf_.data, buf_.rows * 2 / 3 * buf_.cols);

			if (_frame.empty())
			{
				LOG(ERROR) << "视频帧为空";
			}

			has_new_gray_frame_ = false;
			mtx_.unlock();
			return true;
		}
		break;

	case BGR:
		if (has_new_bgr_frame_) {
			mtx_.lock();
			cv::cvtColor(buf_, _frame, CV_YUV2BGR_YV12);
			has_new_bgr_frame_ = false;
			mtx_.unlock();

			return true;
		}
		break;

	default: break;
	}
	return false;
}


bool RTSPCamera::get(cv::Mat& frame, FrameFormat format)
{
	switch (format)
	{
	case Camera::BGR:
	{
		camera_.read(frame);
	//	LOG(INFO) << tag_ << ": " << frame.cols << " x " << frame.rows;

		// 空帧处理，连续空帧5次视为断流，进行重连
		if (frame.empty()) {
			counter_++;
		//	LOG(ERROR) << tag_ << ": Frame is EMPTY.";
			if (counter_ > 5) {
				camera_.release();
				camera_.open(rtsp_);
		//		LOG(ERROR) << tag_ << ": reopened.";
			}
			return false;
		}

		// 帧大小错误
		if (frame.cols != cols_ || frame.rows != rows_) {
			LOG(ERROR) << tag_ << ": Frame size ERROR.";
			return false;
		}
		counter_ = 0;
		return true;
	}

	case Camera::GRAY:
	{
		cv::Mat _frame;
		camera_ >> _frame;
		LOG(INFO) << tag_ << ": " << _frame.cols << " x " << _frame.rows;
		if (_frame.empty()) {
			counter_++;
			LOG(ERROR) << tag_ << ": Frame is EMPTY.";
			if (counter_ > 5) {
				camera_.release();
				camera_.open(rtsp_);
				LOG(ERROR) << tag_ << ": reopened.";
			}
			return false;
		}

		if (_frame.cols != cols_ || _frame.rows != rows_) {
			LOG(ERROR) << tag_ << ": Frame size ERROR.";
			return false;
		}

		counter_ = 0;

		cv::cvtColor(_frame, frame, cv::COLOR_BGR2GRAY);

		return true;
	}
	default: break;
	}
	return false;
}