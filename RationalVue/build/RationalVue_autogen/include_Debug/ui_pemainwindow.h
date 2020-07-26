/********************************************************************************
** Form generated from reading UI file 'pemainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PEMAINWINDOW_H
#define UI_PEMAINWINDOW_H

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

class Ui_PEMainWindow
{
public:
    QAction *action_open_file;
    QAction *action_save_file;
    QWidget *centralWidget;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PEMainWindow)
    {
        if (PEMainWindow->objectName().isEmpty())
            PEMainWindow->setObjectName(QStringLiteral("PEMainWindow"));
        PEMainWindow->resize(476, 389);
        action_open_file = new QAction(PEMainWindow);
        action_open_file->setObjectName(QStringLiteral("action_open_file"));
        action_save_file = new QAction(PEMainWindow);
        action_save_file->setObjectName(QStringLiteral("action_save_file"));
        centralWidget = new QWidget(PEMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        PEMainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(PEMainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PEMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PEMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PEMainWindow->setStatusBar(statusBar);

        retranslateUi(PEMainWindow);

        QMetaObject::connectSlotsByName(PEMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PEMainWindow)
    {
        PEMainWindow->setWindowTitle(QApplication::translate("PEMainWindow", "PEMainWindow", Q_NULLPTR));
        action_open_file->setText(QApplication::translate("PEMainWindow", "&open file", Q_NULLPTR));
        action_save_file->setText(QApplication::translate("PEMainWindow", "&save file", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PEMainWindow: public Ui_PEMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PEMAINWINDOW_H
