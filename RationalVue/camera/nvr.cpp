#include "nvr.h"

bool NVR::login()
{
	NET_DVR_Init();
	//设置连接时间与重连时间
	NET_DVR_SetConnectTime(10000, 2);
	NET_DVR_SetReconnect(10000, true);

	//---------------------------------------
	// 注册设备
	NET_DVR_DEVICEINFO_V30 struDeviceInfo;

	userid_ = NET_DVR_Login_V30(
		const_cast<char *>(ip_.c_str()),
		8000,
		const_cast<char *>(username_.c_str()),
		const_cast<char *>(password_.c_str()),
		&struDeviceInfo
	);

	if (userid_ < 0) {
		LOG(ERROR) << "Login error: " << NET_DVR_GetLastError();
		NET_DVR_Cleanup();
		return false;
	}
	LOG(INFO) << "Login: success!";
	return true;
}


void NVR::getFileByTime(LONG camera_channel, const NET_DVR_TIME& start_time, const NET_DVR_TIME& end_time, const std::string& filename)
{
	NET_DVR_PLAYCOND struDownloadCond = { 0 };
	struDownloadCond.dwChannel = camera_channel;								//通道号

	struDownloadCond.struStartTime = start_time;
	struDownloadCond.struStopTime = end_time;

	//---------------------------------------
	//按时间下载
	auto hPlayback = NET_DVR_GetFileByTime_V40(userid_, const_cast<char *>(filename.c_str()), &struDownloadCond);
	if (hPlayback < 0) {
		LOG(FATAL) << "NET_DVR_GetFileByTime_V40 fail,last error : " << NET_DVR_GetLastError();
		exit();
		return;
	}
	//---------------------------------------
	//开始下载
	if (!NET_DVR_PlayBackControl_V40(hPlayback, NET_DVR_PLAYSTART, NULL, 0, NULL, NULL)) {
		LOG(FATAL) << "Play back control failed: " << NET_DVR_GetLastError();
		exit();
		return;
	}
	int nPos = 0;
	for (nPos = 0; nPos < 100 && nPos >= 0; nPos = NET_DVR_GetDownloadPos(hPlayback)) {
		LOG(INFO) << "Be downloading... " << nPos << "%";			//下载进度
		Sleep(1000);										//millisecond
	}
	if (!NET_DVR_StopGetFile(hPlayback)) {
		LOG(FATAL) << "failed to stop get file : " << NET_DVR_GetLastError();
		exit();
		return;
	}
	if (nPos < 0 || nPos>100) {
		LOG(ERROR) << "download err : " << NET_DVR_GetLastError();
		exit();
		return;
	}
}
LONG NVR::playbackByTime(LONG camera_channel, const NET_DVR_TIME& start_time, const NET_DVR_TIME& end_time, const HWND hwnd)
{
	NET_DVR_VOD_PARA struVodPara = { 0 };
	struVodPara.dwSize = sizeof(struVodPara);

	struVodPara.struIDInfo.dwChannel = camera_channel; //通道号
	struVodPara.hWnd = hwnd; //回放窗口

	struVodPara.struBeginTime = start_time;
	struVodPara.struEndTime = end_time;

	//---------------------------------------
	//按时间回放
	auto hPlayback = NET_DVR_PlayBackByTime_V40(userid_, &struVodPara);
	if (hPlayback < 0) {
		LOG(ERROR) << "NET_DVR_PlayBackByTime_V40 fail,last error: " << NET_DVR_GetLastError();
		exit();
		return hPlayback;
	}
	//---------------------------------------
	//开始
	if (!NET_DVR_PlayBackControl_V40(hPlayback, NET_DVR_PLAYSTART, NULL, 0, NULL, NULL)) {
		LOG(ERROR) << "play back control failed: " << NET_DVR_GetLastError();
		exit();
		return hPlayback;
	}

	return hPlayback;
}
void NVR::findFile(LONG camera_channel, const NET_DVR_TIME& start_time, const NET_DVR_TIME& end_time)
{
	NET_DVR_FILECOND_V40 struFileCond = { 0 };
	struFileCond.dwFileType = 0xff;
	struFileCond.lChannel = camera_channel; //通道号
	struFileCond.dwIsLocked = 0xFF;
	struFileCond.dwUseCardNo = 0;
	struFileCond.struStartTime = start_time;
	struFileCond.struStopTime = end_time;

	//---------------------------------------
	//查找录像文件
	int lFindHandle = NET_DVR_FindFile_V40(userid_, &struFileCond);
	if (lFindHandle < 0) {
		LOG(FATAL) << "find file fail,last error: " << NET_DVR_GetLastError();
		return;
	}
	NET_DVR_FINDDATA_V40 struFileData;
	while (true)
	{
		//逐个获取查找到的文件信息
		int result = NET_DVR_FindNextFile_V40(lFindHandle, &struFileData);
		if (result == NET_DVR_ISFINDING) {
			continue;
		}
		else if (result == NET_DVR_FILE_SUCCESS) { //获取文件信息成功
			char strFileName[256] = { 0 };
			sprintf(strFileName, "./%s", struFileData.sFileName);
			saveRecordFile(userid_, struFileData.sFileName, strFileName);
			break;
		}
		else if (result == NET_DVR_FILE_NOFIND || result == NET_DVR_NOMOREFILE) { //未查找到文件或者查找结束
			break;
		}
		else {
			LOG(INFO) << "find file fail for illegal get file state";
			break;
		}
	}
	//停止查找
	if (lFindHandle >= 0) {
		NET_DVR_FindClose_V30(lFindHandle);
	}
}

int NVR::saveRecordFile(int userId, char * srcfile, char * destfile)
{
	int bRes = 1;
	int hPlayback = 0;
	//按文件名下载录像
	if ((hPlayback = NET_DVR_GetFileByName(userId, srcfile, destfile)) < 0)
	{
		LOG(ERROR) << "GetFileByName failed. error: " << NET_DVR_GetLastError();
		bRes = -1;
		return bRes;
	}
	//开始下载
	if (!NET_DVR_PlayBackControl_V40(hPlayback, NET_DVR_PLAYSTART, NULL, 0, NULL, NULL)) {
		printf("play back control failed [%d]\n", NET_DVR_GetLastError());
		bRes = -1;
		return bRes;
	}
	int nPos = 0;
	for (nPos = 0; nPos < 100 && nPos >= 0; nPos = NET_DVR_GetDownloadPos(hPlayback))
	{
		LOG(INFO) << "Be downloading... " << nPos << "%"; //下载进度
		Sleep(5000); //millisecond
	}
	LOG(INFO) << "have got : " << nPos << "%";
	//停止下载
	if (!NET_DVR_StopGetFile(hPlayback)) {
		LOG(ERROR) << "failed to stop get file: " << NET_DVR_GetLastError();
		bRes = -1;
		return bRes;
	}
	printf("%s\n", srcfile);
	if (nPos < 0 || nPos>100) {
		LOG(ERROR) << "download err: " << NET_DVR_GetLastError();
		bRes = -1;
		return bRes;
	}
	else {
		return 0;
	}
}