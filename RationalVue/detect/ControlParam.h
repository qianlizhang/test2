#pragma once 

#include <QString>

typedef struct controlparam {
	QString ctrlerIP;			// �������˵�ַ���˿ں�
	quint16 ctrlerPort;

	uint processID;				// ��ǰ����ID
	bool isMaster;				// Master(true), Slave(false)

	uint masterID;				// Master process ID

	bool isLoginCamera;			// �Ƿ��ѵ�¼���

	QString cameraIP;
	QString cameraUsername;
	QString cameraPass;
	int cameraID;//��������

	struct controlparam()
	{
		ctrlerIP = cameraIP = cameraUsername = cameraPass = "";
		cameraID = ctrlerPort = processID = masterID = 0;
		isMaster = isLoginCamera = false;
	}

} ControlParam;

