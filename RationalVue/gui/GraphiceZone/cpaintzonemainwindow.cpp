#include "cpaintzonemainwindow.h"
#include "ui_cpaintzonemainwindow.h"
#include "cpaintview.h"

#include <QToolBar>
#include <QTreeView>
#include <QMessageBox>
#include <QDockWidget>

#include <gp_Circ.hxx>
#include <gp_Elips.hxx>
#include <gp_Pln.hxx>

#include <gp_Lin2d.hxx>

#include <Geom_ConicalSurface.hxx>
#include <Geom_ToroidalSurface.hxx>
#include <Geom_CylindricalSurface.hxx>

#include <GCE2d_MakeSegment.hxx>

#include <TopoDS.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TColgp_Array1OfPnt2d.hxx>

#include <BRepLib.hxx>

#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>

#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>

#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>

#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Common.hxx>

#include <AIS_Shape.hxx>

CPaintZoneMainWindow::CPaintZoneMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CPaintZoneMainWindow)
{
    ui->setupUi(this);
    myCPaintView = new CPaintView(this);
    setCentralWidget(myCPaintView);
    createActions();
    //createMenus();
    //createToolBars();
}

CPaintZoneMainWindow::~CPaintZoneMainWindow()
{
    delete ui;
}
void CPaintZoneMainWindow::createActions(void)
{

	QToolBar* aToolBar = addToolBar(tr("View"));
	QAction *actionZoom = new QAction(tr("&Zoom"), this);
	actionZoom->setIcon(QIcon(":/png/images/Zoom.png"));
	aToolBar->addAction(actionZoom);
	connect(actionZoom, SIGNAL(triggered()), myCPaintView, SLOT(zoom()));

	QAction *actionPan = new QAction(tr("&Pan"), this);
	actionPan->setIcon(QIcon(":/png/images/Pan.png"));
	aToolBar->addAction(actionPan);
	connect(actionPan, SIGNAL(triggered()), myCPaintView, SLOT(pan()));

	QAction *actionRotate = new QAction(tr("&Rotate"), this);
	actionRotate->setIcon(QIcon(":/png/images/Rotate.png"));
	aToolBar->addAction(actionRotate);
	connect(actionRotate, SIGNAL(triggered()), myCPaintView, SLOT(rotate()));

	QAction *actionReset = new QAction(tr("&Reset"), this);
	actionReset->setIcon(QIcon(":/png/images/Home.png"));
	aToolBar->addAction(actionReset);
	connect(actionReset, SIGNAL(triggered()), myCPaintView, SLOT(reset()));

	QAction *actionFitAll = new QAction(tr("&FitAll"), this);
	actionFitAll->setIcon(QIcon(":/png/images/FitAll.png"));
	aToolBar->addAction(actionFitAll);
	connect(actionFitAll, SIGNAL(triggered()), myCPaintView, SLOT(fitAll()));

	QAction *actionRect = new QAction(tr("&rect"), this);
	actionRect->setIcon(QIcon(":/png/images/rect.png"));
	aToolBar->addAction(actionRect);
	connect(actionRect, SIGNAL(triggered()), this, SLOT(makeRect()));


	QAction *actionCircle = new QAction(tr("&circle"), this);
	actionCircle->setIcon(QIcon(":/png/images/circle.png"));
	aToolBar->addAction(actionCircle);
	connect(actionCircle, SIGNAL(triggered()), this, SLOT(makeCircle()));

	QAction *actionEllipse = new QAction(tr("&ellipse"), this);
	actionEllipse->setIcon(QIcon(":/png/images/ellipse.png"));
	aToolBar->addAction(actionEllipse);
	connect(actionEllipse, SIGNAL(triggered()), this, SLOT(makeEllipse()));

	QAction *actionPie = new QAction(tr("&pie"), this);
	actionPie->setIcon(QIcon(":/png/images/pie.png"));
	aToolBar->addAction(actionPie);
	connect(actionPie, SIGNAL(triggered()), this, SLOT(makePie()));

	QAction *actionLine = new QAction(tr("&line"), this);
	actionLine->setIcon(QIcon(":/png/images/line.png"));
	aToolBar->addAction(actionLine);
	connect(actionLine, SIGNAL(triggered()), this, SLOT(makeLine()));

	QAction *actionArc = new QAction(tr("&arc"), this);
	actionArc->setIcon(QIcon(":/png/images/arc.png"));
	aToolBar->addAction(actionArc);
	connect(actionArc, SIGNAL(triggered()), this, SLOT(makeArc()));

	QAction *actionPoint = new QAction(tr("&point"), this);
	actionPoint->setIcon(QIcon(":/png/images/point.png"));
	aToolBar->addAction(actionPoint);
	connect(actionPoint, SIGNAL(triggered()), this, SLOT(makePoint()));


}
void CPaintZoneMainWindow::makeRect()
{
    TopoDS_Shape aTopoBox = BRepPrimAPI_MakeBox(3.0, 4.0, 5.0).Shape();
    Handle(AIS_Shape) anAisBox = new AIS_Shape(aTopoBox);

    anAisBox->SetColor(Quantity_NOC_BLACK);

	myCPaintView->getContext()->Display(anAisBox, Standard_True);
}

void CPaintZoneMainWindow::makeCircle()
{
    gp_Ax2 anAxis;
    anAxis.SetLocation(gp_Pnt(0.0, 10.0, 0.0));

    //TopoDS_Shape aTopoSphere = BRepPrimAPI_MakeSphere(anAxis, 3.0).Shape();
	TopoDS_Shape aTopoSphere = BRepPrimAPI_MakeCylinder(anAxis, 3.0, 3.0).Shape();
    Handle(AIS_Shape) anAisSphere = new AIS_Shape(aTopoSphere);

    anAisSphere->SetColor(Quantity_NOC_BLACK);

	myCPaintView->getContext()->Display(anAisSphere, Standard_True);
}
void CPaintZoneMainWindow::makeEllipse()
{
    gp_Ax2 anAxis;
    anAxis.SetLocation(gp_Pnt(0.0, 20.0, 0.0));

	TopoDS_Edge aEllipseEdge = BRepBuilderAPI_MakeEdge(gp_Elips(anAxis, 3.0, 2.0));
	TopoDS_Wire aEllipseWire = BRepBuilderAPI_MakeWire(aEllipseEdge);
	TopoDS_Face aEllipseFace = BRepBuilderAPI_MakeFace(gp_Pln(gp::XOY()), aEllipseWire);
	Handle(AIS_Shape) anAisPrismEllipse = new AIS_Shape(aEllipseFace);

	anAisPrismEllipse->SetColor(Quantity_NOC_PINK);

	myCPaintView->getContext()->Display(anAisPrismEllipse, Standard_True);
}
void  CPaintZoneMainWindow::makePie()
{
	gp_Ax2 anAxis;
	anAxis.SetLocation(gp_Pnt(8.0, 15.0, 0.0));

	TopoDS_Shape aTopoPie = BRepPrimAPI_MakeCylinder(anAxis, 5.0, 5.0, M_PI_2).Shape();
	Handle(AIS_Shape) anAisPie = new AIS_Shape(aTopoPie);

	anAisPie->SetColor(Quantity_NOC_WHITE);

	myCPaintView->getContext()->Display(anAisPie, Standard_True);
}
void  CPaintZoneMainWindow::makeLine()
{
	TopoDS_Vertex aVertex = BRepBuilderAPI_MakeVertex(gp_Pnt(10.0, 25.0, 0.0));
	TopoDS_Shape aPrismVertex = BRepPrimAPI_MakePrism(aVertex, gp_Vec(3.0, 3.0, 0.0));
	Handle(AIS_Shape) anAisPrismVertex = new AIS_Shape(aPrismVertex);

	anAisPrismVertex->SetColor(Quantity_NOC_WHITE);

	myCPaintView->getContext()->Display(anAisPrismVertex, Standard_True);
}
void  CPaintZoneMainWindow::makeArc()
{
	gp_Ax1 anAxis;

	// revol a vertex result is an edge.
	anAxis.SetLocation(gp_Pnt(0.0, 30.0, 0.0));
	TopoDS_Vertex aVertex = BRepBuilderAPI_MakeVertex(gp_Pnt(2.0, 30.0, 0.0));
	TopoDS_Shape aRevolVertex = BRepPrimAPI_MakeRevol(aVertex, anAxis, M_PI_2*2);
	Handle(AIS_Shape) anAisRevolVertex = new AIS_Shape(aRevolVertex);

	anAisRevolVertex->SetColor(Quantity_NOC_WHITE);

	myCPaintView->getContext()->Display(anAisRevolVertex, Standard_True);
}
void  CPaintZoneMainWindow::makePoint()
{
	TopoDS_Vertex aVertex = BRepBuilderAPI_MakeVertex(gp_Pnt(10.0, 30.0, 0.0));
	Handle(AIS_Shape) anAisVertex = new AIS_Shape(aVertex);

	anAisVertex->SetColor(Quantity_NOC_WHITE);
	myCPaintView->getContext()->Display(anAisVertex, Standard_True);
}
