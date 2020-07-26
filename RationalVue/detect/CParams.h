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
//	@biref		:	类的各种初始化参数
//	@author		:	
//===============================================================================
//定义摄像机参数
//200W: 分辨率：27（1920 * 1080） 码率：25（4096K）
//100W: 分辨率：19（1280 * 720） 码率：23（2048K）
//帧率：14（15帧）17（25帧）
typedef struct CAMERA_INFO {
	BYTE     byStreamType = 0;  //码流类型
	BYTE     byResolution = 0xff;  //分辨率19-1280*720; 27-1920*1080; 30-2048*1536; 0xff-Auto(使用当前码流分辨率)
	BYTE     byBitrateType;
	BYTE     byPicQuality;
	DWORD    dwVideoBitrate = 0xfffffffe;  //视频码率
	DWORD    dwVideoFrameRate = 0xfffffffe; //帧率
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

//固定参数配置
class CParams
{
public:

	float threshold;
	bool is_day = true;			//标志是否是夜晚
	///图片的大小
	int frame_width = 2048;		//图片的宽度
	int frame_height = 1536;	//图片的高度
	/// 运动对象检测算法ViBe参数
	int  NUM_SAMPLES = 20;		//每个像素点的样本个数
	int  MIN_MATCHES = 2;		//#min指数
	int  RADIUS = 20;			//Sqthere半径
	int  SUBSAMPLE_FACTOR = 12;	//子采样概率
	int  NUM = 2500;
	/// 动态检测参数
	int maxAreaSize = 1600;		//检测物体面积最大阈值
	int minAreaSize = 10;		//检测物体面积最小阈值
	int maxLenSize = 300;		//检测物体周长最大阈值
	int minLenSize = 10;		//检测物体周长最小阈值
	/// 跟踪模块参数
	float dt = 0.35;			//两次滤波之间的时间间隔，dt太大精度差，而且可能发散，线性模型无法满足
	float Accel_noise_mag = 3;	//噪音
	double dist_thres = 100;	//阈值设置
	int maximum_allowed_skipped_frames = 7;//最大允许跳过的检测视频帧
	int max_trace_length = 100;	//最大追踪的长度
	int min_frame_num = 9;		//高空抛物检测的最小帧数
	size_t NextTrackID = 1;
	/// 轨迹拟合参数
	int fla_thre = 9;			//统计已经检测到点的个数阈值
	int slow_thre = 15;			//记录减速情况下的阈值，两轨迹点之前的距离小于此数值时才计算是否是减速
	int mean_thre = 15;			//记录匀速情况下的阈值，两轨迹点之前的距离小于此数值时才计算是否是匀速
	float overlap_ratio = 0.3;  //重复点所占比例阈值
	float mean_ratio = 0.4;		//匀速所占比例阈值
	float slow_ratio = 0.3;		//减速所占比例阈值

	int lag_frames = 50;		//延迟判断的帧数

	double first_minus_thre = 30;//
	///曲线拟合后的阈值设置
	float min_fac = 0.05;		//拟合轨迹加速度最小阈值
	float max_fac = 1;			//拟合轨迹加速度最大阈值
	//float R_thre = 0.985;		//拟合R方的阈值
	float R_thre = 0.939;		//拟合R方的阈值
	float RMSE_thre = 20;		//拟合曲线均方根阈值
	float RSS_thre = 1;

	//相机参数
	double fpsRate;
	CAMERA_INFO camera_info;
	//相机登录参数


	ControlParam ctrlParam;


	//存储参数设置,保存视频的参数设置
	int frame_rate = 25; //生成视频的帧率
	int cache_duration = 8;//缓存的时长（单位秒）	
	std::string cache_path = "../../VedioSave/cache/"; //缓存路径（不是文件名）
	std::string save_path = "../../VedioSave/";
	//std::string save_path = "../VedioSave/";
	//回归测试
	int vars = 0;
	cv::Mat resultShow;

	int lowestFloor = 0;//相机拍摄范围内的最低楼层，默认为1
	int floorNum = 5;//一个相机拍摄的总楼层数
	int Pfloor_height = 3;//一层楼的高度
	int floor_Height;//此相机拍摄的楼层的高度
	int floor_distance = 25;//此相机距离楼层的距离
	float Tran_ratio;//相机的倾斜角度对应的高度转换比例

	bool FirstMsk = true;//是否是第一帧
	bool bufferflag = true;//false:不缓冲，true：缓冲
	bool Tranflag = true;//false:不网络传输，true：传输
	bool testflag = true;//0:实时测试，1：本地测试
};