#ifndef CDATAZONELISTWIDGET_H
#define CDATAZONELISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QContextMenuEvent>
#include <QMenu>

class CDataZoneListWidget:public QListWidget
{
public:
    CDataZoneListWidget();


    void contextMenuEvent ( QContextMenuEvent * event );

};

#endif // CDATAZONELISTWIDGET_H
