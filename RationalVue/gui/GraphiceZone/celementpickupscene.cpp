#include "celementpickupscene.h"
#include "qmath.h"
#include <QDebug>
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>
#include"EdgeDetection.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
using namespace cv;

extern QString globalmPickupModel; //声明外部变量

CElementPickupScene::CElementPickupScene(CCommonData *commondata, QGraphicsScene *parent) :
    QGraphicsScene(parent)
{
    mPickupModel = NoShape;
    mCurLineItem = NULL;
    mCurRectItem = NULL;
    mCurEllipseItem = NULL;
    mCurPathItem = NULL;
    mBackgroundItem = NULL;

	////关联信号和槽函数
	//cpaintzonedockwidget = new CPaintZoneDockWidget;
	//connect(cpaintzonedockwidget, SIGNAL(sendPointClicked(string)), this, SLOT(receivepPointEvent(string)));
	//connect(cpaintzonedockwidget, SIGNAL(sendLineClicked(string)), this, SLOT(receivepLineEvent(string)));
	//connect(cpaintzonedockwidget, SIGNAL(sendSectorClicked(string)), this, SLOT(receiveSectorEvent(string)));
	//connect(cpaintzonedockwidget, SIGNAL(sendEllipseClicked(string)), this, SLOT(receiveEllipseEvent(string)));
	
	
}

//void CElementPickupScene::receivepPointEvent(string) {
//	qDebug() << "is Shape_Point";
//}
//
//void CElementPickupScene::receiveLineEvent(string)
//{
//	qDebug() << "is Shape_Line";
//}
//
//void CElementPickupScene::receiveSectorEvent(string)
//{
//	qDebug() << "is Shape_Sector";
//}
//void CElementPickupScene::receiveEllipseEvent(string)
//{
//	qDebug() << "is Shape_Ellipse";
//}


void CElementPickupScene::wheelEvent(QGraphicsSceneMouseEvent*event) //这个是鼠标上下滚轮的时候会调用
{

}

//    鼠标点击事件
void CElementPickupScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	
	qDebug() << "globalmPickupModel==========" << globalmPickupModel;
	globalmPickupModel == "rect" ? mPickupModel = Shape_Rect : NULL;
	globalmPickupModel == "bezircurve" ? mPickupModel = Shape_BezierCurve : NULL;
	globalmPickupModel == "point" ? mPickupModel = Shape_Point : NULL;
	globalmPickupModel == "line" ? mPickupModel = Shape_Line : NULL;
	globalmPickupModel == "path" ? mPickupModel = Shape_Path : NULL;
	globalmPickupModel == "circle" ? mPickupModel = Shape_Circle : NULL;
	globalmPickupModel == "sector" ? mPickupModel = Shape_Sector : NULL;
	globalmPickupModel == "ellipse" ? mPickupModel = Shape_Ellipse : NULL;
	//globalmPickupModel == "*****" ? mPickupModel = ******* : NULL;
	globalmPickupModel == "arc" ? mPickupModel = Shape_Arc : NULL;
	//globalmPickupModel == "edge detection" 

	if (Qt::LeftButton != event->button())
		return;

    if (!mBackgroundItem)
	{
        qDebug() << "you didn't open a file";
        return;
    }	 

	if (globalmPickupModel == "edge detection")
	{
		CEdgeDetection detector(this);
		detector.detect();
		//m_solution->m_vecPartImages = detector.m_solution->m_vecPartImages;
		//imshow("imshow", m_solution->m_vecPartImages);
		QPixmap pixmap;
		pixmap = QPixmap::fromImage(cvMat_to_QImage(m_solution->m_vecPartImages));

		//    将图片添加进背景中
		mBackgroundItem = addPixmap(pixmap);
		qDebug() << "size==========" << pixmap.size();
	}


    switch (mPickupModel) {
		mPen.setWidth(5);
//    开始画点
    case Shape_Point:
    {
		
        mLButtonPressPos = event->scenePos();
        QPointF points[4];
        points[0] = QPointF(mLButtonPressPos.rx(), mLButtonPressPos.ry() - 20);
        points[1] = QPointF(mLButtonPressPos.rx(), mLButtonPressPos.ry() + 20);
        points[2] = QPointF(mLButtonPressPos.rx() - 20, mLButtonPressPos.ry());
        points[3] = QPointF(mLButtonPressPos.rx() + 20, mLButtonPressPos.ry());
        mCurLineItem = addLine(QLineF(points[0], points[1]), mPen);
        mCurLineItem = addLine(QLineF(points[2], points[3]), mPen);
        mCurLineItem->setParentItem(mBackgroundItem);
        get_begin_component(m_solution->m_designParameter.temppiccomponent, PICPOINT, mLButtonPressPos, mPen, mBrush);
        get_next_component(m_solution->m_designParameter.temppiccomponent, endPoints);
        get_all_component(m_solution->m_designParameter.temppiccomponent, m_solution->m_designParameter.point_component);
        m_solution->m_designParameter.temppiccomponent.points.clear();
    }
        break;

//    开始画水平线
    case Shape_HorLine:
        mLButtonPressPos = event->scenePos();
        mCurLineItem = addLine(QLineF(event->scenePos(), event->scenePos()), mPen);
        get_begin_component(m_solution->m_designParameter.temppiccomponent, PICHLINE, mLButtonPressPos, mPen, mBrush);
        break;

//    开始画垂直线
    case Shape_VerLine:
        mLButtonPressPos = event->scenePos();
        mCurLineItem = addLine(QLineF(event->scenePos(), event->scenePos()), mPen);
        get_begin_component(m_solution->m_designParameter.temppiccomponent, PICVLINE, mLButtonPressPos, mPen, mBrush);
        break;

//    开始画直线
    case Shape_Line:
        mLButtonPressPos = event->scenePos();
        mCurLineItem = addLine(QLineF(event->scenePos(), event->scenePos()), mPen);
        get_begin_component(m_solution->m_designParameter.temppiccomponent, PICLINE, mLButtonPressPos, mPen, mBrush);
        break;

//    开始画矩形
    case Shape_Rect:
        mLButtonPressPos = event->scenePos();
        mCurRectItem = addRect(QRectF(event->scenePos(), event->scenePos()), mPen, mBrush);
        get_begin_component(m_solution->m_designParameter.temppiccomponent, PICRECT, mLButtonPressPos, mPen, mBrush);
        break;

//    开始画椭圆
    case Shape_Ellipse:
        mLButtonPressPos = event->scenePos();
        mCurEllipseItem = addEllipse(QRectF(event->scenePos(), event->scenePos()), mPen, mBrush);
        get_begin_component(m_solution->m_designParameter.temppiccomponent, PICELLIPSE, mLButtonPressPos, mPen, mBrush);
        break;

//    开始画曲线
    case Shape_Path:
        mCurPathItem = new QGraphicsPathItem;
        mLButtonPressPos = event->scenePos();
        mCurPathItem->setPen(mPen);
        mCurPathItem->setBrush(mBrush);
        mCurPathItem->setPath(QPainterPath(event->scenePos()));
        mCurPathItem->setParentItem(mBackgroundItem);
        get_begin_component(m_solution->m_designParameter.temppiccomponent, PICPATH, mLButtonPressPos, mPen, mBrush);
        break;

//    开始画圆
    case Shape_Circle:
        mLButtonPressPos = event->scenePos();
        mCurEllipseItem = addEllipse(QRectF(event->scenePos(), event->scenePos()), mPen, mBrush);
        break;

//    开始画圆弧
    case Shape_Arc:
    {
        mLButtonPressPos = event->scenePos();
        get_begin_component(m_solution->m_designParameter.temppiccomponent, PICARC, mLButtonPressPos, mPen, mBrush);
        endPoints = QPointF(mLButtonPressPos.rx()+2, mLButtonPressPos.ry()+2);
        mCurRectItem = addRect(getRectByPoints(mLButtonPressPos, endPoints));

        if (m_solution->m_designParameter.temppiccomponent.points.size() == 3)
        {
            get_all_component(m_solution->m_designParameter.temppiccomponent, m_solution->m_designParameter.arc_component);

            double begin_angle, all_angle, Radius;
            QPointF center_point;
            getArcAngle(m_solution->m_designParameter.temppiccomponent.points[0], m_solution->m_designParameter.temppiccomponent.points[1], m_solution->m_designParameter.temppiccomponent.points[2], begin_angle, all_angle, center_point, Radius);
            mCurPathItem = new QGraphicsPathItem;
            QRect arc_rect = QRect(getRectArc(center_point, Radius));
            QPainterPath *painterPath = new QPainterPath;
            painterPath->moveTo(m_solution->m_designParameter.temppiccomponent.points[2]); //先移动到最后标记的点
            painterPath->arcTo(arc_rect, begin_angle, all_angle);
            mCurPathItem->setPen(mPen);
            mCurPathItem->setBrush(mBrush);
            mCurPathItem->setPath(*painterPath);
            mCurPathItem->setParentItem(mBackgroundItem);

            m_solution->m_designParameter.temppiccomponent.points.clear();
        }
    }
        break;

//    开始画扇形
    case Shape_Sector:
    {
        mLButtonPressPos = event->scenePos();
        get_begin_component(m_solution->m_designParameter.temppiccomponent, PICSECTOR, mLButtonPressPos, mPen, mBrush);
        endPoints = QPointF(mLButtonPressPos.rx()+2, mLButtonPressPos.ry()+2);
        mCurRectItem = addRect(getRectByPoints(mLButtonPressPos, endPoints));
        if (m_solution->m_designParameter.temppiccomponent.points.size() == 3)
        {
            get_all_component(m_solution->m_designParameter.temppiccomponent, m_solution->m_designParameter.sector_component);

            double begin_angle, all_angle, Radius;
            QPointF center_point;
            getArcAngle(m_solution->m_designParameter.temppiccomponent.points[0], m_solution->m_designParameter.temppiccomponent.points[1], m_solution->m_designParameter.temppiccomponent.points[2], begin_angle, all_angle, center_point, Radius);
            mCurPathItem = new QGraphicsPathItem;
            QRect arc_rect = QRect(getRectArc(center_point, Radius));
            QPainterPath *painterPath = new QPainterPath;
//            画扇形的圆弧部分
            painterPath->moveTo(center_point); //先移动到最后标记的点
            painterPath->arcTo(arc_rect, begin_angle, all_angle);
//            画扇形的两条直线
            painterPath->moveTo(center_point); //先移动到最后标记的点
            painterPath->lineTo(m_solution->m_designParameter.temppiccomponent.points[0]);
            mCurPathItem->setPen(mPen);
            mCurPathItem->setBrush(mBrush);
            mCurPathItem->setPath(*painterPath);
            mCurPathItem->setParentItem(mBackgroundItem);

            m_solution->m_designParameter.temppiccomponent.points.clear();
        }
    }
        break;

//    开始画带有垂直中心线的矩形
    case Shape_RectWithHCenterLine:
        mLButtonPressPos = event->scenePos();
        mCurRectItem = addRect(QRectF(event->scenePos(), event->scenePos()), mPen, mBrush);
        break;

//    开始画带有水平中心线的矩形
    case Shape_RectWithVCenterLine:
        mLButtonPressPos = event->scenePos();
        mCurRectItem = addRect(QRectF(event->scenePos(), event->scenePos()), mPen, mBrush);
        break;

//    开始画带有三角形标记的矩形
    case Shape_RectWithFlagTriangle:
        mLButtonPressPos = event->scenePos();
        mCurRectItem = addRect(QRectF(event->scenePos(), event->scenePos()), mPen, mBrush);
        get_begin_component(m_solution->m_designParameter.temppiccomponent, PICRECTWITHFLAGTRIANGLE, mLButtonPressPos, mPen, mBrush);
        break;


//    开始画贝塞尔曲线
    case Shape_BezierCurve:
    {
//        先画起点和终点，再画中间两边的点
        mLButtonPressPos = event->scenePos();
        get_begin_component(m_solution->m_designParameter.temppiccomponent, PICBEZIRCURVE, mLButtonPressPos, mPen, mBrush);
        endPoints = QPointF(mLButtonPressPos.rx()+2, mLButtonPressPos.ry()+2);
        mCurRectItem = addRect(getRectByPoints(mLButtonPressPos, endPoints));

        if (m_solution->m_designParameter.temppiccomponent.points.size() == 4)
        {
            get_all_component(m_solution->m_designParameter.temppiccomponent, m_solution->m_designParameter.bezircurve_component);

            mCurPathItem = new QGraphicsPathItem;
            QPainterPath *bezierPath = new QPainterPath;//贝塞尔曲线；
            QPointF c1, c2, endPoint;
            c1 = m_solution->m_designParameter.temppiccomponent.points[2];
            c1 = m_solution->m_designParameter.temppiccomponent.points[3];
            endPoint = m_solution->m_designParameter.temppiccomponent.points[1];
            bezierPath->moveTo(m_solution->m_designParameter.temppiccomponent.points[0]);
            bezierPath->cubicTo(c1, c2, endPoint);//(控制点1，控制点2，终点)；
            mCurPathItem->setPen(mPen);
            mCurPathItem->setBrush(mBrush);
            mCurPathItem->setPath(*bezierPath);
            mCurPathItem->setParentItem(mBackgroundItem);
            m_solution->m_designParameter.temppiccomponent.points.clear();
        }


    }
        break;

    default:
        break;
    }

    return QGraphicsScene::mousePressEvent(event);
}


void CElementPickupScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    if (event->button() & Qt::RightButton)
//    {
//        mCurRectItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);
////                | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);

//    }
//    else if (event->button() & Qt::LeftButton)
	/*if (connect(cpaintzonedockwidget, SIGNAL(sendModelLine(string)), this, SLOT(receivePickupModel(string))))
	{
		mCurLineItem->setLine(QLineF(mLButtonPressPos, event->scenePos()));
	}*/

    switch (mPickupModel) {
//    点
    case Shape_Point:
        break;
//    水平线
    case Shape_HorLine:
        mCurLineItem->setLine(QLineF(getHorizontalLine(mLButtonPressPos, event->scenePos())));
        break;
//    垂直线
    case Shape_VerLine:
        mCurLineItem->setLine(QLineF(getVerticalLine(mLButtonPressPos, event->scenePos())));
        break;
//    直线
    case Shape_Line:
        mCurLineItem->setLine(QLineF(mLButtonPressPos, event->scenePos()));
        break;
//    矩形
    case Shape_Rect:
        mCurRectItem->setRect(getRectByPoints(mLButtonPressPos, event->scenePos()));
        mLButtonMovePos = event->scenePos();
        break;
//    椭圆
    case Shape_Ellipse:
        mCurEllipseItem->setRect(getRectByPoints(mLButtonPressPos, event->scenePos()));
        break;
//    曲线
    case Shape_Path:
    {
        mLButtonMovePos = event->scenePos();
        QPainterPath path = mCurPathItem->path();
        path.lineTo(mLButtonMovePos);
        mCurPathItem->setPath(path);
        get_next_component(m_solution->m_designParameter.temppiccomponent, mLButtonMovePos);
    }
        break;
//    圆形
    case Shape_Circle:
        mCurEllipseItem->setRect(getCirclePoints(mLButtonPressPos, event->scenePos()));
        break;
//    圆弧
    case Shape_Arc:
        break;
//    扇形
    case Shape_Sector:
        break;
//    带有垂直中心线的矩形
    case Shape_RectWithHCenterLine:
        mCurRectItem->setRect(getRectByPoints(mLButtonPressPos, event->scenePos()));
        break;
//    带有水平中心线的矩形
    case Shape_RectWithVCenterLine:
        mCurRectItem->setRect(getRectByPoints(mLButtonPressPos, event->scenePos()));
        break;
//    带有三角形标记的矩形
    case Shape_RectWithFlagTriangle:
        mCurRectItem->setRect(getRectByPoints(mLButtonPressPos, event->scenePos()));
        mLButtonMovePos = event->scenePos();
        break;

    default:
        break;
    }
    return QGraphicsScene::mouseMoveEvent(event);
}

void CElementPickupScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    if (event->button() == Qt::RightButton)
//    {
//        mCurRectItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable
//                | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);

//    }
//    else if (event->button() == Qt::LeftButton)
    {
    if (Qt::LeftButton != event->button())
        return;

    switch (mPickupModel) {
//    水平线
    case Shape_HorLine:
    {
        mLButtonReleasePos = event->scenePos();
        QLineF horline = QLineF(getHorizontalLine(mLButtonPressPos, mLButtonReleasePos));
        mCurLineItem = addLine(horline, mPen);
        mCurLineItem->setParentItem(mBackgroundItem);
        mLButtonReleasePos = horline.p2();
        get_next_component(m_solution->m_designParameter.temppiccomponent, mLButtonReleasePos);
        get_all_component(m_solution->m_designParameter.temppiccomponent, m_solution->m_designParameter.hline_component);
        m_solution->m_designParameter.temppiccomponent.points.clear();
    }
        break;
//    垂线
    case Shape_VerLine:
    {
        mLButtonReleasePos = event->scenePos();
        QLineF horline = QLineF(getVerticalLine(mLButtonPressPos, mLButtonReleasePos));
        mCurLineItem = addLine(horline, mPen);
        mCurLineItem->setParentItem(mBackgroundItem);
        mLButtonReleasePos = horline.p2();
        get_next_component(m_solution->m_designParameter.temppiccomponent, mLButtonReleasePos);
        get_all_component(m_solution->m_designParameter.temppiccomponent, m_solution->m_designParameter.vline_component);
        m_solution->m_designParameter.temppiccomponent.points.clear();
    }
        break;
//    直线
    case Shape_Line:
        mLButtonReleasePos = event->scenePos();
        mCurLineItem = addLine(QLineF(mLButtonReleasePos, mLButtonReleasePos), mPen);
        mCurLineItem->setParentItem(mBackgroundItem);

        get_next_component(m_solution->m_designParameter.temppiccomponent, mLButtonReleasePos);
        get_all_component(m_solution->m_designParameter.temppiccomponent, m_solution->m_designParameter.line_component);
        m_solution->m_designParameter.temppiccomponent.points.clear();
        break;
//    矩形
    case Shape_Rect:
        mLButtonReleasePos = event->scenePos();
        mCurRectItem = addRect(QRectF(event->scenePos(), event->scenePos()), mPen, mBrush);
        mCurRectItem->setParentItem(mBackgroundItem);
//        mCurRectItem->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

        get_next_component(m_solution->m_designParameter.temppiccomponent, mLButtonReleasePos);
        get_all_component(m_solution->m_designParameter.temppiccomponent, m_solution->m_designParameter.rect_component);
        m_solution->m_designParameter.temppiccomponent.points.clear();
        break;
//    椭圆
    case Shape_Ellipse:
        mLButtonReleasePos = event->scenePos();      
        mCurEllipseItem = addEllipse(QRectF(event->scenePos(), event->scenePos()), mPen, mBrush);
        mCurEllipseItem->setParentItem(mBackgroundItem);
//        设置椭圆可以移动
//        mCurEllipseItem->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

        get_next_component(m_solution->m_designParameter.temppiccomponent, mLButtonReleasePos);
        get_all_component(m_solution->m_designParameter.temppiccomponent, m_solution->m_designParameter.ellipse_component);
        m_solution->m_designParameter.temppiccomponent.points.clear();
        break;
//    曲线
    case Shape_Path:
    {
        mLButtonReleasePos = event->scenePos();
        QPainterPath path = mCurPathItem->path();
        path.lineTo(mLButtonReleasePos);
        mCurPathItem->setPath(path);

        get_next_component(m_solution->m_designParameter.temppiccomponent, mLButtonReleasePos);
        get_all_component(m_solution->m_designParameter.temppiccomponent, m_solution->m_designParameter.path_component);
        m_solution->m_designParameter.temppiccomponent.points.clear();
    }
        break;
//    圆形
    case Shape_Circle:
    {
        mLButtonReleasePos = event->scenePos();
        QRectF rect;
        rect = getCirclePoints(mLButtonPressPos, mLButtonReleasePos);
        mCurEllipseItem = addEllipse(rect, mPen, mBrush);
        mCurEllipseItem->setParentItem(mBackgroundItem);

        mLButtonPressPos = rect.topLeft();
        mLButtonReleasePos = rect.bottomRight();
        m_solution->m_designParameter.temppiccomponent.points.clear();
        get_begin_component(m_solution->m_designParameter.temppiccomponent, PICCIRCLE, mLButtonPressPos, mPen, mBrush);
        get_next_component(m_solution->m_designParameter.temppiccomponent, mLButtonReleasePos);
        get_all_component(m_solution->m_designParameter.temppiccomponent, m_solution->m_designParameter.circle_component);
        m_solution->m_designParameter.temppiccomponent.points.clear();
    }

        break;
//    圆弧
    case Shape_Arc:
        break;
//    扇形
    case Shape_Sector:
        break;
//    带有垂直中心线的矩形
    case Shape_RectWithHCenterLine:
    {
        mLButtonReleasePos = event->scenePos();
        QRectF rect = getRectByPoints(mLButtonPressPos, event->scenePos());
        m_solution->m_designParameter.temppiccomponent.points.clear();
        mLButtonReleasePos = rect.topLeft();
        get_begin_component(m_solution->m_designParameter.temppiccomponent, PICRECTWITHHCENTERLINE, mLButtonReleasePos, mPen, mBrush);
        mLButtonReleasePos = rect.bottomRight();
        get_next_component(m_solution->m_designParameter.temppiccomponent, mLButtonReleasePos);

        QLineF hline = getRectToHLine(rect);
        QVector<QPointF> points;
        getLineToPoint(hline, points);
        get_next_component(m_solution->m_designParameter.temppiccomponent, points[0]);
        get_next_component(m_solution->m_designParameter.temppiccomponent, points[1]);

        get_all_component(m_solution->m_designParameter.temppiccomponent, m_solution->m_designParameter.rectwithhcenterline_component);
        m_solution->m_designParameter.temppiccomponent.points.clear();

        mCurRectItem = addRect(rect, mPen, mBrush);
        mCurRectItem->setParentItem(mBackgroundItem);
        mCurLineItem = addLine(hline, mPen);
        mCurLineItem->setParentItem(mBackgroundItem);
    }
        break;
//    带有水平中心线的矩形
    case Shape_RectWithVCenterLine:
    {
        mLButtonReleasePos = event->scenePos();
        QRectF rect = getRectByPoints(mLButtonPressPos, mLButtonReleasePos);
        m_solution->m_designParameter.temppiccomponent.points.clear();
        mLButtonReleasePos = rect.topLeft();
        get_begin_component(m_solution->m_designParameter.temppiccomponent, PICRECTWITHVCENTERLINE, mLButtonReleasePos, mPen, mBrush);
        mLButtonReleasePos = rect.topLeft();
        get_next_component(m_solution->m_designParameter.temppiccomponent, mLButtonReleasePos);

        QLineF hline = getRectToVLine(rect);
        QVector<QPointF> points;
        getLineToPoint(hline, points);
        get_next_component(m_solution->m_designParameter.temppiccomponent, points[0]);
        get_next_component(m_solution->m_designParameter.temppiccomponent, points[1]);

        get_all_component(m_solution->m_designParameter.temppiccomponent, m_solution->m_designParameter.rectwithvcenterline_component);
        m_solution->m_designParameter.temppiccomponent.points.clear();

        mCurRectItem = addRect(rect, mPen, mBrush);
        mCurRectItem->setParentItem(mBackgroundItem);
        mCurLineItem = addLine(hline, mPen);
        mCurLineItem->setParentItem(mBackgroundItem);
    }
        break;
//    带有三角形标记的矩形
    case Shape_RectWithFlagTriangle:
    {
        mLButtonReleasePos = event->scenePos();
        mCurRectItem = addRect(QRectF(event->scenePos(), event->scenePos()), mPen, mBrush);
        mCurRectItem->setParentItem(mBackgroundItem);

        QVector<QPointF> triangle;
        triangle.push_back(QPointF(0.5 * (mLButtonPressPos.rx() + mLButtonReleasePos.rx()), mLButtonPressPos.ry()));
        triangle.push_back(QPointF(triangle[0].rx() - 8, triangle[0].ry() - 30));
        triangle.push_back(QPointF(triangle[0].rx() + 8, triangle[0].ry() - 30));
        if (mLButtonPressPos != mLButtonReleasePos)
        {
            mCurPolygonItem = addPolygon(triangle, mPen, mBrush);
            mCurPolygonItem->setParentItem(mBackgroundItem);
        }


        get_next_component(m_solution->m_designParameter.temppiccomponent, mLButtonReleasePos);
        get_all_component(m_solution->m_designParameter.temppiccomponent, m_solution->m_designParameter.rect_component);
        m_solution->m_designParameter.temppiccomponent.points.clear();
    }
        break;

    default:
        break;
    }

    }
    return QGraphicsScene::mouseReleaseEvent(event);
}

//转换矩形的坐标点
QRectF CElementPickupScene::getRectByPoints(const QPointF &p1, const QPointF &p2)
{
    QRectF r;

    if ((p2.x() >= p1.x()) && (p2.y() >= p1.y())) {
        r.setTopLeft(p1);
        r.setBottomRight(p2);

    } else if ((p2.x() < p1.x()) && (p2.y() < p1.y())) {
        r.setTopLeft(p2);
        r.setBottomRight(p1);

    } else if ((p2.x() >= p1.x()) && (p2.y() < p1.y())) {
        r.setLeft(p1.x());
        r.setRight(p2.x());
        r.setTop(p2.y());
        r.setBottom(p1.y());

    } else if ((p2.x() < p1.x()) && (p2.y() >= p1.y())) {
        r.setLeft(p2.x());
        r.setRight(p1.x());
        r.setTop(p1.y());
        r.setBottom(p2.y());

    }

    return r;
}

//转换水平线的坐标点
QLineF CElementPickupScene::getHorizontalLine(const QPointF &startPos, const QPointF &endPos)
{
    QLineF line;
    line.setP1(startPos);
    line.setP2(QPointF(endPos.x(), startPos.y()));
    return line;
}

//转换垂直线的坐标点
QLineF CElementPickupScene::getVerticalLine(const QPointF &startPos, const QPointF &endPos)
{
    QLineF line;
    line.setP1(startPos);
    line.setP2(QPointF(startPos.x(), endPos.y()));
    return line;
}

//转换圆形的坐标点
QRectF CElementPickupScene::getCirclePoints(const QPointF &p1, const QPointF &p2)
{
    QRectF r;
    double l, x1, x2, y1, y2;
    r = getRectByPoints(p1, p2);
    x1 = r.topLeft().rx();
    y1 = r.topLeft().ry();
    x2 = r.bottomRight().rx();
    y2 = r.bottomRight().ry();
    l = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    r.setTopLeft(QPointF((x2+x1-l) * 0.5, (y2+y1-l) * 0.5));
    r.setBottomRight(QPointF((x2+x1+l) * 0.5, (y2+y1+l) * 0.5));
    return r;
}

//转换圆弧的坐标点
bool CElementPickupScene::getArcAngle(QPointF &p1, QPointF &p2, QPointF &p3, double &begin_angle, double &end_angle, QPointF &center_point, double &Radius)
{
    //三点确定一个圆,硬解，可得到表达式（三点一线的时候，则无法形成圆）
     double x1 = p1.x(), x2 = p2.x(), x3 = p3.x();
     double y1 = p1.y(), y2 = p2.y(), y3 = p3.y();
     double a = x1 - x2;
     double b = y1 - y2;
     double c = x1 - x3;
     double d = y1 - y3;
     double e = ((x1 * x1 - x2 * x2) + (y1 * y1 - y2 * y2)) / 2.0;
     double f = ((x1 * x1 - x3 * x3) + (y1 * y1 - y3 * y3)) / 2.0;
     double det = b * c - a * d;
     if((x1 == x2 && x1 == x3) || (y1 == y2 && y1 == y3))
     {
         //三点一线,
         return false;
     }
     double x0 = -(d * e - b * f) / det;
     double y0 = -(a * f - c * e) / det;
     center_point.setX(x0);
     center_point.setY(y0);
     Radius = hypot(x1 - x0, y1 - y0);

     //计算三点的对应的角度
     double angle1 = acos((x1-x0)/(hypot((x1-x0),(y1-y0))));
     double angle2 = acos((x2-x0)/(hypot((x2-x0),(y2-y0))));
     double angle3 = acos((x3-x0)/(hypot((x3-x0),(y3-y0))));
     if(y1-y0 < 0){
         angle1 = 2*PEG_PI - angle1;  //点1在第三、四象限
     }else{
         angle1 = angle1;
     }
     if(y3-y0 < 0){
         angle3 = 2*PEG_PI - angle3; //点2在第三、四象限
     }else{
         angle3 = angle3;
     }

     if(y2-y0 < 0){
         angle2 = 2*PEG_PI - angle2; //点3在第三、四象限
     }else{
         angle2 = angle2;
     }

     //上面计算的角度是基于QGraphicsView中的坐标，需要进行转换为数学坐标中的角度
     angle1 = 360-angle1*180/PEG_PI;
     angle2 = 360-angle2*180/PEG_PI;
     angle3 = 360-angle3*180/PEG_PI;


     QPointF pointf;
     if(angle1 < angle3){
         //1是起点，3是终点
         if(angle2 < angle3 && angle2 > angle1){
             //2在中间，1-2-3
             begin_angle = angle1;
             end_angle = angle3 - angle1;
             pointf = p1;
             p1 = p3;
             p3 = pointf;

         }else{
             // 2在1-3外面   3-2-1
             begin_angle = angle3;
             end_angle = 360-(angle3 - angle1);
         }
     }else{
         //3是起点，1是终点  正方向--  3-2-1
         if(angle2 < angle1 && angle2 > angle3){
             //3-2-1
             begin_angle = angle3;
             end_angle = angle1 - angle3;
         }else{
             //1-2-3
             begin_angle = angle1;
             end_angle = 360-(angle1 - angle3);
             pointf = p1;
             p1 = p3;
             p3 = pointf;
         }
     }
     //begin_angle圆弧在圆上的起点角度，end_angle圆弧的角度
     return true;

}

QRect CElementPickupScene::getRectArc(QPointF &center_point, double &Radius)
{
    QRect r;
    r.setLeft(center_point.rx() - Radius);
    r.setRight(center_point.rx() + Radius);
    r.setTop(center_point.ry() - Radius);
    r.setBottom(center_point.ry() + Radius);
    return r;
}

double CElementPickupScene::getMinValue(const qreal &a, const qreal &b, const qreal &c)
{
    double result;
    if (a <= b && a <= c)
        result = a;
    else if (b <= a && b <= c)
        result = b;
    else
        result = c;
    return result;
}

double CElementPickupScene::getMaxValue(const qreal &a, const qreal &b, const qreal &c)
{
    double result;
    if (a >= b && a > c)
        result = a;
    else if (b >= a && b >= c)
        result = b;
    else
        result = c;
    return result;
}

//获取每次绘图的起点坐标
void CElementPickupScene::get_begin_component(PicComponents &piccomponent, Component ComponentType, QPointF &points, QPen &pen, QBrush &brush)
{
    m_solution->m_designParameter.temppiccomponent.ComponentType = ComponentType;
    m_solution->m_designParameter.temppiccomponent.pen = pen;
    m_solution->m_designParameter.temppiccomponent.brush = brush;
    m_solution->m_designParameter.temppiccomponent.points.push_back(points);
}

//获取下一个坐标点
void CElementPickupScene::get_next_component(PicComponents &temppiccomponent, QPointF &points)
{
	m_solution->m_designParameter.temppiccomponent.points.push_back(points);

}

//将临时坐标点存放在容器中
void CElementPickupScene::get_all_component(PicComponents &temppiccomponent, QVector<PicComponents> &point_component)
{
	m_solution->m_designParameter.point_component.push_back(m_solution->m_designParameter.temppiccomponent);

}

//    将矩形的坐标点转换成矩形垂直中心线的直线坐标点
QLineF CElementPickupScene::getRectToHLine(QRectF &rect)
{
    QLineF line;
    QPointF point1, point2;
    point1.rx() = 0.5 * (rect.topLeft().rx() + rect.bottomRight().rx());
    point1.ry() = rect.topLeft().ry();
    point2.rx() = point1.rx();
    point2.ry() = rect.bottomRight().ry();
    line.setPoints(point1, point2);
    return line;

}
//    将矩形的坐标点转换成矩形水平中心线的直线坐标点
QLineF CElementPickupScene::getRectToVLine(QRectF &rect)
{
    QLineF line;
    QPointF point1, point2;
    point1.rx() = rect.topLeft().rx();
    point1.ry() = 0.5 * (rect.topLeft().ry() + rect.bottomRight().ry());
    point2.rx() = rect.bottomRight().rx();
    point2.ry() = point1.ry();
    line.setPoints(point1, point2);
    return line;
}
//    将直线的坐标点转换成坐标点
void CElementPickupScene::getLineToPoint(QLineF &line, QVector<QPointF> &point)
{
    point.push_back(line.p1());
    point.push_back(line.p2());
}
QImage CElementPickupScene::cvMat_to_QImage(const cv::Mat &mat) {
	switch (mat.type())
	{
		// 8-bit, 4 channel
	case CV_8UC4:
	{
		QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB32);
		return image;
	}

	// 8-bit, 3 channel
	case CV_8UC3:
	{
		QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}

	// 8-bit, 1 channel
	case CV_8UC1:
	{
		static QVector<QRgb>  sColorTable;
		// only create our color table once
		if (sColorTable.isEmpty())
		{
			for (int i = 0; i < 256; ++i)
				sColorTable.push_back(qRgb(i, i, i));
		}
		QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
		image.setColorTable(sColorTable);
		return image;
	}

	default:
		qDebug("Image format is not supported: depth=%d and %d channels\n", mat.depth(), mat.channels());
		break;
	}
	return QImage();
}
//打开文件
bool CElementPickupScene::openFile(const QString &filePath)
{
    clear();
    setSceneRect(QRectF());

	m_solution->m_vecPartImages = cv::imread(filePath.toStdString());
	//m_solution->m_vecPartImages.resize(800, 600);

	qDebug() << "=============" << m_solution->m_vecPartImages.rows << "cols:" << m_solution->m_vecPartImages.cols;
    QPixmap pixmap;
	/*pixmap = QPixmap::fromImage(cvMat_to_QImage(m_solution->m_vecPartImages));*/
    pixmap.load(filePath);
    if (pixmap.isNull())
        return false;

//    将图片添加进背景中
    mBackgroundItem = addPixmap(pixmap);
	qDebug() << "size==========" << pixmap.size();
    return true;
}


void CElementPickupScene::destroyGroup(QGraphicsItemGroup *group)
{
	group->setSelected(false);
	foreach(QGraphicsItem *item, group->childItems()) {
		item->setSelected(true);
		group->removeFromGroup(item);
	}
	removeItem(group);
	delete group;
}
