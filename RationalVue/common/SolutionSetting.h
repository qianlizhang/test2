#pragma once

enum ResetType {
	ResetCRDToMCS,//重置坐标系到MCS
	KeepAllCRD,//保留所有坐标系
};
class CSolutionSetting {
	int m_nRecentSolution;//最近解决方案数
	int m_nRecentImportCAD;//最近导入CAD数
	ResetType m_resetType;//设置重置类型
	bool m_bIsAutoSaveSolution;//设置是否自动保存解决方案
	int m_nAutoSaveInterval;//设置自动保存的间隔
	bool m_bSaveCADModel;//设置是否同时保存CAD模型
};