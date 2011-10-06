#include "MainWindow.h"

#include <qt4/QtGui/QVBoxLayout>

#include <andromeda/elements.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	Schematic *sch = new Schematic();

	SENetEndpoint *a = new SENetEndpoint(0, 10, 10);
	SENetEndpoint *b = new SENetEndpoint(0, 20, 20);
	SENetSegment *seg = new SENetSegment(0, a, b, 0);
	SENet *net = new SENet(0, seg);

	sch->addElement(net);

	schem = new SchematicWindow(this, sch);
	schem->setCursor(Qt::CrossCursor);
	setCentralWidget(schem);

	status = new QStatusBar(this);
	setStatusBar(status);
}
