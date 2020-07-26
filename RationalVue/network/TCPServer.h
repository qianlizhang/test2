#pragma once
#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include <QObject>
#include <QHBoxLayout>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QDir>
#include "common.h"
#include "route.h"
#include "json.hpp"
#include <QByteArray>
#include <QDateTime>
#include <CNetTransmission.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <nvr.h>
//#include "dbManager.h"
#include "newdb.h"
#include <QThread>
#include <WarningVideoDialog.h>
#include <exception>
//#include <thread>

using JSON = nlohmann::json;

/**
 * TCP Server - in Singleton mode
 */
class CTCPServer : public QObject {
	Q_OBJECT

public:
	static CTCPServer* Instance(unsigned short port = TCP_SERVER_DEFAULT_PROT)
	{
		static CTCPServer instance(port);
		return &instance;
	}
	~CTCPServer();

	QThread tcpServerThread_;

	void run();

	int get_floor(int down, int top, int height, int pos);

	// Stop this server
	void stop();

	// 获取所有连接的客户端
	std::vector<QTcpSocket *> clients() const { return clients_; }

	// 获取server端口
	uint16_t port() const { return port_; }
//	bool isDetectData = false;

	//将时间转化为NET_DVR_TIME类型
	NET_DVR_TIME covertTime(QDateTime timeStamp);

signals:
	// 收到TCP Client的数据消息
	void received(QTcpSocket*, JSON);
	void result(QString);

	// TCP Client断开连接的消息
	void disconnected(QTcpSocket*);
	void btnstate(QPushButton*);//, bool

public slots:
	void send(QTcpSocket *socket, JSON data);
	void send(QTcpSocket *socket, string data_str);
	void btnChange(QPushButton* btn);//, bool is_closed

private slots:
	// Receive new connections.
	void handleConnection();


	// Handle given client: parse input message
	void handleClient(QTcpSocket *);


	// Remove client.
	void removeClient(QTcpSocket *);

private:
	CTCPServer(uint16_t port);

	uint16_t port_ = TCP_SERVER_DEFAULT_PROT;

	QTcpServer *server_ = nullptr;
	vector<QTcpSocket *> clients_;
	vector<WarningVideoDialog *> dialogs_;
};


class VideoShow :public QWidget {
	Q_OBJECT
public:

	VideoShow(QWidget * parent = nullptr)
		:QWidget(parent)
	{
		//setFixedSize(400, 300);
		QHBoxLayout * layout = new QHBoxLayout();

		label_ = new QLabel();
		label_->setFixedSize(400, 300);
		layout->addWidget(label_);

		setLayout(layout);
	}

	HWND getHWND() const { return (HWND)(label_->winId()); };

private:
	QLabel * label_;
};

#endif	// TCPSERVER_H_