#ifndef ANDROMEDA_ELEMENT_H
#define ANDROMEDA_ELEMENT_H

#include <andromeda/layer.h>

#include <vector>

/* Generic Element class for all elements in the design */

enum ElementType {
	ELEMENT_SCHEMATIC,
	ELEMENT_LAYOUT,
};

class Element {
	static int currId;
	int m_id;
	Layer *m_layer;
	ElementType m_type;
public:
	Element(Layer *p_layer, ElementType p_type);
	Layer *getLayer();
	ElementType getElementType();
};

/* Schematic Element class for all elements related to schematics */

enum SchematicElementType {
	SE_WIRE_ENDPOINT,
	SE_WIRE_SEGMENT,
	SE_WIRE,
};

class SchematicElement : public Element {
	SchematicElementType m_schType;
public:
	SchematicElement(Layer *p_layer, SchematicElementType p_schType) :
		Element(p_layer, ELEMENT_SCHEMATIC), m_schType(p_schType) {}
	
	SchematicElementType getSchematicElementType() { return m_schType; }
};

/* List of schematic elements (prefixed with SE) */

/* An endpoint of a net segment */
class SENetEndpoint : public SchematicElement {
	int m_x;
	int m_y;
public:
	SENetEndpoint(Layer *p_layer, int p_x, int p_y) :
		SchematicElement(p_layer, SE_WIRE_ENDPOINT), m_x(p_x), m_y(p_y) {}
	int getX() { return m_x; }
	int getY() { return m_y; }
	bool operator==(const SENetEndpoint& other) const {
		return ((other.m_x == m_x) && (other.m_y == m_y));
	}
	bool operator!=(const SENetEndpoint& other) const {
		return !(*this == other);
	}
};

/* A net segment (line between 2 wire endpoints) */
class SENetSegment : public SchematicElement {
	SENetEndpoint *m_start;
	SENetEndpoint *m_end;
	unsigned long m_color;
public:
	SENetSegment(Layer *p_layer, SENetEndpoint *p_start, SENetEndpoint *p_end, unsigned long p_color) :
		SchematicElement(p_layer, SE_WIRE_SEGMENT), m_start(p_start), m_end(p_end), m_color(p_color) {}
	
	SENetEndpoint *getStart() { return m_start; }
	SENetEndpoint *getEnd() { return m_end; }
	bool isEndpoint(SENetEndpoint *p_test)
	{
		return ((*p_test == *m_start) && (*p_test == *m_end));
	}
};

/* Net consisting of multiple wire segments (eg. bent wire = 2 segments) */
class SENet : public SchematicElement {
	std::vector<SENetSegment *> m_segments;
public:
	SENet(Layer *p_layer, SENetSegment *p_segment) :
		SchematicElement(p_layer, SE_WIRE)
	{
		m_segments.push_back(p_segment);
	}
	SENet(Layer *p_layer, std::vector<SENetSegment *> p_segments) :
		SchematicElement(p_layer, SE_WIRE), m_segments(p_segments) {}
	
	std::vector<SENetSegment *>& getSegments() { return m_segments; }
	void addSegment(SENetSegment *segment) { m_segments.push_back(segment); }
};

#endif
