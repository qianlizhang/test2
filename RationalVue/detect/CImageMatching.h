#pragma once
#include <QtCore/QCoreApplication> 
#include <QtCore/QObject> 
#include <QtCore/QThread> 
#include <QtCore/QDebug> 

#include "CParams.h"
#include "CFeature.h"
#include "CObjectRect.h"

//***********************************************************************
//	name	: CImageMatching
//	brief	: 图像匹配算法基类
//	author	: 
//***********************************************************************

class CImageMatching : public QObject {
	Q_OBJECT

protected:

	// 各种初始化参数
	CParams parameter;

public:


	// 设置参数
	virtual void SetParameter(CParams InputParam);

	// 计算相似度，输入特征1，输入特征2，输出结果,输出是否为同一对象
	//  1:1
	virtual void CalSimilarity(CFeature &feature1, CFeature &feature2, float *result, bool &istarget)
	{}


	// 计算相似度，输入特征1，输入特征2，输出结果,输出是否为同一对象
	//  n :1
	virtual void CalSimilarity(std::vector<CFeature> &feature1, CFeature &feature2, std::vector<float> *result, std::vector< bool> &istarget)
	{}


	// 计算距离，输入特征1，输入特征2，输出结果
	virtual void CalDistance(CFeature &feature1, CFeature &feature2, float * result, bool &istarget)
	{}


	// 特征匹配

	//输入点阵1 ，输出是自己
	virtual void FeatureMatching(CObjectRect &var)
	{}

signals:
	void Matching_end_Sig();
};

