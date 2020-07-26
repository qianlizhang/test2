#ifndef _UWC_H
#define _UWC_H

#include "common.h"
#include "UWC4000.h"
//#include "stdafx.h"

#define UWC_8blocks		0
#define UWC6045			1
#define UWC6163			2
#define UWC6100			3
#define UWC6016			4



class uwc : public CBaseProcessLogic
{
public:
	unsigned char ucInput[100];
	unsigned char ucOutput[100];
	unsigned char *ucp;
private:
	long uchar_to_long(unsigned char *puchar)
	{
		long i = 0;
		i = *puchar++;
		i <<= 8;
		i += *puchar++;
		i <<= 8;
		i += *puchar++;
		i <<= 8;
		return i + *puchar;
	}
	void long_to_uchar(long data, unsigned char *puchar)
	{
		puchar += 3;
		*puchar-- = (unsigned char)data;
		data >>= 8;
		*puchar-- = (unsigned char)data;
		data >>= 8;
		*puchar-- = (unsigned char)data;
		*puchar = (unsigned char)(data >> 8);
	}

	void uint_to_uchar(unsigned int data, unsigned char *puchar)
	{
		puchar++;
		*puchar-- = (unsigned char)data;
		data >>= 8;
		*puchar = (unsigned char)data;
	}

	unsigned int uchar_to_uint(unsigned char *puchar)
	{
		unsigned int  i = 0;
		i = *puchar++;
		i <<= 8;
		return i + *puchar;
	}
public:

	//NO1.获取光源解决方案属性(分环数, 分区数, 颜色种数, 升降速度)
	long uwc4000based_get_light_solution(char *solution_identify, long *rings, long *blocks, long *colors, long *speed);

	//NO2. 不超过40个分区的单色环形光源调光, 适用范围:8区(UWC4003/UWC6008/用户自制8分区)、16区(2环8相UWC6016)、40区(5环8相UWC6045)
	long uwc4000based_no_more_than_40_area_set_light(unsigned char *light_array);

	//NO3. 5环8相4色(UWC6163)调光
	long uwc4000based_6163_set_light(unsigned char *light_array);

	//NO4. 3环8相4色电动升降(UWC6100) 调光
	long uwc4000based_6100_set_light(unsigned char *light_array);

	//NO5. UWC6100 回原点, 即升到顶部限位开关处
	long uwc4000based_6100_go_home(long speed);

	//NO6. UWC6100 Jog运动, 即采用鼠标拖拽或点动箭头按钮, 使光源升降运动,速度设置为0即为停止
	long uwc4000based_6100_jog_move(long speed);

	//NO7. UWC6100 PTP运动, 命令光源移动到某处
	long uwc4000based_6100_move_to(long speed, long target_pos);

	//NO8. 读取UWC6100 状态信息
	long uwc4000based_6100_get_msg(long *pos, long *status);

	//NO9. 停车命令
	long uwc4000based_6100_stop(long mode);



};

#endif