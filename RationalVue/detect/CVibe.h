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
//	brief	: �˶���������  �̳� Ŀ�����㷨����
//	author	: 
//***********************************************************************

class CVibe {

public :
	CParams parameter;
	CVibe(CParams parameter)
	{
		this->parameter = parameter;
	}//���캯��  
	~CVibe(void);  //�����������Կ��ٵ��ڴ�����Ҫ��������  

	void DetectObjects(cv::Mat frame,  CObjectRect & tarobj);
public:
	bool startflag = true;//�ж��Ƿ��ǵ�һ֡
	void init(const cv::Mat _image);   //��ʼ�� 
private:   
	int XX = 0;
	cv::RNG rng;
	IplImage temp;
	IplImage * src;
	CvMemStorage *storage = cvCreateMemStorage(0);
	CvSeq *seq = NULL;
	void processFirstFrame(cv::Mat _image); //���õ�һ֡���н�ģ   
	int Rect(const cv::Mat frame, cv::Mat mask2);
	//int first(cv::VideoCapture capture);
	//int InitialOpencl();//��ʼ��Opencl����
	//int Vibe();
	//int EndOpencl();



	cv::Mat m_samples[20];  //ÿһ֡ͼ���ÿһ�����ص�������  
	cv::Mat m_foregroundMatchCount;  //ͳ�����ر��ж�Ϊǰ���Ĵ��������ڸ���  
	cv::Mat m_mask;  //ǰ����ȡ���һ֡ͼ��  
	cv::Mat frame_u;//����
	cv::Mat frame_d; //ǰ��
	cv::Mat frame_cpy;
	double alpha = 0.05;    //������ģalphaֵ
	double std_init = 20;    //��ʼ��׼��
	double var_init = std_init * std_init;    //��ʼ����
	double lamda = 2.5 * 1.2;    //�������²���
	double value = 0.5*lamda * std_init;

	int InitialOpencl();//��ʼ��Opencl����
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