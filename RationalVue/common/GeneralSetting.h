#pragma once
#include<string>
enum Language {
	English,//英语
	Chinese,//中文
};

class CGenaralSetting {
public:
	//目录设置
	std::string m_strIGESDiractory;//IGES默认目录
	std::string m_strDMISDiractory;//DMIS默认目录
	std::string m_strDBaseDiractory;//DBase默认目录
	std::string m_strOutputDiractory;//Output默认目录

	//语言设置
	Language m_lanUILanguage;//界面语言
	Language m_lanOutputLanguage;//输出文件的语言

	bool m_bPersistantCRD;//是否保存坐标系
	bool m_bProbeOrStyliChanger;//激活
	int m_nProPageDecimalPlaces;//属性页界面显示的小数点维数

	//临时文件管理
	std::string m_strTempFileFolder;//临时文件的文件夹
	int m_nDaysKeepTempFile;//临时文件保留时间，单位天
	bool m_bDoubleClickClearFiles;//是否双击清除文件
	bool m_bDoubleClickViewFiles;//是否双击查看文件
	
};
