#pragma once
#include<string>
#include"GeneralSetting.h"
#include "UISetting.h"
#include "FeatureSetting.h"
#include "MeasureSetting.h"
#include "OutputSetting.h"
#include "SolutionSetting.h"
#include"DMISSetting.h"
#include "PrefixSetting.h"
#include "ToleranceSetting.h"
class CApplicationSetting {
public:
	CGenaralSetting m_genaralSetting;//��������
	CUISetting m_uiSetting;//��������
	CFeatureSetting m_featureSetting;//Ԫ������
	CMeasureSetting m_measureSetting;//��������
	COutputSetting m_outputSetting;//�������
	CSolutionSetting m_solutionSetting;//�����������
	CDMISSetting m_DMISSetting;//DMIS����
	CPrefixSetting m_prefixSetting;//ǰ׺����
	CToleranceSetting m_toleranceSetting;//��������
	std::string m_strAdminPassword;

};