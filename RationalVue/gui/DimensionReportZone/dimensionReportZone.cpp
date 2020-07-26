#include "dimensionReportZone.h"
#include "ui_dimensionReportZone.h"

CDimensionReportZoneDockWidget::CDimensionReportZoneDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::CDimensionReportZoneDockWidget)
{
    ui->setupUi(this);
    m = new occQt();
    setWidget(m);

	connect(this, SIGNAL(commit_receiveShow()), m, SLOT(createToolBars()));
}

CDimensionReportZoneDockWidget::~CDimensionReportZoneDockWidget()
{
    delete ui;
      delete m;
}
void CDimensionReportZoneDockWidget::receiveShow()
{
	emit commit_receiveShow();
}