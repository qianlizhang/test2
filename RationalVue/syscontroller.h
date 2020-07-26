// 

#ifndef _SYSCONTROLLER_H
#define _SYSCONTROLLER_H

#include "mainwindow.h"
//#include "db/dbManager.h"
#include "newdb.h"
#include "HKCamera.h"
//#include "CameraLogInWindow.h"
#include "uwc.h"

#define SYS_SET_FLOORS(x, y)														\
	QString floorMsg = QString::number(x) + "层~" + QString::number(y) + "层";	\
	App::pShowEdit[id / 10][id % 10]->setText(floorMsg)
#define SYS_CLR_FLOORS()															\
	QString floorMsg = "** 层 ~ ** 层 (未登录)";									\
	App::pShowEdit[id / 10][id % 10]->setText(floorMsg)
#define SYS_SET_FLOORS(x, y)														\
	QString floorMsg = QString::number(x) + "层~" + QString::number(y) + "层";	\
	App::pShowEdit[id / 10][id % 10]->setText(floorMsg)


class SysController : public QObject {
	Q_OBJECT

public:
	static SysController& Instance(int argc, char *argv[])
	{
		static SysController instance(argc, argv);
		return instance;
	}

	SysController(const SysController&) = delete;
	SysController& operator=(const SysController&) = delete;
	~SysController();

signals:
	void result(QString);

private:
	SysController(int argc, char *argv[]);

	//void connects();

	//CTCPServer * tcpServer_ = nullptr;
//	dbManager* dbManager_ = nullptr;
	mysqldb* newdb_ = nullptr;
//	QThread tcpServerThread_;
//	DetectThread* dt;
	DetectAlgorithm* dt;
	uwc* uwc_;

	MainWindow * mainwindow_ = nullptr;

//	void changeCameraState(int row, int col)
//	{
//			switch (col) {
//			case 8:
//			{
//				auto camera = App::cameras[mainwindow_->cameraloginwindow->getID(row)];
//				(camera == nullptr || !camera->isOpened()) ? startCamera(row) : closeCamera(row);
//
//				break;
//			}
//
//			default: break;
//			}
//	}
//
//	// 在客户端启动摄像头
//	void startCamera(int row)
//	{
//		LOG(INFO) << "Start Camera @ " << row;
//
//		auto cameraIP = mainwindow_->cameraloginwindow->getCameraIP(row);
//		auto cameraUsername = mainwindow_->cameraloginwindow->getCameraUser(row);
//		auto cameraPass = mainwindow_->cameraloginwindow->getCameraPSW(row);
//
//		int id = mainwindow_->cameraloginwindow->getID(row);
//		int cameraLowFloor = mainwindow_->cameraloginwindow->getCameraLowFloor(row);
//		int cameraHighFloor = mainwindow_->cameraloginwindow->getCameraHighFloor(row);
//
//		auto camera = new HKWin64_Camera(cameraIP, cameraUsername, cameraPass, id);
//		App::cameras[id] = camera;
//
//		camera->hwnd_ = (HWND)App::labels[id / 10][id % 10]->winId();
//		camera->LowFloor_ = cameraLowFloor;
//		camera->HighFloor_ = cameraHighFloor;
//
//		if (!camera->isOpened()) {
//			QMessageBox::about(NULL, "警告", "客户端相机打开失败");
//		}
//		else {
//			camera->startRealPlay();
//			camera->enableDataStream();
//
//			SYS_SET_FLOORS(cameraLowFloor, cameraHighFloor);
//
//			// 启动对应的线程
////			auto dt = new DetectThread(id, this);
//			auto dt = new DetectAlgorithm(id);
//			App::threads_[id] = dt;
//			
//			connect(dt, &DetectAlgorithm::resultReady, this, [=](const QString &s) {
//				// TODO: 处理检测端的消息
//				emit result(s);
//			});
//
//			connect(dt, SIGNAL(detectResult(DETRESULT)), dt, SLOT(resultHandle(DETRESULT)));
//
//			//connect(dt, &DetectAlgorithm::finished, dt, &QObject::deleteLater);
//			//dt->start();
//			
//			mainwindow_->cameraloginwindow->ui.camera_table->item(row, 8)->setText("退出");
//		}
//	}
//	void closeCamera(int row)
//	{
//		auto id = mainwindow_->cameraloginwindow->getID(row);
//		auto& camera = App::cameras[id]; if (camera == nullptr) return;
//		auto& thread = App::threads[id]; delete thread;
//
//		SYS_CLR_FLOORS();
//
//		camera->close();
//
//		delete camera;
//		App::cameras[id] = nullptr;
//
////		ui.camera_table->item(row, 8)->setText("登录");
//		mainwindow_->cameraloginwindow->ui.camera_table->item(row, 8)->setText("登录");
//	}



};

#endif // !_SYSCONTROLLER_H