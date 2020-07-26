#include "WindowNotation.h"
#include <QIntValidator>



QWindowNotation::QWindowNotation(QWidget* parent)
{

	this->setGeometry(0, 0, 2048, 1024);
	gridLayout = new QGridLayout();
	gridLayout2 = new QGridLayout();
	scrollArea = new QScrollArea();
	scrollArea->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

	widget = new QWidget();

#define SHOWIMG(num, row, col)	\
	LbImg##num = new MyLabel(widget);	\
	LbImg##num->setPixmap(QPixmap(#num".jpg"));	\
	LbImg##num->setAlignment(Qt::AlignCenter);	\
	gridLayout->addWidget(LbImg##num,row,col);

	SHOWIMG(0, 0, 0)
	SHOWIMG(1, 0, 1)
	SHOWIMG(10, 1, 0)
	SHOWIMG(11, 1, 1)
	SHOWIMG(20, 2, 0)
	SHOWIMG(21, 2, 1)
	SHOWIMG(30, 3, 0)
	SHOWIMG(31, 3, 1)
	SHOWIMG(40, 4, 0)
	SHOWIMG(41, 4, 1)
	SHOWIMG(50, 5, 0)
	SHOWIMG(51, 5, 1)
	SHOWIMG(60, 6, 0)
	SHOWIMG(61, 6, 1)


/*	LbImg0 = new MyLabel(widget);
	LbImg0->setPixmap(QPixmap("0.BMP"));
	LbImg0->setAlignment(Qt::AlignCenter);
	gridLayout->addWidget(LbImg0, 0, 0);


	LbImg1 = new MyLabel(widget);
	LbImg1->setPixmap(QPixmap("1.BMP"));
	LbImg1->setAlignment(Qt::AlignCenter);
	gridLayout->addWidget(LbImg1, 0, 1);

	LbImg10 = new MyLabel(widget);
	LbImg10->setPixmap(QPixmap("10.BMP"));
	LbImg10->setAlignment(Qt::AlignCenter);
	gridLayout->addWidget(LbImg10, 1, 0);

	LbImg11 = new MyLabel(widget);
	LbImg11->setPixmap(QPixmap("11.BMP"));
	LbImg11->setAlignment(Qt::AlignCenter);
	gridLayout->addWidget(LbImg11, 1, 1);
*/


	widget->setLayout(gridLayout);
	scrollArea->setWidget(widget);
	gridLayout2->addWidget(scrollArea);
	this->setLayout(gridLayout2);

#undef SHOWIMG

}


QWindowNotation::~QWindowNotation()
{
	//delete gridWidget;
	delete widget;
	//delete gridLayout;
	delete gridLayout2;
	delete scrollArea;
//	delete LbImg0; delete LbImg1; delete LbImg10; delete LbImg11; delete LbImg20; delete LbImg21; delete LbImg30; delete LbImg31;
//	delete LbImg40; delete LbImg41; delete LbImg50; delete LbImg51; delete LbImg60; delete LbImg61;

}


NotationDialog::NotationDialog(QWidget* parent)
{
	this->setWindowTitle(QStringLiteral("标记窗口"));
	this->setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint);
	LbUnit = new QLabel();
	LbFloor = new QLabel();
	LbRoom = new QLabel();


	OKButton = new QPushButton();
	CancelButton = new QPushButton();
	LEUnit = new QLineEdit();
	LEFloor = new QLineEdit();
	LERoom = new QLineEdit();
	hlayout1 = new QHBoxLayout();
	hlayout2 = new QHBoxLayout();
	hlayout3 = new QHBoxLayout();
	hlayout4 = new QHBoxLayout();
	pLayout = new QVBoxLayout();

	//格式验证
	ival = new QIntValidator();
	ival->setRange(1, 100);
	LEUnit->setValidator(ival);
	LEFloor->setValidator(ival);
	LERoom->setValidator(ival);

	LbUnit->setText(QStringLiteral("单元号"));

	hlayout1->addWidget(LbUnit);
	hlayout1->addWidget(LEUnit);


	LbFloor->setText(QStringLiteral("楼层号"));

	hlayout2->addWidget(LbFloor);
	hlayout2->addWidget(LEFloor);

	LbRoom->setText(QStringLiteral("房间号"));
	hlayout3->addWidget(LbRoom);
	hlayout3->addWidget(LERoom);
	

	OKButton->setText(QStringLiteral("确定"));
	CancelButton->setText(QStringLiteral("取消"));
	hlayout4->addWidget(OKButton);
	hlayout4->addWidget(CancelButton);


	pLayout->addLayout(hlayout1);
	pLayout->addLayout(hlayout2);
	pLayout->addLayout(hlayout3);
	pLayout->addLayout(hlayout4);
	this->setLayout(pLayout);

	connect(OKButton, &QPushButton::clicked, this, &NotationDialog::OKClicked);
	connect(CancelButton, &QPushButton::clicked, this, &NotationDialog::CancelClicked);
}

NotationDialog::~NotationDialog()
{
	delete LbUnit; delete LbFloor; delete LbRoom; delete OKButton; delete CancelButton;
	delete LEUnit; delete LEFloor;
	delete hlayout1; delete hlayout2; delete hlayout3,delete hlayout4;
	delete pLayout;
	delete ival;
}

void NotationDialog::OKClicked()
{
	int floor = LEFloor->text().toInt();
	int unit = LEUnit->text().toInt();
	int room = LERoom->text().toInt();

	emit infoSig(floor, unit, room);
	LEFloor->clear();
	LEUnit->clear();
	LERoom->clear();
	this->hide();
}


void NotationDialog::CancelClicked()
{
	//this->~NotationDialog();
	LEFloor->clear();
	LEUnit->clear();
	LERoom->clear();
	this->hide();
}


void MyLabel::paintEvent(QPaintEvent* event) 
{
	QLabel::paintEvent(event);
	//用鼠标拖出一个矩形
	
	int x, y, w, h;
	x = lastPoint.x();
	y = lastPoint.y();
	w = endPoint.x() - x;
	h = endPoint.y() - y;
	QPainter painter(this);
	painter.fillRect(x, y, w, h, *color);
	//if (isDrawing)
	//{
	//	tempPix = pix;
	//	QPainter pp(&tempPix);
	//	pp.drawRect(x, y, w, h);
	//	painter.drawPixmap(0, 0, tempPix);
	//}
	//else
	//{
	//	QPainter pp(&pix);
	//	pp.drawRect(x, y, w, h);
	//	painter.drawPixmap(0, 0, pix);
	//}
	

}

void MyLabel::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		lastPoint = event->pos();
	}
}

void MyLabel::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons()&Qt::LeftButton)
	{
		endPoint = event->pos();
		update();  //执行painterEvent函数重绘
	}
}

void MyLabel::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		endPoint = event->pos();
		update();
	}
	notationDialog->show();
}

void MyLabel::infoSlot(int floor, int unit, int room)
{
	std::vector<int>node{};
	//记录窗户的x方向上下边界、y方向上下边界
	node.push_back(lastPoint.x());
	node.push_back(endPoint.x());
	node.push_back(lastPoint.y());
	node.push_back(endPoint.y());
	windows win(node, floor, unit, room);

	Windows.push_back(win);

}
void QWindowNotation::SavewindowInformation(MyLabel* Img,int id)
{
	std::string filename;
	filename = "windows" + std::to_string(id)+".csv";
	QString str = QString::fromStdString(filename);
	
	QFile file(str);
	if (!file.open(QIODevice::WriteOnly| QIODevice::Text))

	{

		

		return;

	}
	QTextStream out(&file);
	int len = Img->Windows.size();
	for (int i = 0; i < len; i++)
	{
		
		out << Img->Windows[i].node[0] <<"\t"<< Img->Windows[i].node[1] << "\t" << Img->Windows[i].node[2] << "\t" <<
			Img->Windows[i].node[3] << "\t" << Img->Windows[i].floor << "\t" << Img->Windows[i].unit << "\t" << Img->Windows[i].room << "\t" << endl;
			
	}
	

}
void QWindowNotation:: closeEvent(QCloseEvent *event)
{
	auto temp = QMessageBox::information(this, "tooltip", QString::fromLocal8Bit("你是否要关闭?"), QMessageBox::Yes | QMessageBox::No);
	//获取创建的csv文件名
	SavewindowInformation(LbImg0, 0);
	SavewindowInformation(LbImg1, 1);
	SavewindowInformation(LbImg10, 10);
	SavewindowInformation(LbImg11, 11);
	SavewindowInformation(LbImg20, 20);
	SavewindowInformation(LbImg21, 21);
	SavewindowInformation(LbImg30, 30);
	SavewindowInformation(LbImg31, 31);
	SavewindowInformation(LbImg40, 40);
	SavewindowInformation(LbImg41, 41);
	SavewindowInformation(LbImg50, 50);
	SavewindowInformation(LbImg51, 51);
	SavewindowInformation(LbImg60, 60);
	SavewindowInformation(LbImg61, 61);
}