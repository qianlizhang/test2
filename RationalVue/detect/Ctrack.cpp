///*****************************************************************
///  文件名称: 
///  简要描述:  
///  作者:  Dreamhigh
///  创建日期: 
///*****************************************************************
#include "Ctrack.h"
//CTrack的构造函数
CTrack::CTrack(cv::Point2f pt, float dt, float Accel_noise_mag)
{
	track_id = NextTrackID;
	NextTrackID++;
	KF = new TKalmanFilter(pt, dt, Accel_noise_mag);

	prediction = pt;
	skipped_frames = 0;
	num_frames = 0;
	ptrack_id = cam_id = 0;
}

// CTrack的析构函数
CTrack::~CTrack()
{
	delete KF;
}
