#pragma once
#include<QString>
class CConstructorElement { //����Ԫ������
public:
	Angles* m_pAngles;//����ϵ
	Misc* m_pMisc;//����Ԫ�����͡� ʱ��
	ConstInfo* m_pConstInfo;//���빹���Ԫ�ص���Ϣ
};
class Misc { //����Ԫ�����͡� ʱ��
public:
	QString m_strCrdType;//����Ԫ������
	QString m_strAct;
	QString m_strD&T(N);//����ʱ��
	QString m_strD&T(A);
};

class Angles {//����ϵ
public:
	QString m_strType;//2D or 3D
	QString m_strSen;//����̽ͷ
	QString m_strCrd;//��������ϵ
};

class ConstInfo {
public:
	QString m_strConstMethod;//���췽��
	ConstFeatures* m_pConstFeatures;//���빹���Ԫ��
};

class ConstFeatures { //���빹���Ԫ��
	QString m_str1;
	QString m_str2;
};