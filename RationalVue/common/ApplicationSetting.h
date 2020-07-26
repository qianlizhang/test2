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
	CGenaralSetting m_genaralSetting;//常规设置
	CUISetting m_uiSetting;//界面设置
	CFeatureSetting m_featureSetting;//元素设置
	CMeasureSetting m_measureSetting;//测量设置
	COutputSetting m_outputSetting;//输出设置
	CSolutionSetting m_solutionSetting;//解决方案设置
	CDMISSetting m_DMISSetting;//DMIS设置
	CPrefixSetting m_prefixSetting;//前缀设置
	CToleranceSetting m_toleranceSetting;//公差设置
	std::string m_strAdminPassword;

};