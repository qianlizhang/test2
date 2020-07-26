#include "dataZoneLeft.h"
#include "dataZoneListWidget.h"

CCreateDataZoneLeftControl::CCreateDataZoneLeftControl(CCommonData *commondata):CCommonData(commondata)
{
	m_pToolButton_8 = new QToolButton();;

    m_pDataZoneLeftDockWidget = new QDockWidget();

	//qDebug() << QString::fromStdString("leftdataDockWidget:" );
    QUiLoader loader;
	
    QFile file(":/ui/gui/DataZoneLeft/dataZoneLeftDockWidget.ui");
    file.open(QFile::ReadOnly);
    m_pDataZoneLeftDockWidget = (QDockWidget*)loader.load(&file);

    m_pToolButton_8 = m_pDataZoneLeftDockWidget->findChild<QToolButton*>("toolButton_8");
    m_pWidget_2 = m_pDataZoneLeftDockWidget->findChild<QWidget*>("widget_2");


    m_pMenu = new QMenu();
    m_pMenu->addMenu(QString("Prompt"));
    m_pMenu->addMenu(QString("Output"));
    m_pMenu->addMenu(QString("Macro"));
    m_pMenu->addMenu(QString("Goto"));
    m_pMenu->addMenu(QString("Control Command"));
    m_pMenu->addMenu(QString("Define Feature"));

    m_pToolButton_8->setMenu(m_pMenu);

    m_pToolButton_8->setPopupMode(QToolButton::InstantPopup);



    m_pVBoxLayout_2 = new QVBoxLayout();

    m_pVBoxLayout_2->setContentsMargins(0, 0, 0, 0);
    m_pVBoxLayout_2->setSpacing(0);

	m_pListWidget = new CDataZoneListWidget();


    //check_box

    m_pCheckBox = new QCheckBox();
    /*m_pCheckBox_2 = new QCheckBox();
    m_pCheckBox_3 = new QCheckBox();
    m_pCheckBox_4 = new QCheckBox();
    m_pCheckBox_5 = new QCheckBox();
    m_pCheckBox_6 = new QCheckBox();
    m_pCheckBox_7 = new QCheckBox();
    m_pCheckBox_8 = new QCheckBox();
    m_pCheckBox_9 = new QCheckBox();*/

	QString iconType;
	QString iconColor;
	QString iconLabel;

	switch (m_solution->m_vecElements[0].m_enuElementType)
	{
	case 2:
		iconType = QString("ln_");
	default:
		break;
	}
	switch (m_solution->m_vecElements[0].m_enuElementLabel)
	{
	case 1:
		iconColor = QString("red.png");
	default:
		break;
	}
	iconLabel = QString(m_solution->m_vecElements[0].m_strLable);
	QString iconDir = QString(":/icon/") + iconType + iconColor;
    m_pCheckBox->setChecked(1);
    m_pCheckBox->setIcon(QIcon(iconDir));
    m_pCheckBox->setIconSize(QSize(20, 20));
    m_pCheckBox->setText(iconLabel);

   /* m_pCheckBox_2->setChecked(1);
    m_pCheckBox_2->setIcon(QIcon(":/icon/cir_red.png"));
    m_pCheckBox_2->setIconSize(QSize(20, 20));
    m_pCheckBox_2->setText(QString("CIR2"));

    m_pCheckBox_3->setChecked(1);
    m_pCheckBox_3->setIcon(QIcon(":/icon/ln_green.png"));
    m_pCheckBox_3->setIconSize(QSize(20, 20));
    m_pCheckBox_3->setText(QString("LN1"));

    m_pCheckBox_4->setChecked(1);
    m_pCheckBox_4->setIcon(QIcon(":/icon/ln_red.png"));
    m_pCheckBox_4->setIconSize(QSize(20, 20));
    m_pCheckBox_4->setText(QString("LN2"));

    m_pCheckBox_5->setChecked(1);
    m_pCheckBox_5->setIcon(QIcon(":/icon/arc_red.png"));
    m_pCheckBox_5->setIconSize(QSize(20, 20));
    m_pCheckBox_5->setText(QString("ARC1"));

    m_pCheckBox_6->setChecked(1);
    m_pCheckBox_6->setIcon(QIcon(":/icon/ln_red.png"));
    m_pCheckBox_6->setIconSize(QSize(20, 20));
    m_pCheckBox_6->setText(QString("LN3"));

    m_pCheckBox_7->setChecked(1);
    m_pCheckBox_7->setIcon(QIcon(":/icon/goto.png"));
    m_pCheckBox_7->setIconSize(QSize(20, 20));
    m_pCheckBox_7->setText(QString("GOTO1"));

    m_pCheckBox_8->setChecked(1);
    m_pCheckBox_8->setIcon(QIcon(":/icon/macro.png"));
    m_pCheckBox_8->setIconSize(QSize(20, 20));
    m_pCheckBox_8->setText(QString("Macro1"));

    m_pCheckBox_9->setChecked(1);
    m_pCheckBox_9->setIcon(QIcon(":/icon/output.png"));
    m_pCheckBox_9->setIconSize(QSize(20, 20));
    m_pCheckBox_9->setText(QString("Output1"));*/

    m_pItem = new QListWidgetItem();
   /* m_pItem_2 = new QListWidgetItem();
    m_pItem_3 = new QListWidgetItem();
    m_pItem_4 = new QListWidgetItem();
    m_pItem_5 = new QListWidgetItem();
    m_pItem_6 = new QListWidgetItem();
    m_pItem_7 = new QListWidgetItem();
    m_pItem_8 = new QListWidgetItem();
    m_pItem_9 = new QListWidgetItem();*/

	m_pListWidget->addItem(m_pItem);
	m_pListWidget->setItemWidget(m_pItem, m_pCheckBox);

	/*m_pListWidget->addItem(m_pItem_2);
	m_pListWidget->setItemWidget(m_pItem_2, m_pCheckBox_2);

	m_pListWidget->addItem(m_pItem_3);
	m_pListWidget->setItemWidget(m_pItem_3, m_pCheckBox_3);

	m_pListWidget->addItem(m_pItem_4);
	m_pListWidget->setItemWidget(m_pItem_4, m_pCheckBox_4);

	m_pListWidget->addItem(m_pItem_5);
	m_pListWidget->setItemWidget(m_pItem_5, m_pCheckBox_5);

	m_pListWidget->addItem(m_pItem_6);
	m_pListWidget->setItemWidget(m_pItem_6, m_pCheckBox_6);

	m_pListWidget->addItem(m_pItem_7);
	m_pListWidget->setItemWidget(m_pItem_7, m_pCheckBox_7);

	m_pListWidget->addItem(m_pItem_8);
	m_pListWidget->setItemWidget(m_pItem_8, m_pCheckBox_8);

	m_pListWidget->addItem(m_pItem_9);
	m_pListWidget->setItemWidget(m_pItem_9, m_pCheckBox_9);*/


	m_pListWidget->setStyleSheet("border-style:none;");

    m_pVBoxLayout_2->addWidget(m_pListWidget);
    m_pWidget_2->setLayout(m_pVBoxLayout_2);

}


CCreateDataZoneLeftControl::~CCreateDataZoneLeftControl()
{
    //delete ui;
}
