#include "MainWindow.h"
#include "SchematicWindow.h"
#include "ObjectManager.h"
#include "LayerManager.h"

#include <andromeda/elements.h>

#include <QToolButton>
#include <QAction>

#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	SchematicRenderer *renderer = new SchematicRenderer();
	Schematic *sch = new Schematic();

	#if 0
	m_clayer = new Layer(0, "NETS");//LayerManager::instance()->createLayer(0, "NETS");
	m_clayer->setNetColor(0x00ff00);
	m_clayer->setNetWidth(1);
	#endif

	m_clayer = 0;

	schem = new SchematicWindow(this, sch, renderer);
	schem->setCursor(Qt::CrossCursor);
	setCentralWidget(schem);

	status = new QStatusBar(this);
	setStatusBar(status);

	message = new QLabel("No Message");
	status->addWidget(message);

	QToolBar *tool = new QToolBar;
	tool->setGeometry(0, 0, 200, 20);
	tool->setIconSize(QSize(20, 20));

	drawNet = new QAction(QIcon("icons/draw_net.png"), "Place a Net/Wire (pw)", this);
	connect(drawNet, SIGNAL(triggered()), this, SLOT(netToolSelect()));
	drawNet->setShortcut(QKeySequence(Qt::Key_P, Qt::Key_W));
	tool->addAction(drawNet);

	addToolBar(Qt::LeftToolBarArea, tool);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
}

void MainWindow::netToolSelect()
{
	message->setText("Net tool selected");
	schem->setTool(TOOL_NET, m_clayer);
}
