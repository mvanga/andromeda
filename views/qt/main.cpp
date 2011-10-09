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

	Layer *layer = LayerManager::instance()->createLayer(0, "NETS");
	layer->setNetColor(0x00ff00);
	layer->setNetWidth(1);

	MainWindow window(0);
	window.resize(800, 600);
	window.showMaximized();

	app.exec();

	ObjectManager::destroy();
	LayerManager::destroy();

	return 0;
}
