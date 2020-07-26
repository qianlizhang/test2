#ifndef CREATEOPERATIONZONERIGHT_H
#define CREATEOPERATIONZONERIGHT_H

#include <qfile.h>
#include <quiloader.h>
#include <qdockwidget.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qtablewidget.h>
#include <qcombobox.h>

#include <qdebug.h>

#include "CommonData.h"
class CCreateOperationZoneRight:CCommonData
{
public:
	//CCreateOperationZoneRight();
	CCreateOperationZoneRight(CCommonData*);
    ~CCreateOperationZoneRight();

public:
	QDockWidget *m_pOperationZoneRightDockWidget;
};

#endif // CREATEOPERATIONZONERIGHT_H
