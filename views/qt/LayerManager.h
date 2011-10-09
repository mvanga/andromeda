#ifndef ANDROMEDA_QT_LAYER_MANAGER_H
#define ANDROMEDA_QT_LAYER_MANAGER_H

#include <andromeda/elements.h>

#include <vector>

/* All units are either mils or mm */
class LayerManager {
public:
	static void init()
	{
		m_instance = new LayerManager();
	}

	static LayerManager *instance()
	{
		return m_instance;
	}

	static void destroy()
	{
		if (m_instance)
			delete m_instance;
	}

	Layer *createLayer(int, std::string);
	Layer *getLayer(int);
	Layer *getLayerByName(std::string);
private:
	LayerManager();
	~LayerManager();
	LayerManager(LayerManager const&);
	void operator=(LayerManager const&);

	static LayerManager *m_instance;

	std::vector<Layer *> m_layers;
};

#endif
