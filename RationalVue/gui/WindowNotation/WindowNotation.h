#pragma once
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>
#include <QLabel>
#include <QApplication>
#include <QDebug>
#include <QMouseEvent>
#include <QString>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QColor>
#include <vector>
#include <QIntValidator>
#include<qmessagebox.h>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QString>
#include <QDateTime>

struct windows
{
	windows(std::vector<int>node_, int floor_, int unit_, int room_) :
		node(node_), floor(floor_), unit(unit_), room(room_) {}
	std::vector<int>node;//记录窗户的x方向上下边界、y方向上下边界
	int floor;//记录窗户所属楼层
	int unit;//记录窗户所述单元
	int room;//房间号
};

class NotationDialog : public QWidget
{
	Q_OBJECT

public:
	NotationDialog(QWidget* parent);
	~NotationDialog();

signals:
	void infoSig(int, int, int);



private:
	QLabel *LbUnit, *LbFloor,*LbRoom;
	QPushButton *OKButton,*CancelButton;
	QLineEdit *LEUnit,*LEFloor,*LERoom;
	QHBoxLayout *hlayout1, *hlayout2,*hlayout3,*hlayout4;
	QVBoxLayout *pLayout;
	QIntValidator* ival;


private:
	void OKClicked();
	void CancelClicked();

};


class MyLabel : public QLabel
{
	Q_OBJECT


public:
//	MyLabel() = default;
	MyLabel(QWidget* widget) :QLabel(widget) 
	{ 
		notationDialog = new NotationDialog(this); 
		color = new QColor(120, 0, 0, 100);
		connect(notationDialog,SIGNAL(infoSig(int,int,int)),this,SLOT(infoSlot(int,int,int)));


	}

	~MyLabel() { delete notationDialog; delete color; }


	std::vector<windows> Windows;

public slots:
	void infoSlot(int, int, int);

protected:
	void paintEvent(QPaintEvent*);  
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent*);

	//void mousePressEvent(QMouseEvent* event) {
	//	qDebug() << "mousePreeEvent";
	//	qDebug() << event->x() << " : " << event->y();
	//	int xoffset = (this->contentsRect().width() - this->pixmap()->rect().width()) / 2;
	//	int yoffset = (this->contentsRect().height() - this->pixmap()->rect().height()) / 2;
	//	qDebug() << "modifide " << event->x() - xoffset << " : " << event->y() - yoffset;
	//	notationDialog->show();

	//}

private:
	NotationDialog* notationDialog;
	QPixmap pix;
	QPoint lastPoint;
	QPoint endPoint;


	QPixmap tempPix;
	QColor* color;

};

class QWindowNotation : public QWidget
{
	Q_OBJECT

public:
	explicit QWindowNotation(QWidget* parent);
	~QWindowNotation();
	void closeEvent(QCloseEvent *event);
	void SavewindowInformation(MyLabel* Img,int id);
private:
	QWidget* gridWidget;
	QWidget* widget;
	QGridLayout *gridLayout, *gridLayout2;
	QScrollArea* scrollArea;
	MyLabel *LbImg0, *LbImg1, *LbImg10, *LbImg11, *LbImg20, *LbImg21, *LbImg30, *LbImg31;
	MyLabel *LbImg40, *LbImg41, *LbImg50, *LbImg51, *LbImg60, *LbImg61;
};

