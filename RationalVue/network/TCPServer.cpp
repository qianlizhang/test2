#include "TCPServer.h"

#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog\logging.h>
#include <QMessageBox>
#include <QTimer>
#include <iostream>
#include <HKCamera.h>
CTCPServer::CTCPServer(uint16_t port)
	: port_(port)
{
//	LOG(INFO) << "Init with port: " + std::to_string(port_);

	server_ = new QTcpServer();
	server_->listen(QHostAddress::AnyIPv4, port_);
}

CTCPServer::~CTCPServer()
{
	if (server_ != nullptr) {
		delete server_;
		server_ = nullptr;
	}
	if (!dialogs_.empty()) {
		for (auto dialog : dialogs_) {
			delete dialog;
		}
	}
}

void CTCPServer::run()
{
	connect(server_, SIGNAL(newConnection()), this, SLOT(handleConnection()));
}

// ����TCP����:handleClient
void CTCPServer::handleConnection()
{
	auto client = server_->nextPendingConnection();

	connect(client, &QTcpSocket::readyRead, [client, this]() {
		handleClient(client);
	});

	connect(client, &QTcpSocket::disconnected, [client, this]() {
		removeClient(client);
	});

	clients_.push_back(client);

	LOG(INFO) << "New connection: " << client->peerAddress().toString().toStdString() << ":" << client->peerPort();
}

void CTCPServer::removeClient(QTcpSocket * client)
{
	// TODO: remove code.
	LOG(INFO) << "disconnected:" << client->peerAddress().toString().toStdString() << ":" << client->peerPort();
	emit disconnected(client);
}

void CTCPServer::handleClient(QTcpSocket *client)
{
	QByteArray block;
	block = client->readAll(); //ע��readAll()����ֻ�ܶ�һ��
//	auto json_string = QString(client->readAll()).toStdString(); 
	//�����ֽ�����С�ж��������ݻ���json�ı�����
	if (block.size() > 100 ) {
		//����һ��ʱ���
		QDateTime timeStamp = QDateTime::currentDateTime();
		CommonData Data; //ȫ�ֱ���

		/**************����������*****************/
		QDataStream in(block);
		in.setVersion(QDataStream::Qt_4_0);
		uint msgLen;
		qint8 respType;
		int frameHeight;  //��ֱ���������صĸ���
		int cameraID;
		CNetTransmission netTransmission;
		int traceY;  //��һ���켣���Y���꣬����¥�����
		in >> msgLen >> respType >> netTransmission;
	//	frameHeight = netTransmission.height;
		cameraID = netTransmission.camera_ID;
		int tracenum = netTransmission.mDetectObjects.size();//�켣��
		//dbManager* dbmanager = dbManager::Instance();
		newdb* newdb_ = newdb::Instance();
		for (int i = 0; i < tracenum; i++)
		{
			int pointnum = netTransmission.mDetectObjects[i].trace.size();
			traceY = netTransmission.mDetectObjects[i].first_trace.y;
			if (traceY <= 130 && fabs(netTransmission.mDetectObjects[i].trace[1].y- netTransmission.mDetectObjects[i].trace[1].y)>30)
				continue;
			QString date_str = timeStamp.toString("yyyyMMdd");
			QString time_str = timeStamp.toString("hhmmss");
			QString saveFilename = QString::number(cameraID, 10) + "_" + date_str + "_" + time_str + "_" + QString::number(i, 10) + ".mp4";
			auto chs = Data.ID2Channel[cameraID];

			//TODO: set playbtn enabled after downloading video
			WarningVideoDialog *videodialog;
			dialogs_.push_back(videodialog);
			videodialog->playBtn->setEnabled(false);
			//auto playBtn = videodialog->playBtn;
			//connect(this, SIGNAL(btnstate(QPushButton*)), this, SLOT(btnChange(QPushButton*)));
			QTimer::singleShot(130000, this, [=]() {

				NET_DVR_TIME time1 = covertTime(timeStamp.addSecs(-20));
				NET_DVR_TIME time2 = covertTime(timeStamp.addSecs(10));

				string filename = "save/VideoSave/" + saveFilename.toStdString();
				NVR nvr("192.168.10.60", "admin", "Hik123456");
				nvr.login(); 

				nvr.getFileByTime(chs, time1, time2, filename);
				nvr.exit();
				if(videodialog) videodialog->playBtn->setEnabled(true);
				//emit btnstate(playBtn);
			});

			/******************************/
			std::vector<cv::Point> trace1;
			//traceY = netTransmission.mDetectObjects[i].trace[0].y;
			for (int j = 0; j < pointnum; j++) { //��floatת��Ϊint��
				cv::Point p = netTransmission.mDetectObjects[i].trace[j];
				trace1.push_back(p);
			}
			//���ƹ켣���洢��Ƭ
			QString bgpicturePath = QString::number(cameraID, 10) + ".BMP";
			QString pictureSavePath = "./save/ImgSave/" + QString::number(cameraID, 10) + "_" + date_str + "_" + time_str + "_" + QString::number(i,10) + ".BMP";
			cv::Mat background = cv::imread(bgpicturePath.toStdString());
			cv::polylines(background, trace1, false, cv::Scalar(0, 0, 255), 2, cv::LINE_8);
	//		cv::imshow("Detected", background);
			cv::imwrite(pictureSavePath.toStdString(), background);
	//		cv::waitKey(3000);
			frameHeight = background.rows;

			//��������¥����
			int ResultFloor;
			int LowestFloor = App::clients[cameraID]->camera_->LowFloor_;
			int HighestFloor = App::clients[cameraID]->camera_->HighFloor_;
			ResultFloor = get_floor(LowestFloor, HighestFloor, frameHeight, traceY);


			//������м�¥��ĸ߶�
	/*		float floor_Height = ((LowestFloor + HighestFloor - 1) / 2) * Data.perFloor;
			//ת������
			float Tran_ratio = Data.distance / sqrt(floor_Height * floor_Height + Data.distance * Data.distance);
			//����ת���������
			float Tran_frameHeight = frameHeight * Tran_ratio;
			//ÿ��¥��ռ������
			float pFloorSize = Tran_frameHeight / (HighestFloor - LowestFloor + 1);
			ResultFloor = LowestFloor + (Tran_frameHeight - traceY * Tran_ratio) / pFloorSize;
	*/

			//���ļ�����·��������ʱ�䡢����š�����¥��������ݿ�
			QString workpath = QDir::currentPath();
			QString absolutepath = workpath + "/save/VideoSave/" + saveFilename;
			QString imgpath = workpath+"/save/ImgSave/"+ QString::number(cameraID, 10) + "_" + date_str + "_" + time_str + "_" + QString::number(i, 10) + ".BMP";
			QString datetime = timeStamp.toString("yyyy-MM-dd hh:mm:ss");
		//	newdb_->InsertVideoSaveTable(saveFilename, absolutepath, datetime, cameraID, ResultFloor);
			newdb_->InsertVideoSaveTable(saveFilename, absolutepath, imgpath, datetime, cameraID, ResultFloor);

			int buildingnum;
			int unitnum;
			newdb_->GetBuildinginfo(cameraID, buildingnum, unitnum);

	//		QString showstr = "������ֲ���:" + QString::number(ResultFloor, 10);
			QString showstr = "ʱ��: " + timeStamp.toString("yyyy-MM-dd hh:mm:ss")
				+ "\n����ţ� " + QString::number(cameraID, 10)
				+ "\n¥���ţ� " + QString::number(buildingnum, 10)
				+ "\n��Ԫ�ţ� " + QString::number(unitnum, 10)
				+ "\n����¥����: " + QString::number(ResultFloor, 10);

			emit result(showstr);

			
			videodialog->Init(timeStamp, QString::number(buildingnum, 10), QString::number(unitnum, 10), QString::number(ResultFloor, 10), absolutepath,pictureSavePath);
		//	videodialog.Init(timeStamp, QString::number(buildingnum, 10), QString::number(unitnum, 10), QString::number(ResultFloor, 10), pictureSavePath);
			videodialog->show();
			//videodialog.exec();

	//		QMessageBox::about(nullptr, "����", str);
		}
		
	}
	else {
		auto json_string = QString(block).toStdString();

		LOG(INFO) << "Message from: " + client->peerAddress().toString().toStdString() << ":" << client->peerPort() << ":" << json_string;

		JSON data;
		STR2JSON(json_string, data);
		emit received(client, data);
	} //�Ǽ������
}


void CTCPServer::send(QTcpSocket *socket, JSON data)
{
	send(socket, data.dump());
}

void CTCPServer::send(QTcpSocket *socket, string data_str)
{
	LOG(INFO) << "Send: " << data_str;

	socket->write(data_str.c_str(), data_str.length());
	socket->flush();
}

void CTCPServer::stop()
{
	// disconnect signals
	disconnect(server_);

	// close server socket
	server_->close();
	delete server_;
	server_ = nullptr;

	//	LOG(INFO) << "Stopped.";
}

	//��ʱ��ת��ΪNET_DVR_TIME����
NET_DVR_TIME CTCPServer::covertTime(QDateTime timeStamp)
{
	string dateTime_str = timeStamp.toString("yyyy-MM-dd hh:mm:ss").toStdString();
	int index = dateTime_str.find(" ");
	string YMD = dateTime_str.substr(0, index);
	string HMS = dateTime_str.substr(index + 1);
	int Y = std::stoi(YMD.substr(0, 4));
	int M = std::stoi(YMD.substr(5, 7));
	int D = std::stoi(YMD.substr(8));

	int h = std::stoi(HMS.substr(0, 2));
	int m = std::stoi(HMS.substr(3, 5));
	int s = std::stoi(HMS.substr(6));

	NET_DVR_TIME time;
	time.dwYear = Y;
	time.dwMonth = M;
	time.dwDay = D;
	time.dwHour = h;
	time.dwMinute = m;
	time.dwSecond = s;


	return time;
}

int CTCPServer::get_floor(int down, int top, int height, int pos)
{
	vector<double>floors;
	floors.push_back(1);
	floors.push_back(0.99);
	floors.push_back(0.98);
	floors.push_back(0.97);
	floors.push_back(0.96);
	floors.push_back(0.95);
	floors.push_back(0.94);
	floors.push_back(0.93);
	floors.push_back(0.92);
	floors.push_back(0.91);
	int n = top - down + 1;
	double sum = 0;
	reverse(floors.begin(), floors.begin() + n);
	for (int i = 0; i < n; i++)
	{
		sum += floors[i];
		if (i != 0)
		{
			floors[i] += floors[i - 1];
		}
	}
	for (int i = 0; i < n; i++)
	{
		floors[i] = (floors[i] / sum)*height;
	}
	int res = top;
	for (int i = 0; i < n; i++)
	{
		if (pos <= floors[i])
		{
			return res;
		}
		res--;
	}
	return res;
}

void CTCPServer::btnChange(QPushButton* btn)
{
	btn->setEnabled(true);
}