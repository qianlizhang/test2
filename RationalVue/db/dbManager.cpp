#include "dbManager.h"



dbManager::dbManager()
{
	QStringList list2 = QSqlDatabase::drivers();
	qDebug() << "list2" << list2;
}


dbManager::~dbManager()
{

}

bool dbManager::connect(const QString &dbName)
{
	db = QSqlDatabase::addDatabase("QSQLITE","connect");
	db.setDatabaseName(dbName);
	if (!db.open()) {
		QMessageBox::critical(0, "Database Error", db.lastError().text());
		return false;
	}
	return true;
}

bool dbManager::createTable()
{
	QSqlQuery query(db);
	if (!query.exec("CREATE TABLE videosave ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"filename VARCHAR,"
		"path VARCHAR,"
		"cameraID TINYINT,"
		"floornum TINYINT)"
	)) {
		QMessageBox::critical(0, "Database Error", query.lastError().text());
		return false;
	}
	else {
		return true;
	}
}

void dbManager::writetest()
{
	QSqlQuery query(db);
	query.prepare("INSERT INTO videosave (filename, path) "
							"VALUES (?,?)");
	QVariantList filenames, paths;
	filenames << "01_20180121_1409" << "02_20181201_2310" << "08_20180809_2130";
	query.addBindValue(filenames);
//	paths << "D:/GitRep/HighTossActClient/save/VideoSave/01_20180121_1409.mp4"
//			  << "D:/GitRep/HighTossActClient/save/VideoSave/02_20181201_2310.mp4"
//		  	 << "D:/GitRep/HighTossActClient/save/VideoSave/08_20180809_2130.mp4";
	paths << "D:/20181017/HighTossActClient/x64/save/VideoSave/01_20180121_1409.mp4"
			<< "D:/20181017/HighTossActClient/x64/save/VideoSave/02_20181201_2310.mp4"
			<< "D:/20181017/HighTossActClient/x64/save/VideoSave/08_20180809_2130.mp4";
	query.addBindValue(paths);
	if (!query.execBatch()) {
		QMessageBox::critical(0, "Database Error", query.lastError().text());
	}
	query.finish();

	query.exec("select filename,path FROM videosave");
	while (query.next()) {
		QString filename = query.value(0).toString();
		QString path = query.value(1).toString();
		qDebug() << filename << ":" << path;
	}


}

void dbManager::readtest()
{
	QSqlQuery query(db);
	query.exec("select id,filename,path FROM videosave");
	while (query.next()) {
		int id = query.value(0).toInt();
		QString filename = query.value(1).toString();
		QString path = query.value(2).toString();
		qDebug() << "id is: " << id;
		qDebug() << filename << ":" << path;
	}
}

void dbManager::readvideosave(QStringList& filenames, QStringList& paths)
{
	QSqlQuery query(db);
	query.exec("select filename,path FROM videosave");
	while (query.next()) {
		filenames << query.value(0).toString();
		paths << query.value(1).toString();
	}

	return;
}
