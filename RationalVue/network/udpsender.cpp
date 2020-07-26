#include "udpsender.h"

#include <iomanip>
#include <QHostInfo>
#include "json.hpp"

using JSON = nlohmann::json;

#define BROADCAST_TIME_INTERVAL		(5)		// secs

void UDPSender::run()
{
	sender_ = new QUdpSocket(nullptr);


	for (;;) {
		LOG(INFO) << "UPD Sender start runing...";
		JSON data = { { "type", CAMERA_LOGIN }, { "text", std::to_string(3721) } };

		//static int __counter = 0;
		//LOG(INFO) << "Broadcast " << std::setw(4) << __counter++ << " package: " << data.dump();

		if (sender_->writeDatagram(data.dump().c_str(), data.dump().length(), QHostAddress::Broadcast, 41314) == -1) {
			LOG(ERROR) << "Boradcast data failed.";
		}

		QThread::sleep(BROADCAST_TIME_INTERVAL);
	}
}

// https://stackoverflow.com/questions/13835989/get-local-ip-address-in-qt
string UDPSender::getLocalIP()
{
	auto addresses = QHostInfo::fromName(QHostInfo::localHostName()).addresses();
	for (const QHostAddress& address : addresses) {
		if (address.protocol() == QAbstractSocket::IPv4Protocol && !address.isLoopback()) {
			return address.toString().toStdString();
		}
	}

	LOG(ERROR) << "Failed to get local ip address.";
	return {};
}