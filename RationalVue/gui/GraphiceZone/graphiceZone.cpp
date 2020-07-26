#include "graphiceZone.h"
#include "ui_graphiceZone.h"

#include "celementpickupscene.h"
#include "celementpickupview.h"

#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDockWidget>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QPainter>

CGraphiceZoneDockWidget::CGraphiceZoneDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::CGraphiceZoneDockWidget),
	mScene(NULL)
{
    ui->setupUi(this);
	
	m = new CPaintZoneMainWindow();
	setWidget(m);

	// view and scene
	//mView = new CElementPickupView();
	//QHBoxLayout *hLay = new QHBoxLayout();
	//hLay->addWidget(mView);
	//mView->setScene(mScene = new CElementPickupScene);

	//关联信号和槽函数
	connect(this, SIGNAL(commit_receive()), m, SLOT(on_action_open_file_triggered()));
	//connect(this, SIGNAL(commit_receive()), this, SLOT(on_action_open_file_triggered()));
}

CGraphiceZoneDockWidget::~CGraphiceZoneDockWidget()
{
    delete ui;
	delete m;
}

//槽函数，用于接收mainwindow函数传来的打开文件消息
void CGraphiceZoneDockWidget::receivePickupModel() {
	emit commit_receive();
}


