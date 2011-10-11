#ifndef ANDROMEDA_QT_SCHEMATIC_RENDERER
#define ANDROMEDA_QT_SCHEMATIC_RENDERER

#include <andromeda/renderer.h>

class SchematicRenderer : public Renderer {
public:
	void setZoom(double);

	void renderNetEndpoint(SENetEndpoint *);
	void renderNetSegment(SENetSegment *);
	void renderNet(SENet *);
	void setGridWidth(double);
private:
	double m_grid;
	double m_zoom;
};

#endif
