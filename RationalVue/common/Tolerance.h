#pragma once
#include<string>
using namespace std;

enum EvalMethod
{
	Avg, MAX, MIN 	//计算方法：平均、最大、最小
};

enum DistType	//距离方式
{
	PT2PT,	//点到点
	ToX,	//到X轴
	ToY,
	ToZ
};

enum DefineType {
	Nominal,	//名义
	Border		//边界
};

//公差
class CTolerance {
	string m_strLabel;//标签
	double m_dUpTol;//上公差
	double m_dLowTol;//下公差
	double m_dNomDist;//理论公差
	EvalMethod m_strEvalMethod;//计算方法
	DistType m_strDirection;//方向
	DefineType m_strDefineType;//
	string m_strEvalFeature1;//元素1
	string m_strEvalFeature2;//元素2
	double m_dActDist;//实际公差
	double m_dDeviation;//偏差值
};
