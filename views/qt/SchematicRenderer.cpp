#include "SchematicRenderer.h"
#include "LayerManager.h"

#include <QGLWidget>

#include <iostream>
#include <cmath>

void SchematicRenderer::renderNetEndpoint(SENetEndpoint *end)
{
#if 0
	int i;
	double x, y, r;

	x = end->getX() * m_grid;
	y = end->getY() * m_grid;
	r = LayerManager::instance()->getLayer(end->getLayer())->getNetWidth()/2;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (i = 0; i < 360; i++)
		glVertex2f(x + sin(i)*r, y + cos(i)*r);
	glEnd();
#endif
}

void SchematicRenderer::setGridWidth(double p_grid)
{
	m_grid = p_grid;
}

void SchematicRenderer::setZoom(double zoom)
{
	m_zoom = zoom;
}

void SchematicRenderer::renderNetSegment(SENetSegment *nseg)
{
	GLdouble oldWidth;
	Layer *layer;
	unsigned int col, w;
	double x1, y1, x2, y2;

	layer = LayerManager::instance()->getLayer(nseg->getLayer());
	col = layer->getNetColor();
	w = layer->getNetWidth();
	x1 = nseg->getStart()->getX() * m_grid;
	y1 = nseg->getStart()->getY() * m_grid;
	x2 = nseg->getEnd()->getX() * m_grid;
	y2 = nseg->getEnd()->getY() * m_grid;

#if 0
	renderNetEndpoint(nseg->getStart());
	renderNetEndpoint(nseg->getEnd());
#endif

	glColor3f(((col>>16)&0xff)/255, ((col>>8)&0xff)/255, (col&0xff)/255);
	glGetDoublev(GL_LINE_WIDTH, &oldWidth);
	glLineWidth(w*m_zoom);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
	glLineWidth(oldWidth);
}

void SchematicRenderer::renderNet(SENet *net)
{
	unsigned int i;
	std::vector<SENetSegment *> *segments = net->getSegments();

	for (i = 0; i < segments->size(); i++) {
		renderNetSegment(segments->at(i));
	}
}
