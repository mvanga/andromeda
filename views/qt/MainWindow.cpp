#include "MainWindow.h"
#include "SchematicWindow.h"

#include <qt4/QtGui/QToolButton>
#include <qt4/QtGui/QAction>

#include <andromeda/elements.h>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	QtSchematicRenderer *renderer = new QtSchematicRenderer();
	Schematic *sch = new Schematic();

	m_clayer = new Layer(0, "SCH_NETS");
	m_clayer->setNetColor(0x00ff00);
	m_clayer->setNetWidth(1);

	schem = new SchematicWindow(this, sch, renderer);
	schem->setCursor(Qt::CrossCursor);
	setCentralWidget(schem);

	status = new QStatusBar(this);
	setStatusBar(status);

	message = new QLabel("No Message");
	status->addWidget(message);

	QToolBar *tool = new QToolBar;
	tool->setGeometry(0, 0, 200, 20);

	drawNet = new QAction(QIcon("icons/draw_net.png"), "Net/Wire", this);
	connect(drawNet, SIGNAL(triggered()), this, SLOT(netToolSelect()));
	drawNet->setShortcut(QKeySequence(Qt::Key_P, Qt::Key_W));
	tool->addAction(drawNet);

	addToolBar(Qt::LeftToolBarArea, tool);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	event = 0;
	std::cout << "mainwindow keypress\n" << std::flush;
}

void MainWindow::netToolSelect()
{
	message->setText("Net tool selected");
	schem->setTool(TOOL_NET, m_clayer);
}
