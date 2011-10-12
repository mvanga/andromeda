#include "MainWindow.h"
#include "ObjectManager.h"
#include "LayerManager.h"

#include <andromeda/schematic.h>
#include <andromeda/elements.h>

#include <QApplication>

void initLayers()
{
	Layer *layer;
	
	layer = LayerManager::instance()->createLayer(0, "NETS");
	layer->setNetColor(0x008000);
	layer->setNetWidth(2);

	layer = LayerManager::instance()->createLayer(1, "BUSES");
	layer->setNetColor(0x000080);
	layer->setNetWidth(3);

	layer = LayerManager::instance()->createLayer(2, "PINS");
	layer->setNetColor(0x000000);
	layer->setNetWidth(1);

	layer = LayerManager::instance()->createLayer(3, "SYMBOLS");
	layer->setNetColor(0x800000);
	layer->setNetWidth(1);

	layer = LayerManager::instance()->createLayer(4, "NAMES");
	layer->setNetColor(0x000080);
	layer->setNetWidth(1);

	layer = LayerManager::instance()->createLayer(5, "VALUES");
	layer->setNetColor(0x000080);
	layer->setNetWidth(1);

	layer = LayerManager::instance()->createLayer(6, "INFO");
	layer->setNetColor(0x808080);
	layer->setNetWidth(1);

	layer = LayerManager::instance()->createLayer(7, "GUIDE");
	layer->setNetColor(0x000000);
	layer->setNetWidth(1);

}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	LayerManager::init();
	ObjectManager::init();

	initLayers();

	MainWindow window(0);
	window.resize(800, 600);
	window.showMaximized();

	app.exec();

	ObjectManager::destroy();
	LayerManager::destroy();

	return 0;
}
