#include "createOperationZoneLeftControl.h"
#include <quiloader.h>
#include <qfile.h>
#include <qtoolbutton.h>

CCreateOperationZoneLeftControl::CCreateOperationZoneLeftControl(CCommonData *commondata) :CCommonData(commondata)
{
	QUiLoader loader;
	QFile file(":/ui/gui/OperationZoneLeft/operationZoneLeftDockwidget.ui");
	file.open(QFile::ReadOnly);
	m_pOperationZoneLeftDockWidget = static_cast<QDockWidget*>(loader.load(&file));

	file.close();
}

QDockWidget* CCreateOperationZoneLeftControl::init()
{
	return m_pOperationZoneLeftDockWidget;
}

CCreateOperationZoneLeftControl::~CCreateOperationZoneLeftControl()
{
    
}
