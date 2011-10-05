#ifndef ANDROMEDA_SCHEMATIC_H
#define ANDROMEDA_SCHEMATIC_H

#include <andromeda/elements.h>

class Schematic {
	std::vector<SchematicElement *> m_elements;
public:
	Schematic();
	void addElement(SchematicElement *p_element);
	std::vector<SchematicElement *>& getElements() { return m_elements; }
};

#endif
