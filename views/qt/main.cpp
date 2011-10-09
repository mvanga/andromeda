#include "MainWindow.h"
#include "ObjectManager.h"
#include "LayerManager.h"

#include <andromeda/schematic.h>
#include <andromeda/elements.h>

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	LayerManager::init();
	ObjectManager::init();

	MainWindow window(0);
	window.resize(800, 600);
	window.showMaximized();

	ObjectManager::destroy();
	LayerManager::destroy();

	return app.exec();
}
