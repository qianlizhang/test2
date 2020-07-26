#pragma once
#include <Windows.h>
//#include <minwindef.h>
#include <opencv2\opencv.hpp>
#include "qstring.h"
#include "QMessageBox"
#include "QDateTime"
#include "QFileDialog"
#include "ControlParam.h"

# pragma execution_character_set("utf-8")

//==============================================================================
//	@name		:	Params
//	@biref		:	��ĸ��ֳ�ʼ������
//	@author		:	
//===============================================================================
//�������������
//200W: �ֱ��ʣ�27��1920 * 1080�� ���ʣ�25��4096K��
//100W: �ֱ��ʣ�19��1280 * 720�� ���ʣ�23��2048K��
//֡�ʣ�14��15֡��17��25֡��
typedef struct CAMERA_INFO {
	BYTE     byStreamType = 0;  //��������
	BYTE     byResolution = 0xff;  //�ֱ���19-1280*720; 27-1920*1080; 30-2048*1536; 0xff-Auto(ʹ�õ�ǰ�����ֱ���)
	BYTE     byBitrateType;
	BYTE     byPicQuality;
	DWORD    dwVideoBitrate = 0xfffffffe;  //��Ƶ����
	DWORD    dwVideoFrameRate = 0xfffffffe; //֡��
	WORD     wIntervalFrameI;
	BYTE     byIntervalBPFrame;
	BYTE     byres1;
	BYTE     byVideoEncType;
	BYTE     byAudioEncType;
	BYTE     byVideoEncComplexity;
	BYTE     byEnableSvc;
	BYTE     byFormatType;
	BYTE     byAudioBitRate;
	BYTE     bySteamSmooth;
	BYTE     byAudioSamplingRate;
	BYTE     bySmartCodec;
	BYTE     byres;
	WORD     wAverageVideoBitrate;
	BYTE	 begintime = 6;
	BYTE	 begintimemin = 0;
	BYTE	 begintimesec = 0;
	BYTE	 endtime = 18;
	BYTE	 endtimemin = 0;
	BYTE	 endtimesec = 0;
}CAMERA_INFO, *LPCAMERA_INFO;

//�̶���������
class CParams
{
public:

	float threshold;
	bool is_day = true;			//��־�Ƿ���ҹ��
	///ͼƬ�Ĵ�С
	int frame_width = 2048;		//ͼƬ�Ŀ��
	int frame_height = 1536;	//ͼƬ�ĸ߶�
	/// �˶��������㷨ViBe����
	int  NUM_SAMPLES = 20;		//ÿ�����ص����������
	int  MIN_MATCHES = 2;		//#minָ��
	int  RADIUS = 20;			//Sqthere�뾶
	int  SUBSAMPLE_FACTOR = 12;	//�Ӳ�������
	int  NUM = 2500;
	/// ��̬������
	int maxAreaSize = 1600;		//���������������ֵ
	int minAreaSize = 10;		//������������С��ֵ
	int maxLenSize = 300;		//��������ܳ������ֵ
	int minLenSize = 10;		//��������ܳ���С��ֵ
	/// ����ģ�����
	float dt = 0.35;			//�����˲�֮���ʱ������dt̫�󾫶Ȳ���ҿ��ܷ�ɢ������ģ���޷�����
	float Accel_noise_mag = 3;	//����
	double dist_thres = 100;	//��ֵ����
	int maximum_allowed_skipped_frames = 7;//������������ļ����Ƶ֡
	int max_trace_length = 100;	//���׷�ٵĳ���
	int min_frame_num = 9;		//�߿����������С֡��
	size_t NextTrackID = 1;
	/// �켣��ϲ���
	int fla_thre = 9;			//ͳ���Ѿ���⵽��ĸ�����ֵ
	int slow_thre = 15;			//��¼��������µ���ֵ�����켣��֮ǰ�ľ���С�ڴ���ֵʱ�ż����Ƿ��Ǽ���
	int mean_thre = 15;			//��¼��������µ���ֵ�����켣��֮ǰ�ľ���С�ڴ���ֵʱ�ż����Ƿ�������
	float overlap_ratio = 0.3;  //�ظ�����ռ������ֵ
	float mean_ratio = 0.4;		//������ռ������ֵ
	float slow_ratio = 0.3;		//������ռ������ֵ

	int lag_frames = 50;		//�ӳ��жϵ�֡��

	double first_minus_thre = 30;//
	///������Ϻ����ֵ����
	float min_fac = 0.05;		//��Ϲ켣���ٶ���С��ֵ
	float max_fac = 1;			//��Ϲ켣���ٶ������ֵ
	//float R_thre = 0.985;		//���R������ֵ
	float R_thre = 0.939;		//���R������ֵ
	float RMSE_thre = 20;		//������߾�������ֵ
	float RSS_thre = 1;

	//�������
	double fpsRate;
	CAMERA_INFO camera_info;
	//�����¼����


	ControlParam ctrlParam;


	//�洢��������,������Ƶ�Ĳ�������
	int frame_rate = 25; //������Ƶ��֡��
	int cache_duration = 8;//�����ʱ������λ�룩	
	std::string cache_path = "../../VedioSave/cache/"; //����·���������ļ�����
	std::string save_path = "../../VedioSave/";
	//std::string save_path = "../VedioSave/";
	//�ع����
	int vars = 0;
	cv::Mat resultShow;

	int lowestFloor = 0;//������㷶Χ�ڵ����¥�㣬Ĭ��Ϊ1
	int floorNum = 5;//һ������������¥����
	int Pfloor_height = 3;//һ��¥�ĸ߶�
	int floor_Height;//����������¥��ĸ߶�
	int floor_distance = 25;//���������¥��ľ���
	float Tran_ratio;//�������б�Ƕȶ�Ӧ�ĸ߶�ת������

	bool FirstMsk = true;//�Ƿ��ǵ�һ֡
	bool bufferflag = true;//false:�����壬true������
	bool Tranflag = true;//false:�����紫�䣬true������
	bool testflag = true;//0:ʵʱ���ԣ�1�����ز���
};