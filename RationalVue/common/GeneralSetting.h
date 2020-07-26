#pragma once
#include<string>
enum Language {
	English,//Ӣ��
	Chinese,//����
};

class CGenaralSetting {
public:
	//Ŀ¼����
	std::string m_strIGESDiractory;//IGESĬ��Ŀ¼
	std::string m_strDMISDiractory;//DMISĬ��Ŀ¼
	std::string m_strDBaseDiractory;//DBaseĬ��Ŀ¼
	std::string m_strOutputDiractory;//OutputĬ��Ŀ¼

	//��������
	Language m_lanUILanguage;//��������
	Language m_lanOutputLanguage;//����ļ�������

	bool m_bPersistantCRD;//�Ƿ񱣴�����ϵ
	bool m_bProbeOrStyliChanger;//����
	int m_nProPageDecimalPlaces;//����ҳ������ʾ��С����ά��

	//��ʱ�ļ�����
	std::string m_strTempFileFolder;//��ʱ�ļ����ļ���
	int m_nDaysKeepTempFile;//��ʱ�ļ�����ʱ�䣬��λ��
	bool m_bDoubleClickClearFiles;//�Ƿ�˫������ļ�
	bool m_bDoubleClickViewFiles;//�Ƿ�˫���鿴�ļ�
	
};
