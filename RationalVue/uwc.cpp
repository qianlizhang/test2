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
   ����һ: UWC4000(����8��)/UWC6008(8��), ����,��UWC4003/UWC6008���ݵĿͻ����ƵĻ��ι�Դ
   ������: UWC6016(2��8��)
   ������: UWC6045/UWC6043(5��8��)��Դ
   ʹ��uwc4000based_not_more_then_40_area_set_light
***********************************************************************/
//�������ֵ200, ��Сֵ0
//light_array[0]-light_array[39]:��1-��40����, ����40��������0���
//light_array[40]:�׹�(contour)
//light_array[41]:ͬ���(Coaxial)
//light_array[42]:����ָʾ(laser)
long uwc::uwc4000based_no_more_than_40_area_set_light(unsigned char *light_array)
{
	long i;
	for (i = 0; i < 45; i++)
		ucInput[i] = *light_array++;
	return uwc4000_super_command(210, 45, 1, ucInput, ucOutput);
}

/************************************************************************/
/*  ������: UWC6163 5��8��4ɫ��Դ*/
//	ʹ��uwc4000based_6163_set_light

//!!!!!!!!!!!!!!!!!!!ע��!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!ע��!!!!!!!!!!!!!!!!!!!!!!!
//uwc4000based_6163_set_light�Ĳ�����ԭuwc6163_set_light����������һ��!!!

//ԭ��:�׹���������λ, ͬ�����ĩβ
//����uwc4000base:�������ǰ,�׹��ͬ���˳���ں�
/************************************************************************/

//light_array[0]-light_array[39]:   ������1-��40������ɫ, �ͱ�ŷ������ڻ�, ���LED˳ʱ����ת
//light_array[40]-light_array[79]:  ������1-��40������ɫ
//light_array[80]-light_array[119]: ������1-��40������ɫ
//light_array[120]-light_array[159]:������1-��40������ɫ
//light_array[160]:�׹�(contour)
//light_array[161]:ͬ���(Coaxial)
//light_array[162]:����ָʾ(laser)
//!!!!!!!!!!!!!!!!!!!ע��!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!ע��!!!!!!!!!!!!!!!!!!!!!!!
//uwc4000based_6163_set_light�Ĳ�����ԭuwc6163_set_light����������һ��!!!
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
/* ������: UWC6100 3��8��4ɫ�綯������Դ*/
/************************************************************************/

//light_array[0]-light_array[23]:  ������1-��24������ɫ, �ͱ�ŷ������ڻ�, ���LED˳ʱ����ת
//light_array[24]-light_array[47]: ������1-��24������ɫ
//light_array[48]-light_array[71]: ������1-��24������ɫ
//light_array[72]-light_array[95]: ������1-��23������ɫ
//light_array[96]:�׹�(contour)
//light_array[97]:ͬ���(Coaxial)
//light_array[98]:����ָʾ(laser)
long uwc::uwc4000based_6100_set_light(unsigned char *light_array)
{
	long i, j;
	long rtn;
	unsigned char *ucp = ucInput;
	unsigned char ucArray[165];
	unsigned char *ucp2 = ucArray;

	//����Դ��ɫ�Ų�˳�����ϲ�ƷUWC6163һ��

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

//NO4. UWC6100 ��ԭ��, ������������λ���ش�
//speed: 160-64000 ��Ϊ64000ʱ, �ƶ��ٶ�ԼΪ50.8mm/s
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

//NO5. UWC6100 Jog�˶�, �����������ק��㶯��ͷ��ť, ʹ��Դ�����˶�,�ٶ�����Ϊ0��Ϊֹͣ
//speed: -64000 ~ 64000 ��Ϊ64000ʱ, �ƶ��ٶ�ԼΪ50.8mm/s
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

//NO6. UWC6100 PTP�˶�, �����Դ�ƶ���ĳ��; ����ԭ���ڶ���, ���Ŀ��λ������С�ڵ���0, ��Сֵ���豸����
//��ο�uwc4000based_6100_get_msg ֮ position����
//move_speed: 50-64000, ��Ϊ64000ʱ, �ƶ��ٶ�ԼΪ50.8mm/s
//target_pos: 0 ~ - 125984 (����OEM���������г�Ϊ100.00mm)
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

//NO7. ��ȡUWC6100 ״̬��Ϣ
//pos: ��ǰ����λ��, ��ԭ���, ������λ������С�ڵ���0
//status: �������˶�״̬, 0-�˶���,1024-��ֹͣ
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

//NO.8 ͣ������
//mode=1 ����ֹͣ, =0����ֹͣ
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


