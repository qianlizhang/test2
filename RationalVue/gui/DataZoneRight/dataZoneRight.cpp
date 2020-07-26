#include "dataZoneRight.h"
#include <QFile>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include <QTextEdit>
#include <QtUiTools/QtUiTools>
CCreatDataZoneRight::CCreatDataZoneRight(CCommonData *commondata) :CCommonData(commondata)
{
	qDebug() << QString::fromStdString("rightdataDockWidget:" + m_solution->m_strSolutionName);
    m_pDataZoneRightDockWidget = readDataZoneRight();
    initDataZoneRight(m_pDataZoneRightDockWidget);
    setDataZoneRigthStyle();
    /*
    createMenu();*/
}
QDockWidget* CCreatDataZoneRight::readDataZoneRight()
{
    QUiLoader loader;
    //QFile file("G:\\qtproject\\untitled13\\creatDataZoneRight.ui");
    QFile file(":/ui/gui/DataZoneRight/dataZoneRightDockWidget.ui");
    file.open(QFile::ReadOnly);
    return static_cast<QDockWidget *>(loader.load(&file));
}

void CCreatDataZoneRight::initDataZoneRight(QDockWidget *dockWidget)
{
    treeWidget = dockWidget->findChild<QTreeWidget*>("treeWidget");
    treeWidget->setHeaderLabel("label");
    treeWidget_2 = dockWidget->findChild<QTreeWidget*>("treeWidget_2");
    treeWidget_2->setHeaderLabel("parent label");
    {
        QTreeWidgetItem *mcs = new QTreeWidgetItem(treeWidget);
        mcs->setText(0,"MCS");
        mcs->setIcon(0,QIcon(":/images/mcs.png"));
    }

    {
        QTreeWidgetItem *focusplane = new QTreeWidgetItem(treeWidget);
        focusplane->setText(0,"Focus Plane");
        focusplane->setIcon(0,QIcon(":/images/focusplane.png"));
        QTreeWidgetItem *fpln_1 = new QTreeWidgetItem(focusplane);
        fpln_1->setText(0,"FPLN_1");
    }

    {
        QTreeWidgetItem *reposition = new QTreeWidgetItem(treeWidget);
        reposition->setText(0,"Reposition");
        reposition->setIcon(0,QIcon(":/images/reposition.png"));
    }

    {
        QTreeWidgetItem *cadmodels = new QTreeWidgetItem(treeWidget,QStringList(QString("Cad Models")));
        //cadmodels->setText(0,"Cad Models");
        cadmodels->setIcon(0,QIcon(":/images/cadmodels.png"));
        QTreeWidgetItem *cadm_1 = new QTreeWidgetItem(cadmodels);
        cadm_1->setText(0,"CADM_1");
    }

    {
        QTreeWidgetItem *pointclouds = new QTreeWidgetItem(treeWidget);
        pointclouds->setText(0,"Point Clouds");
        pointclouds->setIcon(0,QIcon(":/images/pointclouds.png"));
    }

    {
        QTreeWidgetItem *formerrorreports = new QTreeWidgetItem(treeWidget);
        formerrorreports->setText(0,"Form Error Reports");
        formerrorreports->setIcon(0,QIcon(":/images/formerrorreports.png"));
    }

    {
        QTreeWidgetItem *sensor = new QTreeWidgetItem(treeWidget);
        sensor->setText(0,"Sensor");
        sensor->setIcon(0,QIcon(":/images/sensor.png"));
    }
}

void CCreatDataZoneRight::setDataZoneRigthStyle()
{
    QFile file(":/css/styleSheet.css");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    m_pDataZoneRightDockWidget->setStyleSheet(stylesheet);
}

CCreatDataZoneRight::~CCreatDataZoneRight()
{
    //delete ui;
}

/*
void CDataZoneRightDockWidget::createMenu()
{
    m_PopMenu = new QMenu;
    m_AddMenu = new QMenu("Add Action");

    m_AddAction = new QAction("myadd");
    m_AddAction->setIcon(QIcon(":/images/add.png"));

    m_DelAction = new QAction("Del Action");
    m_DelAction->setIcon(QIcon(":/images/del.png"));

    m_PopMenu->addAction(m_AddAction);
    m_PopMenu->addAction(m_DelAction);

    //connect(m_AddAction,SIGNAL(triggered(bool)),this,SLOT(onAddAction()));
    //connect(m_DelAction,SIGNAL(triggered(bool)),this,SLOT(onDelAction()));
}

void CDataZoneRight::contextMenuEvent(QContextMenuEvent *event)
{
    if(ui->treeWidget->hasFocus())
    {
        m_PopMenu->move(cursor().pos());
        m_PopMenu->show();
    }
}
void CDataZoneRight::onDelAction()
{
    QTreeWidgetItem *currentitem = ui->treeWidget->currentItem();
    if(!currentitem->parent()){
        QMessageBox::information(this,"information","Can Not Delete");
        return;
    }
    else if(currentitem->parent()){
        currentitem->parent()->removeChild(currentitem);
    }
}

void CDataZoneRight::onAddAction()
{
    QTreeWidgetItem *currentitem = ui->treeWidget->currentItem();
    QString wellName = currentitem->text(0);
    if(!currentitem->parent()){
        QMessageBox::information(this,"information","Did Not Choose");
        return;
    }
    else if(currentitem->parent()->text(0)=="Cad Models"){
        bool ok;
        QString cadmodelstext = QInputDialog::getText(this,tr("input CadModels Name"),tr("CadModels Name:"),QLineEdit::Normal,"",&ok);
        if(ok && !cadmodelstext.isEmpty()){
             QTreeWidgetItem *cadmodelsitem = new QTreeWidgetItem(currentitem->parent());
             cadmodelsitem->setText(0,cadmodelstext);
        }
    }
    else if(currentitem->parent()->text(0)=="Focus Plane"){
        bool ok;
        QString focusplanetext = QInputDialog::getText(this,tr("input FocusPlane Name"),tr("FocusPlane Name:"),QLineEdit::Normal,"",&ok);
        if(ok && !focusplanetext.isEmpty()){
             QTreeWidgetItem *cadmodelsitem = new QTreeWidgetItem(currentitem->parent());
             cadmodelsitem->setText(0,focusplanetext);
        }
    }
    else if(currentitem->text(0)=="Focus Plane"){
        qDebug("1");
    }
    else if(currentitem->child(0)->parent()->text(0)=="Focus Plane"){
        qDebug("1");
    }
}
*/
