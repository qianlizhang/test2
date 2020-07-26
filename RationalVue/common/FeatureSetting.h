#pragma once

//显示类型
enum DisplayType {
	Dot,//点显示
	Solid,//实体显示
	Vector,//向量显示
	Wire，//线框显示
};
//误差质量
enum ToleranceQuality {
	Normal,//正常
};

//分解种类
enum DecomposeType {
	Compound,//混合物体
};

//滤波类型
enum FilterType {
	LowPass,
};
class CFeatureSetting {
	//元素显示设置
	DisplayType m_displayPointType;//点显示
	DisplayType m_displayPlaneType;//平面显示

	//实际元素更新设置
	bool m_bIsupdateCRDRecall;//是否更新实际元素的位置

	//误差选项
	bool m_bIsRecalculateFormError;//是否重新计算form误差
	bool m_bIsDisplayTRCBand;//显示公差带
	ToleranceQuality m_TRCQua;//误差质量

	//CAD选项
	bool m_bIsImpCADColor;//是否导入CAD颜色信息
	DecomposeType m_decomposeType;//分解的对象种类
	bool m_bIsFastPickFace;//是否快速选取面

	//构造选项
	bool m_bIsUsingPtmeas;//是否进行极值构造

	//曲线过滤设置
	bool m_bIsOpenCurveFilter;//是否开启曲线过滤
	FilterType m_fileType;//滤波类型
	double m_dStandardDev;//开发标准
	double m_dUPR;
	double m_dOutlierMaxValue;
};