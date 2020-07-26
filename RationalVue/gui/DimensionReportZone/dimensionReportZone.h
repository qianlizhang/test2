#ifndef DIMENSIONREPORTZONE_H
#define DIMENSIONREPORTZONE_H

#include <QDockWidget>
#include "occQt.h"

namespace Ui {
class CDimensionReportZoneDockWidget;
}

class CDimensionReportZoneDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit CDimensionReportZoneDockWidget(QWidget *parent = 0);
    ~CDimensionReportZoneDockWidget();

public slots:
	void receiveShow();

signals:
	void commit_receiveShow();

private:
    Ui::CDimensionReportZoneDockWidget *ui;
    occQt *m;
};

#endif // DIMENSIONREPORTZONE_H
