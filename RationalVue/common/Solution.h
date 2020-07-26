#pragma once
#include<string>
#include<time.h>
#include<QImage>
#include"PartImage.h"
#include"Element.h"
#include "DesignerParameter.h"
using namespace std;

class CSolution {
public:
	string m_strSolutionName;//解决方案名字
	int m_nSolutionId;//解决方案id
	string m_strDesignerName;//解决方案设计者名字
	time_t m_tDesignTime;//设计时间
	string m_strLockPassward;//锁定解决方案的密码
	string m_strFilePath;//解决方案文件地址
	bool m_bReadOnly;//只读
	QImage m_componentImage;//部件图像
	double m_dLenMagnification;//放大倍数obj.push_back(i);
	cv::Mat m_vecPartImages;//局部图像
	vector<CElement> m_vecElements;//各个元素
	CDesignParameter m_designParameter;//设计参数

	CSolution() {
		CElement Element1;
		m_vecElements.push_back(Element1);
	}
};
