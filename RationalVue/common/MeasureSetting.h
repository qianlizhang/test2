#pragma once

enum FittingAlgorithm {
	LeastSquare,//最小二乘法
	FitActualSurface,//拟合实际曲面
};

enum SoundType {
	None,//探针测量没有声音
	Beep_2,//蜂鸣器
	Sound,//软件定义声音
	SelectWAVFile,//选择WAV声音
};

enum ScanDensity {
	Normal_2,
	Full,
	High,
	Fast,
	Custom,
};

enum ConfirmBtn {
	RightBtn,//鼠标右键
	MiddleBtn,//鼠标中间按键
	LeftBtn,//鼠标左键
};
class CMeasureSetting {
	//测头设置
	double m_dApproachDistance;//接近距离
	double m_dRetractDistance;//回退距离
	double m_dDepth;//深度
	double m_dClearDistance;//清除距离
	double m_dSearchDistance;//搜索距离
	bool m_bEnableClearMove;//清除距离开关
	bool m_bIsDropProbe;//是否切换探头，当使用影像或者激光探头时

	//拟合算法
	FittingAlgorithm m_circleFittingAlg;//圆的拟合算法
	FittingAlgorithm m_arcFittingAlg;//圆弧的拟合算法
	FittingAlgorithm m_planeFittingAlg;//平面拟合算法
	FittingAlgorithm m_cylinderFittingAlg;//圆柱拟合算法
	FittingAlgorithm m_surfaceFittingAlg;//曲面拟合算法
	int m_nMinIteration;//最小迭代次数

	//声音设置
	SoundType m_soundType;

	//警告和错误设置
	bool m_bIsTreatOutofTRC;//是否处理超差
	bool m_bIsShowNGOrOK;//显示与隐藏超差

	//曲线快速投影设置
	bool m_bEnableCurveFastPro;//是否权限快速投影
	//快速拟合设置
	int m_nBestfitSamplePoints;//拟合点数
	int m_nBestfitIteration;//拟合次数

	//CCD扫描设置
	ScanDensity m_scanDensity;//扫描点密度
	double m_dAutoMeasToolWidth;//自动测量工具宽度
	bool m_bEnableCentralMeas;//是否开启中心测量
	bool m_bEnableDefaultDirection;//是否开启默认方向
	ConfirmBtn m_confirmBtn;//确认按钮
	bool m_bIsUsingVectorSearch;//是否使用向量搜索

	//图形视图视角设置
	double m_dMaxAngle;//平行线的最大角度
	double m_dLineLength;//线段长度

	//手动机运行程序设置
	bool m_bIsGotoCmd;//Goto命令设置
	int m_nZoneXY;//XY的到位设置
	double m_dZoneZ;//Z值的区域
	int m_nDelay;//稳定时间

};