#include <andromeda/elements.h>

Element::Element(Layer *p_layer, ElementType p_type) :
	m_layer(p_layer), m_type(p_type)
{
	currId++;
}

Layer *Element::getLayer()
{
	return m_layer;
}

ElementType Element::getElementType()
{
	return m_type;
}
