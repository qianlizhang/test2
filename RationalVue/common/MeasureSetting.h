#pragma once

enum FittingAlgorithm {
	LeastSquare,//��С���˷�
	FitActualSurface,//���ʵ������
};

enum SoundType {
	None,//̽�����û������
	Beep_2,//������
	Sound,//�����������
	SelectWAVFile,//ѡ��WAV����
};

enum ScanDensity {
	Normal_2,
	Full,
	High,
	Fast,
	Custom,
};

enum ConfirmBtn {
	RightBtn,//����Ҽ�
	MiddleBtn,//����м䰴��
	LeftBtn,//������
};
class CMeasureSetting {
	//��ͷ����
	double m_dApproachDistance;//�ӽ�����
	double m_dRetractDistance;//���˾���
	double m_dDepth;//���
	double m_dClearDistance;//�������
	double m_dSearchDistance;//��������
	bool m_bEnableClearMove;//������뿪��
	bool m_bIsDropProbe;//�Ƿ��л�̽ͷ����ʹ��Ӱ����߼���̽ͷʱ

	//����㷨
	FittingAlgorithm m_circleFittingAlg;//Բ������㷨
	FittingAlgorithm m_arcFittingAlg;//Բ��������㷨
	FittingAlgorithm m_planeFittingAlg;//ƽ������㷨
	FittingAlgorithm m_cylinderFittingAlg;//Բ������㷨
	FittingAlgorithm m_surfaceFittingAlg;//��������㷨
	int m_nMinIteration;//��С��������

	//��������
	SoundType m_soundType;

	//����ʹ�������
	bool m_bIsTreatOutofTRC;//�Ƿ�����
	bool m_bIsShowNGOrOK;//��ʾ�����س���

	//���߿���ͶӰ����
	bool m_bEnableCurveFastPro;//�Ƿ�Ȩ�޿���ͶӰ
	//�����������
	int m_nBestfitSamplePoints;//��ϵ���
	int m_nBestfitIteration;//��ϴ���

	//CCDɨ������
	ScanDensity m_scanDensity;//ɨ����ܶ�
	double m_dAutoMeasToolWidth;//�Զ��������߿��
	bool m_bEnableCentralMeas;//�Ƿ������Ĳ���
	bool m_bEnableDefaultDirection;//�Ƿ���Ĭ�Ϸ���
	ConfirmBtn m_confirmBtn;//ȷ�ϰ�ť
	bool m_bIsUsingVectorSearch;//�Ƿ�ʹ����������

	//ͼ����ͼ�ӽ�����
	double m_dMaxAngle;//ƽ���ߵ����Ƕ�
	double m_dLineLength;//�߶γ���

	//�ֶ������г�������
	bool m_bIsGotoCmd;//Goto��������
	int m_nZoneXY;//XY�ĵ�λ����
	double m_dZoneZ;//Zֵ������
	int m_nDelay;//�ȶ�ʱ��

};