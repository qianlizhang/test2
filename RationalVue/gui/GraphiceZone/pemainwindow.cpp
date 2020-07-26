#include "pemainwindow.h"
#include "ui_pemainwindow.h"

#include "celementpickupscene.h"
#include "celementpickupview.h"

#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDockWidget>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QPainter>


PEMainWindow::PEMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PEMainWindow),
    mScene(NULL)
{
    ui->setupUi(this);

    // view and scene
    mView = new CElementPickupView(centralWidget());
    QHBoxLayout *hLay = new QHBoxLayout(centralWidget());
    hLay->addWidget(mView);
    mView->setScene(mScene = new CElementPickupScene);

}

PEMainWindow::~PEMainWindow()
{
    delete ui;
}

void PEMainWindow::on_action_open_file_triggered()
{
    QString filePath = QFileDialog::getOpenFileName();
    //QString filePath = "/Users/chenjian/Downloads/test.jpeg";
    qDebug() << "filepath" << filePath;
    if (filePath.isEmpty())
        return;

    if (!mScene->openFile(filePath))
        QMessageBox::warning(this, "Warning", "Open file failed", QMessageBox::Yes);
}


//void PEMainWindow::on_action_save_file_triggered()
//{
//    qDebug() << "save file";
//    QSize mysize(mScene->width(), mScene->height());
//    QImage image(mysize,QImage::Format_RGB32);
//    QPainter painter(&image);
//    image.fill(Qt::white);//用白色填充
//    painter.begin(&image);
//
//    if(mScene->point_component.size() > 0)
//    {
//        for (int i = 0; i < mScene->point_component.size(); i++)
//        {
//            painter.setPen(mScene->point_component[i].pen);
//            painter.setBrush(mScene->point_component[i].brush);
//            //画点
//            if (mScene->point_component[i].ComponentType == mScene->PICPOINT)
//            {
//                QRectF selectedRect = QRectF(mScene->point_component[i].points[0], mScene->point_component[i].points[1]);
//                painter.drawRect(selectedRect);
//            }
//        }
//    }
//
////    画垂线
//    if(mScene->hline_component.size() > 0)
//    {
//        for (int i = 0; i < mScene->hline_component.size(); i++)
//        {
//            painter.setPen(mScene->hline_component[i].pen);
//            painter.setBrush(mScene->hline_component[i].brush);
//            if (mScene->hline_component[i].ComponentType == mScene->PICHLINE)
//            {
//                QLineF selectedRect = QLineF(mScene->hline_component[i].points[0], mScene->hline_component[i].points[1]);
//                painter.drawLine(selectedRect);
//            }
//        }
//    }
//
////    画水平线
//    if(mScene->vline_component.size() > 0)
//    {
//        for (int i = 0; i < mScene->vline_component.size(); i++)
//        {
//            painter.setPen(mScene->vline_component[i].pen);
//            painter.setBrush(mScene->vline_component[i].brush);
//            if (mScene->vline_component[i].ComponentType == mScene->PICVLINE)
//            {
//                QLineF selectedRect = QLineF(mScene->vline_component[i].points[0], mScene->vline_component[i].points[1]);
//                painter.drawLine(selectedRect);
//            }
//        }
//    }
////    画直线
//    if(mScene->line_component.size() > 0)
//    {
//        for (int i = 0; i < mScene->line_component.size(); i++)
//        {
//            painter.setPen(mScene->line_component[i].pen);
//            painter.setBrush(mScene->line_component[i].brush);
//            if (mScene->line_component[i].ComponentType == mScene->PICLINE)
//            {
//                QLineF selectedRect = QLineF(mScene->line_component[i].points[0], mScene->line_component[i].points[1]);
//                painter.drawLine(selectedRect);
//            }
//        }
//    }
////    画矩形
//    if(mScene->rect_component.size() > 0)
//    {
//        for (int i = 0; i < mScene->rect_component.size(); i++)
//        {
//            painter.setPen(mScene->rect_component[i].pen);
//            painter.setBrush(mScene->rect_component[i].brush);
//            if (mScene->rect_component[i].ComponentType == mScene->PICRECT)
//            {
//                QRectF selectedRect = QRectF(mScene->rect_component[i].points[0], mScene->rect_component[i].points[1]);
//                painter.drawRect(selectedRect);
//            }
//        }
//    }
////    画椭圆
//    if(mScene->ellipse_component.size() > 0)
//    {
//        for (int i = 0; i < mScene->ellipse_component.size(); i++)
//        {
//            painter.setPen(mScene->ellipse_component[i].pen);
//            painter.setBrush(mScene->ellipse_component[i].brush);
//            if (mScene->ellipse_component[i].ComponentType == mScene->PICELLIPSE)
//            {
//                QRectF selectedRect = QRectF(mScene->ellipse_component[i].points[0], mScene->ellipse_component[i].points[1]);
//                painter.drawEllipse(selectedRect);
//            }
//        }
//    }
////    画曲线
//    if(mScene->path_component.size() > 0)
//    {
//        for (int i = 0; i < mScene->path_component.size(); i++)
//        {
//            painter.setPen(mScene->path_component[i].pen);
//            painter.setBrush(mScene->path_component[i].brush);
//            if (mScene->path_component[i].ComponentType == mScene->PICPATH)
//            {
//                painter.drawPolyline(mScene->path_component[i].points);
//            }
//        }
//    }
////    画圆形
//    if(mScene->circle_component.size() > 0)
//    {
//        for (int i = 0; i < mScene->circle_component.size(); i++)
//        {
//            painter.setPen(mScene->circle_component[i].pen);
//            painter.setBrush(mScene->circle_component[i].brush);
//            if (mScene->circle_component[i].ComponentType == mScene->PICCIRCLE)
//            {
//                QRectF selectedRect = QRectF(mScene->circle_component[i].points[0], mScene->circle_component[i].points[1]);
//                painter.drawEllipse(selectedRect);
//            }
//        }
//    }
////    画圆弧
//    if(mScene->arc_component.size() > 0)
//    {
//        for (int i = 0; i < mScene->arc_component.size(); i++)
//        {
//            painter.setPen(mScene->arc_component[i].pen);
//            painter.setBrush(mScene->arc_component[i].brush);
//            double begin_angle, end_angle, Radius;
//            QPointF points[3], center_point;
//            points[0] = mScene->arc_component[i].points[0];
//            points[1] = mScene->arc_component[i].points[1];
//            points[2] = mScene->arc_component[i].points[2];
//            if (mScene->arc_component[i].ComponentType == mScene->PICARC)
//            {
//                if (mScene->getArcAngle(points[0], points[1], points[2], begin_angle, end_angle, center_point, Radius))
//                {
//                    QRect rect = QRect(mScene->getRectArc(center_point, Radius));
//                    painter.drawArc(rect, begin_angle*16, end_angle*16);
//                }
//            }
//        }
//    }
//
////    画扇形
//    if(mScene->sector_component.size() > 0)
//    {
//        for (int i = 0; i < mScene->sector_component.size(); i++)
//        {
//            painter.setPen(mScene->sector_component[i].pen);
//            painter.setBrush(mScene->sector_component[i].brush);
//            double begin_angle, end_angle, Radius;
//            QPointF points[3], center_point;
//            points[0] = mScene->sector_component[i].points[0];
//            points[1] = mScene->sector_component[i].points[1];
//            points[2] = mScene->sector_component[i].points[2];
//            if (mScene->sector_component[i].ComponentType == mScene->PICSECTOR)
//            {
//                if (mScene->getArcAngle(points[0], points[1], points[2], begin_angle, end_angle, center_point, Radius))
//                {
//                    QRect rect = QRect(mScene->getRectArc(center_point, Radius));
//                    painter.drawPie(rect, begin_angle*16, end_angle*16);
//                }
//            }
//        }
//    }
//
////    画带有垂直中心线的矩形
//    if(mScene->rectwithhcenterline_component.size() > 0)
//    {
//        for (int i = 0; i < mScene->rectwithhcenterline_component.size(); i++)
//        {
//            painter.setPen(mScene->rectwithhcenterline_component[i].pen);
//            painter.setBrush(mScene->rectwithhcenterline_component[i].brush);
//            if (mScene->rectwithhcenterline_component[i].ComponentType == mScene->PICRECTWITHHCENTERLINE)
//            {
//                QRectF selectedRect = QRectF(mScene->rectwithhcenterline_component[i].points[0], mScene->rectwithhcenterline_component[i].points[1]);
//                QLineF selectedLine = QLineF(mScene->rectwithhcenterline_component[i].points[2], mScene->rectwithhcenterline_component[i].points[3]);
//                painter.drawRect(selectedRect);
//                painter.drawLine(selectedLine);
//            }
//        }
//    }
//
////    画带有水平中心线的矩形
//    if(mScene->rectwithvcenterline_component.size() > 0)
//    {
//        for (int i = 0; i < mScene->rectwithvcenterline_component.size(); i++)
//        {
//            painter.setPen(mScene->rectwithvcenterline_component[i].pen);
//            painter.setBrush(mScene->rectwithvcenterline_component[i].brush);
//            if (mScene->rectwithvcenterline_component[i].ComponentType == mScene->PICRECTWITHVCENTERLINE)
//            {
//                QRectF selectedRect = QRectF(mScene->rectwithvcenterline_component[i].points[0], mScene->rectwithvcenterline_component[i].points[1]);
//                QLineF selectedLine = QLineF(mScene->rectwithvcenterline_component[i].points[2], mScene->rectwithvcenterline_component[i].points[3]);
//                painter.drawRect(selectedRect);
//                painter.drawLine(selectedLine);
//
//            }
//        }
//    }
//
////    画带有三角形标记的矩形
//    if(mScene->rectwithflagtriangle_component.size() > 0)
//    {
//        for (int i = 0; i < mScene->rectwithflagtriangle_component.size(); i++)
//        {
//            painter.setPen(mScene->rectwithflagtriangle_component[i].pen);
//            painter.setBrush(mScene->rectwithflagtriangle_component[i].brush);
//            if (mScene->rectwithflagtriangle_component[i].ComponentType == mScene->PICRECTWITHFLAGTRIANGLE)
//            {
//
//            }
//        }
//    }
//
////    画贝塞尔曲线
//    if(mScene->bezircurve_component.size() > 0)
//    {
//        for (int i = 0; i < mScene->bezircurve_component.size(); i++)
//        {
//            painter.setPen(mScene->bezircurve_component[i].pen);
//            painter.setBrush(mScene->bezircurve_component[i].brush);
//            if (mScene->bezircurve_component[i].ComponentType == mScene->PICBEZIRCURVE)
//            {
//                QPainterPath bezircurve;
//                QPointF c1, c2, endPoint;
//                c1 = mScene->bezircurve_component[i].points[2];
//                c2 = mScene->bezircurve_component[i].points[3];
//                endPoint = mScene->bezircurve_component[i].points[1];
//                bezircurve.moveTo(mScene->bezircurve_component[i].points[0]);
//                bezircurve.cubicTo(c1, c2, endPoint);
//                painter.drawPath(bezircurve);
//            }
//        }
//
//    }
//
//
//    painter.end();
////    QString filename = QFileDialog::getSaveFileName(this,
////            tr("Save Image"),
////            "",
////            tr("*.bmp;; *.png;; *.jpg;; *.tif;; *.GIF")); //选择路径
////    if (filename.isEmpty())
////    {
////        return;
////    }
////    else
////    {
////        image.save(filename);
//
////    }
//    image.save("/Users/chenjian/Downloads/111.png");
//
//
//    return;
//}
//
