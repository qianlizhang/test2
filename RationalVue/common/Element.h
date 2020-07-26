#pragma once
#include<vector>
#include<QPoint>
#include<QString>
#include "Coordinate.h"
#include "Tolerance.h"
#include"Sensor.h"
class CElement {
public:
	enum ElementType {
		PointElement = 0,//点元素
		BorderPointElement,//边界点元素
		LineElement,//直线元素
		PlanarElement,//平面元素
		CircleElement,//圆元素
		ArcElement,//圆弧元素
		CylinderElement,//圆柱元素
		ConeElement,//圆锥元素
		SpherosomeElement,//圆球元素
		OvalElement,//椭圆元素
		KeySlotElement,//键槽元素
		AnnulusElement,//圆环元素
		CADElement,//CAD元素
		ModelElement,//模型元素
		Distance,//距离
		Angle,//角度
		Gradient,//倾斜率
		Perpendicularity,//垂直度
		Parallelism,//平行度
		Position,//位置度
		CoordinateTolerance,//坐标公差
		Concenticity,//同心度
		CircleRunout,//圆跳动
		DiameterTolerance,//直径公差
		RadiusTolerance,//半径公差
		Flatness,//平面度
		Straightness,//直线度
		PointContour,//点轮廓
		LineContour,//线轮廓
		Symmetry,//对称
		Width//宽度
	};
	enum ElementLabel {
		Theory = 0,//理论元素
		Reality,//实际元素
		Constructor,//构造元素
		Tolerance//公差元素
	};

	enum Direction {
		Up = 0,
		Down,
		Left,
		Right,
	};
	Direction  m_eDirection;
	int m_nElementId;//元素id
	QString m_strLable; //元素标签名 
	std::vector<QPoint> m_vecElementData;//元素点数据
	ElementType m_enuElementType;//元素种类
	ElementLabel m_enuElementLabel;//元素标签
	// QPoint m_originPoint;//原点
	double m_fX;//X Y Z当前坐标系当前长度单位下的几何参数
	double m_fY;
	double m_fZ;
	double m_fI;//I J K当前坐标系当前角度单位下的几何参数
	double m_fJ;
	double m_fK;
	int m_nPointDensiny;//点密度
	int m_nNumOfSection;//测量段数
	Direction m_direction;//测量方向
	CCoordinate m_coordinate;//坐标系
	CTolerance m_tolerancec;//公差
	CSensor m_sensor;//探头

	CElement() {
		m_enuElementType = LineElement;
		m_enuElementLabel = Reality;
		m_strLable = QString("LN1");
	}
};