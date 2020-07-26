#ifndef MACHINESTATUSZONE_H
#define MACHINESTATUSZONE_H

#include <QDockWidget>
#include <QResizeEvent>
#include <QSize>
#include <QComboBox>
#include <QToolButton>
#include <QLCDNumber>
#include <CommonData.h>
class CCreateMachineStatusZone:CCommonData
{
public:
    CCreateMachineStatusZone(CCommonData *commondata);
    bool m_bIsLock=true;
	QDockWidget * m_pMachineStatusZoneDockWidget;
	QDockWidget* init();
	QComboBox * m_pSmallDecimalCountComboBox;
	QToolButton * m_pLockButton;
	QToolButton * m_pResetButton;
	QLCDNumber * m_pLCDX;
	QLCDNumber * m_pLCDY;
	QLCDNumber * m_pLCDZ;
    ~CCreateMachineStatusZone();
};

#endif // MACHINESTATUSZONE_H
