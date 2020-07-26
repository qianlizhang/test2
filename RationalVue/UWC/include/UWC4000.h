//Uinon Win Control Tech
#ifndef _UWCTECH_
#define _UWCTECH_

#define __UWC4000_EXPORTS

#define X_AXIS	0
#define Y_AXIS	1
#define Z_AXIS	2
#define W_AXIS	3


#ifdef __UWC4000_EXPORTS
#define UWC4000_API __declspec(dllexport)
#else
#define UWC4000_API __declspec(dllimport)
#endif

/*#ifdef __cplusplus
extern "C" {
#endif	*/
//��uwc4000��������,����ʼ������������
UWC4000_API int __stdcall uwc4000_initial(void);

//�Ͽ������������������
UWC4000_API int __stdcall uwc4000_close(void);

//��ȡ����ģ��״̬�� �÷������ο�:unsigned int status[4];uwc4000_get_count_status(status);
UWC4000_API int __stdcall uwc4000_get_count_status(unsigned int *status);

//��ȡ�˶�ģ��״̬�� �÷������ο�:unsigned int status;uwc4000_get_motion_status(&status);
UWC4000_API int __stdcall uwc4000_get_motion_status(unsigned int *status);

//������״̬ �÷������ο�:unsigned int status[4];uwc4000_get_axis_status(status);
UWC4000_API int __stdcall uwc4000_get_axis_status(unsigned int *status);

//��ȡ��������趨�ĸ�������ٶȺͼ��ٶ�
UWC4000_API int __stdcall uwc4000_get_profile(double *acc_time,double *max_speed);

//��ȡ��դ��λ�� �÷������ο�:double x_scale,double y_scale,double z_scale;uwc4000_get_scale(&x_scale,&y_scale,&z_scale)
UWC4000_API int __stdcall uwc4000_get_scale(double *x_scale,double *y_scale,double *z_scale);

//��ȡ4·��դ��λ��
UWC4000_API int __stdcall uwc4000_get_all_scale(double *scale_pos);

//��ȡ�������������
UWC4000_API int __stdcall uwc4000_get_pulse_count(long *count);

//���ù�Դ���� �÷������ο�:unsigned int light[44];uwc4000_set_light(light);
UWC4000_API int __stdcall uwc4000_set_light(unsigned int *light);

//��ȡ���ݸ���Ϣ �÷������ο�:int Message[5];uwc4000_get_joystick_Msg(Message);
UWC4000_API int __stdcall uwc4000_get_joystick_Msg(int *message);

//��ԭ���˶� �÷������ο�:uwc4000_go_home(0,10);//x�������ԭ��
UWC4000_API int __stdcall uwc4000_go_home(int axis,double search_speed);

//�����λ�˶� �÷������ο�:uwc4000_single_move_to(0,10000,10);//x��������ٶȶ�λ������ԭ��10mm��
UWC4000_API int __stdcall uwc4000_single_move_to(int axis,double speed,double target_pos);

//����˶���ʽ�����λ�˶�
UWC4000_API int __stdcall uwc4000_single_move_to_rel(int axis,double speed,double pos_rel);

//XYֱ�߲岹��ָ��λ�� �÷������ο�:double target[2]={10,20};uwc4000_XY_move_to(10000,target);//xy��������ٶȲ���ֱ�߲岹��ʽ��λ������ԭ��X=10mm,Y=20mm��
UWC4000_API int __stdcall uwc4000_XY_move_to(double speed,double *target_pos);

//XYֱ�߲岹��ָ���������λ��
UWC4000_API int __stdcall uwc4000_XY_move_to_rel(double speed,double *pos_rel);

//XYZֱ�߲岹��ָ��λ�� �÷������ο�:double target_pos[4]={10,10,10,0};uwc4000_XYZ_move_to(10000,target_pos);X/Y/Z������ٶ�ֱ�߲岹��λ��10,10,10
UWC4000_API int __stdcall uwc4000_XYZ_move_to(double speed,double *target_pos);

//XYZֱ�߲岹��ָ���������λ��
UWC4000_API int __stdcall uwc4000_XYZ_move_to_rel(double speed,double *pos_rel);

//ָ����ֱ�߲岹�˶�
UWC4000_API int __stdcall uwc4000_linear_move_to(long *axis_array,double speed,double *target_pos);

//��XOYƽ����Բ���岹�˶�,��line_speedΪ���ٶ�, x_center,y_centerΪԲ����������������λ��,angleΪ��ת�Ƕ�:-360--+360
UWC4000_API int __stdcall uwc4000_arc_move_xy(double x_center, double y_center, double line_speed, double angle);

//��YOZƽ����Բ���岹�˶�,��line_speedΪ���ٶ�, y_center,z_centerΪԲ����������������λ��,angleΪ��ת�Ƕ�:-360--+360
UWC4000_API int __stdcall uwc4000_arc_move_yz(double y_center, double z_center, double line_speed, double angle);

//��ZOXƽ����Բ���岹�˶�,��line_speedΪ���ٶ�, z_center,x_centerΪԲ����������������λ��,angleΪ��ת�Ƕ�:-360--+360
UWC4000_API int __stdcall uwc4000_arc_move_zx(double z_center, double x_center, double line_speed, double angle);

//ʾ���˶����� �÷������ο�:uwc4000_jog_start(0,30);//x������JOG�˶�,�˺���uwc4000_change_speed���ٷ�ΧΪ-30~30mm/s,����ϸ���800��
UWC4000_API int __stdcall uwc4000_jog_start(int axis,double jog_speed_max);

//ʾ���˶����� �÷������ο�:uwc4000_change_speed(0,-3);//����X���ǰ��jog_start,��x��jog�ٶȸı�,ʹX�Ḻ���˶�,�ٶ�Ϊ-3mm/s
UWC4000_API int __stdcall uwc4000_change_speed(int axis,double curnt_speed);

//ֹͣʾ���˶� �÷������ο�:uwc4000_jog_stop();//ͣ���������jog�˶�,����û���ᴦ��jog�˶�״̬����jog_stop�޸�����
UWC4000_API int __stdcall uwc4000_jog_stop(void);

//��ֹ���ݸ˿��� �÷������ο�:uwc4000_disable_joystick();
UWC4000_API int __stdcall uwc4000_disable_joystick(void);

//������ݸ˿���,ͬʱָ�������/�͵�������
//�÷������ο�:double low_speed[4]={5,5,5,5},high_speed[4]={50,50,50,50};//ҡ�˸���״̬ʱ,�⶯ҡ�˵����Ƕ��ٶ�Ϊ50mm/s,����״̬ʱ,�⶯�����Ƕ��ٶ�Ϊ5mm/s
UWC4000_API int __stdcall uwc4000_enable_joystick(double *low_speed,double *high_speed);

//��ȡ���ݸ˷�ʽ̽��ɵ㷴�����˲���դ������λ��
UWC4000_API int __stdcall uwc4000_get_joy_comeback_position(double *scale_pos);

//ͣ��ָ�� �÷������ο�:uwc4000_stop(0,0);//����ֹͣX��
UWC4000_API int __stdcall uwc4000_stop(int axis,int mode);

//���ø��ᶨλ����,��λ�������ò�����2΢�� �÷������ο�:double precision[4]={0.005,0,005,0.002,0.005};uwc4000_set_inposition_precision(precision);//x:5΢��,y:5΢��,z:2΢��
UWC4000_API int __stdcall uwc4000_set_inposition_precision(double *precision);

//̽�빦������ �÷������ο�:uwc4000_set_motion_probe(0x0001 | 0x0002);//0x0001ʹ��̽��,0x0000����̽��,0x0002renishaw//TESA
UWC4000_API int __stdcall uwc4000_set_motion_probe(unsigned int probe_set);

//����ҡ�˲ɵ���˲��� �÷������ο�:uwc4000_set_joystick_comeback(20,3);//ҡ�˲ɵ�ֹͣ����20mm/s�ٶȻ��˵����봥����3mmλ��
UWC4000_API int  __stdcall uwc4000_set_joystick_comeback(double comeback_speed,double comeback_distance);

//̽��ɵ��˶�ָ�� �÷������ο�:double target_pos[4]={10,10,10,0};uwc4000_touch_move(5,20,10,target_pos);//��5mm/s�ϳ��ٶȳ�������10,10,10��������,�������������20mm/s�ٶȻ��˵��ú������õ�;�����������,������������10,10,10λ��5mm��ͣ����.
UWC4000_API int __stdcall uwc4000_touch_move(double touch_speed,double comeback_speed,double search_radius,double *target_pos);

//��ȡ̽������ֵ �÷������ο�:double x_scale,y_scale,z_scale;uwc4000_get_probe_capture(&x_scale,&y_scale,&z_scale);
UWC4000_API int __stdcall uwc4000_get_probe_capture(double *x_scale,double *y_scale,double *z_scale);

//��ȡ�ڶ�̽������ֵ
UWC4000_API int __stdcall uwc4000_get_probe2_capture(double *x_scale,double *y_scale,double *z_scale);

//��ȡ̽�봥��ʸ��
UWC4000_API int __stdcall uwc4000_get_probe_capture_ijk(double *x_scale, double *y_scale, double *z_scale, double *i, double *j, double *k);

//��ͨ�������״̬
UWC4000_API int __stdcall uwc4000_get_input(unsigned int *input);

//дͨ�������״̬
UWC4000_API int __stdcall uwc4000_set_output(unsigned int output);

//�������״̬
UWC4000_API int __stdcall uwc4000_get_output(unsigned int *output);

//��ȡuwc4000�������÷�
UWC4000_API int __stdcall uwc4000_get_function_describe(unsigned int *function_describe);

//��ȡ�����ѧ�߷ֱ���
UWC4000_API int __stdcall uwc4000_get_scale_resolution(double *resolution);

//���ù�դ��λ��
UWC4000_API int __stdcall uwc4000_set_scale(double x_scale,double y_scale,double z_scale);

//��ȡ�����λ����(����ڻ�е��λ)
UWC4000_API int __stdcall uwc4000_get_soft_limit(int axis,double *pos_limit,double *neg_limit);

//��ȡ��������ٶ����� 
UWC4000_API int __stdcall uwc4000_get_max_speed(double *max_speed);

//��ȡ��λ���ȣ���λ��ɴ��ڣ�����
UWC4000_API int __stdcall uwc4000_get_inposition_precision(double *precision);

//��ȡ�̼�����汾
UWC4000_API int __stdcall uwc4000_get_firmware(char *firmware);

//��ȡ���һ��������Ϣ����
UWC4000_API int __stdcall uwc4000_get_last_err(unsigned int *err_code);

//��������
UWC4000_API int __stdcall uwc4000_super_command(unsigned int ch,int Slen,int Rlen,unsigned char *ucIn,unsigned char *ucOut);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
���º���Ϊ�ϰ汾���ݻ����Ŀ�Ķ��������󲿷ֹ�������Ч������ֱ��ʹ�ã����ʹ����Ҫ������UWC����֧����ϵ ljs1384@163.com
�Ƽ�ʹ��uwc4000_super_commandʵ������APIδ����ٵĲ������뽫���������͵������ʼ���UWC���ṩһ�λ���super_command��װ�Ĵ�����ʵ��֮
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//����3D�������ᶨλ����,��λ�������ò�����5΢��,Ĭ��50um
UWC4000_API int __stdcall uwc4000_set_inposition_precision_3D(double *precision);

//�����ȡ������״̬��Ϣ,ֻ��Ҫһ��ͨѶ���ɶ�ȡ���󲿷ֳ�����Ϣ:����״̬,�˶�ģ��״̬,����ģ��״̬,��դ������,�쳣����,���ݺм���״̬,ͨ�������״̬
//���ú���ִ��ʱ����ֻ��ȡ������Ϣ����ִ��ʱ�����
UWC4000_API long __stdcall uwc4000_get_controller_msg(unsigned long *ulStatus,double *dScalePosition);

//���ܹ�����ȥ������������
//��������ַ���
UWC4000_API int __stdcall uwc4000_set_security_string(int security_number,char *string);
//���м����㷨
UWC4000_API int __stdcall uwc4000_run_security_algorithmic(int security_number,float *param);

//��ȡ������UWC4000.INI�ļ��еĻ����ͺ�
UWC4000_API int __stdcall uwc4000_get_machine_type(char *string);

//��ȡmof����ֵ
UWC4000_API int __stdcall uwc4000_get_MOF_capture(double *x_scale,double *y_scale,double *z_scale);

//�������������
UWC4000_API int __stdcall uwc4000_set_follow_err(unsigned int *follow_err,int active1_save0);

//�������������
UWC4000_API int __stdcall uwc4000_get_follow_err(unsigned int *follow_err);

//��ȡ���ݸ�adcת�����
UWC4000_API int __stdcall uwc4000_get_joystick_ADC(int *offset);

//��λuwc4000���ù�����ȥ������������
UWC4000_API int __stdcall uwc4000_reset(void);

//���ù�դ�߷ֱ���
UWC4000_API int __stdcall uwc4000_set_scale_resolution(double *resolution);

//��ȡUWC4000 ID��
UWC4000_API int __stdcall uwc4000_get_uwc4000_ID(long *ID);

//��ȡjoystick ID��
UWC4000_API int __stdcall uwc4000_get_joystick_ID(long *ID);

//���ø����դ��RI����
UWC4000_API int __stdcall uwc4000_set_RI_mode(int *RI,int active1_save0);

//��ȡ�����դ��RI����
UWC4000_API int __stdcall uwc4000_get_RI_mode(int *RI);

//����UWC4000 ID��
UWC4000_API int __stdcall uwc4000_set_uwc4000_ID(long ID);

//����joystick ID��
UWC4000_API int __stdcall uwc4000_set_joystick_ID(long ID);

//����joystick ������Ϣ
UWC4000_API int __stdcall uwc4000_set_joystick_calibration(int *data_array,int active1_save0);

//��ȡjoystick ������Ϣ
UWC4000_API int __stdcall uwc4000_get_joystick_calibration(int *data_array);

//���ø�������/��դ��������
UWC4000_API int __stdcall uwc4000_set_pulse_scale_map(long *pulse,long *scale,int active1_save0);

//��ȡ��������/��դ��������
UWC4000_API int __stdcall uwc4000_get_pulse_scale_map(long *pulse,long *scale);

//���ø�������ٶȺͼ��ٶ�
UWC4000_API int __stdcall uwc4000_set_profile(double *acc_time,double *max_speed,int active1_save0);

//��ȡ��������ٶȺͼ��ٶ�
UWC4000_API int __stdcall uwc4000_get_profile(double *acc_time,double *max_speed);

//����uwc4000�������÷�
UWC4000_API int __stdcall uwc4000_set_function_describe(unsigned int *function_describe);

//�����դ�߼�����������
UWC4000_API int __stdcall uwc4000_set_count_dir(unsigned int *dir,int active1_save0);

//��ȡ��դ�߼�����������
UWC4000_API int __stdcall uwc4000_get_count_dir(unsigned int *dir);

//�������ר��i/o����
UWC4000_API int __stdcall uwc4000_set_IO_config(unsigned int *config,int active1_save0);

//��ȡ����ר��i/o����
UWC4000_API int __stdcall uwc4000_get_IO_config(unsigned int *config);

//��������ͺ�
UWC4000_API int __stdcall uwc4000_set_machine_type(char *string);

//���ø������巽���ź�
UWC4000_API int __stdcall uwc4000_set_pulse_dir(unsigned int *dir,int active1_save0);

//��ȡ���巽������
UWC4000_API int __stdcall uwc4000_get_pulse_dir(unsigned int *dir);

//���ø���PID,Kvff����
UWC4000_API int __stdcall uwc4000_set_PID(float *Kp,float *Ki,float *Kd,float *Kvff,int active1_save0);

//��ȡ����PID,Kvff����
UWC4000_API int __stdcall uwc4000_get_PID(float *Kp,float *Ki,float *Kd,float *Kvff);

//����̽�볣�����������ͣ�̽�����������ʱ��
UWC4000_API int __stdcall uwc4000_set_probe(int enable,int led_logic,int buzzer_time);

//����̽���ź�ȥ����ʱ��
UWC4000_API int __stdcall uwc4000_set_trig_debounce(int time);

//���ô����ź�ȥ����ʱ��
UWC4000_API int __stdcall uwc4000_get_trig_debounce(int *time);

//RI_function:0-������,1-����1��
UWC4000_API int __stdcall uwc4000_set_RI_function(unsigned int axis,int function);

//��ͨѶģ���������Ϣ
UWC4000_API int __stdcall uwc4000_get_err_msg(int *err_msg);

//����0-2�ᶨλ��ʽ
UWC4000_API int __stdcall uwc4000_set_inposition_mode(int axis,int mode);

//����0-2�ᶨλģʽ���õ�ini�ļ�
UWC4000_API int __stdcall uwc4000_set_inposition_mode_save(int axis,int mode);

//��ȡ0-2�ᶨλģʽ����
UWC4000_API int __stdcall uwc4000_get_inposition_mode(int axis,int *mode);

//�����״̬�Ĵ���
UWC4000_API int __stdcall uwc4000_clear_status(int axis);

//��ȡ�������������
UWC4000_API int __stdcall uwc4000_get_pulse_count(long *count);

//���ø������������
UWC4000_API int __stdcall uwc4000_set_pulse_count(long *count);

//��ȡָ����pid������Ϣ
UWC4000_API int __stdcall uwc4000_get_PID_tunning(int axis,double *data);

//ʹ�����������·
UWC4000_API int __stdcall uwc4000_enable_pulse_output(unsigned int enable);

//��ȡ��������Դ��ѹ
UWC4000_API int __stdcall uwc4000_get_power_voltage(double *voltage);

//ʹ��zoom��
UWC4000_API int __stdcall uwc4000_zoom(int enable);

//�����λ����(��ԭ�����Ч)
UWC4000_API int __stdcall uwc4000_set_soft_limit(int axis,double pos_limit,double neg_limit);

//��������λ��ini�ļ�
UWC4000_API int __stdcall uwc4000_set_soft_limit_save(int axis,double pos_limit,double neg_limit);


//���������
UWC4000_API int  __stdcall uwc4000_clear_motion_err(int ID);

//����Զ�̽�������
UWC4000_API int __stdcall uwc4000_clear_auto_touch_err(void);

//��ȡ��̤��������ֵ
UWC4000_API int __stdcall uwc4000_get_footswitch_capture(double *x_scale,double *y_scale,double *z_scale);

//���DSP���ݹ۲�������
UWC4000_API int  __stdcall uwc4000_clear_MDSP_param(int number);

//��ȡDSP���ݹ۲�������
UWC4000_API int  __stdcall uwc4000_get_MDSP_param(int number,long *param);

//����2D������λ���ʱ��
UWC4000_API int __stdcall uwc4000_set_INP_time(double time);

//��ȡ2D������λ���ʱ��
UWC4000_API int __stdcall uwc4000_get_INP_time(double *time);


//ʹ�ܡ���ֹ����������־
UWC4000_API int __stdcall uwc4000_enable_Error_Log(bool enable1_disable0);

//��������λ����ɲ������
UWC4000_API int __stdcall uwc4000_set_limit_brake_distance(unsigned int *distance,int active1_save0);

//��ȡ������λɲ������
UWC4000_API int __stdcall uwc4000_get_limit_brake_distance(unsigned int *distance);

//����̽�봥��ɲ������
UWC4000_API int __stdcall uwc4000_set_probe_brake_distance(double distance,int active1_save0);

//�����״̬���еĴ�����Ϣ
UWC4000_API int __stdcall uwc4000_clear_status(int axis);

//��ȡ̽�봥��ɲ������
UWC4000_API int __stdcall uwc4000_get_probe_brake_distance(double *distance);

//��ȡҡ��̽����
UWC4000_API int __stdcall uwc4000_get_joystick_touch_flag(unsigned int *flag);

//��ȡ�Զ�̽����
UWC4000_API int __stdcall uwc4000_get_auto_touch_flag(unsigned int *flag);

//��ȡ��Դ��ͨ��������ֵ
UWC4000_API int __stdcall uwc4000_get_light_current(unsigned int *current);

//���ò���ģʽ,0-2D����,1-3D����
UWC4000_API int __stdcall uwc4000_set_measure_mode(unsigned int un3D1_2D0);


//����3D������λʱ��
UWC4000_API int __stdcall uwc4000_set_INP_time_3D(double time);

//��ȡ3D������λʱ��
UWC4000_API int __stdcall uwc4000_get_INP_time_3D(double *time);

//��ȡDLL�汾��
UWC4000_API int __stdcall uwc4000_get_dll_version(char *ver);

//����ָ����������ٵ�����
UWC4000_API int __stdcall uwc4000_set_SD_position(int axis,double positive_position,double negtive_position,int active1_save0);

//��ȡָ����������ٵ�����
UWC4000_API int __stdcall uwc4000_get_SD_position(int axis,double *positive_position,double *negtive_position);

//����ָ�����������ٵ���ٶ�
UWC4000_API int __stdcall uwc4000_set_SD_speed(int axis,double low_speed,int active1_save0);

//��ȡָ�����������ٵ���ٶ�
UWC4000_API int __stdcall uwc4000_get_SD_speed(int axis,double *low_speed);

//����ͨ������˿�״̬
//port_ch=1-3,status=0-65535
UWC4000_API int __stdcall uwc4000_set_GP_outport(int port_ch,unsigned short status);

UWC4000_API int __stdcall uwc4000_get_GP_outport(int port_ch,unsigned short *status);

//��ȡͨ������˿�״̬
//port_ch=1-3,status=0-65535
UWC4000_API int __stdcall uwc4000_get_GP_inport(int port_ch,unsigned short *status);

//���ÿ����������
//0-OTP6����(ѡ����������ò��ݸ����ݲɼ���)
//1-OTP7����(ѡ�����ò��ݺ�)
//2-���ƻ����ò��ݺ� 
UWC4000_API int __stdcall uwc4000_set_control_panel_type(int type,int active1_save0);

UWC4000_API int __stdcall uwc4000_get_control_panel_type(int *type);

//�����ٶ�������S���߶�ռ�ܼӼ���ʱ��ı���
//scale=2-50,����S���߶�ռ�ܼӼ���ʱ���1/2~1/50,scale��ֵԽ��Խ�ӽ������ٶ�����Ч��
UWC4000_API int __stdcall uwc4000_set_profile_ts(int axis,int scale,int active1_save0);

UWC4000_API int __stdcall uwc4000_get_profile_ts(int axis,int *scale);

//���ø����������ٶ�
UWC4000_API int __stdcall uwc4000_set_design_max_speed(double *design_max_speed,int active1_save0);

//��ȡ�����������ٶ�
UWC4000_API int __stdcall uwc4000_get_design_max_speed(double *design_max_speed);

//����ָ������Ư 
UWC4000_API int __stdcall uwc4000_set_offset(int axis,int offset,int active1_save0);

//��ȡָ������Ư 
UWC4000_API int __stdcall uwc4000_get_offset(int axis,int *offset);

//���ÿ������������ѹ
UWC4000_API int __stdcall uwc4000_set_output_voltage(unsigned int axis,double voltage);

//����PID���ƻ����������
UWC4000_API int __stdcall uwc4000_set_sum_max(unsigned int axis,long sum_max,int active1_save0);

//��ȡPID���ƻ����������
UWC4000_API int __stdcall uwc4000_get_sum_max(unsigned int axis,long *sum_max);

//����2D��λʱ�����õ�ini�ļ�
UWC4000_API int __stdcall uwc4000_set_INP_time_save(double time);

//����3D��λʱ�����õ�ini�ļ�
UWC4000_API int __stdcall uwc4000_set_INP_time_3D_save(double time);

//����2D������λ��Χ���õ�ini�ļ�
UWC4000_API int __stdcall uwc4000_set_inposition_precision_save(double *precision);

//����3D������λ��Χ���õ�ini�ļ�
UWC4000_API int __stdcall uwc4000_set_inposition_precision_3D_save(double *precision);

//��������դ�߷ֱ��ʵ�ini�ļ�,��λ����
UWC4000_API int __stdcall uwc4000_set_scale_resolution_save(double *resolution);

//�ŷ�������ʹ��/��ֹ,1-ʹ��,0-��ֹ
UWC4000_API int __stdcall uwc4000_servo_enable(unsigned int axis,unsigned int enable1_disable0);

//���ÿ���/�ջ����Ʒ�ʽ
UWC4000_API int __stdcall uwc4000_close_loop(unsigned int axis,unsigned int close1_open0);

UWC4000_API int __stdcall uwc4000_light_doubling(unsigned int LightType,int *doubling,int active1_save0);

//��ȡ��Դ����
UWC4000_API int __stdcall uwc4000_get_light_property(int *property);

//��ȡ����������¼
UWC4000_API int __stdcall uwc4000_get_max_En(unsigned int axis,double *Max_En);

//����CPLD ˫�ֽڲ���
UWC4000_API int __stdcall uwc4000_set_CPLD16(unsigned char ucAdd,unsigned short value);

//����CPLD ���ֽڲ���
UWC4000_API int __stdcall uwc4000_set_CPLD32(unsigned char ucAdd,unsigned long value);

UWC4000_API int __stdcall uwc4000_get_CPLD16(unsigned char ucAdd,unsigned short *value);

UWC4000_API int __stdcall uwc4000_get_CPLD32(unsigned char ucAdd,unsigned long *value);

UWC4000_API int __stdcall uwc4000_set_squash(int axis,double squash,int active1_save0);

UWC4000_API int __stdcall uwc4000_get_squash(int axis,double *squash);

UWC4000_API int __stdcall uwc4000_set_auto_enable(unsigned int axis,unsigned int initial_auto_enable1_api_enable0);

UWC4000_API int __stdcall uwc4000_get_auto_enable(unsigned int axis,unsigned int *initial_auto_enable1_api_enable0);

UWC4000_API int __stdcall uwc4000_set_lens_type(unsigned int type);

UWC4000_API int __stdcall uwc4000_set_channel_light(unsigned int channel,unsigned int light);

/*
#ifdef __cplusplus
}
#endif
*/

#endif 

