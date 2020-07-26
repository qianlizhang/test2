#include <vector>
#include <CTracking.h>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"
#include "CHungarianAlg.h"
//#include "Kalman.h"
#include "Ctrack.h"
#include "DetectResults.h"

class CTracker
{
public:
	//size_t camNum;//�����ͨ����
	//float dt;//�����˲�֮���ʱ������dt̫�󾫶Ȳ���ҿ��ܷ�ɢ������ģ���޷�����
	//size_t NextTrackID;//��һ��׷��Ŀ����
	//float Accel_noise_mag;//����	
	//double dist_thres;//��ֵ����
	//int maximum_allowed_skipped_frames;//������������ļ����Ƶ֡
	//int max_trace_length;//���׷�ٵĳ���
	//int min_frame_num;//�߿����������С֡��
	
	std::vector<CTrack*> tracks;//׷�ٶ���
	std::vector<CTrack*> tracks2;//׷�ٶ���
	std::vector<CTrack*> tracks3;//׷�ٶ���
	//std::vector<DetectResults> mDetectObjects;//����߿��������
	CParams parameter;
	CTracker(CParams parameter)
	{
		this->parameter = parameter;
	}
public:
	
	CTracker(float _dt, float _Accel_noise_mag, double _dist_thres = 60, int _maximum_allowed_skipped_frames = 5, int _max_trace_length = 100, int _min_frame_num = 15);
	~CTracker();
	//size_t camNum;//�����ͨ����
	//vector<DetectResults> mDetectObjects;//����߿��������
	void UpdateModel(CObjectRect &var, cv::Mat frame);
	void UpdateModel4(CObjectRect &var, cv::Mat frame);
	void UpdateModel5(CObjectRect var, std::vector<DetectResults> &mDetectObjects);
	void UpdateModel2(CObjectRect var, std::vector<DetectResults> &mDetectObjects);
	void UpdateModel3(CObjectRect var, cv::Mat frame, CvRect &track_rect, std::vector<DetectResults> &mDetectObjects);
	//void SetParameter(CParams InputParam);
	void UpdateModel6(CObjectRect &var, cv::Mat frame);
	void UpdateModel7(CObjectRect var, std::vector<DetectResults> &mDetectObjects);
	CvRect rect;//��¼���˿�
};