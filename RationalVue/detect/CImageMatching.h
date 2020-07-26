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
//	brief	: ͼ��ƥ���㷨����
//	author	: 
//***********************************************************************

class CImageMatching : public QObject {
	Q_OBJECT

protected:

	// ���ֳ�ʼ������
	CParams parameter;

public:


	// ���ò���
	virtual void SetParameter(CParams InputParam);

	// �������ƶȣ���������1����������2��������,����Ƿ�Ϊͬһ����
	//  1:1
	virtual void CalSimilarity(CFeature &feature1, CFeature &feature2, float *result, bool &istarget)
	{}


	// �������ƶȣ���������1����������2��������,����Ƿ�Ϊͬһ����
	//  n :1
	virtual void CalSimilarity(std::vector<CFeature> &feature1, CFeature &feature2, std::vector<float> *result, std::vector< bool> &istarget)
	{}


	// ������룬��������1����������2��������
	virtual void CalDistance(CFeature &feature1, CFeature &feature2, float * result, bool &istarget)
	{}


	// ����ƥ��

	//�������1 ��������Լ�
	virtual void FeatureMatching(CObjectRect &var)
	{}

signals:
	void Matching_end_Sig();
};

