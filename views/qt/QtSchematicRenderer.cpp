#include "QtSchematicRenderer.h"
#include <qt4/QtOpenGL/QGLWidget>

#include <iostream>

void QtSchematicRenderer::renderNetEndpoint(SENetEndpoint *end)
{
}

void QtSchematicRenderer::renderNetSegment(SENetSegment *nseg)
{
	GLdouble oldWidth;
	unsigned int col = nseg->getLayer()->getNetColor();
	unsigned int w = nseg->getLayer()->getNetWidth();
	glColor3f(((col>>16)&0xff)/255, ((col>>8)&0xff)/255, (col&0xff)/255);
	glGetDoublev(GL_LINE_WIDTH, &oldWidth);
	glLineWidth(w);
	glBegin(GL_LINES);
	glVertex2f(nseg->getStart()->getX(), nseg->getStart()->getY());
	glVertex2f(nseg->getEnd()->getX(), nseg->getEnd()->getY());
	glEnd();
	glLineWidth(oldWidth);
}

void QtSchematicRenderer::renderNet(SENet *net)
{
	unsigned int i;
	std::vector<SENetSegment *> *segments = net->getSegments();

	for (i = 0; i < segments->size(); i++)
		renderNetSegment(segments->at(i));
}
