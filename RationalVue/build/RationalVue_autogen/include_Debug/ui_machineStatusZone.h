/********************************************************************************
** Form generated from reading UI file 'machineStatusZone.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MACHINESTATUSZONE_H
#define UI_MACHINESTATUSZONE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMachineStatusZoneDockWidget
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_1;
    QToolButton *toolButton_lock;
    QLineEdit *lineEdit;
    QToolButton *toolButton_reset;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_1;
    QLCDNumber *lcdNumber_x;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLCDNumber *lcdNumber_y;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLCDNumber *lcdNumber_z;

    void setupUi(QDockWidget *CMachineStatusZoneDockWidget)
    {
        if (CMachineStatusZoneDockWidget->objectName().isEmpty())
            CMachineStatusZoneDockWidget->setObjectName(QStringLiteral("CMachineStatusZoneDockWidget"));
        CMachineStatusZoneDockWidget->resize(274, 226);
        QFont font;
        font.setPointSize(9);
        CMachineStatusZoneDockWidget->setFont(font);
        CMachineStatusZoneDockWidget->setStyleSheet(QStringLiteral(""));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        dockWidgetContents->setMinimumSize(QSize(1, 1));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(dockWidgetContents);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        horizontalLayout_1 = new QHBoxLayout(widget);
        horizontalLayout_1->setObjectName(QStringLiteral("horizontalLayout_1"));
        horizontalLayout_1->setContentsMargins(0, 3, 0, 3);
        toolButton_lock = new QToolButton(widget);
        toolButton_lock->setObjectName(QStringLiteral("toolButton_lock"));
        toolButton_lock->setAutoFillBackground(false);
        toolButton_lock->setStyleSheet(QStringLiteral("border:0px"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/lock.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_lock->setIcon(icon);

        horizontalLayout_1->addWidget(toolButton_lock);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        lineEdit->setMinimumSize(QSize(80, 0));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(9);
        lineEdit->setFont(font1);
        lineEdit->setAutoFillBackground(false);
        lineEdit->setStyleSheet(QLatin1String("background-color:#A8ACB7;\n"
"border: 1px solid gray;\n"
"border-radius: 3px;\n"
"padding: 1px 2px 1px 2px;"));

        horizontalLayout_1->addWidget(lineEdit);

        toolButton_reset = new QToolButton(widget);
        toolButton_reset->setObjectName(QStringLiteral("toolButton_reset"));
        toolButton_reset->setStyleSheet(QStringLiteral("border:0px"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/arrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_reset->setIcon(icon1);

        horizontalLayout_1->addWidget(toolButton_reset);

        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setAutoFillBackground(false);
        comboBox->setStyleSheet(QLatin1String("QComboBox{border: 1px solid gray;border-radius: 3px;padding: 1px 2px 1px 2px;}\n"
"QComboBox::editable{background-color:#8B8494}\n"
"QComboBox::!editable{background-color:#C5C8DB}\n"
"QComboBox::drop-down{width:25px;}\n"
"QComboBox::down-arrow{image:url(:/res/triangle.png);}\n"
"QComboBox::item{background-color:white};"));
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
        comboBox->setMinimumContentsLength(5);

        horizontalLayout_1->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_1->addItem(horizontalSpacer);

        horizontalLayout_1->setStretch(1, 5);
        horizontalLayout_1->setStretch(3, 3);
        horizontalLayout_1->setStretch(4, 5);

        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(dockWidgetContents);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setAutoFillBackground(true);
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_1 = new QLabel(widget_2);
        label_1->setObjectName(QStringLiteral("label_1"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font2.setPointSize(18);
        label_1->setFont(font2);
        label_1->setStyleSheet(QStringLiteral("background-color:#000000;color:#6BE7FF;padding-left:10px"));
        label_1->setFrameShape(QFrame::Box);
        label_1->setLineWidth(0);
        label_1->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_1);

        lcdNumber_x = new QLCDNumber(widget_2);
        lcdNumber_x->setObjectName(QStringLiteral("lcdNumber_x"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lcdNumber_x->sizePolicy().hasHeightForWidth());
        lcdNumber_x->setSizePolicy(sizePolicy1);
        QFont font3;
        font3.setFamily(QStringLiteral("Adobe Arabic"));
        font3.setPointSize(9);
        font3.setBold(false);
        font3.setWeight(50);
        lcdNumber_x->setFont(font3);
        lcdNumber_x->setAutoFillBackground(false);
        lcdNumber_x->setStyleSheet(QLatin1String("background-color:#000000;\n"
"color:#6BE7FF"));
        lcdNumber_x->setLineWidth(0);
        lcdNumber_x->setSmallDecimalPoint(true);
        lcdNumber_x->setDigitCount(8);
        lcdNumber_x->setSegmentStyle(QLCDNumber::Flat);
        lcdNumber_x->setProperty("value", QVariant(222.1));

        horizontalLayout_2->addWidget(lcdNumber_x);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 8);

        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(dockWidgetContents);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setAutoFillBackground(true);
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font2);
        label_2->setStyleSheet(QStringLiteral("background-color:#000000;color:#6BE7FF;padding-left:10px"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_2);

        lcdNumber_y = new QLCDNumber(widget_3);
        lcdNumber_y->setObjectName(QStringLiteral("lcdNumber_y"));
        sizePolicy1.setHeightForWidth(lcdNumber_y->sizePolicy().hasHeightForWidth());
        lcdNumber_y->setSizePolicy(sizePolicy1);
        QFont font4;
        font4.setFamily(QStringLiteral("Adobe Arabic"));
        font4.setPointSize(9);
        lcdNumber_y->setFont(font4);
        lcdNumber_y->setAutoFillBackground(false);
        lcdNumber_y->setStyleSheet(QLatin1String("background-color:#000000;\n"
"color:#6BE7FF"));
        lcdNumber_y->setLineWidth(0);
        lcdNumber_y->setSmallDecimalPoint(true);
        lcdNumber_y->setDigitCount(8);
        lcdNumber_y->setSegmentStyle(QLCDNumber::Flat);
        lcdNumber_y->setProperty("value", QVariant(2));

        horizontalLayout_3->addWidget(lcdNumber_y);

        horizontalLayout_3->setStretch(0, 1);
        horizontalLayout_3->setStretch(1, 8);

        verticalLayout->addWidget(widget_3);

        widget_4 = new QWidget(dockWidgetContents);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setFont(font2);
        widget_4->setAutoFillBackground(true);
        horizontalLayout_4 = new QHBoxLayout(widget_4);
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(widget_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font2);
        label_3->setStyleSheet(QStringLiteral("background-color:#000000;color:#6BE7FF;padding-left:10px"));
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_3);

        lcdNumber_z = new QLCDNumber(widget_4);
        lcdNumber_z->setObjectName(QStringLiteral("lcdNumber_z"));
        sizePolicy1.setHeightForWidth(lcdNumber_z->sizePolicy().hasHeightForWidth());
        lcdNumber_z->setSizePolicy(sizePolicy1);
        lcdNumber_z->setAutoFillBackground(false);
        lcdNumber_z->setStyleSheet(QLatin1String("background-color:#000000;\n"
"color:#6BE7FF"));
        lcdNumber_z->setLineWidth(0);
        lcdNumber_z->setSmallDecimalPoint(true);
        lcdNumber_z->setDigitCount(8);
        lcdNumber_z->setSegmentStyle(QLCDNumber::Flat);
        lcdNumber_z->setProperty("value", QVariant(2));

        horizontalLayout_4->addWidget(lcdNumber_z);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 8);

        verticalLayout->addWidget(widget_4);

        CMachineStatusZoneDockWidget->setWidget(dockWidgetContents);

        retranslateUi(CMachineStatusZoneDockWidget);

        QMetaObject::connectSlotsByName(CMachineStatusZoneDockWidget);
    } // setupUi

    void retranslateUi(QDockWidget *CMachineStatusZoneDockWidget)
    {
        CMachineStatusZoneDockWidget->setWindowTitle(QApplication::translate("CMachineStatusZoneDockWidget", "DockWidget", Q_NULLPTR));
        toolButton_lock->setText(QApplication::translate("CMachineStatusZoneDockWidget", "...", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("CMachineStatusZoneDockWidget", "CRD1", Q_NULLPTR));
        toolButton_reset->setText(QApplication::translate("CMachineStatusZoneDockWidget", "...", Q_NULLPTR));
        label_1->setText(QApplication::translate("CMachineStatusZoneDockWidget", "X", Q_NULLPTR));
        label_2->setText(QApplication::translate("CMachineStatusZoneDockWidget", "Y", Q_NULLPTR));
        label_3->setText(QApplication::translate("CMachineStatusZoneDockWidget", "Z", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CMachineStatusZoneDockWidget: public Ui_CMachineStatusZoneDockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MACHINESTATUSZONE_H
