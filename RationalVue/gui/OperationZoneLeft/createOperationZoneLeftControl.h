#ifndef CREATEOPERATIONZONELEFTCONTROL_H
#define CREATEOPERATIONZONELEFTCONTROL_H

#include <QDockWidget>
#include "CommonData.h"

class CCreateOperationZoneLeftControl : public CCommonData
{
public:
	CCreateOperationZoneLeftControl(CCommonData *commondata);
    ~CCreateOperationZoneLeftControl();
	QDockWidget* init();
	QDockWidget* m_pOperationZoneLeftDockWidget;
};

#endif // CREATEOPERATIONZONELEFTCONTROL_H
