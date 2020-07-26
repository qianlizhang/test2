#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "CommonData.h"
using namespace std;
using namespace cv;
class CEdgeDetection : public CCommonData
{
public:
	CEdgeDetection();
	CEdgeDetection(CCommonData *commonData) :CCommonData(commonData) {};

	void detect() {
		Mat src = m_solution->m_vecPartImages;
		if (!src.data)
		{
			cout << "Can not load the image!" << endl;
		}
		Mat src1 = src;
		
		Mat edge, gray;


		//将原图像转为灰度
		cvtColor(src1, gray, COLOR_RGB2GRAY);
		

		//滤波(降噪)
		blur(gray, edge, Size(3, 3));

		//canny
		Mat out;
		Canny(edge, out, 150, 100);
		//imshow("1111", out);
		m_solution->m_vecPartImages = out;
		//imshow("222", m_solution->m_vecPartImages);
	}
};
