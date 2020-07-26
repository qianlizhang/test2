/********************************************************************************
** Form generated from reading UI file 'occQt.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OCCQT_H
#define UI_OCCQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_occQtClass
{
public:
    QAction *actionExit;
    QAction *actionZoom;
    QAction *actionPan;
    QAction *actionRotate;
    QAction *actionReset;
    QAction *actionFitAll;
    QAction *actionAbout;
    QAction *actionBox;
    QAction *actionCone;
    QAction *actionSphere;
    QAction *actionCylinder;
    QAction *actionTorus;
    QAction *actionFillet;
    QAction *actionChamfer;
    QAction *actionExtrude;
    QAction *actionRevolve;
    QAction *actionLoft;
    QAction *actionCut;
    QAction *actionFuse;
    QAction *actionCommon;
    QAction *actionHelix;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuPrimitive;
    QMenu *menuModeling;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *occQtClass)
    {
        if (occQtClass->objectName().isEmpty())
            occQtClass->setObjectName(QStringLiteral("occQtClass"));
        occQtClass->resize(800, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/lamp.png"), QSize(), QIcon::Normal, QIcon::Off);
        occQtClass->setWindowIcon(icon);
        actionExit = new QAction(occQtClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionZoom = new QAction(occQtClass);
        actionZoom->setObjectName(QStringLiteral("actionZoom"));
        actionZoom->setCheckable(false);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Resources/Zoom.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom->setIcon(icon1);
        actionPan = new QAction(occQtClass);
        actionPan->setObjectName(QStringLiteral("actionPan"));
        actionPan->setCheckable(false);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Resources/Pan.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPan->setIcon(icon2);
        actionRotate = new QAction(occQtClass);
        actionRotate->setObjectName(QStringLiteral("actionRotate"));
        actionRotate->setCheckable(false);
        actionRotate->setChecked(false);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Resources/Rotate.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRotate->setIcon(icon3);
        actionReset = new QAction(occQtClass);
        actionReset->setObjectName(QStringLiteral("actionReset"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Resources/Home.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionReset->setIcon(icon4);
        actionFitAll = new QAction(occQtClass);
        actionFitAll->setObjectName(QStringLiteral("actionFitAll"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/Resources/FitAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFitAll->setIcon(icon5);
        actionAbout = new QAction(occQtClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionAbout->setIcon(icon);
        actionBox = new QAction(occQtClass);
        actionBox->setObjectName(QStringLiteral("actionBox"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/Resources/box.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBox->setIcon(icon6);
        actionCone = new QAction(occQtClass);
        actionCone->setObjectName(QStringLiteral("actionCone"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/Resources/cone.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCone->setIcon(icon7);
        actionSphere = new QAction(occQtClass);
        actionSphere->setObjectName(QStringLiteral("actionSphere"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/Resources/sphere.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSphere->setIcon(icon8);
        actionCylinder = new QAction(occQtClass);
        actionCylinder->setObjectName(QStringLiteral("actionCylinder"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/Resources/cylinder.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCylinder->setIcon(icon9);
        actionTorus = new QAction(occQtClass);
        actionTorus->setObjectName(QStringLiteral("actionTorus"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/Resources/torus.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTorus->setIcon(icon10);
        actionFillet = new QAction(occQtClass);
        actionFillet->setObjectName(QStringLiteral("actionFillet"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/Resources/fillet.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFillet->setIcon(icon11);
        actionChamfer = new QAction(occQtClass);
        actionChamfer->setObjectName(QStringLiteral("actionChamfer"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/Resources/chamfer.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionChamfer->setIcon(icon12);
        actionExtrude = new QAction(occQtClass);
        actionExtrude->setObjectName(QStringLiteral("actionExtrude"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/Resources/extrude.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExtrude->setIcon(icon13);
        actionRevolve = new QAction(occQtClass);
        actionRevolve->setObjectName(QStringLiteral("actionRevolve"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/Resources/revolve.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRevolve->setIcon(icon14);
        actionLoft = new QAction(occQtClass);
        actionLoft->setObjectName(QStringLiteral("actionLoft"));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/Resources/loft.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoft->setIcon(icon15);
        actionCut = new QAction(occQtClass);
        actionCut->setObjectName(QStringLiteral("actionCut"));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/Resources/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCut->setIcon(icon16);
        actionFuse = new QAction(occQtClass);
        actionFuse->setObjectName(QStringLiteral("actionFuse"));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/Resources/fuse.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFuse->setIcon(icon17);
        actionCommon = new QAction(occQtClass);
        actionCommon->setObjectName(QStringLiteral("actionCommon"));
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/Resources/common.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCommon->setIcon(icon18);
        actionHelix = new QAction(occQtClass);
        actionHelix->setObjectName(QStringLiteral("actionHelix"));
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/Resources/helix.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelix->setIcon(icon19);
        centralWidget = new QWidget(occQtClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        occQtClass->setCentralWidget(centralWidget);
       /* menuBar = new QMenuBar(occQtClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuPrimitive = new QMenu(menuBar);
        menuPrimitive->setObjectName(QStringLiteral("menuPrimitive"));
        menuModeling = new QMenu(menuBar);
        menuModeling->setObjectName(QStringLiteral("menuModeling"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        occQtClass->setMenuBar(menuBar);*/
        statusBar = new QStatusBar(occQtClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        occQtClass->setStatusBar(statusBar);

       /* menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuPrimitive->menuAction());
        menuBar->addAction(menuModeling->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionExit);
        menuView->addAction(actionZoom);
        menuView->addAction(actionPan);
        menuView->addAction(actionRotate);
        menuView->addSeparator();
        menuView->addAction(actionReset);
        menuView->addAction(actionFitAll);
        menuPrimitive->addAction(actionBox);
        menuPrimitive->addAction(actionCone);
        menuPrimitive->addAction(actionSphere);
        menuPrimitive->addAction(actionCylinder);
        menuPrimitive->addAction(actionTorus);
        menuModeling->addAction(actionFillet);
        menuModeling->addAction(actionChamfer);
        menuModeling->addAction(actionExtrude);
        menuModeling->addAction(actionRevolve);
        menuModeling->addAction(actionLoft);
        menuModeling->addSeparator();
        menuModeling->addAction(actionCut);
        menuModeling->addAction(actionFuse);
        menuModeling->addAction(actionCommon);
        menuModeling->addSeparator();
        menuModeling->addAction(actionHelix);
        menuHelp->addAction(actionAbout);
		*/
        retranslateUi(occQtClass);

        QMetaObject::connectSlotsByName(occQtClass);
    } // setupUi

    void retranslateUi(QMainWindow *occQtClass)
    {
        occQtClass->setWindowTitle(QApplication::translate("occQtClass", "occQt", Q_NULLPTR));
        actionExit->setText(QApplication::translate("occQtClass", "Exit", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionExit->setShortcut(QApplication::translate("occQtClass", "Ctrl+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionZoom->setText(QApplication::translate("occQtClass", "Zoom", Q_NULLPTR));
        actionPan->setText(QApplication::translate("occQtClass", "Pan", Q_NULLPTR));
        actionRotate->setText(QApplication::translate("occQtClass", "Rotate", Q_NULLPTR));
        actionReset->setText(QApplication::translate("occQtClass", "Reset", Q_NULLPTR));
        actionFitAll->setText(QApplication::translate("occQtClass", "FitAll", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("occQtClass", "About", Q_NULLPTR));
        actionBox->setText(QApplication::translate("occQtClass", "Box", Q_NULLPTR));
        actionCone->setText(QApplication::translate("occQtClass", "Cone", Q_NULLPTR));
        actionSphere->setText(QApplication::translate("occQtClass", "Sphere", Q_NULLPTR));
        actionCylinder->setText(QApplication::translate("occQtClass", "Cylinder", Q_NULLPTR));
        actionTorus->setText(QApplication::translate("occQtClass", "Torus", Q_NULLPTR));
        actionFillet->setText(QApplication::translate("occQtClass", "Fillet", Q_NULLPTR));
        actionChamfer->setText(QApplication::translate("occQtClass", "Chamfer", Q_NULLPTR));
        actionExtrude->setText(QApplication::translate("occQtClass", "Extrude", Q_NULLPTR));
        actionRevolve->setText(QApplication::translate("occQtClass", "Rovelve", Q_NULLPTR));
        actionLoft->setText(QApplication::translate("occQtClass", "Loft", Q_NULLPTR));
        actionCut->setText(QApplication::translate("occQtClass", "Cut", Q_NULLPTR));
        actionFuse->setText(QApplication::translate("occQtClass", "Fuse", Q_NULLPTR));
        actionCommon->setText(QApplication::translate("occQtClass", "Common", Q_NULLPTR));
        actionHelix->setText(QApplication::translate("occQtClass", "Helix", Q_NULLPTR));
        /*menuFile->setTitle(QApplication::translate("occQtClass", "File", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("occQtClass", "View", Q_NULLPTR));
        menuPrimitive->setTitle(QApplication::translate("occQtClass", "Primitive", Q_NULLPTR));
        menuModeling->setTitle(QApplication::translate("occQtClass", "Modeling", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("occQtClass", "Help", Q_NULLPTR));*/
    } // retranslateUi

};

namespace Ui {
    class occQtClass: public Ui_occQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OCCQT_H
