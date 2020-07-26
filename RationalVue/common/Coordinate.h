#pragma once
#include<string>
#include<vector>
using namespace std;
class CCoordinate {
	string m_strFromCrd;
	string m_strDatum;
	string m_strAxis;
	string m_strMCS;//坐标系
	string m_strFocusPlane;//对焦平面
	string m_strReposition;//重定位
	string m_strCADModels;//导入的CAD模型
	string m_strPointClouds;//点云数据
	string m_strFormErrorReports;//Form误差报告
	vector<string> m_vecSensor;//测头信息

};