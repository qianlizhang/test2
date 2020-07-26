#ifndef NVR_H
#define NVR_H

#include <string>
#include <glog/logging.h>
#include "HCNetSDK.h"


class NVR {
public:
	NVR(std::string ip, std::string username, std::string password)
		: ip_(ip), username_(username), password_(password)
	{ }

	~NVR() 
	{
		exit();
	}

	bool login();
	void getFileByTime(LONG camera_channel, const NET_DVR_TIME& start_time, const NET_DVR_TIME& end_time, const std::string& filename);
	
	LONG playbackByTime(LONG camera_channel, const NET_DVR_TIME& start_time, const NET_DVR_TIME& end_time, const HWND hwnd);
	void stopPlayback(LONG hPlayback)
	{
		if (!NET_DVR_StopPlayBack(hPlayback)) {
			LOG(ERROR) << "failed to stop file: " << NET_DVR_GetLastError();
			exit();
			return;
		}
	}

	void findFile(LONG camera_channel, const NET_DVR_TIME& start_time, const NET_DVR_TIME& end_time);
	int saveRecordFile(int userId, char * srcfile, char * destfile);

	void exit()
	{
		NET_DVR_Logout(userid_);
		NET_DVR_Cleanup();
	}

	
	
private:
	LONG userid_ = -1;

	std::string ip_;
	std::string username_;
	std::string password_;
};



#endif