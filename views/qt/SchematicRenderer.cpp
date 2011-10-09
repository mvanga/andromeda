#include "SchematicRenderer.h"
#include <QGLWidget>

#include <iostream>

void SchematicRenderer::renderNetEndpoint(SENetEndpoint *end)
{
}

void SchematicRenderer::setGridWidth(double p_grid)
{
	m_grid = p_grid;
}

void SchematicRenderer::renderNetSegment(SENetSegment *nseg)
{
	GLdouble oldWidth;
	unsigned int col = nseg->getLayer()->getNetColor();
	unsigned int w = nseg->getLayer()->getNetWidth();
	double x1, y1, x2, y2;
	x1 = nseg->getStart()->getX() * m_grid;
	y1 = nseg->getStart()->getY() * m_grid;
	x2 = nseg->getEnd()->getX() * m_grid;
	y2 = nseg->getEnd()->getY() * m_grid;

	glColor3f(((col>>16)&0xff)/255, ((col>>8)&0xff)/255, (col&0xff)/255);
	glGetDoublev(GL_LINE_WIDTH, &oldWidth);
	glLineWidth(w);
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
