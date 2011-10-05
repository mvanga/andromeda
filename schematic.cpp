#include <andromeda/schematic.h>

int Element::currId = 0;

Schematic::Schematic()
{
}

void Schematic::addElement(SchematicElement *p_element)
{
	m_elements.push_back(p_element);
}
