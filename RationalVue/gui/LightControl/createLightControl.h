#ifndef CreateLightControl_H
#define CreateLightControl_H

#include <QWidget>
#include <QDockWidget> 
#include <CommonData.h>


class CCreateLightControlDockWidget:CCommonData
{
//    Q_OBJECT

public:

	 CCreateLightControlDockWidget(CCommonData *commondata);
	~CCreateLightControlDockWidget();

	QDockWidget* init();

	QDockWidget* m_pLightControlDockWidget;



private:

//    Ui::CLightControlDockWidget *ui;

//private slots:
//    void initForm();
};

#endif // CREATELIGHTCONTROL_H
