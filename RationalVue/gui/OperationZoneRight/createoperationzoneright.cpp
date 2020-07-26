#include "createoperationzoneright.h"

CCreateOperationZoneRight::CCreateOperationZoneRight(CCommonData* commonData):CCommonData(commonData)
{
	QUiLoader loader;
	QFile file(":/ui/gui/OperationZoneRight/operationzoneright.ui");  //ui路径可能需要略作改动
	file.open(QFile::ReadOnly);

	m_pOperationZoneRightDockWidget = static_cast<QDockWidget*>(loader.load(&file));

	qDebug() << endl << "OperationZoneRight解决方案:" << commonData->m_solution->m_nSolutionId;
	qDebug() << "OperationZoneRightDesigner Name:" << QString::fromStdString(commonData->m_solution->m_strDesignerName)<<endl;

	file.close();
}

CCreateOperationZoneRight::~CCreateOperationZoneRight(){
    delete m_pOperationZoneRightDockWidget;
}
