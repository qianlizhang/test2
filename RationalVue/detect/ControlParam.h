#pragma once 

#include <QString>

typedef struct controlparam {
	QString ctrlerIP;			// 控制器端地址及端口号
	quint16 ctrlerPort;

	uint processID;				// 当前进程ID
	bool isMaster;				// Master(true), Slave(false)

	uint masterID;				// Master process ID

	bool isLoginCamera;			// 是否已登录相机

	QString cameraIP;
	QString cameraUsername;
	QString cameraPass;
	int cameraID;//摄像机编号

	struct controlparam()
	{
		ctrlerIP = cameraIP = cameraUsername = cameraPass = "";
		cameraID = ctrlerPort = processID = masterID = 0;
		isMaster = isLoginCamera = false;
	}

} ControlParam;

