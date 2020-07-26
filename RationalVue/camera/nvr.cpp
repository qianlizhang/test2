#include "nvr.h"

bool NVR::login()
{
	NET_DVR_Init();
	//��������ʱ��������ʱ��
	NET_DVR_SetConnectTime(10000, 2);
	NET_DVR_SetReconnect(10000, true);

	//---------------------------------------
	// ע���豸
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
	struDownloadCond.dwChannel = camera_channel;								//ͨ����

	struDownloadCond.struStartTime = start_time;
	struDownloadCond.struStopTime = end_time;

	//---------------------------------------
	//��ʱ������
	auto hPlayback = NET_DVR_GetFileByTime_V40(userid_, const_cast<char *>(filename.c_str()), &struDownloadCond);
	if (hPlayback < 0) {
		LOG(FATAL) << "NET_DVR_GetFileByTime_V40 fail,last error : " << NET_DVR_GetLastError();
		exit();
		return;
	}
	//---------------------------------------
	//��ʼ����
	if (!NET_DVR_PlayBackControl_V40(hPlayback, NET_DVR_PLAYSTART, NULL, 0, NULL, NULL)) {
		LOG(FATAL) << "Play back control failed: " << NET_DVR_GetLastError();
		exit();
		return;
	}
	int nPos = 0;
	for (nPos = 0; nPos < 100 && nPos >= 0; nPos = NET_DVR_GetDownloadPos(hPlayback)) {
		LOG(INFO) << "Be downloading... " << nPos << "%";			//���ؽ���
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

	struVodPara.struIDInfo.dwChannel = camera_channel; //ͨ����
	struVodPara.hWnd = hwnd; //�طŴ���

	struVodPara.struBeginTime = start_time;
	struVodPara.struEndTime = end_time;

	//---------------------------------------
	//��ʱ��ط�
	auto hPlayback = NET_DVR_PlayBackByTime_V40(userid_, &struVodPara);
	if (hPlayback < 0) {
		LOG(ERROR) << "NET_DVR_PlayBackByTime_V40 fail,last error: " << NET_DVR_GetLastError();
		exit();
		return hPlayback;
	}
	//---------------------------------------
	//��ʼ
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
	struFileCond.lChannel = camera_channel; //ͨ����
	struFileCond.dwIsLocked = 0xFF;
	struFileCond.dwUseCardNo = 0;
	struFileCond.struStartTime = start_time;
	struFileCond.struStopTime = end_time;

	//---------------------------------------
	//����¼���ļ�
	int lFindHandle = NET_DVR_FindFile_V40(userid_, &struFileCond);
	if (lFindHandle < 0) {
		LOG(FATAL) << "find file fail,last error: " << NET_DVR_GetLastError();
		return;
	}
	NET_DVR_FINDDATA_V40 struFileData;
	while (true)
	{
		//�����ȡ���ҵ����ļ���Ϣ
		int result = NET_DVR_FindNextFile_V40(lFindHandle, &struFileData);
		if (result == NET_DVR_ISFINDING) {
			continue;
		}
		else if (result == NET_DVR_FILE_SUCCESS) { //��ȡ�ļ���Ϣ�ɹ�
			char strFileName[256] = { 0 };
			sprintf(strFileName, "./%s", struFileData.sFileName);
			saveRecordFile(userid_, struFileData.sFileName, strFileName);
			break;
		}
		else if (result == NET_DVR_FILE_NOFIND || result == NET_DVR_NOMOREFILE) { //δ���ҵ��ļ����߲��ҽ���
			break;
		}
		else {
			LOG(INFO) << "find file fail for illegal get file state";
			break;
		}
	}
	//ֹͣ����
	if (lFindHandle >= 0) {
		NET_DVR_FindClose_V30(lFindHandle);
	}
}

int NVR::saveRecordFile(int userId, char * srcfile, char * destfile)
{
	int bRes = 1;
	int hPlayback = 0;
	//���ļ�������¼��
	if ((hPlayback = NET_DVR_GetFileByName(userId, srcfile, destfile)) < 0)
	{
		LOG(ERROR) << "GetFileByName failed. error: " << NET_DVR_GetLastError();
		bRes = -1;
		return bRes;
	}
	//��ʼ����
	if (!NET_DVR_PlayBackControl_V40(hPlayback, NET_DVR_PLAYSTART, NULL, 0, NULL, NULL)) {
		printf("play back control failed [%d]\n", NET_DVR_GetLastError());
		bRes = -1;
		return bRes;
	}
	int nPos = 0;
	for (nPos = 0; nPos < 100 && nPos >= 0; nPos = NET_DVR_GetDownloadPos(hPlayback))
	{
		LOG(INFO) << "Be downloading... " << nPos << "%"; //���ؽ���
		Sleep(5000); //millisecond
	}
	LOG(INFO) << "have got : " << nPos << "%";
	//ֹͣ����
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