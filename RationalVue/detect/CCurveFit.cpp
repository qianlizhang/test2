///*****************************************************************
///  文件名称: 
///  简要描述:  
///  作者:  Dreamhigh
///  创建日期: 
///*****************************************************************

#include "CCurveFit.h"
#include"qtextstream.h"
#include"Qtextstream"
#include "QFile"

# pragma execution_character_set("utf-8")


double temp = 0;
CurveFit::CurveFit()
{
	ssr = 0;
	sse = 0;
	rmse = 0;
	factor.resize(2, 0);
}

CurveFit::~CurveFit()
{
}

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

void CurveFit::linearFit(DetectResults &mDetectResult, bool isSaveFitYs)
{
	linearFit(&mDetectResult.frames_num[0], &mDetectResult.traceY[0], getSeriesLength(mDetectResult.frames_num, mDetectResult.traceY), isSaveFitYs);
	//return linearFit(&x[0], &y[0], getSeriesLength(x, y), isSaveFitYs);
}
///*****************************************************************
///   函数名： linearFit
///   功能描述： 直线拟合 ———— 一元回归，拟合结果为：y=a0+a1*x;
///             使用getFactor获取拟合的结果;
///             使用getSlope获取斜率;
///             getIntercept获取截距;
///
///   参数说明： x 观察值的x  
///             y 观察值的y  
///             length 观测值得长度
///             isSaveFitYs 拟合后的数据是否保存，默认否
///***************************************************************** 
void CurveFit::linearFit(double* x, double* y, size_t length, bool isSaveFitYs)
{
	factor.resize(2, 0);
	double t1 = 0, t2 = 0, t3 = 0, t4 = 0;
	for (int i = 0; i < length; ++i)
	{
		t1 += x[i] * x[i];
		t2 += x[i];
		t3 += x[i] * y[i];
		t4 += y[i];
	}
	factor[1] = (t3*length - t2 * t4) / (t1*length - t2 * t2);
	factor[0] = (t1*t4 - t2 * t3) / (t1*length - t2 * t2);
	//////////////////////////////////////////////////////////////////////////
	//计算误差
	calcError(x, y, length, this->ssr, this->sse, this->rmse, isSaveFitYs);
}

void CurveFit::polyfit(DetectResults &mDetectResult, int poly_n, bool isSaveFitYs)
{
	//polyfit(&mDetectResult.traceX[0], &mDetectResult.traceY[0], getSeriesLength(mDetectResult.traceX, mDetectResult.traceY), 1, false);
	//temp = getR_Square();
	polyfit(&mDetectResult.frames_num[0], &mDetectResult.traceY[0], getSeriesLength(mDetectResult.frames_num, mDetectResult.traceY), poly_n, isSaveFitYs);
}

void CurveFit::polyfit(double* x, double* y, size_t length, int poly_n, bool isSaveFitYs)
{
	factor.resize(poly_n + 1, 0);
	int i, j;
	//double *tempx,*tempy,*sumxx,*sumxy,*ata;
	std::vector<double> tempx(length, 1.0);
	std::vector<double> tempy(y, y + length);
	std::vector<double> sumxx(poly_n * 2 + 1);
	std::vector<double> ata((poly_n + 1)*(poly_n + 1));
	std::vector<double> sumxy(poly_n + 1);
	for (i = 0; i < 2 * poly_n + 1; i++) {
		for (sumxx[i] = 0, j = 0; j < length; j++)
		{
			sumxx[i] += tempx[j];
			tempx[j] *= x[j];
		}
	}
	for (i = 0; i < poly_n + 1; i++) {
		for (sumxy[i] = 0, j = 0; j < length; j++)
		{
			sumxy[i] += tempy[j];
			tempy[j] *= x[j];
		}
	}
	for (i = 0; i < poly_n + 1; i++)
		for (j = 0; j < poly_n + 1; j++)
			ata[i*(poly_n + 1) + j] = sumxx[i + j];
	gauss_solve(poly_n + 1, ata, factor, sumxy);
	//计算拟合后的数据并计算误差
	fitedYs.reserve(length);
	calcError(&x[0], &y[0], length, this->ssr, this->sse, this->rmse, isSaveFitYs);

}

void CurveFit::getFactor(std::vector<double>& factor)
{
	factor = this->factor;
}

void CurveFit::getFitedYs(std::vector<double>& fitedYs)
{
	fitedYs = this->fitedYs;
}

double CurveFit::getY(double x) const
{
	double ans(0);
	for (size_t i = 0; i < factor.size(); ++i)
	{
		ans += factor[i] * pow((double)x, (int)i);
	}
	return ans;
}

double CurveFit::getSlope()
{
	return factor[1];
}

double CurveFit::getIntercept()
{
	return factor[0];
}

double CurveFit::getSSE()
{
	return sse;
}

double CurveFit::getSSR()
{
	return ssr;
}

double CurveFit::getRMSE()
{
	return rmse;
}

double CurveFit::getR_Square()
{
	return 1 - (sse / (ssr + sse));
}

size_t CurveFit::getSeriesLength(std::vector<double>& x, std::vector<double>& y)
{
	return (x.size() > y.size() ? y.size() : x.size());
}

double CurveFit::Mean(std::vector<double>& v)
{
	return Mean(&v[0], v.size());
}

double CurveFit::Mean(double* v, size_t length)
{
	double total(0);
	for (size_t i = 0; i < length; ++i)
	{
		total += v[i];
	}
	return (total / length);
}

size_t CurveFit::getFactorSize()
{
	return factor.size();
}

double CurveFit::getFactor(size_t i)
{
	return factor.at(i);
}


void CurveFit::calcError(double* x, double* y, size_t length, double& r_ssr, double& r_sse, double& r_rmse, bool isSaveFitYs)
{
	double mean_y = Mean(y, length);
	double yi(0);
	fitedYs.reserve(length);
	for (int i = 0; i < length; ++i)
	{
		yi = getY(x[i]);
		r_ssr += ((yi - mean_y)*(yi - mean_y));//计算回归平方和
		r_sse += ((yi - y[i])*(yi - y[i]));//残差平方和
		if (isSaveFitYs)
		{
			fitedYs.push_back(double(yi));
		}
	}
	r_rmse = sqrt(r_sse / (double(length)));
}

void CurveFit::gauss_solve(int n, std::vector<double>& A, std::vector<double>& x, std::vector<double>& b)
{
	gauss_solve(n, &A[0], &x[0], &b[0]);
}

void CurveFit::gauss_solve(int n, double* A, double* x, double* b)
{
	int i, j, k, r;
	double max;
	for (k = 0; k < n - 1; k++)
	{
		max = fabs(A[k*n + k]); /*find maxmum*/
		r = k;
		for (i = k + 1; i < n - 1; i++) {
			if (max < fabs(A[i*n + i]))
			{
				max = fabs(A[i*n + i]);
				r = i;
			}
		}
		if (r != k) {
			for (i = 0; i < n; i++)         /*change array:A[k]&A[r] */
			{
				max = A[k*n + i];
				A[k*n + i] = A[r*n + i];
				A[r*n + i] = max;
			}
		}
		max = b[k];                    /*change array:b[k]&b[r]     */
		b[k] = b[r];
		b[r] = max;
		for (i = k + 1; i < n; i++)
		{
			for (j = k + 1; j < n; j++)
				A[i*n + j] -= A[i*n + k] * A[k*n + j] / A[k*n + k];
			b[i] -= A[i*n + k] * b[k] / A[k*n + k];
		}
	}

	for (i = n - 1; i >= 0; x[i] /= A[i*n + i], i--)
		for (j = i + 1, x[i] = b[i]; j < n; j++)
			x[i] -= A[i*n + j] * x[j];
}

void Search_max_and_min(float* a, int N) {
	int max, min, tmax, tmin;
	if (N % 2 == 0) {
		max = (a[0] > a[1]) ? a[0] : a[1];
		min = (a[0] < a[1]) ? a[0] : a[1];

	}
	else
		max = min = a[0];
	for (int i = 1; i < N / 2; i++) {
		if (a[2 * i - 1] > a[2 * i]) {
			tmax = a[2 * i - 1];
			tmin = a[2 * i];

		}
		else {
			tmax = a[2 * i];
			tmin = a[2 * i - 1];

		}
		if (tmax > max)
			max = tmax;
		if (tmin < min)
			min = tmin;


	}
}

int getMaxOrMin(std::vector<double> arr, int count, bool isMax) {
	float temp = arr[0];
	int index = 0;
	for (int i = 1; i < count; i++) {
		if (isMax) {
			if (temp < arr[i]) {
				temp = arr[i];
				index = i;
			}
		}
		else {
			if (temp > arr[i]) {
				temp = arr[i];
				index = i;
			}
		}
	}
	return index;
}
//计算锐角的个数
int get_num(DetectResults mDetectObject)
{
	int res = 0;
	auto P1 = mDetectObject.trace[0];
	auto P2 = mDetectObject.trace[1];
	auto P3 = mDetectObject.trace[2];
	int index = 3;
	int n = mDetectObject.trace.size();
	while (P3 != mDetectObject.trace[n - 1])
	{
		if ((P3.x - P2.x)*(P1.x - P2.x) + (P3.y - P2.y)*(P1.y - P2.y) > 0)
		{
			res++;
		}
		P1 = P2;
		P2 = P3;
		if (index == n)
			break;
		P3 = mDetectObject.trace[index];
		index++;
	}
	return res;
}
void CurveFit::CurveFit_start(CParams InputParam, std::vector<DetectResults> &mDetectObjects)
{
	//QMessageBox::about(NULL, "提示", "有物体");
	std::vector<DetectResults>::iterator pResult;
	int count = 0;
	for (pResult = mDetectObjects.begin(); pResult != mDetectObjects.end();)// pResult++)
	{
		count++;
		//if (pResult->num == 50)
		{
			double space = 18;//连续两个预测的点Y方向之差小于该值停止迭代
			int fla_count = 0;//统计已经检测到了多少个点
			int mean_num = 0;//匀速出现的帧数
			int overlap_num = 0;//计算y轴重复的数目
			int Slow_num = 0;//计算减速的数目
			int Slow_num2 = 0;//计算减速的数目
			int Slow_num3 = 0;//计算减速的数目
			int hov_num = 0;//计算水平点的个数
			double ff = 0;
			double crap = 0;
			double ff2 = 0;
			double crap2 = 0;
			int change_dir = 0;
			int Slow_num4 = 0;//记录在y方向特别慢的点
			int Slow_num5 = 0;//记录在y方向特别慢的点
			bool up = true;
			//int wrong = 0;//判断连续两个点是否间隔很大
			bool wrong = 0;//判断连续两个点是否间隔很大
			bool start_flag = false;//判断是否已过初始的几个点
			int total_height = 0;
			double min = 1000000;
			double max = 0;
			int out_flag = 0;//记录运动物体是否从边界出去
			for (int j = 0; j < pResult->trace.size(); j++)
			{
				if (pResult->trace[j].x < min)
				{
					min = pResult->trace[j].x;
				}
				if (pResult->trace[j].x > max)
				{
					max = pResult->trace[j].x;
				}
				//去除轨迹点在图像以外的异常
				//total_height = mDetectObjects[j].frame_height;
				//std::cout << "mDetectObjects[0].frame_height" << mDetectObjects[0].frame_height << std::endl;
				if (pResult->trace[j].y < 0 || pResult->trace[j].y >= mDetectObjects[0].frame_height)
				{
					ff = 10000;
					break;
				}
				if (j > 0 && (pResult->trace[j].y - pResult->trace[j - 1].y) < 0)
					continue;
				//计算y轴几乎重合的噪声点的数目
				if (start_flag&&j > 0 && abs(pResult->trace[j].y - pResult->trace[j - 1].y) < 4)
				{
					overlap_num++;
				}
				if (j >= 2)
				{
					if (pResult->trace[j].x < 0)
						pResult->trace[j].x = 0;
					if (pResult->trace[j].x >= mDetectObjects[0].frame_width)
						pResult->trace[j].x = mDetectObjects[0].frame_width - 1;
					//std::cout << pResult->trace[j - 2].y << "  " << pResult->trace[j - 2].x << std::endl;
					ff = pResult->trace[j - 1].y - pResult->trace[j - 2].y;
					crap = pResult->trace[j].y - pResult->trace[j - 1].y;


					ff2 = pResult->trace[j - 1].x - pResult->trace[j - 2].x;
					crap2 = pResult->trace[j].x - pResult->trace[j - 1].x;
					if (ff2*crap2 < 0 && fabs(ff2)>5 && fabs(crap2) > 5)
					{
						change_dir++;
					}
					ff2 = fabs(ff2);
					crap2 = fabs(crap2);
					if (ff > 6)
						start_flag = true;
					if ((start_flag && (((crap > 5 * ff || 5 * crap < ff) && (crap > 6 && ff > 6)) || ((crap > 5 * ff&&crap2 > 5 * ff2 && (ff > 7 || ff2 > 7))) || ((crap * 5 < ff&&crap2 * 5 < ff2) && (crap > 7 || crap2 > 7)))) || ((crap > 20 * ff) && ff > 3) || ((crap2 > 5 * ff2 || crap2 * 5 < ff2) && ff2 > 6 && crap2 > 6))
						wrong = 1;
					//if ((start_flag && (crap*crap + crap2*crap2<36)))
					//	wrong ++;
					//计算匀速的点的数目
					if (ff - crap > 1 && ff < InputParam.slow_thre)
					{
						Slow_num++;
					}
					else if (abs(ff - crap) <= 1 && ff < InputParam.mean_thre*0.5)
					{
						mean_num++;
					}
					else if (ff - crap > 2)
					{
						Slow_num2++;
					}
					if (ff2 / ff == crap2 / crap)
					{
						Slow_num3++;
					}

					if (fabs(ff - crap) < 3 && fabs(ff2 - crap2) > 15)
					{
						hov_num++;
					}
					if (ff <= 6 && start_flag)
						Slow_num4++;
					//if (ff <= 8)
					//	Slow_num5++;
				}
				fla_count++;
			}

			/*cv::Mat aaaaaa = cv::imread("E:\\me.jpg");
			imshow("aaaaaa", aaaaaa);*/
			//从下边界出去
			if (pResult->trace[pResult->trace.size() - 1].y + (pResult->trace[pResult->trace.size() - 1].y - pResult->trace[pResult->trace.size() - 3].y) > mDetectObjects[0].frame_height)
				out_flag = 1;
			else if (pResult->trace[pResult->trace.size() - 1].x + (pResult->trace[pResult->trace.size() - 1].x - pResult->trace[pResult->trace.size() - 3].x) < 0)
				out_flag = 1;
			else if (pResult->trace[pResult->trace.size() - 1].x + (pResult->trace[pResult->trace.size() - 1].x - pResult->trace[pResult->trace.size() - 3].x) > mDetectObjects[0].frame_width)
				out_flag = 1;
#pragma region CurveFitting
			double minus = 1.0*(pResult->trace[pResult->trace.size() - 1].y - pResult->trace[0].y);
			double bie = 1 - minus / mDetectObjects[0].frame_height;
			if (bie < 0.5)
				bie = 0.5;
			//if (1)
			//if (start_flag&&pResult->pre_num <= fla_count*0.58&&fla_count > InputParam.fla_thre&& overlap_num < fla_count*InputParam.overlap_ratio && mean_num < fla_count*InputParam.mean_ratio*2.6&& Slow_num < fla_count*InputParam.slow_ratio&& pResult->trace.size() >= InputParam.min_frame_num && (pResult->trace[pResult->trace.size() - 1].y - pResult->trace[0].y)*(bie) >fabs((pResult->trace[pResult->trace.size() - 1].x - pResult->trace[0].x)) && ((pResult->trace[pResult->trace.size() - 1].y - pResult->trace[0].y) >= 8 * pResult->trace.size()) && Slow_num3<fla_count*0.8&& Slow_num4<fla_count*0.2&& hov_num<fla_count*0.2 && ((Slow_num2<fla_count*InputParam.slow_ratio) || InputParam.is_day) && change_dir <= (1 + fla_count / 11) && !wrong)
			//if (start_flag&&pResult->pre_num <= fla_count*0.58&&fla_count > InputParam.fla_thre&& overlap_num < fla_count*InputParam.overlap_ratio && mean_num < fla_count*InputParam.mean_ratio*2.6&& Slow_num < fla_count*InputParam.slow_ratio&& pResult->trace.size() >= InputParam.min_frame_num && (pResult->trace[pResult->trace.size() - 1].y - pResult->trace[0].y)*(bie) >fabs((pResult->trace[pResult->trace.size() - 1].x - pResult->trace[0].x)) && ((pResult->trace[pResult->trace.size() - 1].y - pResult->trace[0].y) >= 8 * pResult->trace.size()) && Slow_num3<fla_count*0.8&& Slow_num4<fla_count*0.2&& hov_num<fla_count*0.2 && ((Slow_num2<fla_count*InputParam.slow_ratio) || InputParam.is_day) && change_dir <= (1 + fla_count / 11) && !wrong)
			//if (start_flag&&pResult->pre_num <= fla_count*0.58&&fla_count > InputParam.fla_thre&& overlap_num < fla_count*InputParam.overlap_ratio && mean_num < fla_count*InputParam.mean_ratio*2.6&& Slow_num < fla_count*InputParam.slow_ratio&& pResult->trace.size() >= InputParam.min_frame_num && (pResult->trace[pResult->trace.size() - 1].y - pResult->trace[0].y)*(bie) >fabs((pResult->trace[pResult->trace.size() - 1].x - pResult->trace[0].x)) && ((pResult->trace[pResult->trace.size() - 1].y - pResult->trace[0].y) >= 8 * pResult->trace.size()) && Slow_num3<fla_count*0.8&& hov_num<fla_count*0.2 && ((Slow_num2<fla_count*InputParam.slow_ratio) || InputParam.is_day) && change_dir <= (1 + fla_count / 11) && Slow_num4<fla_count*0.4&& !wrong)
			//if (get_num(*pResult) < 2 && start_flag&&pResult->pre_num <= fla_count * 0.58&&fla_count > InputParam.fla_thre&& overlap_num < fla_count*InputParam.overlap_ratio && mean_num < fla_count*InputParam.mean_ratio*2.6&& Slow_num < fla_count*InputParam.slow_ratio&& pResult->trace.size() >= InputParam.min_frame_num && (pResult->trace[pResult->trace.size() - 1].y - pResult->trace[0].y)*(bie) >fabs(max - min) && ((pResult->trace[pResult->trace.size() - 1].y - pResult->trace[0].y) >= 8 * pResult->trace.size()) && Slow_num3 < fla_count*0.8&& hov_num < fla_count*0.2 && ((Slow_num2 < fla_count*InputParam.slow_ratio) || InputParam.is_day) && change_dir <= (1 + fla_count / 11) && Slow_num4 < fla_count*0.4 && !wrong&&out_flag && pResult->trace.size() <= 75)
			
			//if (start_flag&&pResult->pre_num <= fla_count * 0.5&&fla_count > InputParam.fla_thre && Slow_num < fla_count*InputParam.slow_ratio&& pResult->trace.size() >= InputParam.min_frame_num && Slow_num3 < fla_count*0.8&& hov_num < fla_count*0.2 && ((Slow_num2 < fla_count*InputParam.slow_ratio) || InputParam.is_day) && Slow_num4 < fla_count*0.4 && pResult->trace.size() <= 75)
			if (start_flag&&pResult->pre_num <= fla_count * 0.5&&fla_count > InputParam.fla_thre&& overlap_num < fla_count*InputParam.overlap_ratio && mean_num < fla_count*InputParam.mean_ratio*2.6&& Slow_num < fla_count*InputParam.slow_ratio&& pResult->trace.size() >= InputParam.min_frame_num && (pResult->trace[pResult->trace.size() - 1].y - pResult->trace[0].y)*(bie) >fabs(max - min) && ((pResult->trace[pResult->trace.size() - 1].y - pResult->trace[0].y) >= 8 * pResult->trace.size()) && Slow_num3 < fla_count*0.8&& hov_num < fla_count*0.2 && ((Slow_num2 < fla_count*InputParam.slow_ratio) || InputParam.is_day) && change_dir <= (1 + fla_count / 11) && Slow_num4 < fla_count*0.4 && !wrong&&out_flag && pResult->trace.size() <= 75)
			{
				std::cout << "pResult->pre_num" << pResult->pre_num << std::endl;
				std::cout << "fla_count" << fla_count << std::endl;
				//cvWaitKey(0);
				//cv::Mat aaaaaa = cv::imread("E:\\me.jpg");
				//imshow("aaaaaa", aaaaaa);
				////std::cout << NetTransmissiontmp.mDetectObjects[0].traceY.size() << std::endl;
				//cvWaitKey(0);
				pResult->is_object = true;
				polyfit(*pResult, 2, true);

				//std::cout << getR_Square() << std::endl;
				///****************************************************/
				//cv::Mat aaaaaa = cv::imread("E:\\me.jpg");
				//imshow("aaaaaa", aaaaaa);
				////std::cout << NetTransmissiontmp.mDetectObjects[0].traceY.size() << std::endl;
				std::cout << temp << std::endl;

				//if (0&&getR_Square() < InputParam.R_thre)// || temp>=0.9)//||getFactor(2)==0)
				//{
				//	std::cout << getR_Square() << std::endl;
				//	//cv::Mat aaaaaa = cv::imread("E:\\me.jpg");
				//	//imshow("aaaaaa", aaaaaa);
				//	////std::cout << NetTransmissiontmp.mDetectObjects[0].traceY.size() << std::endl;
				//	//cvWaitKey(0);
				//	pResult = mDetectObjects.erase(pResult);
				//	continue;
				//}

				int first_frame = pResult->frames_num[0];//检测到的“第一帧”的“时间”
				double first_Y = pResult->traceY[0];//检测到的“第一帧”的“Y方向上的位置”
				double first_X = pResult->trace[0].x;//检测到的“第一帧”的“X方向上的位置”
				//如果有向上运动的趋势，则直接是轨迹第一帧为检测起始位置
				if (up == true)
				{
					pResult->first_trace = cv::Point2d(first_X, first_Y);
				}
				else
				{
					int iter = 0;//设置迭代
					bool flag_over = true;//记录是否需要继续追踪
					double x_space = pResult->trace[1].x - first_X;
					int is_first = 0;//记录当前抛物的轨迹是否是第一次检测到(即是否第一次出现在视频中)
					double first_minus = getFactor(0) + getFactor(1)*(first_frame + 1) + getFactor(2)*(first_frame + 1)*(first_frame + 1) - first_Y;
					if (!(first_minus > InputParam.first_minus_thre && first_Y <= first_minus))
					{
						is_first = 1;
						space = 10;
					}
					if (getFactor(0) + getFactor(1)*(first_frame + 1) + getFactor(2)*(first_frame + 1)*(first_frame + 1) - first_Y < space)
					{
						//计算起始坐标
						double temp = getFactor(0) + getFactor(1)*first_frame + getFactor(2)*first_frame*first_frame;
						pResult->first_trace = cv::Point2d(first_X, temp);
						//qDebug() << "抛出点横坐标：" << first_X << "      抛出点纵坐标" << temp << endl;
						flag_over = false;
					}
					double last_minus = getFactor(0) + getFactor(1)*(first_frame + 1) + getFactor(2)*(first_frame + 1)*(first_frame + 1) - first_Y;
					first_frame--;
					int count_frames = 0;//保证每次间隔之差大于1个像素
					if (!flag_over && is_first == 0)
					{
						for (int w = 0; w < 3; w++)
						{
							double temp = getFactor(0) + getFactor(1)*first_frame + getFactor(2)*first_frame*first_frame;
							double minus = first_Y - temp;
							first_X = first_X - x_space;
							CvPoint center2;
							center2.x = first_X;
							center2.y = temp + InputParam.vars;
							pResult->trace.insert(pResult->trace.begin(), center2);//插入倒推出来的值
							pResult->frames_num.insert(pResult->frames_num.begin(), first_frame);
							//int save = pResult->frame_num.front();
							//pResult->frame_num.insert(pResult->frame_num.begin(), save);//记录帧数
							first_frame--;
						}
					}
					while (flag_over)
					{
						double temp = getFactor(0) + getFactor(1)*first_frame + getFactor(2)*first_frame*first_frame;
						double minus = first_Y - temp;
						first_X = first_X - x_space;
						CvPoint center2;
						center2.x = first_X;
						center2.y = temp + InputParam.vars;
						pResult->trace.insert(pResult->trace.begin(), center2);//插入倒推出来的值
						pResult->frames_num.insert(pResult->frames_num.begin(), first_frame);
						//int save = pResult->frame_num.front();
						//pResult->frame_num.insert(pResult->frame_num.begin(), save);//记录帧数
						if (minus - count_frames < space)
						{
							pResult->first_trace = center2;
							//qDebug() << "抛出点横坐标：" << first_X << "  " << "      抛出点纵坐标" << temp + InputParam.vars << endl;
							break;
						}
						else
						{
							first_Y = temp;
							first_frame--;
							if (fabs(minus - last_minus) < 1)
							{
								count_frames++;
							}
							last_minus = minus;
						}
					}
				}
#pragma endregion</span>	
				pResult++;
			}
			else
			{
				pResult = mDetectObjects.erase(pResult);
			}
		}
	}
	return;
}



