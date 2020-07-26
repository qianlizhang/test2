#pragma once
#include<opencv2/opencv.hpp>
#include<qimage.h>

class CPartImage {
private:
	cv::Point2d m_pOriginPoint;//基本坐标点
	QImage m_partImage;//局部图片
	double m_dLenMagnification;//放大倍数
};
