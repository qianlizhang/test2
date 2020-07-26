#include "HKCamera.h"

int main()
{
	std::vector<std::shared_ptr<HKCamera>> cameras;

	//cameras.push_back(std::make_shared<HKCamera>("192.168.10.11", "admin", "Hik123456", 1));
	cameras.push_back(std::make_shared<HKCamera>("192.168.10.12", "admin", "Hik123456", 2));
	//cameras.push_back(std::make_shared<RTSPCamera>("192.168.10.13", "admin", "Hik123456", 3));
	//cameras.push_back(std::make_shared<RTSPCamera>("192.168.10.14", "admin", "Hik123456", 4));
	for (auto& camera : cameras) {

		camera->startRealPlay();
		camera->enableDataStream();
	}

	for (;;) {
		for (auto& camera : cameras) {
			cv::Mat frame;
			if (camera->get(frame, Camera::BGR)) {
				cv::imshow("camera_" + std::to_string(camera->id()), frame);
			}
		}

		cv::waitKey(5);
	}

	return 0;
}