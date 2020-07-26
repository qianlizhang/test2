#pragma once
#include"Solution.h"
#include"ApplicationSetting.h"
#include <random>
#include<memory.h>
class CCommonData {
public:
	shared_ptr<CSolution> m_solution = make_shared<CSolution>();
	shared_ptr<CApplicationSetting> m_applicatoinSetting = make_shared<CApplicationSetting>();

	CCommonData() {
		loadSolution("undefined", "qqqq", "../");
	}

	CCommonData(CCommonData *commondata) {
		this->m_solution = commondata->m_solution;
		this->m_applicatoinSetting = commondata->m_applicatoinSetting;
	}
	void loadSolution(string solutionName, string designerName, string filePath) {
		srand((unsigned int)time(NULL));
		m_solution->m_nSolutionId = rand();
		m_solution->m_strSolutionName = solutionName;
		m_solution->m_strDesignerName = designerName;
		m_solution->m_strFilePath = filePath;
	}
};