#ifndef DETECTRESULTS_H_
#define DETECTRESULTS_H_

#include "opencv2/opencv.hpp"
#include <opencv/cv.h>

#include <QDataStream>

struct DetectResults
{
public:
	bool is_object = false;//是否为高空抛物的标志
	size_t skipped_frames;//跳过的视频帧
	std::vector<cv::Point2d> trace;//运动对象运动轨迹坐标
	std::vector<double> traceY;//记录运动对象的Y坐标
	std::vector<double> traceX;//记录运动对象的X坐标
	std::vector<double> frames_num;//记录运动对象的帧时间（相对帧数，从0开始）
	//std::vector<double> frame_num;//与程序的总帧数
	size_t DetectID;//运动对象的ID号

	cv::Point2d first_trace;//保存高空抛物的起始位置

	int num = 0;//统计该轨迹已出现多少次

	int pre_num;//统计有多少个点是预测得到的

	int frame_height = 0;
	int frame_width = 0;
private:

};

inline QDataStream & operator<< (QDataStream & out, const DetectResults & res)
{
	out << res.is_object;
	out << res.skipped_frames;

	int sizeTrace = res.trace.size();
	out << sizeTrace;
	for (int i = 0; i < sizeTrace; ++i) {
		const cv::Point2d & p2d = res.trace[i];
		out << p2d.x
			<< p2d.y;
	}

	int sizeTraceY = res.traceY.size();
	out << sizeTraceY;
	for (int i = 0; i < sizeTraceY; ++i) {
		out << res.traceY[i];
	}

	int sizeTraceX = res.traceX.size();
	out << sizeTraceX;
	for (int i = 0; i < sizeTraceX; ++i) {
		out << res.traceX[i];
	}

	int sizeFramesNum = res.frames_num.size();
	out << sizeFramesNum;
	for (int i = 0; i < sizeFramesNum; ++i) {
		out << res.frames_num[i];
	}

	out << res.DetectID;

	out << res.first_trace.x
		<< res.first_trace.y;

	out << res.num;

	return out;

}

inline QDataStream & operator>> (QDataStream & in, DetectResults & res)
{
	in >> res.is_object;
	in >> res.skipped_frames;

	int sizeTrace;
	in >> sizeTrace;
	res.trace.resize(sizeTrace);
	for (int i = 0; i < sizeTrace; ++i) {
		in >> res.trace[i].x;
		in >> res.trace[i].y;
	}

	int sizeTraceY;
	in >> sizeTraceY;
	res.traceY.resize(sizeTraceY);
	for (int i = 0; i < sizeTraceY; ++i) {
		in >> res.traceY[i];
	}

	int sizeTraceX;
	in >> sizeTraceX;
	res.traceX.resize(sizeTraceX);
	for (int i = 0; i < sizeTraceX; ++i) {
		in >> res.traceX[i];
	}

	int sizeFramesNum;
	in >> sizeFramesNum;
	res.frames_num.resize(sizeFramesNum);
	for (int i = 0; i < sizeFramesNum; ++i) {
		in >> res.frames_num[i];
	}

	in >> res.DetectID;

	in >> res.first_trace.x
		>> res.first_trace.y;

	in >> res.num;

	return in;

}

#endif	// DETECTRESULTS_H_