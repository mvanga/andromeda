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
	Layer *m_layer;
	ElementType m_type;
public:
	Element(Layer *, ElementType);
	Layer *getLayer();
	void setLayer(Layer *);
	ElementType getElementType();
};

class SchematicElement : public Element {
	SchematicElementType m_schType;
public:
	SchematicElement(Layer *, SchematicElementType);
	SchematicElementType getSchematicElementType();
};

/* List of schematic elements (prefixed with SE) */

/* An endpoint of a net segment */
class SENetEndpoint : public SchematicElement {
	int m_x;
	int m_y;
public:
	SENetEndpoint(Layer *, int, int);
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
	SENetSegment(Layer *, SENetEndpoint *, SENetEndpoint *);
	SENetEndpoint *getStart();
	SENetEndpoint *getEnd();
	bool isEndpoint(SENetEndpoint *);
	void setLayer(Layer *);
};

/* Net consisting of multiple wire segments (eg. bent wire = 2 segments) */
class SENet : public SchematicElement {
	std::vector<SENetSegment *> m_segments;
public:
	SENet(Layer *);
	SENet(Layer *, SENetSegment *);
	SENet(Layer *, std::vector<SENetSegment *>);
	std::vector<SENetSegment *> *getSegments();
	void addSegment(SENetSegment *segment);
	void setLayer(Layer *);
};

#endif
