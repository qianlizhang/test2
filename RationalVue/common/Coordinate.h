#pragma once
#include<string>
#include<vector>
using namespace std;
class CCoordinate {
	string m_strFromCrd;
	string m_strDatum;
	string m_strAxis;
	string m_strMCS;//����ϵ
	string m_strFocusPlane;//�Խ�ƽ��
	string m_strReposition;//�ض�λ
	string m_strCADModels;//�����CADģ��
	string m_strPointClouds;//��������
	string m_strFormErrorReports;//Form����
	vector<string> m_vecSensor;//��ͷ��Ϣ

};