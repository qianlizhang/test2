/********************************************************************************
** Form generated from reading UI file 'graphiceZone.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHICEZONE_H
#define UI_GRAPHICEZONE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CGraphiceZoneDockWidget
{
public:
    QWidget *dockWidgetContents;

    void setupUi(QDockWidget *CGraphiceZoneDockWidget)
    {
        if (CGraphiceZoneDockWidget->objectName().isEmpty())
            CGraphiceZoneDockWidget->setObjectName(QStringLiteral("CGraphiceZoneDockWidget"));
        CGraphiceZoneDockWidget->resize(400, 300);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        CGraphiceZoneDockWidget->setWidget(dockWidgetContents);

        retranslateUi(CGraphiceZoneDockWidget);

        QMetaObject::connectSlotsByName(CGraphiceZoneDockWidget);
    } // setupUi

    void retranslateUi(QDockWidget *CGraphiceZoneDockWidget)
    {
        CGraphiceZoneDockWidget->setWindowTitle(QApplication::translate("CGraphiceZoneDockWidget", "DockWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CGraphiceZoneDockWidget: public Ui_CGraphiceZoneDockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHICEZONE_H
