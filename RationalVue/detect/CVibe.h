#include<CObjectDetection.h>
#include<string.h>
//#include<CParams.h>
#include <CL/cl.h>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream> 
#include <fstream>
#include <iomanip>
#include <cstdio>    
#include <stdlib.h> 
#include <vector>


//using namespace cv;
//***********************************************************************
//	name	: CVibe
//	brief	: 运动物体检测类  继承 目标检测算法基类
//	author	: 
//***********************************************************************

class CVibe {

public :
	CParams parameter;
	CVibe(CParams parameter)
	{
		this->parameter = parameter;
	}//构造函数  
	~CVibe(void);  //析构函数，对开辟的内存做必要的清理工作  

	void DetectObjects(cv::Mat frame,  CObjectRect & tarobj);
public:
	bool startflag = true;//判断是否是第一帧
	void init(const cv::Mat _image);   //初始化 
private:   
	int XX = 0;
	cv::RNG rng;
	IplImage temp;
	IplImage * src;
	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq *seq = NULL;
	void processFirstFrame(cv::Mat _image); //利用第一帧进行建模   
	int Rect(const cv::Mat frame, cv::Mat mask2);
	//int first(cv::VideoCapture capture);
	//int InitialOpencl();//初始化Opencl环境
	//int Vibe();
	//int EndOpencl();



	cv::Mat m_samples[20];  //每一帧图像的每一个像素的样本集  
	cv::Mat m_foregroundMatchCount;  //统计像素被判断为前景的次数，便于跟新  
	cv::Mat m_mask;  //前景提取后的一帧图像  
	cv::Mat frame_u;//期望
	cv::Mat frame_d; //前景
	cv::Mat frame_cpy;
	double alpha = 0.05;    //背景建模alpha值
	double std_init = 20;    //初始标准差
	double var_init = std_init * std_init;    //初始方差
	double lamda = 2.5 * 1.2;    //背景更新参数
	double value = 0.5*lamda * std_init;

	int InitialOpencl();//初始化Opencl环境
	int Vibe();
	int EndOpencl();
	cl_uint numPlatforms = 2;
	cl_int status = clGetPlatformIDs(0, NULL, &numPlatforms);
	cl_command_queue commandQueue = nullptr;
	cl_mem m_foregroundMatchCount3 = nullptr;
	cl_kernel kernel = nullptr;         // kernel object
	cl_mem _image3 = nullptr;
	cl_mem m_mask3 = nullptr;
	cl_mem random2 = nullptr;
	cl_context context = nullptr;       // OpenCL context
	int random[1];
	int index2;
	size_t global_work_size[1];
	int N;
	unsigned char **m_mask2;
	unsigned char **gray2;
	unsigned char **m_foregroundMatchCount2;
	cv::Mat gray;
	cl_program program = nullptr;       // OpenCL kernel program object that'll be running on the compute device
	cl_mem frame_u3 = nullptr;
	cl_mem frame_d3 = nullptr;
	cl_mem m_samples3 = nullptr;
	cl_device_id *devices;
	int count;

};