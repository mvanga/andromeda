#ifndef ANDROMEDA_ELEMENT_H
#define ANDROMEDA_ELEMENT_H

#include <andromeda/layer.h>

#include <vector>

/* Generic Element class for all elements in the design */

enum ElementType {
	ELEMENT_SCHEMATIC,
	ELEMENT_LAYOUT,
};

enum SchematicElementType {
	SE_NET_ENDPOINT,
	SE_NET_SEGMENT,
	SE_NET,
};

class Element {
	static int currId;
	int m_id;
	int m_layer;
	ElementType m_type;
public:
	Element(int, ElementType);
	int getLayer();
	void setLayer(int );
	ElementType getElementType();
};

class SchematicElement : public Element {
	SchematicElementType m_schType;
public:
	SchematicElement(int, SchematicElementType);
	SchematicElementType getSchematicElementType();
};

/* List of schematic elements (prefixed with SE) */

/* An endpoint of a net segment */
class SENetEndpoint : public SchematicElement {
	int m_x;
	int m_y;
public:
	SENetEndpoint(int, int, int);
	int getX();
	int getY();
	bool operator==(const SENetEndpoint&) const;
	bool operator!=(const SENetEndpoint&) const;
};

/* A net segment (line between 2 wire endpoints) */
class SENetSegment : public SchematicElement {
	SENetEndpoint *m_start;
	SENetEndpoint *m_end;
public:
	SENetSegment(int, SENetEndpoint *, SENetEndpoint *);
	SENetEndpoint *getStart();
	SENetEndpoint *getEnd();
	bool isEndpoint(SENetEndpoint *);
	void setLayer(int );
};

/* Net consisting of multiple wire segments (eg. bent wire = 2 segments) */
class SENet : public SchematicElement {
	std::vector<SENetSegment *> m_segments;
public:
	SENet(int );
	SENet(int, SENetSegment *);
	SENet(int, std::vector<SENetSegment *>);
	std::vector<SENetSegment *> *getSegments();
	void addSegment(SENetSegment *segment);
	void setLayer(int );
};

#endif
