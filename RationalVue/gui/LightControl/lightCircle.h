#ifndef LIGHTCIRCLE_H
#define LIGHTCIRCLE_H

#include <QWidget>
#include <QMouseEvent>
#include <QRadialGradient>

class lightCircle : public QWidget
{
    Q_OBJECT

public:
    lightCircle(QWidget *parent = 0);
    ~lightCircle();

	QSize sizeHint()
	{
		return QSize(180, 180);
	}

    bool m_lightStatusSign[40];

protected:

    QColor m_color_lightOff = qRgb(70,69,71), m_color_lightOn = qRgb(252,240,110);


    void paintEvent(QPaintEvent *);

    void lightDrawArc(QPainter *painter, qreal radius, int start_angle, int span_angle, int arc_layer, qreal arc_height, QColor color);

    void mousePressEvent(QMouseEvent *event);


};

#endif // LIGHTCIRCLE_H
