#pragma once
#include<QString>
class CConstructorElement { //构造元素属性
public:
	Angles* m_pAngles;//坐标系
	Misc* m_pMisc;//构造元素类型、 时间
	ConstInfo* m_pConstInfo;//参与构造的元素的信息
};
class Misc { //构造元素类型、 时间
public:
	QString m_strCrdType;//构造元素类型
	QString m_strAct;
	QString m_strD&T(N);//构造时间
	QString m_strD&T(A);
};

class Angles {//坐标系
public:
	QString m_strType;//2D or 3D
	QString m_strSen;//激活探头
	QString m_strCrd;//激活坐标系
};

class ConstInfo {
public:
	QString m_strConstMethod;//构造方法
	ConstFeatures* m_pConstFeatures;//参与构造的元素
};

class ConstFeatures { //参与构造的元素
	QString m_str1;
	QString m_str2;
};