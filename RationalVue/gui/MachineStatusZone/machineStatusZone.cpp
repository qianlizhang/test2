#include "machineStatusZone.h"
#include "ui_machineStatusZone.h"
#include <QDebug>
#include <QMenu>
#include <QPoint>
#include <QtUiTools>

CCreateMachineStatusZone::CCreateMachineStatusZone(CCommonData *commondata):CCommonData(commondata)
{
	//----------------------------读取CCommonData的数据-------------------------
	qDebug() << m_solution->m_nSolutionId;
	qDebug() << QString::fromStdString("解决方案:" + m_solution->m_strSolutionName + "读取到m_solution->m_bReadOnly的值为:" )+ m_solution->m_bReadOnly;
	
    //----------------------------动态加载ui文件获取DockWidget-------------------------
	QUiLoader loader;
	QFile file("../gui/MachineStatusZone/machineStatusZone.ui");
	file.open(QFile::ReadOnly);
	m_pMachineStatusZoneDockWidget = qobject_cast<QDockWidget *>(loader.load(&file));

	//----------------------------设置DockWidget的背景颜色-------------------------
    QPalette palette;
    palette.setColor(QPalette::Background, QColor("#93939F"));
	m_pMachineStatusZoneDockWidget->setPalette(palette);


	//----------------------------添加combobox的基础内容-------------------------
	m_pSmallDecimalCountComboBox = m_pMachineStatusZoneDockWidget->findChild<QComboBox *>(QString("comboBox"));
	for (int i = 0; i <= 5; i++)
	{
		m_pSmallDecimalCountComboBox->addItem(QString::number(i));
	}
	// 对小数点设置下拉框添加事件
	QObject::connect(m_pSmallDecimalCountComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int index) {
		m_pLCDX->display(QString::number(m_pLCDX->value(), 'f', index));
		m_pLCDY->display(QString::number(m_pLCDY->value(), 'f', index));
		m_pLCDZ->display(QString::number(m_pLCDZ->value(), 'f', index));
	});

	//----------------------------获取锁按钮并对锁按钮点击添加图片切换-------------------------
	m_pLockButton = m_pMachineStatusZoneDockWidget->findChild<QToolButton *>(QString("toolButton_lock"));
    QObject::connect(m_pLockButton,&QToolButton::clicked,[=](){
        if(m_bIsLock==true)
			m_pLockButton->setIcon(QIcon(":/res/unlock.png"));
        else
			m_pLockButton->setIcon(QIcon(":/res/lock.png"));
        m_bIsLock = !m_bIsLock;
    });

	//----------------------------获取重置按钮并对重置按钮添加重置坐标显示事件-------------------------
	m_pResetButton = m_pMachineStatusZoneDockWidget->findChild<QToolButton *>(QString("toolButton_reset"));
	m_pLCDX = m_pMachineStatusZoneDockWidget->findChild<QLCDNumber *>(QString("lcdNumber_x"));
	m_pLCDY = m_pMachineStatusZoneDockWidget->findChild<QLCDNumber *>(QString("lcdNumber_y"));
	m_pLCDZ = m_pMachineStatusZoneDockWidget->findChild<QLCDNumber *>(QString("lcdNumber_z"));
	QObject::connect(m_pResetButton,&QToolButton::clicked,[=](){
        //sender()可以获取一个Qobject对象，sender->inherits("QPushButton")判断信号来自那个对象，但是属性全部丢失了
        //    QToolButton *button = qobject_cast<QToolButton *>(sender());
		// 这menu只需要使用一次
		QMenu pResetMenu(m_pMachineStatusZoneDockWidget);
        pResetMenu.addAction(QString("Reset All"),[=](){
            m_pLCDX->display(QString::number(0));
            m_pLCDY->display(QString::number(0));
            m_pLCDZ->display(QString::number(0));
        });
        pResetMenu.addAction(QString("Reset X"),[=](){
            m_pLCDX->display(QString::number(0));
        });
        pResetMenu.addAction(QString("Reset Y"),[=](){
			m_pLCDY->display(QString::number(0));
        });
        pResetMenu.addAction(QString("Reset Z"),[=](){
			m_pLCDZ->display(QString::number(0));
        });
        // 第一种方法获取这个widget的全局坐标,然后再改变 this->mapToGlobal(QPoint(0,0))获取当前页面的全局坐标
        //   resetMenu->exec(QPoint(this->mapToGlobal(QPoint(0,0)).x()+ui->toolButton_2->x(),this->mapToGlobal(QPoint(0,0)).y()+ui->toolButton_2->y()));
        // 第二种方法获取鼠标当时的位置
        pResetMenu.exec(QPoint(QCursor::pos().x(),QCursor::pos().y()+ m_pResetButton->height()+4));
    });	 
}


QDockWidget* CCreateMachineStatusZone::init()
{
	return m_pMachineStatusZoneDockWidget;
}

CCreateMachineStatusZone::~CCreateMachineStatusZone()
{
	delete m_pMachineStatusZoneDockWidget;
	delete m_pSmallDecimalCountComboBox;
	delete m_pLockButton;
	delete m_pResetButton;
	delete m_pLCDX;
	delete m_pLCDY;
	delete m_pLCDZ;
}
