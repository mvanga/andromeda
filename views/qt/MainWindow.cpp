#include "MainWindow.h"

#include <qt4/QtGui/QVBoxLayout>

#include <andromeda/elements.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	QtSchematicRenderer *renderer = new QtSchematicRenderer();
	Schematic *sch = new Schematic();

	Layer *l = new Layer(0, "SCH_NETS");
	l->setNetColor(0x000000);
	l->setNetWidth(2);

	SENetEndpoint *a = new SENetEndpoint(l, 10, 10);
	SENetEndpoint *b = new SENetEndpoint(l, 20, 20);
	SENetSegment *seg = new SENetSegment(l, a, b, 0);
	SENet *net = new SENet(l, seg);

	sch->addElement(net);

	schem = new SchematicWindow(this, sch, renderer);
	schem->setCursor(Qt::CrossCursor);
	setCentralWidget(schem);

	status = new QStatusBar(this);
	setStatusBar(status);
}
