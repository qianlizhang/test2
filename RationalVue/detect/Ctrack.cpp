///*****************************************************************
///  �ļ�����: 
///  ��Ҫ����:  
///  ����:  Dreamhigh
///  ��������: 
///*****************************************************************
#include "Ctrack.h"
//CTrack�Ĺ��캯��
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

// CTrack����������
CTrack::~CTrack()
{
	delete KF;
}
