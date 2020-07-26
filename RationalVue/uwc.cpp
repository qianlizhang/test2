#include "uwc.h"

long uwc::uwc4000based_get_light_solution(char *solution_identify, long *rings, long *blocks, long *colors, long *speed)
{
	long rtn, light_ID, l_flag;
	rtn = uwc4000_super_command(208, 0, 14, ucInput, ucOutput);

	l_flag = 1;
	light_ID = ucOutput[6];//Identify of the light device. If you want, you can modify this API to return ID directly.
	*rings = ucOutput[0];
	*blocks = ucOutput[1];
	*colors = ucOutput[2];

	*speed = 0;
	switch (light_ID) {
	case UWC_8blocks:
		strcpy(solution_identify, "UWC_8blocks");
		break;
	case UWC6045:
		strcpy(solution_identify, "UWC6045");
		break;
	case UWC6163:
		strcpy(solution_identify, "UWC6163");
		break;
	case UWC6100:
		strcpy(solution_identify, "UWC6100");

		uint_to_uchar(500, ucInput);
		uwc4000_super_command(78, 2, 4, ucInput, ucOutput);
		*speed = uchar_to_long(ucOutput);
		break;
	case UWC6016:
		strcpy(solution_identify, "UWC6016");
		break;
	default:
		l_flag = 0;
		strcpy(solution_identify, "Undefined Lights");
		break;
	}

	if (l_flag) {
		;
	}
	else {
		*rings = 1;
		*blocks = 1;
		*colors = 1;
	}


	return rtn;
}

/***********************************************************************
   方案一: UWC4000(内置8区)/UWC6008(8区), 或者,与UWC4003/UWC6008兼容的客户自制的环形光源
   方案二: UWC6016(2环8相)
   方案三: UWC6045/UWC6043(5环8相)光源
   使用uwc4000based_not_more_then_40_area_set_light
***********************************************************************/
//亮度最大值200, 最小值0
//light_array[0]-light_array[39]:第1-第40分区, 不足40分区的以0填充
//light_array[40]:底光(contour)
//light_array[41]:同轴光(Coaxial)
//light_array[42]:激光指示(laser)
long uwc::uwc4000based_no_more_than_40_area_set_light(unsigned char *light_array)
{
	long i;
	for (i = 0; i < 45; i++)
		ucInput[i] = *light_array++;
	return uwc4000_super_command(210, 45, 1, ucInput, ucOutput);
}

/************************************************************************/
/*  方案四: UWC6163 5环8相4色光源*/
//	使用uwc4000based_6163_set_light

//!!!!!!!!!!!!!!!!!!!注意!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!注意!!!!!!!!!!!!!!!!!!!!!!!
//uwc4000based_6163_set_light的参数与原uwc6163_set_light函数参数不一样!!!

//原来:底光在数组首位, 同轴光在末尾
//现在uwc4000base:表面光在前,底光和同轴光顺序在后
/************************************************************************/

//light_array[0]-light_array[39]:   表面光第1-第40分区白色, 低编号分区在内环, 面对LED顺时针旋转
//light_array[40]-light_array[79]:  表面光第1-第40分区蓝色
//light_array[80]-light_array[119]: 表面光第1-第40分区绿色
//light_array[120]-light_array[159]:表面光第1-第40分区红色
//light_array[160]:底光(contour)
//light_array[161]:同轴光(Coaxial)
//light_array[162]:激光指示(laser)
//!!!!!!!!!!!!!!!!!!!注意!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!注意!!!!!!!!!!!!!!!!!!!!!!!
//uwc4000based_6163_set_light的参数与原uwc6163_set_light函数参数不一样!!!
long uwc::uwc4000based_6163_set_light(unsigned char *light_array)
{
	long i;
	long rtn;
	unsigned char *ucp = ucInput;

	for (i = 0; i < 40; i++)
		*ucp++ = *light_array++;

	*ucp++ = light_array[160];
	*ucp++ = light_array[161];
	*ucp++ = light_array[162];

	rtn = uwc4000_super_command(210, 45, 1, ucInput, ucOutput);

	if (0 == rtn) {
		ucp = ucInput;
		for (i = 0; i < 60; i++)
			*ucp++ = *light_array++;
		rtn += uwc4000_super_command(211, 60, 1, ucInput, ucOutput);
	}

	if (0 == rtn) {
		ucp = ucInput;
		for (i = 0; i < 60; i++)
			*ucp++ = *light_array++;
		rtn += uwc4000_super_command(212, 60, 1, ucInput, ucOutput);
	}
	return rtn;
}

/************************************************************************/
/* 方案五: UWC6100 3环8相4色电动升降光源*/
/************************************************************************/

//light_array[0]-light_array[23]:  表面光第1-第24分区白色, 低编号分区在内环, 面对LED顺时针旋转
//light_array[24]-light_array[47]: 表面光第1-第24分区蓝色
//light_array[48]-light_array[71]: 表面光第1-第24分区绿色
//light_array[72]-light_array[95]: 表面光第1-第23分区红色
//light_array[96]:底光(contour)
//light_array[97]:同轴光(Coaxial)
//light_array[98]:激光指示(laser)
long uwc::uwc4000based_6100_set_light(unsigned char *light_array)
{
	long i, j;
	long rtn;
	unsigned char *ucp = ucInput;
	unsigned char ucArray[165];
	unsigned char *ucp2 = ucArray;

	//将光源颜色排布顺序与老产品UWC6163一致

	for (i = 72, j = 0; i < 96; j++, i++)
		ucArray[j] = *(light_array + i);
	for (i = 48, j = 24; i < 72; j++, i++)
		ucArray[j] = *(light_array + i);
	for (i = 24, j = 48; i < 48; j++, i++)
		ucArray[j] = *(light_array + i);
	for (i = 0, j = 72; i < 24; j++, i++)
		ucArray[j] = *(light_array + i);

	for (i = 0; i < 40; i++)
		*ucp++ = *ucp2++;

	*ucp++ = *(light_array + 96);
	*ucp++ = *(light_array + 97);
	*ucp++ = *(light_array + 98);

	rtn = uwc4000_super_command(210, 45, 1, ucInput, ucOutput);

	if (0 == rtn) {
		ucp = ucInput;
		for (i = 0; i < 60; i++)
			*ucp++ = *ucp2++;
		rtn += uwc4000_super_command(211, 60, 1, ucInput, ucOutput);
	}

	return rtn;
}

//NO4. UWC6100 回原点, 即升到顶部限位开关处
//speed: 160-64000 设为64000时, 移动速度约为50.8mm/s
long uwc::uwc4000based_6100_go_home(long speed)
{
	long rtn;
	unsigned char *ucp = ucInput;
	*ucp++ = 4;
	if (speed > 64000)
		speed = 64000;
	else if (speed < 50) {
		speed = 50;
	}
	long_to_uchar(speed, ucp); ucp += 4;
	uint_to_uchar(0, ucp); ucp += 2;
	rtn = uwc4000_super_command(214, 7, 1, ucInput, ucOutput);
	return rtn;
}

//NO5. UWC6100 Jog运动, 即采用鼠标拖拽或点动箭头按钮, 使光源升降运动,速度设置为0即为停止
//speed: -64000 ~ 64000 设为64000时, 移动速度约为50.8mm/s
long uwc::uwc4000based_6100_jog_move(long speed)
{
	long rtn;
	unsigned char *ucp = ucInput;
	*ucp++ = 5;
	if (speed > 64000)
		speed = 64000;
	else if (speed < -64000) {
		speed = -64000;
	}
	long_to_uchar(speed, ucp); ucp += 4;
	uint_to_uchar(0, ucp); ucp += 2;
	rtn = uwc4000_super_command(214, 7, 1, ucInput, ucOutput);
	return rtn;
}

//NO6. UWC6100 PTP运动, 命令光源移动到某处; 由于原点在顶端, 因此目标位置总是小于等于0, 最小值视设备而定
//请参考uwc4000based_6100_get_msg 之 position参数
//move_speed: 50-64000, 设为64000时, 移动速度约为50.8mm/s
//target_pos: 0 ~ - 125984 (假设OEM厂商升降行程为100.00mm)
long uwc::uwc4000based_6100_move_to(long move_speed, long target_pos)
{
	long rtn;
	unsigned char *ucp = ucInput;
	*ucp++ = 6;
	if (move_speed > 64000)
		move_speed = 64000;
	else if (move_speed < 50) {
		move_speed = 50;
	}
	long_to_uchar(target_pos, ucp); ucp += 4;
	uint_to_uchar(move_speed, ucp); ucp += 2;
	rtn = uwc4000_super_command(214, 7, 1, ucInput, ucOutput);
	return rtn;
}

//NO7. 读取UWC6100 状态信息
//pos: 当前坐标位置, 回原点后, 该坐标位置总是小于等于0
//status: 升降轴运动状态, 0-运动中,1024-已停止
long uwc::uwc4000based_6100_get_msg(long *pos, long *status)
{
	long rtn;
	unsigned char *ucp = ucOutput;
	rtn = uwc4000_super_command(211, 0, 7, ucInput, ucOutput);
	if (0 == rtn) {
		*pos = uchar_to_long(ucp); ucp += 4;
		*status = uchar_to_uint(ucp) & 0x0401; ucp += 2;
	}
	else {
		*pos = (-2147483647L - 1);
		*status = 0;
	}
	return rtn;
}

//NO.8 停车命令
//mode=1 立即停止, =0减速停止
long uwc::uwc4000based_6100_stop(long mode)
{
	long rtn;
	unsigned char *ucp = ucInput;
	*ucp++ = 7;
	if (mode) {
		long_to_uchar(0x01000000, ucp); ucp += 4;
	}
	else {
		long_to_uchar(0x00000000, ucp); ucp += 4;
	}
	rtn = uwc4000_super_command(214, 4, 1, ucInput, ucOutput);
	return rtn;
}


