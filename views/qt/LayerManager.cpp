#include "LayerManager.h"

LayerManager *LayerManager::m_instance = NULL;
std::vector<Layer *> LayerManager::m_layers;

LayerManager::LayerManager()
{
}

LayerManager::~LayerManager()
{
	while(!m_layers.empty()) {
		delete m_layers.back();
		m_layers.pop_back();
	}
}

Layer *LayerManager::createLayer(int p_num, std::string p_name)
{
	Layer *layer = new Layer(p_num, p_name);
	if (!layer)
		return NULL;
	m_layers.push_back(layer);
	return layer;
}

Layer *LayerManager::getLayer(int p_num)
{
	for(std::vector<Layer>::size_type i = 0; i != m_layers.size(); i++)
		if (m_layers[i]->getNumber() == p_num)
			return m_layers[i];
	return NULL;
}

Layer *LayerManager::getLayer(std::string p_name)
{
	for(std::vector<Layer>::size_type i = 0; i != m_layers.size(); i++)
		if (m_layers[i]->getName() == p_name)
			return m_layers[i];
	return NULL;
}
