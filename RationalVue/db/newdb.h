#ifndef NEWDB_H_
#define NEWDB_H_

#include <stdio.h>
#include <winsock.h>
#include "mysql.h"
#include <iostream>
#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include "common.h"
//#include "glog/logging.h"
//#include "common.h"
#include "json.hpp"
using JSON = nlohmann::json;

class database :public CBaseProcessLogic {

};

class mysqldb : public database
{
public:

	static mysqldb* Instance()
	{
		static mysqldb instance;
		return &instance;
	}

	MYSQL mysql;       //mysql����
	MYSQL_RES* res;   //�����е�һ����ѯ�����
	MYSQL_ROW column; //һ�������ݵ����Ͱ�ȫ��ʾ
	QString querystr;

	//�������ݿ�
	bool Connect();
	bool Connect(QString username, QString password);

	//�ͷ���Դ
	void FreeConnect();

	//�������ID��ѯ��Ӧ��λ����¥����
	bool GetBuildinginfo(int cameraID, int& buildingnum, int& unitnum);
	bool GetCamerainfo(int cameraID, int& buildingnum, int& unitnum, int& uppercameraID);

	//��videosave�����һ������
	bool InsertVideoSaveTable(QString filename, QString filepath, QString datetime, int cameraID, int floornum);
	bool InsertVideoSaveTable(QString filename, QString filepath, QString imgPath, QString datetime, int cameraID, int floornum);
	bool InsertVideoSaveTable(QString filename, QString filepath, QString imgPath, int tossX, int tossY, QString datetime, int cameraID, int floornum);

	//videosave����ɾ��һ����
	bool DelVideoSaveData(QString filepath);

	//��ѯvideosave���е��ļ���filename���ļ�·��filepath
	bool SearchVideo(QStringList& filenames, QStringList& filepaths);



	//��ʾt_videosave��
	JSON ShowVideo();

	//��ʱ���ѯ��ش洢��Ƶ
	JSON SearchVideo(QString beginTime, QString endTime);

	//���ݵ�Ԫ�š�¥���ź�¥������ѯ
	JSON SearchVideo(int unitnum, int buildingnum = 0, int floornum = 0);

	//����ʱ�䡢��Ԫ�š�¥���ź�¥������ѯ
	JSON SearchVideo(QDateTime startTime, QDateTime endTime, int unitnum = 0, int buildingnum = 0, int startFloor = 0, int endFloor = 0);
	void searchVideo(QDateTime startTime, QDateTime endTime, int unitnum = 0, int buildingnum = 0, int startFloor = 0, int endFloor = 0){}

	//��ѯ�����û�
	JSON Showusers();
	//����û�
	bool AddUser(QString username, QString password);
	//ɾ���û�
	bool DelUser(QString username);
	//��鵱ǰ�û�Ȩ��
	bool CheckRight();

	//���ĳһ����Ϸ��������ʱ�����Ƿ�������
	bool TossCheck(int cameraID, QDateTime time);
	JSON TossCheck2(int cameraID, QDateTime time);

	bool TossCheck2(int cameraID, int floor, QDateTime time);

private:
	mysqldb();
};

#endif  //NEWDB_H_

/***********************ʹ��ʾ��***************************
	newdb* testdb = newdb::Instance();
	testdb->Connect();
	testdb->QueryDatabase();
	QString begintime = "2010-01-01 13:20:01";
	QString endtime = "2020-12-07 13:20:01";
	JSON result = testdb->SearchVideo(begintime, endtime);
	for (JSON::iterator it = result.begin(); it != result.end(); ++it)
	{
		std::cout << (*it)["filename"] << "\n";
		auto filename = (*it)["filename"].get<std::string>();
		std::cout << filename << "\n";
		std::cout << (*it)["cameraID"] << "\n";
		auto cameraID = (*it)["cameraID"].get<uint16_t>();
		std::cout << cameraID << "\n";
	}
 **********************************************************/
