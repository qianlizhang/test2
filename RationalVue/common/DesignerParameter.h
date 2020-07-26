#pragma once
#include<QVector>
#include<QPen>
#include<QBrush>

//设计参数
enum Component {
	PICPOINT,                   //点
	PICHLINE,                    //水平线
	PICVLINE,                    //垂线
	PICLINE,                     //直线
	PICRECT,                     //矩形
	PICELLIPSE,                  //椭圆
	PICPATH,                     //曲线
	PICCIRCLE,                   //圆形
	PICARC,                      //圆弧
	PICSECTOR,                   //扇形
	PICRECTWITHHCENTERLINE,      //带有垂直中心线的矩形
	PICRECTWITHVCENTERLINE,      //带有水平中心线的矩形
	PICRECTWITHFLAGTRIANGLE,     //带有三角形标记的矩形
	PICBEZIRCURVE                //贝塞尔曲线
};
typedef struct {
	Component ComponentType;	//绘图类型
	QVector<QPointF> points;	//绘图点坐标
	QPen pen;					//画笔
	QBrush brush;				//笔刷
}PicComponents;
class CDesignParameter {
public:
	//        
	PicComponents temppiccomponent;
	//        
	QVector<PicComponents> point_component;
	QVector<PicComponents> hline_component;
	QVector<PicComponents> vline_component;
	QVector<PicComponents> line_component;
	QVector<PicComponents> rect_component;
	QVector<PicComponents> ellipse_component;
	QVector<PicComponents> path_component;
	QVector<PicComponents> circle_component;
	QVector<PicComponents> arc_component;
	QVector<PicComponents> sector_component;
	QVector<PicComponents> rectwithhcenterline_component;
	QVector<PicComponents> rectwithvcenterline_component;
	QVector<PicComponents> rectwithflagtriangle_component;
	QVector<PicComponents> bezircurve_component;

};