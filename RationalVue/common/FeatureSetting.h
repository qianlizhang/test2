#pragma once

//��ʾ����
enum DisplayType {
	Dot,//����ʾ
	Solid,//ʵ����ʾ
	Vector,//������ʾ
	Wire��//�߿���ʾ
};
//�������
enum ToleranceQuality {
	Normal,//����
};

//�ֽ�����
enum DecomposeType {
	Compound,//�������
};

//�˲�����
enum FilterType {
	LowPass,
};
class CFeatureSetting {
	//Ԫ����ʾ����
	DisplayType m_displayPointType;//����ʾ
	DisplayType m_displayPlaneType;//ƽ����ʾ

	//ʵ��Ԫ�ظ�������
	bool m_bIsupdateCRDRecall;//�Ƿ����ʵ��Ԫ�ص�λ��

	//���ѡ��
	bool m_bIsRecalculateFormError;//�Ƿ����¼���form���
	bool m_bIsDisplayTRCBand;//��ʾ�����
	ToleranceQuality m_TRCQua;//�������

	//CADѡ��
	bool m_bIsImpCADColor;//�Ƿ���CAD��ɫ��Ϣ
	DecomposeType m_decomposeType;//�ֽ�Ķ�������
	bool m_bIsFastPickFace;//�Ƿ����ѡȡ��

	//����ѡ��
	bool m_bIsUsingPtmeas;//�Ƿ���м�ֵ����

	//���߹�������
	bool m_bIsOpenCurveFilter;//�Ƿ������߹���
	FilterType m_fileType;//�˲�����
	double m_dStandardDev;//������׼
	double m_dUPR;
	double m_dOutlierMaxValue;
};