#include "Ctracker.h"
#include<sstream>
#include<string>
#include<math.h>
bool has_old;
IplImage* last_frame;

int judge(std::vector<DetectResults> &mDetectObjects, DetectResults temp)
{
	int count = 0;
	int count2 = 0;
	//if (mDetectObjects.size() == 0)
	//	return 0;
	std::vector<DetectResults>::iterator ittrack;
	DetectResults temp2;
	for (int i = 0; i < mDetectObjects.size(); i++)
	{
		count = 0;
		count2 = 0;
		//mDetectObjects[i].num++;
		//std::vector<double> v;
		//std::vector<double> v1 = mDetectObjects[i].traceY;
		//std::vector<double> v2 = temp.traceY;

		std::vector<cv::Point2d> v1 = mDetectObjects[i].trace;
		std::vector<cv::Point2d> v2 = temp.trace;
		//sort(v1.begin(), v1.end());
		//sort(v2.begin(), v2.end());
		//for (int j = 0; j<v1.size(); j++)
		//	std::cout << v1[j] <<"   "<< std::endl;
		//std::cout << std::endl;
		//for (int j = 0; j<v2.size(); j++)
		//	std::cout << v2[j] << "   " << std::endl;
		//std::cout << std::endl;
		for (int m = 0; m<v1.size(); m++)
		{
			for (int n = 0; n<v2.size(); n++)
			{
				if ((v1[m].x - v2[n].x)*(v1[m].x - v2[n].x) + (v1[m].y - v2[n].y)*(v1[m].y - v2[n].y)<500)
				{
					count++;
				}
				//if (fabs(v1[m] - v2[n])<10)
				//{
				//	count++;
				//}
			}
		}
		//set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v));//�󽻼�   
		//if (v.size()>2)
		if (count >= 2)
		{
			temp2 = mDetectObjects[i];
			//temp.trace = (*ittrack)->trace;
			//temp.DetectID = (*ittrack)->track_id;
			//temp.skipped_frames = (*ittrack)->skipped_frames;
			//temp.traceY = (*ittrack)->traceY;
			//temp.traceX = (*ittrack)->traceX;
			//temp.frames_num = (*ittrack)->frames_num;
			//temp.pre_num = (*ittrack)->pre_num
			//if (v2.size()>v1.size())
			//	mDetectObjects[i] = temp;
			if (v1[0].y <= v2[0].y)
			{
				int index = v1.size()-1;
				for (int k = 0; k < v2.size(); k++)
				{
					if (v1[index].y < v2[k].y)
					{
						temp2.trace.push_back(v2[k]);
						temp2.traceX.push_back(v2[k].x);
						temp2.traceY.push_back(v2[k].y);
						temp2.frames_num.push_back(temp.frames_num[k]);
					}
				}
				mDetectObjects[i] = temp2;
			}
			else
			{
				int index = v2.size()-1;
				for (int k = 0; k < v1.size(); k++)
				{
					if (v2[index].y < v1[k].y)
					{
						temp.trace.push_back(v1[k]);
						temp.traceX.push_back(v1[k].x);
						temp.traceY.push_back(v1[k].y);
						temp.frames_num.push_back(temp2.frames_num[k]);
					}
				}
				mDetectObjects[i] = temp;
			}

			return 1;
		}
	}
	//std::cout << mDetectObjects.size()<< std::endl;
	//cv::Mat aaaaaa = cv::imread("E:\\me.jpg");
	//imshow("aaaaaa", aaaaaa);
	//cvWaitKey(0);
	return 0;
}

/*
����Ctracker��
_dt:
_Accel_noise_mag:
_dist_thres:������ֵ
_maximum_allowed_skipped_frames:�������������֡
_max_trace_length:Ŀ��׷�ٱ�������󳤶�
*/
//std::vector<std::vector<double> > Cost2(N, std::vector<double>(M));//ͳ�Ƶ�ǰ����������׷�������ľ���

CTracker::CTracker(float _dt, float _Accel_noise_mag, double _dist_thres, int _maximum_allowed_skipped_frames, int _max_trace_length, int _min_frame_num)
{
	/*dt = _dt;
	Accel_noise_mag = _Accel_noise_mag;
	dist_thres = _dist_thres;
	maximum_allowed_skipped_frames = _maximum_allowed_skipped_frames;
	max_trace_length = _max_trace_length;
	min_frame_num = _min_frame_num;
	NextTrackID = 1;*/
}



//��CTracker����������
CTracker::~CTracker()
{
	for (int i = 0; i < tracks.size(); i++)
	{
		delete tracks[i];
	}
	tracks.clear();
}
/*
_parameter.dt:
_parameter.Accel_noise_mag:
parameter._parameter.dist_thres:������ֵ
_parameter.maximum_allowed_skipped_frames:�������������֡
_parameter.max_trace_length:Ŀ��׷�ٱ�������󳤶�
*/
//CObjectRect CTracker::UpdateModel(vector<Point2f>detections, vector<Mat> imgs, double frame_num)
void CTracker::UpdateModel(CObjectRect &var, cv::Mat frame)
{
	////�����һ֡��ƥ������Ľ��
	var.Cost.clear();
	var.Cost2.clear();
	var.assignment.clear();
	var.not_assigned_tracks.clear();
	if (var.detections.size() == 0 && tracks.size() == 0)
	{
		return;
	}
	//std::vector<cv::Point2f>detections = var.detections;
	double frame_num = var.frame_num;
	//��׷��Ŀ��Ϊ�յ�ʱ�򣬽�detections����tracks��
	if (tracks.size() == 0)
	{
		this->parameter.NextTrackID = 1;//Ĭ�ϵ�һ��ΪIDΪ1
		for (int i = 0; i < var.detections.size(); i++)
		{
			CTrack* tr = new CTrack(var.detections[i], this->parameter.dt, this->parameter.Accel_noise_mag);
			tr->track_id = this->parameter.NextTrackID;
			tr->num_frames = 0;
			this->parameter.NextTrackID++;
			tracks.push_back(tr);
		}
	}

	int N = tracks.size();//�켣�ĸ���
	int M = var.detections.size();//�������ĸ���
	std::vector<std::vector<double> > Cost2(N, std::vector<double>(M));//ͳ�Ƶ�ǰ����������׷�������ľ���
	std::vector<std::vector<double> > Cost(N, std::vector<double>(M));//ͳ�Ƶ�ǰ����������׷�������ľ���
	//double dist;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cv::Point2d diff = (tracks[i]->prediction - var.detections[j]);//����ù켣����һ�����Ԥ��λ��

			Cost2[i][j] = sqrtf(diff.x*diff.x + diff.y*diff.y);//Ԥ��λ����ʵ��λ�õľ����
			Cost[i][j] = sqrtf(diff.x*diff.x + diff.y*diff.y);//Ԥ��λ����ʵ��λ�õľ����
			Cost[i][j] = Cost[i][j] * (fabs(tracks[i]->area - (var.width[j] * var.height[j]))) / (var.width[j] * var.height[j]);
		}
	}
	//detections.clear();
	var.Cost = Cost;
	var.Cost2 = Cost2;
	Cost.clear();
	Cost2.clear();
	std::vector<int> assignment;
	std::vector<int> not_assigned_tracks;
	var.assignment = assignment;
	var.not_assigned_tracks = not_assigned_tracks;
	var.detections = var.detections;
	var.frame_num = var.frame_num;
	return;
}
//�������㷨����ƥ�䣬����һ֡ͼƬ�м�⵽���˶�����ƥ�䵽��Ӧ�Ĺ켣
//AssignmentProblemSolver APS;
//vector<int> assignment;
//vector<int> n c     zxot_assigned_tracks;
////������������Ϊ���ӣ�����Ҳ���������޸ģ����ܾ��ǰ�����ƥ�䵽�켣��
//APS.Solve(Cost, assignment, AssignmentProblemSolver::optimal);

//�������ܣ�����������ٽ������
void CTracker::UpdateModel2(CObjectRect var, std::vector<DetectResults> &mDetectObjects)
{
	for (int i = 0; i < mDetectObjects.size(); i++)
	{
		mDetectObjects[i].num++;
	}
	if (var.detections.size() == 0 && tracks.size() == 0)
	{
		return;
	}
	//�ж�δƥ���׷�ٶ����Լ��Ƿ�ȱ֡
	for (int i = 0; i<var.assignment.size(); i++)
	{
		if (var.assignment[i] != -1)//��ƥ�䵽�켣
		{
			//if ((var.Cost[i][var.assignment[i]] / ((fabs(tracks[i]->area - (var.width[var.assignment[i]] * var.height[var.assignment[i]]))) / (var.width[var.assignment[i]] * var.height[var.assignment[i]])))>this->parameter.dist_thres)//�����������ֵ
			if ((tracks[i]->traceX.size() >= 2 && fabs(tracks[i]->traceX[tracks[i]->traceX.size() - 1] - var.detections[var.assignment[i]].x)>7 * fabs(tracks[i]->traceX[tracks[i]->traceX.size() - 1] - tracks[i]->traceX[tracks[i]->traceX.size() - 2])) || (var.Cost[i][var.assignment[i]] / ((fabs(tracks[i]->area - (var.width[var.assignment[i]] * var.height[var.assignment[i]]))) / (var.width[var.assignment[i]] * var.height[var.assignment[i]])))>this->parameter.dist_thres)//�����������ֵ
			{
				var.assignment[i] = -1;
				var.not_assigned_tracks.push_back(i);
			}
			else
			{
				//if (((fabs(tracks[i]->area - (var.width[var.assignment[i]] * var.height[var.assignment[i]]))) / (var.width[var.assignment[i]] * var.height[var.assignment[i]])) < 3)
				tracks[i]->area = (var.width[var.assignment[i]] * var.height[var.assignment[i]]);
			}
		}
		else
		{
			tracks[i]->skipped_frames++;
		}
	}
	std::vector<CTrack*>::iterator ittrack;
	std::vector<int>::iterator itint;
	for (ittrack = tracks.begin(), itint = var.assignment.begin(); ittrack != tracks.end() && itint != var.assignment.end();)// int i = 0; i < tracks.size(); i++)
	{
		//�ж��Ƿ�����֡��������ֵ������켣��������>��ֵ���ж�Ϊ�߿�������󣬱�����mDetectObjects�У�����tracks��ɾȥĿ��
		if ((*ittrack)->skipped_frames > this->parameter.maximum_allowed_skipped_frames)
		{
			//����߿��������
			if ((*ittrack)->trace.size() > (this->parameter.min_frame_num + (*ittrack)->skipped_frames)){
				DetectResults temp;// *tracks[i];
				temp.trace = (*ittrack)->trace;
				temp.DetectID = (*ittrack)->track_id;
				temp.skipped_frames = (*ittrack)->skipped_frames;
				temp.frames_num = (*ittrack)->frames_num;
				temp.traceY = (*ittrack)->traceY;
				temp.traceX = (*ittrack)->traceX;
				temp.pre_num = (*ittrack)->pre_num;
				temp.frame_height = var.frame_height;
				temp.frame_width = var.frame_width;
				if (judge(mDetectObjects, temp) == 0)
					mDetectObjects.push_back(temp);
			}
			delete (*ittrack);
			ittrack = tracks.erase(ittrack);
			itint = var.assignment.erase(itint);
		}
		else
		{
			ittrack++;
			itint++;
		}
	}

	//����������˶��켣ȥ����������Ķ���
	for (ittrack = tracks.begin(), itint = var.assignment.begin(); ittrack != tracks.end() && itint != var.assignment.end();)//int i = 0; i < tracks.size(); i++)
	{
		if ((*ittrack)->trace.size()>5)//&& tracks[i]->trace.size()<15)
		{
			cv::Point2d P1, P2, P3, P4;
			P4 = *((*ittrack)->trace.end() - 1);
			P3 = *((*ittrack)->trace.end() - 2);
			P2 = *((*ittrack)->trace.end() - 3);
			P1 = *((*ittrack)->trace.end() - 4);
			if (P1.y >= P2.y || P2.y >= P3.y || P3.y >= P4.y)
			{
				if ((*ittrack)->trace.size() > (this->parameter.min_frame_num + (*ittrack)->skipped_frames)){
					DetectResults temp;// *tracks[i];
					temp.trace = (*ittrack)->trace;
					temp.DetectID = (*ittrack)->track_id;
					temp.skipped_frames = (*ittrack)->skipped_frames;
					temp.traceY = (*ittrack)->traceY;
					temp.traceX = (*ittrack)->traceX;
					temp.frames_num = (*ittrack)->frames_num;
					temp.pre_num = (*ittrack)->pre_num;
					temp.frame_height = var.frame_height;
					temp.frame_width = var.frame_width;
					if (judge(mDetectObjects, temp) == 0)
						mDetectObjects.push_back(temp);
				}
				delete (*ittrack);
				ittrack = tracks.erase(ittrack);
				itint = var.assignment.erase(itint);
			}
			else
			{
				ittrack++;
				itint++;
			}
		}
		else
		{
			ittrack++;
			itint++;
		}
	}

	//����Ƿ���δ��ǵļ�����
	std::vector<int> not_assigned_detections;
	std::vector<int>::iterator it;
	for (int i = 0; i < var.detections.size(); i++)
	{
		it = find(var.assignment.begin(), var.assignment.end(), i);
		if (it == var.assignment.end())
		{
			not_assigned_detections.push_back(i);
		}
	}

	//��δ��Ǽ��������tracks��
	if (not_assigned_detections.size() != 0)
	{
		for (int i = 0; i < not_assigned_detections.size(); i++)
		{
			CTrack* tr = new CTrack(var.detections[not_assigned_detections[i]], this->parameter.dt, this->parameter.Accel_noise_mag);
			tr->track_id = this->parameter.NextTrackID;
			tr->num_frames = 0;
			this->parameter.NextTrackID++;

			//��¼����������ܳ�
			tr->width = var.width[not_assigned_detections[i]];
			tr->height = var.height[not_assigned_detections[i]];
			tr->area = tr->width*tr->height;
			tr->cir = 2 * tr->width + 2 * tr->height;


			tracks.push_back(tr);
		}
	}

	//���ÿ������˲�����Ԥ�������
	for (int i = 0; i<var.assignment.size(); i++)
	{
		//ͨ��ǰ���ʼ���Ŀ�����������ֱ�ӵ���opencv�Դ��ĺ�������Ԥ��
		tracks[i]->KF->GetPrediction();
		if (var.assignment[i] != -1)//��ƥ��
		{
			tracks[i]->skipped_frames = 0;//��ǰ֡�Ѽ�⵽
			//ֱ�ӽ���⵽��ֵ��ΪԤ��ֵ
			tracks[i]->prediction = tracks[i]->KF->Update(var.detections[var.assignment[i]], 1);

			//��¼����������ܳ�
			tracks[i]->width = var.width[var.assignment[i]];
			tracks[i]->height = var.height[var.assignment[i]];
			//tracks[i]->area = tracks[i]->width*tracks[i]->height;
			tracks[i]->cir = 2 * tracks[i]->width + 2 * tracks[i]->height;
		}
		else//δƥ��
		{
			//ʹ�ÿ������˲�����Ԥ��
			tracks[i]->prediction = tracks[i]->KF->Update(cv::Point2f(0, 0), 0);
			tracks[i]->prediction.y += 3;
			tracks[i]->pre_num++;
		}

		size_t tmp = (tracks[i]->num_frames++);//��¼֡��
		tracks[i]->frames_num.push_back(tmp);
		tracks[i]->trace.push_back(tracks[i]->prediction);//��¼�ù켣����һ���ֵ
		tracks[i]->traceY.push_back(tracks[i]->prediction.y);
		tracks[i]->traceX.push_back(tracks[i]->prediction.x);
		tracks[i]->KF->LastResult = tracks[i]->prediction;//�������˲��ĵ�ǰ״̬��¼
	}
	//var.is_old.clear();
	//UpdateModel2_end_Sig();
	return;
}

void CTracker::UpdateModel4(CObjectRect &var, cv::Mat frame)
{
	////�����һ֡��ƥ������Ľ��
	var.Cost.clear();
	var.assignment.clear();
	var.not_assigned_tracks.clear();
	if (var.detections.size() == 0 && tracks2.size() == 0)
	{
		return;
	}
	//std::vector<cv::Point2f>detections = var.detections;
	double frame_num = var.frame_num;
	//��׷��Ŀ��Ϊ�յ�ʱ�򣬽�detections����tracks��
	if (tracks2.size() == 0)
	{
		this->parameter.NextTrackID = 1;//Ĭ�ϵ�һ��ΪIDΪ1
		for (int i = 0; i < var.detections.size(); i++)
		{
			CTrack* tr = new CTrack(var.detections[i], this->parameter.dt, this->parameter.Accel_noise_mag);
			tr->track_id = this->parameter.NextTrackID;
			tr->num_frames = 0;
			this->parameter.NextTrackID++;
			tracks2.push_back(tr);
		}
	}

	int N = tracks2.size();//�켣�ĸ���
	int M = var.detections.size();//�������ĸ���
	std::vector<std::vector<double> > Cost(N, std::vector<double>(M));//ͳ�Ƶ�ǰ����������׷�������ľ���
	//double dist;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cv::Point2d diff = (tracks2[i]->prediction - var.detections[j]);//����ù켣����һ�����Ԥ��λ��

			Cost[i][j] = sqrtf(diff.x*diff.x + diff.y*diff.y);//Ԥ��λ����ʵ��λ�õľ����
		}
	}
	//detections.clear();
	var.Cost = Cost;
	Cost.clear();
	std::vector<int> assignment;
	std::vector<int> not_assigned_tracks;
	var.assignment = assignment;
	var.not_assigned_tracks = not_assigned_tracks;
	var.detections = var.detections;
	var.frame_num = var.frame_num;
	return;
}

void CTracker::UpdateModel5(CObjectRect var, std::vector<DetectResults> &mDetectObjects)
{
	if (var.detections.size() == 0 && tracks2.size() == 0)
	{
		return;
	}
	//�ж�δƥ���׷�ٶ����Լ��Ƿ�ȱ֡
	for (int i = 0; i<var.assignment.size(); i++)
	{
		if (var.assignment[i] != -1)//��ƥ�䵽�켣
		{
			if ((tracks2[i]->traceX.size() >= 2 && (fabs(tracks2[i]->traceX[tracks2[i]->traceX.size() - 1] - var.detections[var.assignment[i]].x)>7 * fabs(tracks2[i]->traceX[tracks2[i]->traceX.size() - 1] - tracks2[i]->traceX[tracks2[i]->traceX.size() - 2])))|| var.Cost[i][var.assignment[i]]>this->parameter.dist_thres)//�����������ֵ
			{
				var.assignment[i] = -1;
				var.not_assigned_tracks.push_back(i);
			}
		}
		else
		{
			tracks2[i]->skipped_frames++;
		}
	}
	std::vector<CTrack*>::iterator ittrack;
	std::vector<int>::iterator itint;
	for (ittrack = tracks2.begin(), itint = var.assignment.begin(); ittrack != tracks2.end() && itint != var.assignment.end();)// int i = 0; i < tracks.size(); i++)
	{
		//�ж��Ƿ�����֡��������ֵ������켣��������>��ֵ���ж�Ϊ�߿�������󣬱�����mDetectObjects�У�����tracks��ɾȥĿ��
		if ((*ittrack)->skipped_frames > this->parameter.maximum_allowed_skipped_frames)
		{
			//����߿��������
			if ((*ittrack)->trace.size() > (this->parameter.min_frame_num + (*ittrack)->skipped_frames)){
				DetectResults temp;// *tracks[i];
				temp.trace = (*ittrack)->trace;
				temp.DetectID = (*ittrack)->track_id;
				temp.skipped_frames = (*ittrack)->skipped_frames;
				temp.frames_num = (*ittrack)->frames_num;
				temp.traceY = (*ittrack)->traceY;
				temp.traceX = (*ittrack)->traceX;
				temp.frames_num = (*ittrack)->frames_num;
				temp.pre_num = (*ittrack)->pre_num;
				temp.frame_height = var.frame_height;
				temp.frame_width = var.frame_width;
				if (judge(mDetectObjects, temp) == 0)
					mDetectObjects.push_back(temp);
				//cv::Mat aaaaaa = cv::imread("E:\\me.jpg");
				//imshow("aaaaaa", aaaaaa);
			}
			delete (*ittrack);
			ittrack = tracks2.erase(ittrack);
			itint = var.assignment.erase(itint);
		}
		else
		{
			ittrack++;
			itint++;
		}
	}

	//����������˶��켣ȥ����������Ķ���
	for (ittrack = tracks2.begin(), itint = var.assignment.begin(); ittrack != tracks2.end() && itint != var.assignment.end();)//int i = 0; i < tracks.size(); i++)
	{
		if ((*ittrack)->trace.size()>5)//&& tracks[i]->trace.size()<15)
		{
			cv::Point2d P1, P2, P3, P4;
			P4 = *((*ittrack)->trace.end() - 1);
			P3 = *((*ittrack)->trace.end() - 2);
			P2 = *((*ittrack)->trace.end() - 3);
			P1 = *((*ittrack)->trace.end() - 4);
			if (P1.y >= P2.y || P2.y >= P3.y || P3.y >= P4.y)
			{
				if ((*ittrack)->trace.size() > (this->parameter.min_frame_num + (*ittrack)->skipped_frames)){
					DetectResults temp;// *tracks[i];
					temp.trace = (*ittrack)->trace;
					temp.DetectID = (*ittrack)->track_id;
					temp.skipped_frames = (*ittrack)->skipped_frames;
					temp.traceY = (*ittrack)->traceY;
					temp.traceX = (*ittrack)->traceX;
					temp.frames_num = (*ittrack)->frames_num;
					temp.frames_num = (*ittrack)->frames_num;
					temp.pre_num = (*ittrack)->pre_num;
					temp.frame_height = var.frame_height;
					temp.frame_width = var.frame_width;
					if (judge(mDetectObjects, temp) == 0)
						mDetectObjects.push_back(temp);

				}
				delete (*ittrack);
				ittrack = tracks2.erase(ittrack);
				itint = var.assignment.erase(itint);
			}
			else
			{
				ittrack++;
				itint++;
			}
		}
		else
		{
			ittrack++;
			itint++;
		}
	}

	//����Ƿ���δ��ǵļ�����
	std::vector<int> not_assigned_detections;
	std::vector<int>::iterator it;
	for (int i = 0; i < var.detections.size(); i++)
	{
		it = find(var.assignment.begin(), var.assignment.end(), i);
		if (it == var.assignment.end())
		{
			not_assigned_detections.push_back(i);
		}
	}

	//��δ��Ǽ��������tracks��
	if (not_assigned_detections.size() != 0)
	{
		for (int i = 0; i < not_assigned_detections.size(); i++)
		{
			CTrack* tr = new CTrack(var.detections[not_assigned_detections[i]], this->parameter.dt, this->parameter.Accel_noise_mag);
			tr->track_id = this->parameter.NextTrackID;
			tr->num_frames = 0;
			this->parameter.NextTrackID++;
			tracks2.push_back(tr);
		}
	}

	//���ÿ������˲�����Ԥ�������
	for (int i = 0; i<var.assignment.size(); i++)
	{
		//ͨ��ǰ���ʼ���Ŀ�����������ֱ�ӵ���opencv�Դ��ĺ�������Ԥ��
		tracks2[i]->KF->GetPrediction();
		if (var.assignment[i] != -1)//��ƥ��
		{
			tracks2[i]->skipped_frames = 0;//��ǰ֡�Ѽ�⵽
			//ֱ�ӽ���⵽��ֵ��ΪԤ��ֵ
			tracks2[i]->prediction = tracks2[i]->KF->Update(var.detections[var.assignment[i]], 1);
		}
		else//δƥ��
		{
			//ʹ�ÿ������˲�����Ԥ��
			tracks2[i]->prediction = tracks2[i]->KF->Update(cv::Point2f(0, 0), 0);
			tracks2[i]->prediction.y += 3;
			tracks2[i]->pre_num++;
		}
		//if (tracks[i]->trace.size()>this->parameter.max_trace_length)//�ﵽ�켣��������
		//{
		//	tracks[i]->trace.erase(tracks[i]->trace.begin(), tracks[i]->trace.end() - this->parameter.max_trace_length);
		//}
		size_t tmp = (tracks2[i]->num_frames++);//��¼֡��
		tracks2[i]->frames_num.push_back(tmp);
		tracks2[i]->trace.push_back(tracks2[i]->prediction);//��¼�ù켣����һ���ֵ
		tracks2[i]->traceY.push_back(tracks2[i]->prediction.y);
		tracks2[i]->traceX.push_back(tracks2[i]->prediction.x);
		tracks2[i]->KF->LastResult = tracks2[i]->prediction;//�������˲��ĵ�ǰ״̬��¼
	}
	//var.is_old.clear();
	//UpdateModel2_end_Sig();
	return;
}
//�������ܣ����������ǰ֡ͼƬ�������ٵ����˿򣬸��ٽ������
//void UpdateModel2(pDoc->tarobj, pDoc->nowframe, pDoc->tarobj.track_rect, pDoc->mDetectObjects);
//��һ�鲻�Ǹ߿������õ�
void CTracker::UpdateModel3(CObjectRect var, cv::Mat frame, CvRect &track_rect, std::vector<DetectResults> &mDetectObjects)
{
	if (var.detections.size() == 0 && tracks.size() == 0)
	{
		//�źŻ���ʵ�ִ���
		//UpdateModel_end_Sig();
		return;
	}
	//if (var.detections.size() == 0)
	//{
	//	cv::Mat dst2;
	//	dst2 = cv::cvarrToMat(last_frame);
	//	if (dst2.empty())
	//	{
	//		UpdateModel2_end_Sig();
	//		return;
	//	}
	//	track_rect = rect;

	//	//UpdateModel2_end_Sig();
	//	return;
	//}
	std::vector<int> assignment = var.assignment;
	std::vector<int> not_assigned_tracks = var.not_assigned_tracks;
	std::vector< std::vector<double> > Cost = var.Cost;
	std::vector<cv::Point2f> detections = var.detections;
	//Mat frame = var.frame;
	//vector<Mat>imgs = var.imgs;
	/*IplImage temp = frame;
	IplImage *show = cvCloneImage(&temp);*/
	//�ж�δƥ���׷�ٶ����Լ��Ƿ�ȱ֡
	for (int i = 0; i<assignment.size(); i++)
	{
		if (assignment[i] != -1)//��ƥ�䵽�켣
		{
			if (Cost[i][assignment[i]]>this->parameter.dist_thres)//�����������ֵ
			{
				assignment[i] = -1;
				not_assigned_tracks.push_back(i);
			}
		}
		else
		{
			tracks[i]->skipped_frames++;
		}
	}

	for (int i = 0; i < tracks.size(); i++)
	{
		tracks[i]->num_frames++;

		//�ж��Ƿ�����֡��������ֵ������켣��������>��ֵ���ж�Ϊ�߿�������󣬱�����mDetectObjects�У�����tracks��ɾȥĿ��
		if (tracks[i]->skipped_frames > this->parameter.maximum_allowed_skipped_frames)
		{
			//����߿��������
			if (tracks[i]->trace.size() > this->parameter.min_frame_num){
				DetectResults temp;// *tracks[i];
				temp.trace = tracks[i]->trace;
				//temp.m_img = tracks[i]->m_img;
				temp.DetectID = tracks[i]->track_id;
				temp.skipped_frames = tracks[i]->skipped_frames;
				temp.frames_num = tracks[i]->frames_num;
				//temp.frame_num = tracks[i]->frame_num;//��Ƶ����֡��
				temp.traceY = tracks[i]->traceY;
				//this->mDetectObjects.push_back(temp);

				mDetectObjects.push_back(temp);
			}
			delete tracks[i];
			tracks.erase(tracks.begin() + i);
			assignment.erase(assignment.begin() + i);
			i--;
		}
	}
	//����������˶��켣ȥ����������Ķ���
	for (int i = 0; i < tracks.size(); i++)
	{
		if (tracks[i]->trace.size()>10)//&& tracks[i]->trace.size()<15)
		{
			cv::Point2d P1, P2, P3, P4;
			P4 = *(tracks[i]->trace.end() - 1);
			P3 = *(tracks[i]->trace.end() - 2);
			P2 = *(tracks[i]->trace.end() - 3);
			P1 = *(tracks[i]->trace.end() - 4);
			if (P1.y >= P2.y || P2.y >= P3.y || P3.y >= P4.y)
				//if (P1.y >= P2.y || P2.y >= P3.y || P3.y >= P4.y || (fabs(P1.y - P2.y) <10 && fabs(P2.y - P3.y) <10 && fabs(P3.y - P4.y) <10&& fabs(fabs(P2.y - P3.y) - fabs(P1.y - P2.y))<2 && fabs(fabs(P3.y - P4.y) - fabs(P2.y - P3.y))<2))
				//if ((fabs(P1.y - P2.y)<2 && fabs(P2.y - P3.y)<2) || (fabs(P2.y - P3.y)<2 && fabs(P3.y - P4.y)<2) || (fabs(P1.y - P2.y)<2 && fabs(P3.y - P4.y)<2))
				//if ((fabs(P1.y - P2.y)<5 && fabs(P2.y - P3.y)<5) || (fabs(P2.y - P3.y)<5 && fabs(P3.y - P4.y)<5) || (fabs(P1.y - P2.y)<5 && fabs(P3.y - P4.y)<5))
				//if ((fabs(P1.y - P2.y)<2 && fabs(P2.y - P3.y)<2 && fabs(P2.y - P3.y)<2))
			{
				if (tracks[i]->trace.size() > this->parameter.min_frame_num){
					DetectResults temp;// *tracks[i];
					temp.trace = tracks[i]->trace;
					//temp.m_img = tracks[i]->m_img;
					temp.DetectID = tracks[i]->track_id;
					temp.skipped_frames = tracks[i]->skipped_frames;
					temp.traceY = tracks[i]->traceY;
					temp.frames_num = tracks[i]->frames_num;

					//temp.frame_num = tracks[i]->frame_num;//��Ƶ����֡��
					//this->mDetectObjects.push_back(temp);
					mDetectObjects.push_back(temp);
				}
				delete tracks[i];
				tracks.erase(tracks.begin() + i);
				assignment.erase(assignment.begin() + i);
				i--;
			}
		}
	}
	//if (has_old == true)
	//{
	//	/*cv::Mat dst2;
	//	dst2 = cv::cvarrToMat(show);
	//	cv::resize(dst2, dst2, cv::Size(), 0.5, 0.5);
	//	cv::imshow("aa", dst2);*/
	//	//cvShowImage("aa", show);
	//	last_frame = show;
	//	has_old = false;
	//	track_rect = rect;
	//}
	//else
	//{
	//	track_rect = rect;//��ֹ���򱣴���һ����
	//}
	//cvWaitKey(1);

	//����Ƿ���δ��ǵļ�����
	std::vector<int> not_assigned_detections;
	std::vector<int>::iterator it;
	for (int i = 0; i < detections.size(); i++)
	{
		it = find(assignment.begin(), assignment.end(), i);
		if (it == assignment.end())
		{
			not_assigned_detections.push_back(i);
		}
	}

	//��δ��Ǽ��������tracks��
	if (not_assigned_detections.size() != 0)
	{
		for (int i = 0; i < not_assigned_detections.size(); i++)
		{
			CTrack* tr = new CTrack(detections[not_assigned_detections[i]], this->parameter.dt, this->parameter.Accel_noise_mag);
			tr->track_id = this->parameter.NextTrackID;
			this->parameter.NextTrackID++;

			//��¼����������ܳ�
			tr->width = var.width[not_assigned_detections[i]];
			tr->height = var.height[not_assigned_detections[i]];
			tr->area = tr->width*tr->height;
			tr->cir = 2 * tr->width + 2 * tr->height;


			tracks.push_back(tr);
		}
	}

	//���ÿ������˲�����Ԥ�������
	for (int i = 0; i<assignment.size(); i++)
	{
		//ͨ��ǰ���ʼ���Ŀ�����������ֱ�ӵ���opencv�Դ��ĺ�������Ԥ��
		tracks[i]->KF->GetPrediction();
		if (assignment[i] != -1)//��ƥ��
		{
			tracks[i]->skipped_frames = 0;//��ǰ֡�Ѽ�⵽
			//ֱ�ӽ���⵽��ֵ��ΪԤ��ֵ
			tracks[i]->prediction = tracks[i]->KF->Update(detections[assignment[i]], 1);



			//��¼����������ܳ�
			tracks[i]->width = var.width[var.assignment[i]];
			tracks[i]->height = var.height[var.assignment[i]];
			tracks[i]->area = tracks[i]->width*tracks[i]->height;
			tracks[i]->cir = 2 * tracks[i]->width + 2 * tracks[i]->height;



		}
		else//δƥ��
		{
			//ʹ�ÿ������˲�����Ԥ��
			tracks[i]->prediction = tracks[i]->KF->Update(cv::Point2f(0, 0), 0);
			tracks[i]->prediction.y += 3;
			//tracks[i]->pre_num++;
		}

		if (tracks[i]->trace.size()>this->parameter.max_trace_length)//�ﵽ�켣��������
		{
			tracks[i]->trace.erase(tracks[i]->trace.begin(), tracks[i]->trace.end() - this->parameter.max_trace_length);
		}
		tracks[i]->num_frames++;//��¼֡��
		tracks[i]->frames_num.push_back(tracks[i]->num_frames);
		//tracks[i]->frame_num.push_back(var.frame_num);//��Ƶ����֡��
		tracks[i]->trace.push_back(tracks[i]->prediction);//��¼�ù켣����һ���Ԥ��ֵ
		tracks[i]->traceY.push_back(tracks[i]->prediction.y);
		tracks[i]->traceX.push_back(tracks[i]->prediction.x);
		tracks[i]->KF->LastResult = tracks[i]->prediction;//�������˲��ĵ�ǰ״̬��¼
	}
	//var.is_old.clear();
	//UpdateModel2_end_Sig();
	return;
}


//float CTracker::similarity(Mat &img_1, Mat & img_2)
//{
//	return 0.5;
//}
void CTracker::UpdateModel6(CObjectRect &var, cv::Mat frame)
{
	////�����һ֡��ƥ������Ľ��
	var.Cost.clear();
	var.assignment.clear();
	var.not_assigned_tracks.clear();
	if (var.detections.size() == 0 && tracks3.size() == 0)
	{
		return;
	}
	//std::vector<cv::Point2f>detections = var.detections;
	double frame_num = var.frame_num;
	//��׷��Ŀ��Ϊ�յ�ʱ�򣬽�detections����tracks��
	if (tracks3.size() == 0)
	{
		this->parameter.NextTrackID = 1;//Ĭ�ϵ�һ��ΪIDΪ1
		for (int i = 0; i < var.detections.size(); i++)
		{
			CTrack* tr = new CTrack(var.detections[i], this->parameter.dt, this->parameter.Accel_noise_mag);
			tr->track_id = this->parameter.NextTrackID;
			tr->num_frames = 0;
			this->parameter.NextTrackID++;
			tracks3.push_back(tr);
		}
	}

	int N = tracks3.size();//�켣�ĸ���
	int M = var.detections.size();//�������ĸ���
	std::vector<std::vector<double> > Cost(N, std::vector<double>(M));//ͳ�Ƶ�ǰ����������׷�������ľ���
	//double dist;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cv::Point2d diff = (tracks3[i]->prediction - var.detections[j]);//����ù켣����һ�����Ԥ��λ��

			Cost[i][j] = sqrtf(diff.x*diff.x + diff.y*diff.y);//Ԥ��λ����ʵ��λ�õľ����
			/*if (tracks[i]->area>(var.width[j] * var.height[j]))
			{

			}*/
			//Cost[i][j] = Cost[i][j] * (fabs(tracks[i]->area - (var.width[j] * var.height[j]))) / (var.width[j] * var.height[j]);
			Cost[i][j] = Cost[i][j] * ((fabs(tracks3[i]->area - (var.width[j] * var.height[j]))) / (var.width[j] * var.height[j] + tracks3[i]->area));
			//std::cout << Cost[i][j] << "  " << var.width[j] * var.height[j] << "  " << tracks3[i]->area << std::endl;
			//Cost[i][j] = Cost2[i][j] * ((fabs(tracks[i]->area - (var.width[j] * var.height[j]))) / (var.width[j] * var.height[j] * tracks[i]->area));
		}
	}
	//detections.clear();
	var.Cost = Cost;
	Cost.clear();
	std::vector<int> assignment;
	std::vector<int> not_assigned_tracks;
	var.assignment = assignment;
	var.not_assigned_tracks = not_assigned_tracks;
	var.detections = var.detections;
	var.frame_num = var.frame_num;
	return;
}
//�������㷨����ƥ�䣬����һ֡ͼƬ�м�⵽���˶�����ƥ�䵽��Ӧ�Ĺ켣
//AssignmentProblemSolver APS;
//vector<int> assignment;
//vector<int> n c     zxot_assigned_tracks;
////������������Ϊ���ӣ�����Ҳ���������޸ģ����ܾ��ǰ�����ƥ�䵽�켣��
//APS.Solve(Cost, assignment, AssignmentProblemSolver::optimal);

//�������ܣ�����������ٽ������
void CTracker::UpdateModel7(CObjectRect var, std::vector<DetectResults> &mDetectObjects)
{
	if (var.detections.size() == 0 && tracks3.size() == 0)
	{
		return;
	}
	//�ж�δƥ���׷�ٶ����Լ��Ƿ�ȱ֡
	for (int i = 0; i<var.assignment.size(); i++)
	{
		if (var.assignment[i] != -1)//��ƥ�䵽�켣
		{
			//if ((var.Cost[i][var.assignment[i]] / ((fabs(tracks[i]->area - (var.width[var.assignment[i]] * var.height[var.assignment[i]]))) / (var.width[var.assignment[i]] * var.height[var.assignment[i]])))>this->parameter.dist_thres)//�����������ֵ
			if ((tracks3[i]->traceX.size()>=2&&fabs(tracks3[i]->traceX[tracks3[i]->traceX.size() - 1] - var.detections[var.assignment[i]].x)>7 * fabs(tracks3[i]->traceX[tracks3[i]->traceX.size() - 1] - tracks3[i]->traceX[tracks3[i]->traceX.size() - 2])) || (var.Cost[i][var.assignment[i]] / ((fabs(tracks3[i]->area - (var.width[var.assignment[i]] * var.height[var.assignment[i]]))) / (var.width[var.assignment[i]] * var.height[var.assignment[i]] + tracks3[i]->area)))>this->parameter.dist_thres)//�����������ֵ
			{
				var.assignment[i] = -1;
				var.not_assigned_tracks.push_back(i);
			}
			else
			{
				//if (((fabs(tracks[i]->area - (var.width[var.assignment[i]] * var.height[var.assignment[i]]))) / (var.width[var.assignment[i]] * var.height[var.assignment[i]])) < 3)
				tracks3[i]->area = (var.width[var.assignment[i]] * var.height[var.assignment[i]]);
			}
		}
		else
		{
			tracks3[i]->skipped_frames++;
		}
	}
	std::vector<CTrack*>::iterator ittrack;
	std::vector<int>::iterator itint;
	for (ittrack = tracks3.begin(), itint = var.assignment.begin(); ittrack != tracks3.end() && itint != var.assignment.end();)// int i = 0; i < tracks.size(); i++)
	{
		//�ж��Ƿ�����֡��������ֵ������켣��������>��ֵ���ж�Ϊ�߿�������󣬱�����mDetectObjects�У�����tracks��ɾȥĿ��
		if ((*ittrack)->skipped_frames > this->parameter.maximum_allowed_skipped_frames)
		{
			//����߿��������
			if ((*ittrack)->trace.size() > (this->parameter.min_frame_num + (*ittrack)->skipped_frames)){
				DetectResults temp;// *tracks[i];
				temp.trace = (*ittrack)->trace;
				temp.DetectID = (*ittrack)->track_id;
				temp.skipped_frames = (*ittrack)->skipped_frames;
				temp.frames_num = (*ittrack)->frames_num;
				temp.traceY = (*ittrack)->traceY;
				temp.traceX = (*ittrack)->traceX;
				temp.pre_num = (*ittrack)->pre_num;
				temp.frame_height = var.frame_height;
				temp.frame_width = var.frame_width;
				if (judge(mDetectObjects, temp) == 0)
					mDetectObjects.push_back(temp);
			}
			delete (*ittrack);
			ittrack = tracks3.erase(ittrack);
			itint = var.assignment.erase(itint);
		}
		else
		{
			ittrack++;
			itint++;
		}
	}

	//����������˶��켣ȥ����������Ķ���
	for (ittrack = tracks3.begin(), itint = var.assignment.begin(); ittrack != tracks3.end() && itint != var.assignment.end();)//int i = 0; i < tracks.size(); i++)
	{
		if ((*ittrack)->trace.size()>5)//&& tracks[i]->trace.size()<15)
		{
			cv::Point2d P1, P2, P3, P4;
			P4 = *((*ittrack)->trace.end() - 1);
			P3 = *((*ittrack)->trace.end() - 2);
			P2 = *((*ittrack)->trace.end() - 3);
			P1 = *((*ittrack)->trace.end() - 4);
			//if (P1.y >= P2.y || P2.y >= P3.y || P3.y >= P4.y)
			if (1)
				//if (P1.y >= P2.y || P2.y >= P3.y || P3.y >= P4.y || (fabs(P1.y - P2.y) <10 && fabs(P2.y - P3.y) <10 && fabs(P3.y - P4.y) <10&& fabs(fabs(P2.y - P3.y) - fabs(P1.y - P2.y))<2 && fabs(fabs(P3.y - P4.y) - fabs(P2.y - P3.y))<2))
				//if ((fabs(P1.y - P2.y)<2 && fabs(P2.y - P3.y)<2) || (fabs(P2.y - P3.y)<2 && fabs(P3.y - P4.y)<2) || (fabs(P1.y - P2.y)<2 && fabs(P3.y - P4.y)<2))
				//if ((fabs(P1.y - P2.y)<5 && fabs(P2.y - P3.y)<5) || (fabs(P2.y - P3.y)<5 && fabs(P3.y - P4.y)<5) || (fabs(P1.y - P2.y)<5 && fabs(P3.y - P4.y)<5))
				//if ((fabs(P1.y - P2.y)<2 && fabs(P2.y - P3.y)<2 && fabs(P2.y - P3.y)<2))
			{
				if ((*ittrack)->trace.size() > (this->parameter.min_frame_num + (*ittrack)->skipped_frames)){
					DetectResults temp;// *tracks[i];
					temp.trace = (*ittrack)->trace;
					temp.DetectID = (*ittrack)->track_id;
					temp.skipped_frames = (*ittrack)->skipped_frames;
					temp.traceY = (*ittrack)->traceY;
					temp.traceX = (*ittrack)->traceX;
					temp.frames_num = (*ittrack)->frames_num;
					temp.pre_num = (*ittrack)->pre_num;
					temp.frame_height = var.frame_height;
					temp.frame_width = var.frame_width;
					if (judge(mDetectObjects, temp) == 0)
						mDetectObjects.push_back(temp);
				}
				delete (*ittrack);
				ittrack = tracks3.erase(ittrack);
				itint = var.assignment.erase(itint);
			}
			else
			{
				ittrack++;
				itint++;
			}
		}
		else
		{
			ittrack++;
			itint++;
		}
	}

	//����Ƿ���δ��ǵļ�����
	std::vector<int> not_assigned_detections;
	std::vector<int>::iterator it;
	for (int i = 0; i < var.detections.size(); i++)
	{
		it = find(var.assignment.begin(), var.assignment.end(), i);
		if (it == var.assignment.end())
		{
			not_assigned_detections.push_back(i);
		}
	}

	//��δ��Ǽ��������tracks��
	if (not_assigned_detections.size() != 0)
	{
		for (int i = 0; i < not_assigned_detections.size(); i++)
		{
			CTrack* tr = new CTrack(var.detections[not_assigned_detections[i]], this->parameter.dt, this->parameter.Accel_noise_mag);
			tr->track_id = this->parameter.NextTrackID;
			tr->num_frames = 0;
			this->parameter.NextTrackID++;

			//��¼����������ܳ�
			tr->width = var.width[not_assigned_detections[i]];
			tr->height = var.height[not_assigned_detections[i]];
			tr->area = tr->width*tr->height;
			tr->cir = 2 * tr->width + 2 * tr->height;


			tracks3.push_back(tr);
		}
	}

	//���ÿ������˲�����Ԥ�������
	for (int i = 0; i<var.assignment.size(); i++)
	{
		//ͨ��ǰ���ʼ���Ŀ�����������ֱ�ӵ���opencv�Դ��ĺ�������Ԥ��
		tracks3[i]->KF->GetPrediction();
		if (var.assignment[i] != -1)//��ƥ��
		{
			tracks3[i]->skipped_frames = 0;//��ǰ֡�Ѽ�⵽
			//ֱ�ӽ���⵽��ֵ��ΪԤ��ֵ
			tracks3[i]->prediction = tracks3[i]->KF->Update(var.detections[var.assignment[i]], 1);

			//��¼����������ܳ�
			tracks3[i]->width = var.width[var.assignment[i]];
			tracks3[i]->height = var.height[var.assignment[i]];
			//tracks[i]->area = tracks[i]->width*tracks[i]->height;
			tracks3[i]->cir = 2 * tracks3[i]->width + 2 * tracks3[i]->height;
		}
		else//δƥ��
		{
			//ʹ�ÿ������˲�����Ԥ��
			tracks3[i]->prediction = tracks3[i]->KF->Update(cv::Point2f(0, 0), 0);
			tracks3[i]->pre_num++;
			tracks3[i]->prediction.y += 3;
		}
		//if (tracks[i]->trace.size()>this->parameter.max_trace_length)//�ﵽ�켣��������
		//{
		//	tracks[i]->trace.erase(tracks[i]->trace.begin(), tracks[i]->trace.end() - this->parameter.max_trace_length);
		//}
		size_t tmp = (tracks3[i]->num_frames++);//��¼֡��
		tracks3[i]->frames_num.push_back(tmp);
		tracks3[i]->trace.push_back(tracks3[i]->prediction);//��¼�ù켣����һ���ֵ
		tracks3[i]->traceY.push_back(tracks3[i]->prediction.y);
		tracks3[i]->traceX.push_back(tracks3[i]->prediction.x);
		tracks3[i]->KF->LastResult = tracks3[i]->prediction;//�������˲��ĵ�ǰ״̬��¼
	}
	//var.is_old.clear();
	//UpdateModel2_end_Sig();
	return;
}