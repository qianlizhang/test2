#include "newdb.h"

mysqldb::mysqldb()
{

}

bool mysqldb::Connect()
{
	mysql_init(&mysql);
	if (!(mysql_real_connect(&mysql, "localhost", "root", "123", "hightoss", 3306, NULL, 0)))
	{
		QMessageBox::about(NULL, "Connect Error", mysql_error(&mysql));
		return false;
	}
	else
	{
		printf("connect success!\n");
		return true;
	}
}

bool mysqldb::Connect(QString username, QString password)
{
	mysql_init(&mysql);
	if (!(mysql_real_connect(&mysql, "localhost", username.toStdString().c_str(), password.toStdString().c_str(), "hightoss", 3306, NULL, 0)))
	{
		QMessageBox::about(NULL, "Connect Error", mysql_error(&mysql));
		return false;
	}
	else
	{
		printf("connect success!\n");
		return true;
	}
}


void mysqldb::FreeConnect()
{
	mysql_close(&mysql);
//	mysql_free_result(res);
}

bool mysqldb::GetBuildinginfo(int cameraID, int& buildingnum, int& unitnum)
{
	querystr = "select buildingnum,unitnum from t_camerainfo where cameraID = " + QString::number(cameraID, 10) + ";";
	if (mysql_query(&mysql, querystr.toStdString().c_str()))
	{
		QMessageBox::about(NULL, "Get Data Error", mysql_error(&mysql));
		return false;
	}
	res = mysql_store_result(&mysql);
	column = mysql_fetch_row(res);
	buildingnum = atoi(column[0]);
	unitnum = atoi(column[1]);
	return true;
}

bool mysqldb::GetCamerainfo(int cameraID, int& buildingnum, int& unitnum, int& uppercameraID)
{
	querystr = "select buildingnum,unitnum,uppercameraID from t_camerainfo where cameraID = " + QString::number(cameraID, 10) + ";";
	if (mysql_query(&mysql, querystr.toStdString().c_str()))
	{
		QMessageBox::about(NULL, "Get Data Error", mysql_error(&mysql));
		return false;
	}
	res = mysql_store_result(&mysql);
	column = mysql_fetch_row(res);
	buildingnum = atoi(column[0]);
	unitnum = atoi(column[1]);
	uppercameraID = atoi(column[2]);
	return true;
}

bool mysqldb::InsertVideoSaveTable(QString filename, QString filepath, QString datetime, int cameraID, int floornum)
{
	querystr = "insert into t_videosave(filename,filepath,tosstime,cameraID,floornum) values ('" + filename + "','" + filepath + "','" + datetime + "',"
		+ QString::number(cameraID, 10) + "," + QString::number(floornum, 10) + ");";
	if (mysql_query(&mysql, querystr.toStdString().c_str()))  //函数返回0表示查询成功
	{
		QMessageBox::about(NULL, "Insert Database Error", mysql_error(&mysql));
		return false;
	}
	else {
		return true;
	}
}

// 添加插入图片
bool mysqldb::InsertVideoSaveTable(QString filename, QString filepath, QString imgPath, QString datetime, int cameraID, int floornum)
{
	//	Connect("root","123");
	querystr = "insert into t_videosave(filename,filepath, imgpath, tosstime,cameraID,floornum) values ('" + filename + "','" + filepath + "','" + imgPath + "','" + datetime + "',"
		+ QString::number(cameraID, 10) + "," + QString::number(floornum, 10) + ");";
	std::string query1 = querystr.toStdString();
	char query2[1000];
	strcpy(query2, query1.c_str());
	if (mysql_query(&mysql, query2))  //函数返回0表示查询成功
	{
		QMessageBox::about(NULL, "Insert Database Error", mysql_error(&mysql));
		return false;
	}
	else {
		return true;
	}
}

bool mysqldb::InsertVideoSaveTable(QString filename, QString filepath, QString imgPath, int tossX, int tossY, QString datetime, int cameraID, int floornum)
{
	Connect("root", "123");
	querystr = "insert into t_videosave(filename,filepath, imgpath,tossX,tossY,tosstime,cameraID,floornum) values ('" + filename + "','" + filepath + "','" + imgPath + "'," + QString::number(tossX, 10) + "," + QString::number(tossY, 10) + ",'" + datetime + "',"
		+ QString::number(cameraID, 10) + "," + QString::number(floornum, 10) + ");";
	std::string query1 = querystr.toStdString();
	char query2[1000];
	strcpy(query2, query1.c_str());
	if (mysql_query(&mysql, query2))  //函数返回0表示查询成功
	{
		QMessageBox::about(NULL, "Insert Database Error", mysql_error(&mysql));
		return false;
	}
	else {
		return true;
	}
}


bool mysqldb::SearchVideo(QStringList& filenames, QStringList& filepaths)
{
	querystr = "select filename,filepath from t_videosave;";
	if (mysql_query(&mysql, querystr.toStdString().c_str()))
	{
		QMessageBox::about(NULL, "Data Search Error", mysql_error(&mysql));
		return false;
	}
	else {
		res = mysql_store_result(&mysql);
		while (column = mysql_fetch_row(res))
		{
			filenames << column[0];
			filepaths << column[1];
		}
		return true;
	}
}



bool mysqldb::DelVideoSaveData(QString filepath)
{
	querystr = "delete from t_videosave where filepath =\'" + filepath + "\';";
	if (mysql_query(&mysql, querystr.toStdString().c_str()))
	{
		QMessageBox::about(NULL, "Delete Data Error", mysql_error(&mysql));
		return false;
	}
	else {
		return true;
	}
}

JSON mysqldb::ShowVideo()
{
	querystr = "SELECT v.filename, v.tosstime,v.cameraID, v.floornum, c.buildingnum,c.unitnum, v.filepath, v.imgpath from t_videosave v join t_camerainfo c on v.cameraID = c.cameraID;";
	JSON result = JSON::array({});
	if (mysql_query(&mysql, querystr.toStdString().c_str()))
	{
		QMessageBox::about(NULL, "Data Search Error", mysql_error(&mysql));
		return result;
	}
	else
	{
		//获取结果集
		res = mysql_store_result(&mysql);
		int affectRows = mysql_affected_rows(&mysql);
		qDebug() << "number of affected rows is " << affectRows;
		//	std::vector<JSON> jsonData;
		while (column = mysql_fetch_row(res))
		{
			JSON resultRow;
			resultRow["filename"] = column[0];
			resultRow["tosstime"] = column[1];
			resultRow["cameraID"] = atoi(column[2]);
			resultRow["floornum"] = atoi(column[3]);
			resultRow["buildingnum"] = atoi(column[4]);
			resultRow["unitnum"] = atoi(column[5]);
			resultRow["filepath"] = column[6];
			resultRow["imgpath"] = column[7];
			result.push_back(resultRow);
		}
		return result;
	}
}

JSON mysqldb::SearchVideo(QString beginTime, QString endTime)
{
	querystr = "select v.filename,v.tosstime,v.cameraID,c.buildingnum,c.unitnum,v.floornum from t_videosave v join t_camerainfo c on v.cameraID = c.cameraID"
		" where v.tosstime>=\'" + beginTime + "\' and v.tosstime<=\'" + endTime + "\';";
	JSON result = JSON::array({});
	if (mysql_query(&mysql, querystr.toStdString().c_str()))
	{
		QMessageBox::about(NULL, "Data Search Error", mysql_error(&mysql));
		return result;
	}
	else
	{
		//获取结果集
		res = mysql_store_result(&mysql);
		int affectRows = mysql_affected_rows(&mysql);
		qDebug() << "number of affected rows is " << affectRows;
		std::vector<JSON> jsonData;
		while (column = mysql_fetch_row(res))
		{
			JSON resultRow;
			resultRow["filename"] = column[0];
			resultRow["tosstime"] = column[1];
			resultRow["cameraID"] = atoi(column[2]);
			resultRow["floornum"] = atoi(column[3]);
			resultRow["buildingnum"] = atoi(column[4]);
			resultRow["unitnum"] = atoi(column[5]);
			result.push_back(resultRow);
		}
		return result;
	}

}

JSON mysqldb::SearchVideo(int unitnum, int buildingnum, int floornum)
{
	if (floornum != 0) {
		querystr = "select v.filename,v.tosstime,v.cameraID,c.buildingnum,c.unitnum,v.floornum from t_videosave v join t_camerainfo c on v.cameraID = c.cameraID"
			" where v.floornum=" + QString::number(floornum, 10) + " and c.buildingnum=" + QString::number(buildingnum, 10) + " and c.unitnum=" + QString::number(unitnum, 10) + ";";
	}
	else if (buildingnum != 0) {
		querystr = "select v.filename,v.tosstime,v.cameraID,c.buildingnum,c.unitnum,v.floornum from t_videosave v join t_camerainfo c on v.cameraID = c.cameraID"
			" where c.buildingnum=" + QString::number(buildingnum, 10) + " and c.unitnum=" + QString::number(unitnum, 10) + ";";
	}
	else {
		querystr = "select v.filename,v.tosstime,v.cameraID,c.buildingnum,c.unitnum,v.floornum from t_videosave v join t_camerainfo c on v.cameraID = c.cameraID"
			" where c.unitnum=" + QString::number(unitnum, 10) + ";";
	}
	JSON result = JSON::array({});
	if (mysql_query(&mysql, querystr.toStdString().c_str()))
	{
		QMessageBox::about(NULL, "Data Search Error", mysql_error(&mysql));
		return result;
	}
	else
	{
		//获取结果集
		res = mysql_store_result(&mysql);
		int affectRows = mysql_affected_rows(&mysql);
		qDebug() << "number of affected rows is " << affectRows;
		std::vector<JSON> jsonData;
		while (column = mysql_fetch_row(res))
		{
			JSON resultRow;
			resultRow["filename"] = column[0];
			resultRow["tosstime"] = column[1];
			resultRow["cameraID"] = atoi(column[2]);
			resultRow["floornum"] = atoi(column[3]);
			resultRow["buildingnum"] = atoi(column[4]);
			resultRow["unitnum"] = atoi(column[5]);
			result.push_back(resultRow);
		}
		return result;
	}
}

JSON mysqldb::SearchVideo(QDateTime startTime, QDateTime endTime, int unitnum, int buildingnum, int startFloor, int endFloor)
{
	JSON result = JSON::array({});
	QString queryCmd = "SELECT v.filename, v.tosstime,v.cameraID, v.floornum, c.buildingnum,c.unitnum, v.filepath, v.imgpath FROM t_videosave v JOIN t_camerainfo c ON v.cameraID = c.cameraID";
	QString queryConditions = "";
	//Judge if starttime <= endtime and if startfloor < endfloor
	if (startTime.toTime_t() > endTime.toTime_t()) {
		QMessageBox::about(NULL, "提醒", "时间输入错误");
		return result;
	}
	if (startFloor > endFloor) {
		QMessageBox::about(NULL, "提醒", "楼层信息输入错误");
		return result;
	}
	//Time condition
	queryConditions += " WHERE tosstime >=\'" + startTime.toString("yyyy-MM-dd hh:mm:ss") + "\'";
	queryConditions += " AND tosstime<=\'" + endTime.toString("yyyy-MM-dd hh:mm:ss") + "\'";
	//Floor condition
	if (0 != startFloor || 0 != endFloor) {
		queryConditions += " AND floornum >=" + QString::number(startFloor, 10);
		queryConditions += " AND floornum<=" + QString::number(endFloor, 10);
	}
	//Building condition
	if (buildingnum != 0)
		queryConditions += " AND buildingnum=" + QString::number(buildingnum, 10);
	//Unit condition
	if (unitnum != 0)
		queryConditions += " AND unitnum=" + QString::number(unitnum, 10);
	//End of sql
	queryCmd += queryConditions + ";";
	//LOG(INFO) << "Generated sql: " << queryCmd.toStdString() <<"\n";

	if (mysql_query(&mysql, queryCmd.toStdString().c_str()))
	{
		QMessageBox::about(NULL, "Data Search Error", mysql_error(&mysql));
		return result;
	}
	else
	{
		//获取结果集
		res = mysql_store_result(&mysql);
		int affectRows = mysql_affected_rows(&mysql);
		qDebug() << "number of affected rows is " << affectRows;

		while (column = mysql_fetch_row(res))
		{
			JSON resultRow;
			resultRow["filename"] = column[0];
			resultRow["tosstime"] = column[1];
			resultRow["cameraID"] = atoi(column[2]);
			resultRow["floornum"] = atoi(column[3]);
			resultRow["buildingnum"] = atoi(column[4]);
			resultRow["unitnum"] = atoi(column[5]);
			resultRow["filepath"] = column[6];
			resultRow["imgpath"] = column[7];
			result.push_back(resultRow);
		}
		return result;
	}
}

JSON mysqldb::Showusers()
{
	querystr = "select distinct user,password from mysql.user";
	JSON result = JSON::array({});
	if (mysql_query(&mysql, querystr.toStdString().c_str()))
	{
		QMessageBox::about(NULL, "User Data Search Error", mysql_error(&mysql));
		return result;
	}
	else
	{
		//获取结果集
		res = mysql_store_result(&mysql);
		int affectRows = mysql_affected_rows(&mysql);
		qDebug() << "number of affected rows is " << affectRows;
		while (column = mysql_fetch_row(res))
		{
			JSON resultRow;
			resultRow["username"] = column[0];
			//	resultRow["password"] = column[1];
			result.push_back(resultRow);
		}
		return result;
	}
}

bool mysqldb::DelUser(QString username)
{
	querystr = "drop user '" + username + "'@'localhost';";
	if (mysql_query(&mysql, querystr.toStdString().c_str()))
	{
		QMessageBox::about(NULL, "Del User Error", mysql_error(&mysql));
		return false;
	}

	querystr = "flush privileges;";
	if (mysql_query(&mysql, querystr.toStdString().c_str()))
	{
		QMessageBox::about(NULL, "Del User Error", mysql_error(&mysql));
		return false;
	}
	return true;

}

bool mysqldb::AddUser(QString username, QString password)
{
	querystr = "create user '" + username + "'@'localhost' IDENTIFIED BY '" + password + "';";
	if (mysql_query(&mysql, querystr.toStdString().c_str()))
	{

		//	QMessageBox::about(NULL, "Add User Error", mysql_error(&mysql));
		//	return false;
	}
	querystr = "grant select,insert on hightoss.* to '" + username + "'@'localhost';";
	if (mysql_query(&mysql, querystr.toStdString().c_str()))
	{
		QMessageBox::about(NULL, "Add User Error", mysql_error(&mysql));
		return false;
	}
	querystr = "flush privileges;";
	if (mysql_query(&mysql, querystr.toStdString().c_str()))
	{
		QMessageBox::about(NULL, "Add User Error", mysql_error(&mysql));
		return false;
	}

	return true;
}

bool mysqldb::CheckRight()
{
	querystr = "select distinct user,password from mysql.user";
	if (mysql_query(&mysql, querystr.toStdString().c_str()))
	{
		return false;
	}
	else {
		res = mysql_store_result(&mysql);
		return true;
	}
}

bool mysqldb::TossCheck(int cameraID, QDateTime time)
{
	querystr = "select * from t_videosave where tosstime >=\'" + time.toString("yyyy-MM-dd hh:mm:ss") + "';";
	if (!mysql_query(&mysql, querystr.toStdString().c_str()))
	{
		//查询失败
		return false;
	}
	else {
		res = mysql_store_result(&mysql);
		return true;
	}
}

bool mysqldb::TossCheck2(int cameraID, int floor,QDateTime time)
{
	querystr = "select * from t_videosave where tosstime >=\'" + time.toString("yyyy-MM-dd hh:mm:ss") + "' and floor_num = "+QString::number(floor,10)+";";
	if (!mysql_query(&mysql, querystr.toStdString().c_str()))
	{
		//查询失败
		return false;
	}
	else {
		res = mysql_store_result(&mysql);
		return true;
	}
}



JSON mysqldb::TossCheck2(int cameraID, QDateTime time)
{
	querystr = "select tossX,tossY from t_videosave where tosstime >=\'" + time.toString("yyyy-MM-dd hh:mm:ss") + "';";
	JSON result = JSON::array({});
	if (mysql_query(&mysql, querystr.toStdString().c_str()))
	{
		QMessageBox::about(NULL, "User Data Search Error", mysql_error(&mysql));
		return result;
	}
	else
	{
		//获取结果集
		res = mysql_store_result(&mysql);
		int affectRows = mysql_affected_rows(&mysql);
		qDebug() << "number of affected rows is " << affectRows;
		while (column = mysql_fetch_row(res))
		{
			JSON resultRow;
			resultRow["tossX"] = column[0];
			resultRow["tossY"] = column[1];

			result.push_back(resultRow);
		}
		return result;
	}
}

/*
JSON newdb::SearchAllUser() {
	querystr = "SELECT u.username, u.password FROM t_user u;";
	JSON result = JSON::array({});
	if (mysql_query(&mysql, querystr.toStdString().c_str()))
	{
		QMessageBox::about(NULL, "Data Search Error", mysql_error(&mysql));
		return result;
	}
	else
	{
		//获取结果集
		res = mysql_store_result(&mysql);
		int affectRows = mysql_affected_rows(&mysql);
		qDebug() << "number of affected rows is " << affectRows;
		std::vector<JSON> jsonData;
		while (column = mysql_fetch_row(res))
		{
			JSON resultRow;
			resultRow["username"] = column[0];
			resultRow["password"] = column[1];
			result.push_back(resultRow);
		}
		return result;
	}
}

bool newdb::InsertUser(QString username, QString password){
	querystr = "insert into t_user values ('" + username + "','" + password +  ");";
	if (mysql_query(&mysql, querystr.toStdString().c_str()))  //函数返回0表示查询成功
	{
		QMessageBox::about(NULL, "Insert Database Error", mysql_error(&mysql));
		return false;
	}
	else {
		return true;
	}
}

bool newdb::DelUser(QString username) {
	querystr = "delete from t_user where username =\'" + username + "\';";
	if (mysql_query(&mysql, querystr.toStdString().c_str()))
	{
		QMessageBox::about(NULL, "Delete Data Error", mysql_error(&mysql));
		return false;
	}
	else {
		return true;
	}
}
*/