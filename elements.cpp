#include <andromeda/elements.h>

Element::Element(int p_layer, ElementType p_type) :
	m_layer(p_layer), m_type(p_type)
{
	currId++;
}

int Element::getLayer()
{
	return m_layer;
}

void Element::setLayer(int p_layer)
{
	m_layer = p_layer;
}

ElementType Element::getElementType()
{
	return m_type;
}

SchematicElement::SchematicElement(int p_layer,
	SchematicElementType p_schType) :
	Element(p_layer, ELEMENT_SCHEMATIC), m_schType(p_schType)
{
}
	
SchematicElementType SchematicElement::getSchematicElementType()
{
	return m_schType;
}

SENetEndpoint::SENetEndpoint(int p_layer, int p_x, int p_y) :
	SchematicElement(p_layer, SE_NET_ENDPOINT), m_x(p_x), m_y(p_y)
{
}

int SENetEndpoint::getX()
{
	return m_x;
}

int SENetEndpoint::getY()
{
	return m_y;
}

bool SENetEndpoint::operator==(const SENetEndpoint& other) const
{
	return ((other.m_x == m_x) && (other.m_y == m_y));
}

bool SENetEndpoint::operator!=(const SENetEndpoint& other) const
{
	return !(*this == other);
}

SENetSegment::SENetSegment(int p_layer, SENetEndpoint *p_start,
	SENetEndpoint *p_end) : SchematicElement(p_layer, SE_NET_SEGMENT),
	m_start(p_start), m_end(p_end)
{
	m_start->setLayer(p_layer);
	m_end->setLayer(p_layer);
}
	
SENetEndpoint *SENetSegment::getStart()
{
	return m_start;
}

SENetEndpoint *SENetSegment::getEnd()
{
	return m_end;
}

bool SENetSegment::isEndpoint(SENetEndpoint *p_test)
{
	return ((*p_test == *m_start) && (*p_test == *m_end));
}

void SENetSegment::setLayer(int p_layer)
{
	SchematicElement::setLayer(p_layer);
	m_start->setLayer(p_layer);
	m_end->setLayer(p_layer);
}

SENet::SENet(int p_layer) : SchematicElement(p_layer, SE_NET)
{
}

SENet::SENet(int p_layer, SENetSegment *p_segment) :
	SchematicElement(p_layer, SE_NET)
{
	m_segments.push_back(p_segment);
}

SENet::SENet(int p_layer, std::vector<SENetSegment *> p_segments) :
	SchematicElement(p_layer, SE_NET), m_segments(p_segments)
{
	unsigned int i;
	for (i = 0; i < m_segments.size();i++)
		m_segments[i]->setLayer(p_layer);
}

std::vector<SENetSegment *> *SENet::getSegments()
{
	return &m_segments;
}

void SENet::addSegment(SENetSegment *segment)
{
	m_segments.push_back(segment);
}

void SENet::setLayer(int p_layer)
{
	unsigned int i;
	SchematicElement::setLayer(p_layer);
	for (i = 0; i < m_segments.size();i++)
		m_segments[i]->setLayer(p_layer);
}
