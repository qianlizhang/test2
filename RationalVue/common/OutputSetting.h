#pragma once
#include<qcolor.h>
enum CARTOrPOLOutput {
	BasedOnFeature,//����Ԫ�ر���
	BasedOnSysStatus,//����ϵͳ״̬
};

enum ExcelUsing {
	MicrosoftOffice,
	OpenOffice,
};
class COutputSetting {
public:
	//UI�������
	bool m_bIsActualCreation;//�Ƿ���ʵ����
	bool m_bTRCEva;//�Ƿ�������۹���
	bool m_bRmvOptWhenFeaDel;//�Ƿ�ɾ��Ԫ�ص�ͬʱɾ��Ԫ�ص����


	//���excel����
	ExcelUsing m_excelUsing;
	bool m_bOpenPDFAfterSave;//������Ƿ��Զ���

	//��ɫ����
	QColor m_normalColor;
	QColor m_intolColor;
	QColor m_intol2Color;
	QColor m_outtolColor;
};