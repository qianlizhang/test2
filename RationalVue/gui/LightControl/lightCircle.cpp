#include "lightCircle.h"
#include <QtMath>
#include <QPainter>
#include <QPixmapCache>
#include <QSize>
#include <algorithm>
#include <QDebug>

lightCircle::lightCircle(QWidget *parent)
    : QWidget(parent)
{
    for(auto &a : m_lightStatusSign)
        a = false;
}

lightCircle::~lightCircle()
{

}


void lightCircle::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //防止绘制的图形走样
    painter.setRenderHint(QPainter::Antialiasing, true);

    //设定半径为窗口高和宽中较小的那一个的一半，每一层宽度为窗口半径的1/8
    qreal radius = (width()>height() ? height()/2 : width()/2);
    qreal arc_height = radius/6;

    painter.translate(width()/2, height()/2);

    //循环画出40个区域
    QColor color;
    for(int arc_layer = 0; arc_layer < 5; arc_layer++)
    {
        for(int fan_area = 0; fan_area < 8; fan_area++)
        {
            if(m_lightStatusSign[arc_layer*8 + fan_area])
                color = m_color_lightOn;
            else
                color = m_color_lightOff;

//            if(arcLayer%2 == 0 && fanArea%2 == 0)
//                color = qRgb(110,190,235);
//            else if(arcLayer%2 == 0 && fanArea%2 != 0)
//                color = qRgb(239,91,155);
//            else if(arcLayer%2 != 0 && fanArea%2 == 0)
//                color = qRgb(101,194,148);
//            else
//                color = qRgb(255,195,14);

            lightDrawArc(&painter, radius, 45*fan_area, 45, arc_layer, arc_height, color);
        }
    }

    //画出中心圆的渐变感
    QRadialGradient radial(0,0,arc_height,-arc_height/3,-arc_height/3);
    radial.setColorAt(0,qRgb(164,164,164));
    radial.setColorAt(1,qRgb(40,31,29));

    painter.setBrush(radial);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(-arc_height, -arc_height, arc_height*2, arc_height*2);

}

void lightCircle::lightDrawArc(QPainter *painter, qreal radius, int start_angle, int span_angle, int arc_layer, qreal arc_height, QColor color)
{
    radius -= arc_height*arc_layer;

    //path是圆弧区域，此时path为扇形
    QRectF rect(-radius, -radius, radius*2, radius*2);
    QPainterPath path;
    path.arcTo(rect, start_angle, span_angle);

    //找到圆弧区域下界
    QPainterPath subPath;
    subPath.addEllipse(rect.adjusted(arc_height, arc_height, -arc_height, -arc_height));

    //此时path为圆弧区域
    path -= subPath;

    //使用填充，开始画
    painter->setBrush(color);
    painter->setPen(QColor(255,195,14,60));
    painter->drawPath(path);
}


void lightCircle::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){

        //找到现在窗口中心的x,y坐标和最外圈圆的半径
        qreal center_x = width()/2, center_y = height()/2;
        qreal radius = (width()>height() ? height()/2 : width()/2);
        //当前鼠标位置
        qreal cur_x = event->pos().x() - center_x;
        qreal cur_y = event->pos().y() - center_y;

        //鼠标位置所在的圆弧层和区域
        qreal cur_distance = sqrt(cur_x * cur_x + cur_y * cur_y);
        int cur_layer = -1;
        if(cur_distance<radius && cur_distance>radius/6){
            if(cur_distance<radius && cur_distance>radius/6*5)
                cur_layer = 0;
            else if(cur_distance<radius/6*5 && cur_distance>radius/6*4)
                cur_layer = 1;
            else if(cur_distance<radius/6*4 && cur_distance>radius/6*3)
                cur_layer = 2;
            else if(cur_distance<radius/6*3 && cur_distance>radius/6*2)
                cur_layer = 3;
            else
                cur_layer = 4;
        }

        int cur_area = -1;
        if(cur_x>0 && cur_y<0 && fabs(cur_x)>fabs(cur_y))
            cur_area = 0;
        else if(cur_x>0 && cur_y<0 && fabs(cur_x)<fabs(cur_y))
            cur_area = 1;
        else if(cur_x<0 && cur_y<0 && fabs(cur_x)<fabs(cur_y))
            cur_area = 2;
        else if(cur_x<0 && cur_y<0 && fabs(cur_x)>fabs(cur_y))
            cur_area = 3;
        else if(cur_x<0 && cur_y>0 && fabs(cur_x)>fabs(cur_y))
            cur_area = 4;
        else if(cur_x<0 && cur_y>0 && fabs(cur_x)<fabs(cur_y))
            cur_area = 5;
        else if(cur_x>0 && cur_y>0 && fabs(cur_x)<fabs(cur_y))
            cur_area = 6;
        else
            cur_area = 7;


        //判断该灯的开闭状态
        if(cur_area>=0 && cur_area<8 && cur_layer>=0 && cur_layer<5)
        {
            if(m_lightStatusSign[cur_layer*8 + cur_area] == false)
                m_lightStatusSign[cur_layer*8 + cur_area] = true;
            else
                m_lightStatusSign[cur_layer*8 + cur_area] = false;
        }

        update();
    }
}
