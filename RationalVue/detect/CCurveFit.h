///*****************************************************************
///  文件名称: 
///  简要描述:  
///  作者:  Dreamhigh
///  创建日期: 
///*****************************************************************
#pragma once
#include <QtCore/QCoreApplication> 
#include <QtCore/QObject> 
#include <QtCore/QThread> 
#include <QtCore/QDebug> 
#include <vector>
#include <DetectResults.h>
#include "CParams.h"
class CurveFit : public QObject{
	Q_OBJECT
public:
	CurveFit();
	~CurveFit();
	
	///*****************************************************************
	///   函数名： linearFit
	///   功能描述： 直线拟合 ———— 一元回归，拟合结果为：y=a0+a1*x;
	///             使用getFactor获取拟合的结果;
	///             使用getSlope获取斜率;
	///             getIntercept获取截距;
	///
	///   参数说明： x 观察值的x  
	///             y 观察值的y  
	///             isSaveFitYs 拟合后的数据是否保存，默认否
	///***************************************************************** 
	void linearFit(DetectResults &mDetectResult, bool isSaveFitYs = false);

	void linearFit(double* x, double* y, size_t length, bool isSaveFitYs = false);


	///*****************************************************************
	///   函数名： polyfit
	///   功能描述： 多项式拟合，拟合y=a0+a1*x+a2*x^2+……+apoly_n*x^poly_n
	///
	///   参数说明： x 观察值的x  
	///             y 观察值的y  
	///             poly_n 期望拟合的阶数，若poly_n=2，则y=a0+a1*x+a2*x^2  
	///             isSaveFitYs 拟合后的数据是否保存，默认是
	///*****************************************************************
	void polyfit(DetectResults &mDetectResult, int poly_n, bool isSaveFitYs = true);

	void polyfit(double* x, double* y, size_t length, int poly_n, bool isSaveFitYs = true);

	///*****************************************************************
	///   函数名： getFactor
	///   功能描述： 获取拟合的系数
	///   参数说明： factor 存放系数的数组 
	///*****************************************************************
	void getFactor(std::vector<double>& factor);

	///*****************************************************************
	///   函数名： getFitedYs
	///   功能描述： 获取拟合方程对应的y值，前提是拟合时设置isSaveFitYs为true
	///   参数说明： fitedYs 存放拟合方程对应的y值 
	///*****************************************************************
	void getFitedYs(std::vector<double>& fitedYs);

	///*****************************************************************
	///   函数名： getY
	///   功能描述： 根据x获取拟合方程的y值
	///   参数说明： x 观测值x
	///   返回值：  x对应下的y值
	///*****************************************************************
	double getY(const double x) const;

	///*****************************************************************
	///   函数名： getSlope
	///   功能描述： 获取斜率
	///   参数说明： void
	///   返回值：  斜率值
	///*****************************************************************
	double getSlope();

	///*****************************************************************
	///   函数名： getIntercept
	///   功能描述： 获取截距
	///   参数说明： void
	///   返回值：  截距值 
	///*****************************************************************
	double getIntercept();

	///*****************************************************************
	///   函数名： getSSE
	///   功能描述： 剩余平方和
	///   返回值：  剩余平方和
	///*****************************************************************
	double getSSE();

	///*****************************************************************
	///   函数名： getSSR
	///   功能描述： 回归平方和
	///   返回值：  剩余平方和
	///*****************************************************************
	double getSSR();

	///*****************************************************************
	///   函数名： getRMSE
	///   功能描述： 均方根误差
	///   返回值：  均方根误差
	///*****************************************************************
	double getRMSE();

	///*****************************************************************
	///   函数名： getR_square
	///   功能描述： 确定系数，系数是0~1之间的数，是数理上判定拟合优度的一个量
	///   返回值：  确定系数
	///*****************************************************************
	double getR_Square();

	///*****************************************************************
	///   函数名： getSeriesLength
	///   功能描述： 获取两个vector的安全size  
	///   参数说明： x 观测值x;y 观测值y
	///   返回值：  最小的一个长度
	///*****************************************************************
	size_t getSeriesLength(std::vector<double>& x, std::vector<double>& y);

	///*****************************************************************
	///   函数名： Mean
	///   功能描述： 计算均值
	///   参数说明： x 观测值x;y 观测值y
	///   返回值：  最小的一个长度
	///*****************************************************************
	double Mean(std::vector<double>& v);
	double Mean(double* v, size_t length);

	///*****************************************************************
	///   函数名： getFactorSize
	///   功能描述： 获取拟合方程系数的个数
	///   返回值：  拟合方程系数的个数
	///*****************************************************************
	size_t getFactorSize();

	///*****************************************************************
	///   函数名： getFactor
	///   功能描述： 根据阶次获取拟合方程的系数如getFactor(2),
	///             就是获取y=a0+a1*x+a2*x^2+……+apoly_n*x^poly_n中a2的值
	///   返回值：  拟合方程的系数
	///*****************************************************************  
	double getFactor(size_t i);

private:
	//计算误差
	void calcError(double* x, double* y, size_t length, double& r_ssr, double& r_sse, double& r_rmse, bool isSaveFitYs = true);
 
	void gauss_solve(int n,std::vector<double>& A,std::vector<double>& x,std::vector<double>& b);
 
	void gauss_solve(int n,double* A,double* x,double* b);

	std::vector<double> factor; ///<拟合后的方程系数  
	double ssr;                 ///<回归平方和  
	double sse;                 ///<(剩余平方和)  
	double rmse;                ///<RMSE均方根误差  
	std::vector<double> fitedYs;///<存放拟合后的y值，在拟合时可设置为不保存节省内存

public :
void CurveFit_start(CParams InputParam,std::vector<DetectResults> &mDetectObjects);

signals:
	void CurveFit_end_sig();

};