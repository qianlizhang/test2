#ifndef GRAPHICEZONE_H
#define GRAPHICEZONE_H

#include <QMainWindow>
#include <QDockWidget>
#include <QGraphicsView>
#include "pemainwindow.h"
#include "cpaintzonemainwindow.h"

using namespace std;

namespace Ui {
class CGraphiceZoneDockWidget;
}

class CElementPickupScene;
class CElementPickupView;

class CGraphiceZoneDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit CGraphiceZoneDockWidget(QWidget *parent = 0);
    ~CGraphiceZoneDockWidget();

	CElementPickupScene     *mScene;
	CElementPickupView      *mView;

public slots:
	void receivePickupModel();
 
signals:
	void commit_receive();

private:

    Ui::CGraphiceZoneDockWidget *ui;
	CPaintZoneMainWindow *m;

	QGraphicsItem             *item;
};

#endif // GRAPHICEZONE_H
