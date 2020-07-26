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

	//NO1.��ȡ��Դ�����������(�ֻ���, ������, ��ɫ����, �����ٶ�)
	long uwc4000based_get_light_solution(char *solution_identify, long *rings, long *blocks, long *colors, long *speed);

	//NO2. ������40�������ĵ�ɫ���ι�Դ����, ���÷�Χ:8��(UWC4003/UWC6008/�û�����8����)��16��(2��8��UWC6016)��40��(5��8��UWC6045)
	long uwc4000based_no_more_than_40_area_set_light(unsigned char *light_array);

	//NO3. 5��8��4ɫ(UWC6163)����
	long uwc4000based_6163_set_light(unsigned char *light_array);

	//NO4. 3��8��4ɫ�綯����(UWC6100) ����
	long uwc4000based_6100_set_light(unsigned char *light_array);

	//NO5. UWC6100 ��ԭ��, ������������λ���ش�
	long uwc4000based_6100_go_home(long speed);

	//NO6. UWC6100 Jog�˶�, �����������ק��㶯��ͷ��ť, ʹ��Դ�����˶�,�ٶ�����Ϊ0��Ϊֹͣ
	long uwc4000based_6100_jog_move(long speed);

	//NO7. UWC6100 PTP�˶�, �����Դ�ƶ���ĳ��
	long uwc4000based_6100_move_to(long speed, long target_pos);

	//NO8. ��ȡUWC6100 ״̬��Ϣ
	long uwc4000based_6100_get_msg(long *pos, long *status);

	//NO9. ͣ������
	long uwc4000based_6100_stop(long mode);



};

#endif