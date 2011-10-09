#include "ObjectManager.h"

#include <iostream>

ObjectManager *ObjectManager::m_instance = NULL;

std::vector<SchematicElement *> ObjectManager::m_sobj;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	while(!m_sobj.empty()) {
		delete m_sobj.back();
		m_sobj.pop_back();
	}
}

/* Create a net endpoint */
SENetEndpoint *ObjectManager::createNetEndpoint(int p_layer, double x, double y)
{
	SENetEndpoint *end;

	end = new SENetEndpoint(p_layer, x, y);
	if (!end)
		return NULL;
	m_sobj.push_back(end);

	return end;
}

/* Create a net segment */
SENetSegment *ObjectManager::createNetSegment(int p_layer, SENetEndpoint *s1, SENetEndpoint *s2)
{
	SENetSegment *seg;

	if (!s1 || !s2)
		return NULL;
	seg = new SENetSegment(p_layer, s1, s2);
	if (!seg)
		return NULL;
	m_sobj.push_back(seg);

	return seg;
}

/* Create a net with up to 2 segments */
SENet *ObjectManager::createNet(int p_layer, SENetSegment *s1, SENetSegment *s2)
{
	SENet *net;

	if (!s1) {
		net = new SENet(p_layer);
		if (!net)
			return NULL;
	} else {
		net = new SENet(p_layer, s1);
		if (!net)
			return NULL;
		if (s2)
			net->addSegment(s2);
	}
	return net;
}
