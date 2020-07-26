#ifndef CPAINTZONEMAINWINDOW_H
#define CPAINTZONEMAINWINDOW_H

#include "ui_CPaintZoneMainWindow.h"
#include <QMainWindow>

#include <AIS_InteractiveContext.hxx>

class CPaintView;
namespace Ui {
class CPaintZoneMainWindow;
}

class CPaintZoneMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CPaintZoneMainWindow(QWidget *parent = 0);
    ~CPaintZoneMainWindow();
protected:
    //! create all the actions.
    void createActions(void);
   
private slots:
    //! make box test.
    void makeRect(void);

    //! make sphere test.
    void makeCircle(void);

    //! make cylinder test.
    void makeEllipse(void);

	void makePie(void);

	void makeLine(void);

	void makeArc(void);

	void makePoint(void);

private:
    Ui::CPaintZoneMainWindow *ui;
    CPaintView* myCPaintView;
};

#endif // CPAINTZONEMAINWINDOW_H
