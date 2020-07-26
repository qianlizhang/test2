#pragma once
#include<QString>
class TheryElement {
public:
	double m_fD;
	QString m_strType;//元素种类
	QString m_strSen;//激活探头
	QString m_strCrd;//激活坐标系
	double m_fForm;
	Misc* m_pMisc;//构造元素类型、 时间
	bool m_bLastPoints;
};
class Misc { //构造元素类型、 时间
public:
	QString m_strCrdType;//构造元素类型
	QString m_strAct;
	QString m_strD&T(N);//构造时间
	QString m_strD&T(A);
};