#ifndef ANDROMEDA_QT_SCHEMATIC_RENDERER
#define ANDROMEDA_QT_SCHEMATIC_RENDERER

#include <andromeda/renderer.h>

class QtSchematicRenderer : public SchematicRenderer {
public:
	void renderNetEndpoint(SENetEndpoint *);
	void renderNetSegment(SENetSegment *);
	void renderNet(SENet *);
};

#endif
