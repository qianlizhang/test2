#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QDockWidget>
#include <qmenu.h>
#include <qaction.h>
#include <QTreeWidgetItem>
#include <QContextMenuEvent>
#include "CommonData.h"


class CCreatDataZoneRight :CCommonData
{
public:
    CCreatDataZoneRight(CCommonData *commondata);
    ~CCreatDataZoneRight();
    QDockWidget* readDataZoneRight();
    void initDataZoneRight(QDockWidget *dockWidget);
    void setDataZoneRigthStyle();
    void initTreeWidget();
    void createMenu();
    QDockWidget *get_CDataZoneRightDockWidget();

    QDockWidget *m_pDataZoneRightDockWidget;
    QTreeWidget* treeWidget;
    QTreeWidget* treeWidget_2;

    QMenu *m_PopMenu;
    QMenu *m_AddMenu;
    QMenu *m_DelMenu;

    QAction *m_AddAction;
    QAction *m_DelAction;
/*private slots:
    void onDelAction();
    void onAddAction();

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private:

    */
};

#endif // DOCKWIDGET_H
