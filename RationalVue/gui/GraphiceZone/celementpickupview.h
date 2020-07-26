#ifndef CELEMENTPICKUPVIEW_H
#define CELEMENTPICKUPVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>

class CElementPickupView : public QGraphicsView
{
    Q_OBJECT
public:
    CElementPickupView(QWidget *parent = 0);

protected:
    /*void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);*/
    void wheelEvent(QWheelEvent *event);

private slots:
    void onScorllBarRangeChanged(int min, int max);

public slots:
    void zoomIn();
    void zoomOut();
    void showOriginalSize();
    void showFitViewSize();
    void rotate90Clockwise();
    void rotate90AntiClockwise();
    void rotate180();

    QSize getViewEntireSize();

private:
    QPointF mLButtonPressPos;
    QPointF mViewCenterAtScene;

    double  mZoomRate;
};

#endif // CElementPickupView_H
