#pragma once  
#include "CVibe.h"    
#include <string>
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <glog/logging.h>
using namespace std;
using namespace cv;
extern int c_xoff[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };  //x的邻居点，9宫格  
extern int c_yoff[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };  //y的邻居点    



CVibe::~CVibe(void)
{

}

int convertToString(const char *filename, std::string& s)
{
	size_t size;
	char*  str;
	std::fstream f(filename, (std::fstream::in | std::fstream::binary));

	if (f.is_open())
	{
		size_t fileSize;
		f.seekg(0, std::fstream::end);
		size = fileSize = (size_t)f.tellg();
		f.seekg(0, std::fstream::beg);
		str = new char[size + 1];
		if (!str)
		{
			f.close();
			return 0;
		}

		f.read(str, fileSize);
		f.close();
		str[size] = '\0';
		s = str;
		delete[] str;
		return 0;
	}
	cout << "Error: failed to open file\n:" << filename << endl;
	return -1;
}

cv::Point2f getCenterPoint2(cv::Rect rect)
{
	cv::Point2f cpt;
	cpt.x = rect.x + cvRound(rect.width / 2.0);
	cpt.y = rect.y + cvRound(rect.height / 2.0);
	return cpt;
}

void CVibe::DetectObjects(cv::Mat frame,  CObjectRect & tarobj)
{
	qDebug() << "in detectobject fun";
	//clock_t t1 = clock();
	if (frame.empty())
		return;
	tarobj.detectrects.clear();
	tarobj.width.clear();
	tarobj.height.clear();
	tarobj.detections.clear();
	tarobj.width.clear();
	tarobj.height.clear();
	if (frame.channels() != 1)
		cvtColor(frame, gray, CV_RGB2GRAY); //不是灰度图时转化为灰度图像   
	else
		gray = frame;
	//std::cout << "gray.rows:" << gray.rows << "       gray.cols:" << gray.cols << std::endl;
	if (this->startflag == true)
	{
		init(gray);
		processFirstFrame(gray); //背景模型初始化   
		InitialOpencl();//初始化opencl环境
		this->startflag = false;
	}
	else
	{
		qDebug() << "in detectobject fun222";
		Vibe();
		if (countNonZero(m_mask) > (m_mask.rows*m_mask.cols*0.2))
		{
			
			init(gray);
			processFirstFrame(gray); //背景模型初始化   
			return;
		}

		//IplImage temp = m_mask;
		//IplImage * src = &temp;
		//CvMemStorage *storage = cvCreateMemStorage(0);
		//CvSeq *seq = NULL;

		/*temp = m_mask;
		src = &temp;*/
		//std::cout << 111 << std::endl;
		//threshold(m_mask, m_mask, 100, 255, CV_THRESH_BINARY);
		src = &(IplImage)m_mask;
		storage = cvCreateMemStorage(0);
		seq = NULL;
		int cnt = cvFindContours(src, storage, &seq, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));//, CV_CHAIN_APPROX_SIMPLE);
		cout << "cnt:" << cnt << endl;
		if (cnt <= 1500)
		{
			this->parameter.minAreaSize = 20;
			this->parameter.minLenSize = 20;
		}
		else
		{
			this->parameter.minAreaSize = 10;
			this->parameter.minLenSize = 10;
		}
		while (seq != NULL)
		{
			if (seq == NULL || seq == nullptr)
				break;
			double areaSeq = fabs(cvContourArea(seq));
			double lengthSeq = cvArcLength(seq);
			if (areaSeq > this->parameter.minAreaSize && areaSeq < this->parameter.maxAreaSize
				&& lengthSeq < this->parameter.maxLenSize && lengthSeq > this->parameter.minLenSize)
			{
				CvRect rect = cvBoundingRect(seq, 0);
				tarobj.frame_num = 1;
				tarobj.detectrects.push_back(rect);

				tarobj.width.push_back(rect.width);
				tarobj.height.push_back(rect.height);

				tarobj.detections.push_back(getCenterPoint2(rect));
				tarobj.frame_height = gray.rows;
				tarobj.frame_width = gray.cols;
			}
			if (seq == NULL || seq == nullptr)
				break;
			seq = seq->h_next;
		}
		cvReleaseMemStorage(&storage);
	}
	//cv::Mat show_center = m_mask.clone();
	//cv::imshow("sax", gray);
	//for (int i = 0; i < tarobj.detections.size(); i++)
	//{
	//	cv::circle(show_center, tarobj.detections[i], 4, cv::Scalar(255, 0, 0), -1, 1, 0);
	//}
	//cv::resize(show_center, show_center, cv::Size(show_center.cols * 0.6, show_center.rows *0.6), (0, 0), (0, 0));
	//cv::imshow("show_center", show_center);
	//show_center.release();
	////cv::resize(show_center, show_center, cv::Size(show_center.cols * 0.6, show_center.rows *0.6), (0, 0), (0, 0));
	//imshow("aax", m_mask);
	//cv::waitKey(1);
	//LOG(INFO) <<"DetectObjects fun: " <<frame.empty() << std::endl;
	return;
}

/**************** Assign space and init ***************************/
void CVibe::init(const cv::Mat _image)  //成员函数初始化  
{
	for (int i = 0; i < parameter.NUM_SAMPLES; i++) //可以这样理解，针对一帧图像，建立了20帧的样本集  
	{
		m_samples[i] = cv::Mat::zeros(_image.size(), CV_8UC1);  //针对每一帧样本集的每一个像素初始化为8位无符号0，单通道  
	}
	m_mask = cv::Mat::zeros(_image.size(), CV_8UC1); //初始化   
	m_foregroundMatchCount = cv::Mat::zeros(_image.size(), CV_8UC1);  //每一个像素被判断为前景的次数，初始化  
	frame_u = cv::Mat::zeros(_image.size(), CV_8UC1);
	frame_d = cv::Mat::zeros(_image.size(), CV_8UC1);
	frame_cpy = cv::Mat::zeros(_image.size(), CV_8UC1);
	//double alpha = 0.05;    //背景建模alpha值
	//double std_init = 20;    //初始标准差
	//double var_init = std_init * std_init;    //初始方差
	//double lamda = 2.5 * 1.2;    //背景更新参数
	//frame_d = std_init;
	frame_u = _image;
}

void CVibe::processFirstFrame(cv::Mat _image)
{
	cv::RNG rng;    //随机数产生器                                      
	int row, col;
	for (int i = 0; i < _image.rows; i++)
	{
		for (int j = 0; j < _image.cols; j++)
		{
			for (int k = 0; k < parameter.NUM_SAMPLES; k++)
			{
				int random = rng.uniform(0, 9);
				row = i + c_yoff[random];
				if (row < 0)
					row = 0;
				if (row >= _image.rows)
					row = _image.rows - 1;

				col = j + c_xoff[random];
				if (col < 0)
					col = 0;
				if (col >= _image.cols)
					col = _image.cols - 1;

				m_samples[k].at<uchar>(i, j) = _image.at<unsigned char>(row, col);  //将相应的像素值复制到样本集中  
			}
		}
	}
}

int CVibe::Rect(const cv::Mat frame, cv::Mat mask2)
{
	int count = 0;
	IplImage temp = mask2;
	IplImage * src = &temp;
	CvMemStorage *storage = cvCreateMemStorage();
	CvSeq *seq = NULL;
	int mode = CV_RETR_CCOMP;
	int cnt = cvFindContours(src, storage, &seq, sizeof(CvContour), CV_RETR_EXTERNAL);//, CV_CHAIN_APPROX_SIMPLE);
	IplImage dst1 = frame;
	IplImage *dst = &dst1;
	if (cnt < 1)
	{
		cvShowImage("dst", dst);
		return 0;
	}
	//cout << cnt << endl;
	int i = 0;
	while (seq != NULL)
	{
		//cout << "dadada" << endl;
		if (!seq)
			continue;
		double length = cvArcLength(seq);
		double area = cvContourArea(seq);
		if (length <= 2 || area <= 2)
		{
			seq = seq->h_next;
			continue;
		}
		CvRect rect = cvBoundingRect(seq, i + 1);
		i = i + 1;
		CvBox2D box = cvMinAreaRect2(seq, NULL);
		cvRectangleR(dst, rect, CV_RGB(0, 0, 0));
		seq = seq->h_next;
		count++;
	}
	//resize(dst, dst, Size(), 0.6, 0.6);
	//Mat dst2;
	//dst2 = cv::cvarrToMat(dst);
	//resize(dst2, dst2, Size(),1.67, 1.67);
	//imshow("dst", dst2);
	//cvShowImage("dst", dst);
	return 0;
}

int CVibe::InitialOpencl()
{
	N = frame_u.rows*frame_u.cols;
	int rows = frame_u.rows;
	int cols = frame_u.cols;

	//int rows = frame_u.cols;
	//int cols = frame_u.rows;

	cv::RNG rng;

	int **random_s = (int **)malloc(rows * sizeof(int*));
	random_s[0] = (int *)malloc((N + rows) * sizeof(int));
	for (int i = 1; i < rows; i++)
		random_s[i] = random_s[i - 1] + cols + 1;
	memset(random_s[0], 0, (N + rows) * sizeof(int));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols + 1; j++)
		{
			random_s[i][j] = rng.uniform(0, parameter.SUBSAMPLE_FACTOR);
		}
	}


	int **flag3 = (int **)malloc(rows * sizeof(int*));//判断是否可以进行邻域内的背景更新
	flag3[0] = (int *)malloc(N * sizeof(int));
	for (int i = 1; i < rows; i++)
		flag3[i] = flag3[i - 1] + cols;
	memset(flag3[0], 0, (N) * sizeof(int));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (j == 0 || j == cols - 1 || i == 0 || i == rows - 1)
				flag3[i][j] = 1;
		}
	}


	int **random_n = (int **)malloc(rows * sizeof(int*));
	random_n[0] = (int *)malloc((N + rows) * sizeof(int));
	for (int i = 1; i < rows; i++)
		random_n[i] = random_n[i - 1] + cols + 1;
	memset(random_n[0], 0, (N + rows) * sizeof(int));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols + 1; j++)
		{
			random_n[i][j] = rng.uniform(0, parameter.NUM_SAMPLES);
		}
	}


	int **random_9 = (int **)malloc(rows * sizeof(int*));
	random_9[0] = (int *)malloc((N + rows) * sizeof(int));
	for (int i = 1; i < rows; i++)
		random_9[i] = random_9[i - 1] + cols + 1;
	memset(random_9[0], 0, (N + rows) * sizeof(int));
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols + 1; j++)
		{
			random_9[i][j] = rng.uniform(0, 9);
		}
	}


	cl_mem random_s2 = nullptr;
	cl_mem random_n2 = nullptr;
	cl_mem random_92 = nullptr;


	unsigned char **frame_u2 = (unsigned char **)malloc(rows * sizeof(unsigned char*));
	frame_u2[0] = (unsigned char *)malloc(N * sizeof(unsigned char));
	for (int i = 1; i < rows; i++)
		frame_u2[i] = frame_u2[i - 1] + cols;
	memset(frame_u2[0], 0, N * sizeof(unsigned char));

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			frame_u2[i][j] = frame_u.at<uchar>(i, j);
		}
	}

	unsigned char **frame_d2 = (unsigned char **)malloc(rows * sizeof(unsigned char*));
	frame_d2[0] = (unsigned char *)malloc(N * sizeof(unsigned char));
	for (int i = 1; i < rows; i++)
		frame_d2[i] = frame_d2[i - 1] + cols;
	memset(frame_d2[0], 0, N * sizeof(unsigned char));


	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			frame_d2[i][j] = 0;
		}
	}


	//unsigned char **m_foregroundMatchCount2 = (unsigned char **)malloc(rows * sizeof(unsigned char*));
	m_foregroundMatchCount2 = (unsigned char **)malloc(rows * sizeof(unsigned char*));
	m_foregroundMatchCount2[0] = (unsigned char *)malloc(N * sizeof(unsigned char));
	for (int i = 1; i < rows; i++)
		m_foregroundMatchCount2[i] = m_foregroundMatchCount2[i - 1] + cols;
	memset(m_foregroundMatchCount2[0], 0, N * sizeof(unsigned char));


	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			m_foregroundMatchCount2[i][j] = 0;
		}
	}




	m_mask2 = (unsigned char **)malloc(rows * sizeof(unsigned char*));
	m_mask2[0] = (unsigned char *)malloc(N * sizeof(unsigned char));
	for (int i = 1; i < rows; i++)
		m_mask2[i] = m_mask2[i - 1] + cols;
	memset(m_mask2[0], 0, N * sizeof(unsigned char));


	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			m_mask2[i][j] = 0;
		}
	}

	gray2 = (unsigned char **)malloc(rows * sizeof(unsigned char*));
	gray2[0] = (unsigned char *)malloc(N * sizeof(unsigned char));
	for (int i = 1; i < rows; i++)
		gray2[i] = gray2[i - 1] + cols;
	memset(gray2[0], 0, N * sizeof(unsigned char));


	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			gray2[i][j] = 0;
		}
	}



	unsigned char ***m_samples2 = (unsigned char ***)malloc(20 * sizeof(unsigned char**));
	unsigned char **aa, *a;
	aa = (unsigned char**)malloc(sizeof(unsigned char*)*rows * 20);
	a = (unsigned char*)malloc(sizeof(unsigned char) * 20 * rows*cols);
	for (int i = 0; i < 20 * rows; i++)
		aa[i] = &a[i*cols];
	for (int j = 0; j < 20; j++)
		m_samples2[j] = &aa[j*rows];
	memset(m_samples2[0][0], 0, 20 * N * sizeof(unsigned char));
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			for (int k = 0; k < cols; k++)
			{
				m_samples2[i][j][k] = m_samples[i].at<uchar>(j, k);
			}
		}
	}
	//cl_mem frame_u3 = nullptr;
	//cl_mem frame_d3 = nullptr;
	//cl_mem m_foregroundMatchCount3 = nullptr;
	//cl_mem m_mask3 = nullptr;
	//cl_mem m_samples3 = nullptr;

	//cl_mem _image3 = nullptr;


	//cl_mem random2 = nullptr;

	//cl_uint numPlatforms = 0;           //the NO. of platforms
	cl_platform_id platform = nullptr;  //the chosen platform
	//cl_context context = nullptr;       // OpenCL context
	//cl_command_queue commandQueue = nullptr;
	//cl_program program = nullptr;       // OpenCL kernel program object that'll be running on the compute device
	//cl_mem dst = nullptr;
	//cl_kernel kernel = nullptr;         // kernel object

	//cl_int status = clGetPlatformIDs(0, NULL, &numPlatforms);
	if (status != CL_SUCCESS)
	{
		cout << "Error: Getting platforms!" << endl;
		return 0;
	}

	/*For clarity, choose the first available platform. */
	if (numPlatforms > 0)
	{
		cl_platform_id* platforms = (cl_platform_id*)malloc(numPlatforms * sizeof(cl_platform_id));
		status = clGetPlatformIDs(numPlatforms, platforms, NULL);
		if (status != CL_SUCCESS)
		{
			cout << "Error: Getting platform!" << endl;
			return 0;
		}
		platform = platforms[0];
		free(platforms);
	}
	else
	{
		puts("Your system does not have any OpenCL platform!");
		return 0;
	}
	/*Step 2:Query the platform and choose the first GPU device if has one.Otherwise use the CPU as device.*/
	cl_uint numDevices = 1;
	status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
	if (status != CL_SUCCESS)
	{
		cout << "Error: Getting Device!" << endl;
		return 0;
	}
	if (numDevices == 0) //no GPU available.
	{
		cout << "No GPU device available." << endl;
		cout << "Choose CPU as default device." << endl;
		status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 0, NULL, &numDevices);
		devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));

		status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, numDevices, devices, NULL);
	}
	else
	{
		//numDevices--;
		devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));
		status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, numDevices, devices, NULL);
		cout << "The number of devices: " << numDevices << endl;
	}
	char name_data[48];
	clGetDeviceInfo(devices[0], CL_DEVICE_NAME, sizeof(name_data), name_data, NULL);
	if (name_data[0] != 'G')
	{
		if (numPlatforms > 0)
		{
			cl_platform_id* platforms = (cl_platform_id*)malloc(numPlatforms * sizeof(cl_platform_id));
			status = clGetPlatformIDs(numPlatforms, platforms, NULL);
			if (status != CL_SUCCESS)
			{
				cout << "Error: Getting platform!" << endl;
				return 0;
			}
			platform = platforms[1];
			free(platforms);
		}
		else
		{
			puts("Your system does not have any OpenCL platform!");
			return 0;
		}
		/*Step 2:Query the platform and choose the first GPU device if has one.Otherwise use the CPU as device.*/
		cl_uint numDevices = 1;
		status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
		if (status != CL_SUCCESS)
		{
			cout << "Error: Getting Device!" << endl;
			return 0;
		}
		if (numDevices == 0) //no GPU available.
		{
			cout << "No GPU device available." << endl;
			cout << "Choose CPU as default device." << endl;
			status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 0, NULL, &numDevices);
			devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));

			status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, numDevices, devices, NULL);
		}
		else
		{
			//numDevices--;
			devices = (cl_device_id*)malloc(numDevices * sizeof(cl_device_id));
			status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, numDevices, devices, NULL);
			cout << "The number of devices: " << numDevices << endl;
		}
		clGetDeviceInfo(devices[0], CL_DEVICE_NAME, sizeof(name_data), name_data, NULL);
	}
	printf("NAME: %s\n", name_data);
	/*Step 3: Create context.*/
	context = clCreateContext(NULL, 1, devices, NULL, NULL, NULL);

	/*Step 4: Creating command queue associate with the context.*/
	commandQueue = clCreateCommandQueue(context, devices[0], 0, NULL);

	/*Step 5: Create program object */
	// Read the kernel code to the buffer
	const char *filename = "D://calc.cl";
	string sourceStr;
	status = convertToString(filename, sourceStr);
	const char *source = sourceStr.c_str();
	size_t sourceSize[] = { strlen(source) };
	program = clCreateProgramWithSource(context, 1, &source, sourceSize, NULL);
	/*Step 6: Build program. */
	status = clBuildProgram(program, 1, devices, NULL, NULL, NULL);
	/*Step 7: Initial inputs and output for the host and create memory objects for the kernel*/
	// Create mmory object
	frame_u3 = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, N * sizeof(unsigned char), frame_u2[0], nullptr);
	frame_d3 = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, N * sizeof(unsigned char), frame_d2[0], nullptr);
	m_foregroundMatchCount3 = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, N * sizeof(unsigned char), m_foregroundMatchCount2[0], nullptr);
	//m_mask3 = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, N * sizeof(unsigned char), m_mask2[0], nullptr);
	m_mask3 = clCreateBuffer(context, CL_MEM_WRITE_ONLY, N * sizeof(unsigned char), m_mask2[0], nullptr);
	m_samples3 = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, 20 * N * sizeof(unsigned char), m_samples2[0][0], nullptr);

	random_s2 = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, (rows + N) * sizeof(int), random_s[0], nullptr);
	random_n2 = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, (rows + N) * sizeof(int), random_n[0], nullptr);
	random_92 = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, (rows + N) * sizeof(int), random_9[0], nullptr);

	//int random[1] = { rng.uniform(0, N) };
	//random2 = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(int), random, nullptr);
	///random2 = clCreateBuffer(context, 	CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(int), random, nullptr);
	/*Step 8: Create kernel object */
	kernel = clCreateKernel(program, "MyCLAdd", NULL);

	/*Step 9: Sets Kernel arguments.*/
	//status = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&dst);
	status = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&frame_u3);
	status = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&frame_d3);
	status = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&m_foregroundMatchCount3);
	//cl_int ret;
	//ret = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void *)&m_mask3);
	status = clSetKernelArg(kernel, 3, sizeof(cl_mem), (void *)&m_mask3);
	status = clSetKernelArg(kernel, 4, sizeof(cl_mem), (void *)&m_samples3);
	//cout << rows << " " << cols << endl;

	status = clSetKernelArg(kernel, 6, sizeof(cl_mem), (void *)&random_s2);
	status = clSetKernelArg(kernel, 7, sizeof(cl_mem), (void *)&random_n2);
	status = clSetKernelArg(kernel, 8, sizeof(cl_mem), (void *)&random_92);


	status = clSetKernelArg(kernel, 9, sizeof(int), &XX);


	int c_xoff[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
	int c_yoff[9] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };
	cl_mem c_xoff1, c_yoff1;
	c_xoff1 = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, 9 * sizeof(int), c_xoff, nullptr);
	c_yoff1 = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, 9 * sizeof(int), c_yoff, nullptr);
	status = clSetKernelArg(kernel, 10, sizeof(cl_mem), (void *)&c_xoff1);
	status = clSetKernelArg(kernel, 11, sizeof(cl_mem), (void *)&c_yoff1);



	cl_mem flag2;
	flag2 = clCreateBuffer(context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, N * sizeof(int), flag3[0], nullptr);
	status = clSetKernelArg(kernel, 12, sizeof(cl_mem), (void *)&flag2);
	int NUM_SAMPLES2 = parameter.NUM_SAMPLES;
	int RADIUS2 = parameter.RADIUS;
	int MIN_MATCHES2 = parameter.MIN_MATCHES;
	int SUBSAMPLE_FACTOR2 = parameter.SUBSAMPLE_FACTOR;
	clSetKernelArg(kernel, 13, sizeof(int), &N);
	clSetKernelArg(kernel, 14, sizeof(int), &rows);
	clSetKernelArg(kernel, 15, sizeof(int), &cols);
	clSetKernelArg(kernel, 16, sizeof(int), &NUM_SAMPLES2);
	clSetKernelArg(kernel, 17, sizeof(int), &RADIUS2);
	clSetKernelArg(kernel, 18, sizeof(int), &MIN_MATCHES2);
	clSetKernelArg(kernel, 19, sizeof(int), &SUBSAMPLE_FACTOR2);

	global_work_size[0] = N;
	int flag = 0;
	int index3 = N - rows - rows - cols;
	index2 = index3;
	_image3 = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, N * sizeof(unsigned char), gray.data, nullptr);
	status = clSetKernelArg(kernel, 5, sizeof(cl_mem), (void *)&_image3);

}


int CVibe::Vibe()
{
	double t1;
	double t2;
	t1 = (double)cv::getTickCount();
	//XX = (XX++)%int(index2/1.2);
	XX = (XX++) % int(5000);
	//std::cout << index2 << "XXXX:" << XX << std::endl;
	status = clSetKernelArg(kernel, 9, sizeof(int), &XX);

	status = clEnqueueWriteBuffer(commandQueue, _image3, CL_TRUE, 0, N * sizeof(unsigned char), gray.data, NULL, NULL, NULL);
	status = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, global_work_size, NULL, 0, NULL, NULL);     // Force wait until the OpenCL kernel is completed

	status = clEnqueueReadBuffer(commandQueue, m_mask3, CL_TRUE, 0, N * sizeof(unsigned char), m_mask.data, 0, NULL, NULL);
	t2 = (double)cv::getTickCount();
	//cout << "\nwaste time : " << (t2 - t1) / cv::getTickFrequency()<<endl;
	return 0;
}


int CVibe::EndOpencl()
{
	status = clReleaseKernel(kernel);//*Release kernel.
	status = clReleaseProgram(program);    //Release the program object.
	status = clReleaseMemObject(frame_u3);
	status = clReleaseMemObject(frame_d3);
	status = clReleaseMemObject(m_foregroundMatchCount3);
	status = clReleaseMemObject(m_mask3);
	status = clReleaseMemObject(m_samples3);
	status = clReleaseMemObject(_image3);
	status = clReleaseCommandQueue(commandQueue);//Release  Command queue.
	status = clReleaseContext(context);//Release context.
	free(devices);
	return 0;
}