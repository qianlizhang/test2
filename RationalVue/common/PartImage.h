#pragma once
#include<opencv2/opencv.hpp>
#include<qimage.h>

class CPartImage {
private:
	cv::Point2d m_pOriginPoint;//���������
	QImage m_partImage;//�ֲ�ͼƬ
	double m_dLenMagnification;//�Ŵ���
};
