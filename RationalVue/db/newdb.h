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

	MYSQL mysql;       //mysql连接
	MYSQL_RES* res;   //返回行的一个查询结果集
	MYSQL_ROW column; //一个行数据的类型安全表示
	QString querystr;

	//连接数据库
	bool Connect();
	bool Connect(QString username, QString password);

	//释放资源
	void FreeConnect();

	//根据相机ID查询对应单位数和楼栋号
	bool GetBuildinginfo(int cameraID, int& buildingnum, int& unitnum);
	bool GetCamerainfo(int cameraID, int& buildingnum, int& unitnum, int& uppercameraID);

	//向videosave表插入一行数据
	bool InsertVideoSaveTable(QString filename, QString filepath, QString datetime, int cameraID, int floornum);
	bool InsertVideoSaveTable(QString filename, QString filepath, QString imgPath, QString datetime, int cameraID, int floornum);
	bool InsertVideoSaveTable(QString filename, QString filepath, QString imgPath, int tossX, int tossY, QString datetime, int cameraID, int floornum);

	//videosave表中删除一数据
	bool DelVideoSaveData(QString filepath);

	//查询videosave表中的文件名filename和文件路径filepath
	bool SearchVideo(QStringList& filenames, QStringList& filepaths);



	//显示t_videosave表
	JSON ShowVideo();

	//按时间查询相关存储视频
	JSON SearchVideo(QString beginTime, QString endTime);

	//根据单元号、楼栋号和楼层数查询
	JSON SearchVideo(int unitnum, int buildingnum = 0, int floornum = 0);

	//根据时间、单元号、楼栋号和楼层数查询
	JSON SearchVideo(QDateTime startTime, QDateTime endTime, int unitnum = 0, int buildingnum = 0, int startFloor = 0, int endFloor = 0);
	void searchVideo(QDateTime startTime, QDateTime endTime, int unitnum = 0, int buildingnum = 0, int startFloor = 0, int endFloor = 0){}

	//查询所有用户
	JSON Showusers();
	//添加用户
	bool AddUser(QString username, QString password);
	//删除用户
	bool DelUser(QString username);
	//检查当前用户权限
	bool CheckRight();

	//检测某一相机上方的相机短时间内是否有抛物
	bool TossCheck(int cameraID, QDateTime time);
	JSON TossCheck2(int cameraID, QDateTime time);

	bool TossCheck2(int cameraID, int floor, QDateTime time);

private:
	mysqldb();
};

#endif  //NEWDB_H_

/***********************使用示例***************************
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
