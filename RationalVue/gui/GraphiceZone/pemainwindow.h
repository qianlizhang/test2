#ifndef PEMAINWINDOW_H
#define PEMAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QGraphicsView>
using namespace std;

namespace Ui {
class PEMainWindow;
}

class CElementPickupScene;
class CElementPickupView;

class PEMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PEMainWindow(QWidget *parent = 0);
    ~PEMainWindow();
	CElementPickupScene     *mScene;
	CElementPickupView      *mView;

private slots:
    void on_action_open_file_triggered();
    //void on_action_save_file_triggered();

private:
    Ui::PEMainWindow *ui;

    QGraphicsItem             *item;
};

#endif // PEMAINWINDOW_H
