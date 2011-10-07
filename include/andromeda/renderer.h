#ifndef ANDROMEDA_RENDERER_H
#define ANDROMEDA_RENDERER_H

#include <andromeda/elements.h>

class SchematicRenderer {
	virtual void renderNetEndpoint(SENetEndpoint *) {}
	virtual void renderNetSegment(SENetSegment *) {}
	virtual void renderNet(SENet *) {}
};

#endif
