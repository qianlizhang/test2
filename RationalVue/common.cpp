#include "common.h"


std::vector<std::vector<QLabel *>> App::labels;
std::map<uint16_t, Camera *> App::cameras;
std::map<uint16_t, DetectThread *> App::threads;
std::map<uint16_t, DetectAlgorithm *> App::threads_;
QVector<QVector<QLabel*>> App::pShowEdit;

std::map<long, CBlockingQueue<cv::Mat>*> App::cameraImages;
std::map<int, long> App::id2handle;

cv::VideoCapture App::cap;

QString App::CurrentUser;

std::map<int, vector<windows>> CommonData::Windows;

