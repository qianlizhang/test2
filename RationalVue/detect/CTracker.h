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
	//size_t camNum;//相机的通道号
	//float dt;//两次滤波之间的时间间隔，dt太大精度差，而且可能发散，线性模型无法满足
	//size_t NextTrackID;//下一个追踪目标编号
	//float Accel_noise_mag;//噪音	
	//double dist_thres;//阈值设置
	//int maximum_allowed_skipped_frames;//最大允许跳过的检测视频帧
	//int max_trace_length;//最大追踪的长度
	//int min_frame_num;//高空抛物检测的最小帧数
	
	std::vector<CTrack*> tracks;//追踪对象
	std::vector<CTrack*> tracks2;//追踪对象
	std::vector<CTrack*> tracks3;//追踪对象
	//std::vector<DetectResults> mDetectObjects;//保存高空抛物对象
	CParams parameter;
	CTracker(CParams parameter)
	{
		this->parameter = parameter;
	}
public:
	
	CTracker(float _dt, float _Accel_noise_mag, double _dist_thres = 60, int _maximum_allowed_skipped_frames = 5, int _max_trace_length = 100, int _min_frame_num = 15);
	~CTracker();
	//size_t camNum;//相机的通道号
	//vector<DetectResults> mDetectObjects;//保存高空抛物对象
	void UpdateModel(CObjectRect &var, cv::Mat frame);
	void UpdateModel4(CObjectRect &var, cv::Mat frame);
	void UpdateModel5(CObjectRect var, std::vector<DetectResults> &mDetectObjects);
	void UpdateModel2(CObjectRect var, std::vector<DetectResults> &mDetectObjects);
	void UpdateModel3(CObjectRect var, cv::Mat frame, CvRect &track_rect, std::vector<DetectResults> &mDetectObjects);
	//void SetParameter(CParams InputParam);
	void UpdateModel6(CObjectRect &var, cv::Mat frame);
	void UpdateModel7(CObjectRect var, std::vector<DetectResults> &mDetectObjects);
	CvRect rect;//记录老人框
};