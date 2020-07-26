/********************************************************************************
** Form generated from reading UI file 'dimensionReportZone.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIMENSIONREPORTZONE_H
#define UI_DIMENSIONREPORTZONE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDimensionReportZoneDockWidget
{
public:
    QWidget *dockWidgetContents;

    void setupUi(QDockWidget *CDimensionReportZoneDockWidget)
    {
        if (CDimensionReportZoneDockWidget->objectName().isEmpty())
            CDimensionReportZoneDockWidget->setObjectName(QStringLiteral("CDimensionReportZoneDockWidget"));
        CDimensionReportZoneDockWidget->resize(400, 300);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        CDimensionReportZoneDockWidget->setWidget(dockWidgetContents);

        retranslateUi(CDimensionReportZoneDockWidget);

        QMetaObject::connectSlotsByName(CDimensionReportZoneDockWidget);
    } // setupUi

    void retranslateUi(QDockWidget *CDimensionReportZoneDockWidget)
    {
        CDimensionReportZoneDockWidget->setWindowTitle(QApplication::translate("CDimensionReportZoneDockWidget", "DockWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CDimensionReportZoneDockWidget: public Ui_CDimensionReportZoneDockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIMENSIONREPORTZONE_H
