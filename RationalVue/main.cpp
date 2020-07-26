/*
 * @Description: 
 * @Author: szq
 * @Github: https://github.com/MrQqqq
 * @Date: 2020-07-14 14:48:57
 * @LastEditors: szq
 * @LastEditTime: 2020-07-14 16:12:54
 * @FilePath: \undefinedd:\downloads\HighTossAct3\RationalVue\main.cpp
 */ 
#include <QApplication>
//#include "CameraLogInWindow.h"
#include "syscontroller.h"
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
#include <glog/log_severity.h>
#include"mainwindow.h"
#include<QTranslator>
#include<QDebug>
#include <qfile.h>

int main(int argc, char *argv[])
{
	google::InitGoogleLogging(argv[0]);

	FLAGS_log_dir = "d:\\Logs";

	google::SetLogDestination(google::GLOG_INFO, "d:\\Logs\\00_I_");
//	google::SetLogDestination(google::GLOG_WARNING, "d:\\Logs\\01_W_");
//	google::SetLogDestination(google::GLOG_ERROR, "d:\\Logs\\02_E_");
//	google::SetLogDestination(google::GLOG_FATAL, "d:\\Logs\\03_F_");

	FLAGS_alsologtostderr = true; //同时输出到终端
	FLAGS_colorlogtostderr = true; //输出彩色日志到stderr
	FLAGS_minloglevel = 0;
	FLAGS_logbufsecs = 0; //实时输出
	FLAGS_max_log_size = 1024;					// Sets the maximum log file size (in MB).
	FLAGS_stop_logging_if_full_disk = true;

	google::InstallFailureSignalHandler();      //捕捉 core dumped

	QApplication a(argc, argv);

	//qRegisterMetaType<DETRESULT>("DETRESULT");

	//加载界面格式QSS文件
	QFile qss(":/mainResource/default.qss");
	qss.open(QFile::ReadOnly);
	qApp->setStyleSheet(qss.readAll());
	qss.close();

	//auto& controller = SysController::Instance(argc, argv);

	
	QTranslator translator;
	MainWindow::loadTranslate();
	translator.load(MainWindow::tr_file);
	a.installTranslator(&translator);


	auto& controller = SysController::Instance(argc, argv);

	return a.exec();
}
