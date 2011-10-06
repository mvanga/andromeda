#include <qt4/QtGui/QApplication>
#include "MainWindow.h"

#include <andromeda/schematic.h>
#include <andromeda/elements.h>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MainWindow window(0);
	window.resize(800, 600);
	window.showMaximized();

	return app.exec();
}
