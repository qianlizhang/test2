#include "syscontroller.h"
#include <QMessageBox>
#include "common.h"
#include "CommonData.h"

SysController::SysController(int argc, char *argv[])
{
	CCommonData *commondata = new CCommonData();
	// 启动主界面
	mainwindow_ = new MainWindow(commondata);
	mainwindow_->show();
//	newdb_->Instance();
//
//	//mainwindow_->show();
//	connects();
}

SysController::~SysController()
{
	//delete mainwindow_;
	google::ShutdownGoogleLogging();
}

//void SysController::connects()
//{
//	connect(mainwindow_,&MainWidget::cellClick, this,&SysController::changeCameraState);
//	connect(mainwindow_->cameraloginwindow, &CameraLogInWindow::result, mainwindow_->rtmonwidget, &RTMonWidget::ResultShowUpdate);
//	connect(mainwindow_->playbackwidget->ui.listWidget, &QListWidget::itemSelectionChanged, mainwindow_->playbackwidget, &PlaybackWidget::ShowVedio);
//	connect(mainwindow_->playbackwidget, &PlaybackWidget::SearchVideo, newdb_, &mysqldb::searchVideo);
//}