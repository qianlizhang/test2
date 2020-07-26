#pragma once
#include <QObject>
#include <QSqlDatabase>
#include <QCoreApplication>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQuery>
#include <iostream>
#include <stdio.h>
#include <qDebug>

class dbManager : public QObject
{
public:
	QSqlDatabase db;
//	QSqlQuery query;
	static dbManager* Instance()
	{
		static dbManager instance;
		return &instance;
	}

public:
	~dbManager();
	bool connect(const QString &dbName);
	bool createTable();
//	bool insert(const QString &str);

	void writetest();
	void readtest();
	void readvideosave(QStringList& filenames, QStringList& paths);

private:
	dbManager();

};

