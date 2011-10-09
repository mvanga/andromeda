#ifndef ANDROMEDA_QT_OBJECT_MANAGER_H
#define ANDROMEDA_QT_OBJECT_MANAGER_H

#include <andromeda/elements.h>

/* All units are either mils or mm */
class ObjectManager {
public:
	static void init()
	{
		m_instance = new ObjectManager();
	}

	static ObjectManager *instance()
	{
		return m_instance;
	}

	static void destroy()
	{
		if (m_instance)
			delete m_instance;
	}

	/* Set the layer to use */
	void setLayer(Layer *);

	/* Create a net endpoint */
	SENetEndpoint *createNetEndpoint(Layer *, double, double);
	/* Create a net segment */
	SENetSegment *createNetSegment(Layer *, SENetEndpoint *, SENetEndpoint *);
	/* Create a net with up to 2 segments */
	SENet *createNet(Layer *, SENetSegment *s1 = 0, SENetSegment *s2 = 0);
private:
	ObjectManager();
	~ObjectManager();
	ObjectManager(ObjectManager const&);
	void operator=(ObjectManager const&);

	static ObjectManager *m_instance;

	static std::vector<SchematicElement *> m_sobj;
};

#endif
