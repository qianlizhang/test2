#ifndef DETECTRESULTS_H_
#define DETECTRESULTS_H_

#include "opencv2/opencv.hpp"
#include <opencv/cv.h>

#include <QDataStream>

struct DetectResults
{
public:
	bool is_object = false;//�Ƿ�Ϊ�߿�����ı�־
	size_t skipped_frames;//��������Ƶ֡
	std::vector<cv::Point2d> trace;//�˶������˶��켣����
	std::vector<double> traceY;//��¼�˶������Y����
	std::vector<double> traceX;//��¼�˶������X����
	std::vector<double> frames_num;//��¼�˶������֡ʱ�䣨���֡������0��ʼ��
	//std::vector<double> frame_num;//��������֡��
	size_t DetectID;//�˶������ID��

	cv::Point2d first_trace;//����߿��������ʼλ��

	int num = 0;//ͳ�Ƹù켣�ѳ��ֶ��ٴ�

	int pre_num;//ͳ���ж��ٸ�����Ԥ��õ���

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