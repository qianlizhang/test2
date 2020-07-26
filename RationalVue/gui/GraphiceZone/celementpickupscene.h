#ifndef CELEMENTPICKUPSCENE_H
#define CELEMENTPICKUPSCENE_H

#define PEG_PI 3.14159265358979323846

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPathItem>
#include <QVector>
#include <QPaintEvent>
#include "DesignerParameter.h"
#include "CommonData.h"
using namespace std;

class CPaintZoneDockWidget;

class CElementPickupScene : public QGraphicsScene, CCommonData
{
    Q_OBJECT

public:
    CElementPickupScene(CCommonData *commondata = NULL, QGraphicsScene *parent = 0);

    enum PickupModel {
        NoShape = 0,
        Shape_Point,
        Shape_HorLine,
        Shape_VerLine,
        Shape_Line,
        Shape_Rect,
        Shape_Ellipse,
        Shape_Path,
        Shape_Circle,
        Shape_Arc,
        Shape_Sector,
        Shape_RectWithHCenterLine,
        Shape_RectWithVCenterLine,
        Shape_RectWithFlagTriangle,
        Shape_BezierCurve
    };
	

private slots:
	/*void receivepPointEvent(string);
	void receiveLineEvent(string);
	void receiveSectorEvent(string);
	void receiveEllipseEvent(string);*/

protected:
//    鼠标点击事件
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    鼠标移动事件
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
//    鼠标释放事件
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
//	 这个是鼠标上下滚轮的时候会调用
	void wheelEvent(QGraphicsSceneMouseEvent*event);

public:
//    转换成矩形的坐标点（对角线坐标）
    static QRectF getRectByPoints(const QPointF &p1, const QPointF &p2);
//    转换成水平线的坐标点
    static QLineF getHorizontalLine(const QPointF &startPos, const QPointF &endPos);
//    转换成垂直线的坐标点
    static QLineF getVerticalLine(const QPointF &startPos, const QPointF &endPos);
//    转换成圆形的坐标点
    static QRectF getCirclePoints(const QPointF &p1, const QPointF &p2);
//    获取圆弧的起始角度，结束角度和圆弧所在圆的圆心坐标
    static bool getArcAngle(QPointF &p1, QPointF &p2, QPointF &p3, double &begin_angle, double &end_angle, QPointF &center_point, double &Radius);
//    获取圆弧所在的矩形框
    static QRect getRectArc(QPointF &center_point, double &Radius);
//    求三个数值中的最小值
    static double getMinValue(const qreal &a, const qreal &b, const qreal &c);
//    求三个数值中的最大值
    static double getMaxValue(const qreal &a, const qreal &b, const qreal &c);
//    将矩形的坐标点转换成矩形垂直中心线的直线坐标点
    static QLineF getRectToHLine(QRectF &rect);
//    将矩形的坐标点转换成矩形垂直中心线的直线坐标点
    static QLineF getRectToVLine(QRectF &rect);
//    将直线的坐标点转换成坐标点
    static void getLineToPoint(QLineF &line, QVector<QPointF> &point);
	//mat转Qimage
	QImage cvMat_to_QImage(const cv::Mat &mat);

public slots:
//    选择本地图片文件函数
    bool openFile(const QString &filePath);
//    以下函数在CtrlSceneDialog函数中调用
    void setPenWidth(const int w)                   { mPen.setWidth(w); }
    void setPenColor(const QColor &color)       { mPen.setColor(color); }
    QPen pen()                                                  { return mPen; }
    void setBrushColor(const QColor &color)     { mBrush.setColor(color); }
    QBrush brush()                                          { return mBrush; }
    PickupModel pickupmodel()                           { return mPickupModel; }
    void setPickupModel(PickupModel shape)       { mPickupModel = shape; }
	
	void destroyGroup(QGraphicsItemGroup *group);

private:
    PickupModel       mPickupModel;

    QPointF                 mLButtonPressPos;
    QPointF                 mLButtonReleasePos;
    QPointF                 mLButtonMovePos;
    QGraphicsLineItem       *mCurLineItem;
    QGraphicsRectItem       *mCurRectItem;
    QGraphicsPolygonItem    *mCurPolygonItem;
    QGraphicsEllipseItem    *mCurEllipseItem;
    QGraphicsPathItem       *mCurPathItem;
    QPen                    mPen;
    QBrush                  mBrush;
    QGraphicsPixmapItem     *mBackgroundItem;

    QPointF endPoints;

    QPainter *painter;
    int states;

public:

//    //    用于将或得到的绘图坐标点传递到pemainwindow函数中
//        enum Component {
//            PICPOINT ,                   //点
//            PICHLINE,                    //水平线
//            PICVLINE,                    //垂线
//            PICLINE,                     //直线
//            PICRECT,                     //矩形
//            PICELLIPSE,                  //椭圆
//            PICPATH,                     //曲线
//            PICCIRCLE,                   //圆形
//            PICARC,                      //圆弧
//            PICSECTOR,                   //扇形
//            PICRECTWITHHCENTERLINE,      //带有垂直中心线的矩形
//            PICRECTWITHVCENTERLINE,      //带有水平中心线的矩形
//            PICRECTWITHFLAGTRIANGLE,     //带有三角形标记的矩形
//            PICBEZIRCURVE                //贝塞尔曲线
//        };
//        typedef struct{
//            Component ComponentType;
//            QVector<QPointF> points;
//            QPen pen;
//            QBrush brush;
//        }PicComponents;
////        存放每次绘图的时候的临时坐标
//        PicComponents temppiccomponent;
////        存放每次画完一个图形后的所有坐标，一种图形放在同一个vector中
//        QVector<PicComponents> point_component;
//        QVector<PicComponents> hline_component;
//        QVector<PicComponents> vline_component;
//        QVector<PicComponents> line_component;
//        QVector<PicComponents> rect_component;
//        QVector<PicComponents> ellipse_component;
//        QVector<PicComponents> path_component;
//        QVector<PicComponents> circle_component;
//        QVector<PicComponents> arc_component;
//        QVector<PicComponents> sector_component;
//        QVector<PicComponents> rectwithhcenterline_component;
//        QVector<PicComponents> rectwithvcenterline_component;
//        QVector<PicComponents> rectwithflagtriangle_component;
//        QVector<PicComponents> bezircurve_component;

public slots:
//        获取每次绘图的起点坐标
    void get_begin_component(PicComponents &piccomponent, Component ComponentType,
                                QPointF &points, QPen &pen, QBrush &brush);
//        获取下一个坐标点
    void get_next_component(PicComponents &temppiccomponent, QPointF &points);
//        将临时坐标点存放在容器中
    void get_all_component(PicComponents &temppiccomponent, QVector<PicComponents> &point_component);
		
	
};

#endif // CElementPickupScene_H
