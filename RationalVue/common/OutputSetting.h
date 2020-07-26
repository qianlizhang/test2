#pragma once
#include<qcolor.h>
enum CARTOrPOLOutput {
	BasedOnFeature,//根据元素本身
	BasedOnSysStatus,//根据系统状态
};

enum ExcelUsing {
	MicrosoftOffice,
	OpenOffice,
};
class COutputSetting {
public:
	//UI输出控制
	bool m_bIsActualCreation;//是否真实创建
	bool m_bTRCEva;//是否输出评价公差
	bool m_bRmvOptWhenFeaDel;//是否删除元素的同时删除元素的输出


	//输出excel控制
	ExcelUsing m_excelUsing;
	bool m_bOpenPDFAfterSave;//保存后是否自动打开

	//颜色设置
	QColor m_normalColor;
	QColor m_intolColor;
	QColor m_intol2Color;
	QColor m_outtolColor;
};