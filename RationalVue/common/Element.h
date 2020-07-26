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
		PointElement = 0,//��Ԫ��
		BorderPointElement,//�߽��Ԫ��
		LineElement,//ֱ��Ԫ��
		PlanarElement,//ƽ��Ԫ��
		CircleElement,//ԲԪ��
		ArcElement,//Բ��Ԫ��
		CylinderElement,//Բ��Ԫ��
		ConeElement,//Բ׶Ԫ��
		SpherosomeElement,//Բ��Ԫ��
		OvalElement,//��ԲԪ��
		KeySlotElement,//����Ԫ��
		AnnulusElement,//Բ��Ԫ��
		CADElement,//CADԪ��
		ModelElement,//ģ��Ԫ��
		Distance,//����
		Angle,//�Ƕ�
		Gradient,//��б��
		Perpendicularity,//��ֱ��
		Parallelism,//ƽ�ж�
		Position,//λ�ö�
		CoordinateTolerance,//���깫��
		Concenticity,//ͬ�Ķ�
		CircleRunout,//Բ����
		DiameterTolerance,//ֱ������
		RadiusTolerance,//�뾶����
		Flatness,//ƽ���
		Straightness,//ֱ�߶�
		PointContour,//������
		LineContour,//������
		Symmetry,//�Գ�
		Width//���
	};
	enum ElementLabel {
		Theory = 0,//����Ԫ��
		Reality,//ʵ��Ԫ��
		Constructor,//����Ԫ��
		Tolerance//����Ԫ��
	};

	enum Direction {
		Up = 0,
		Down,
		Left,
		Right,
	};
	Direction  m_eDirection;
	int m_nElementId;//Ԫ��id
	QString m_strLable; //Ԫ�ر�ǩ�� 
	std::vector<QPoint> m_vecElementData;//Ԫ�ص�����
	ElementType m_enuElementType;//Ԫ������
	ElementLabel m_enuElementLabel;//Ԫ�ر�ǩ
	// QPoint m_originPoint;//ԭ��
	double m_fX;//X Y Z��ǰ����ϵ��ǰ���ȵ�λ�µļ��β���
	double m_fY;
	double m_fZ;
	double m_fI;//I J K��ǰ����ϵ��ǰ�Ƕȵ�λ�µļ��β���
	double m_fJ;
	double m_fK;
	int m_nPointDensiny;//���ܶ�
	int m_nNumOfSection;//��������
	Direction m_direction;//��������
	CCoordinate m_coordinate;//����ϵ
	CTolerance m_tolerancec;//����
	CSensor m_sensor;//̽ͷ

	CElement() {
		m_enuElementType = LineElement;
		m_enuElementLabel = Reality;
		m_strLable = QString("LN1");
	}
};