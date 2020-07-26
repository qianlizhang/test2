/********************************************************************************
** Form generated from reading UI file 'cpaintzonemainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CPAINTZONEMAINWINDOW_H
#define UI_CPAINTZONEMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CPaintZoneMainWindow
{
public:
    QWidget *centralWidget;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CPaintZoneMainWindow)
    {
        if (CPaintZoneMainWindow->objectName().isEmpty())
            CPaintZoneMainWindow->setObjectName(QStringLiteral("CPaintZoneMainWindow"));
        CPaintZoneMainWindow->resize(400, 300);
        centralWidget = new QWidget(CPaintZoneMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CPaintZoneMainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(CPaintZoneMainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CPaintZoneMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CPaintZoneMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CPaintZoneMainWindow->setStatusBar(statusBar);

        retranslateUi(CPaintZoneMainWindow);

        QMetaObject::connectSlotsByName(CPaintZoneMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CPaintZoneMainWindow)
    {
        CPaintZoneMainWindow->setWindowTitle(QApplication::translate("CPaintZoneMainWindow", "CPaintZoneMainWindow", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CPaintZoneMainWindow: public Ui_CPaintZoneMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CPAINTZONEMAINWINDOW_H
