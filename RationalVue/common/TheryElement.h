#pragma once
#include<QString>
class TheryElement {
public:
	double m_fD;
	QString m_strType;//Ԫ������
	QString m_strSen;//����̽ͷ
	QString m_strCrd;//��������ϵ
	double m_fForm;
	Misc* m_pMisc;//����Ԫ�����͡� ʱ��
	bool m_bLastPoints;
};
class Misc { //����Ԫ�����͡� ʱ��
public:
	QString m_strCrdType;//����Ԫ������
	QString m_strAct;
	QString m_strD&T(N);//����ʱ��
	QString m_strD&T(A);
};