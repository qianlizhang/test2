#pragma once

enum ResetType {
	ResetCRDToMCS,//��������ϵ��MCS
	KeepAllCRD,//������������ϵ
};
class CSolutionSetting {
	int m_nRecentSolution;//������������
	int m_nRecentImportCAD;//�������CAD��
	ResetType m_resetType;//������������
	bool m_bIsAutoSaveSolution;//�����Ƿ��Զ�����������
	int m_nAutoSaveInterval;//�����Զ�����ļ��
	bool m_bSaveCADModel;//�����Ƿ�ͬʱ����CADģ��
};