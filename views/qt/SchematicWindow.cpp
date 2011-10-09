#include "SchematicWindow.h"

#include <QMouseEvent>

#include <cstdio>
#include <cmath>
#include <iostream>

SchematicWindow::SchematicWindow(QWidget *parent, Schematic *p_sch, SchematicRenderer *r) :
	QGLWidget(parent), m_sch(p_sch), m_renderer(r)
{
	setMouseTracking(true);
	m_gridWidth = 10;
	setFocus();

	setGrid(false);

	m_zoom = 1;
	m_zoomDist = 0.01;

	m_pansx = 0;
	m_pansy = 0;
	m_panex = 0;
	m_paney = 0;

	m_panx = 0;
	m_pany = 0;

	m_tool = TOOL_NONE;

	m_netTool = new NetTool(m_sch, &m_bufsch);

	m_renderer->setGridWidth(m_gridWidth);
}

void SchematicWindow::initializeGL()
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glEnable(GL_POLYGON_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
	glClearColor(255, 255, 255, 0);
}

void SchematicWindow::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w/2, w/2, -h/2, h/2); // set origin to center of screen
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	m_width = w;
	m_height = h;
}

void SchematicWindow::setGrid(bool draw)
{
	if (draw)
		m_flags |= SCH_RENDER_SHOWGRID;
	else
		m_flags &= ~SCH_RENDER_SHOWGRID;
}

bool SchematicWindow::showGrid()
{
	return m_flags & SCH_RENDER_SHOWGRID;
}

void SchematicWindow::drawOrigin()
{
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_LINES);
	glVertex2f(-10, 0);
	glVertex2f(10, 0);
	glVertex2f(0, 10);
	glVertex2f(0, -10);
	glEnd();
}

void SchematicWindow::drawGrid()
{
	int i;

	if (!showGrid())
		return;

	/* Draw a basic grid */
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_LINES);
	/* Horizontal */
	for (i=-m_height/2; i <= m_height/2; i++) {
		glVertex2f(0, i*m_gridWidth);
		glVertex2f(m_width/2, i*m_gridWidth);
	}
	for (i=-m_height/2; i <= m_height/2; i++) {
		glVertex2f(-m_width/2, i*m_gridWidth);
		glVertex2f(0, i*m_gridWidth);
	}

	/* Vertical */
	for (i=-m_width/2; i<=m_width/2; i++) {
		glVertex2f(i*m_gridWidth, 0);
		glVertex2f(i*m_gridWidth, m_height/2);
	}
	for (i=-m_width/2; i<=m_width/2; i++) {
		glVertex2f(i*m_gridWidth, 0);
		glVertex2f(i*m_gridWidth, -m_height/2);
	}
	glEnd();

	/* Draw stronger lines every 10 units */
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_LINES);
	/* Horizontal lines. */
	for (i=-m_height/2; i<=m_height/2; i+=10) {
		glVertex2f(0, i*m_gridWidth);
		glVertex2f(m_width/2, i*m_gridWidth);
	}
	for (i=-m_height/2; i<=m_height/2; i+=10) {
		glVertex2f(-m_width/2, i*m_gridWidth);
		glVertex2f(0, i*m_gridWidth);
	}
	/* Vertical lines. */
	for (i=-m_width/2; i<=m_width/2; i+=10) {
		glVertex2f(i*m_gridWidth, -m_height/2);
		glVertex2f(i*m_gridWidth, m_height/2);
	}
	glEnd();
}

void SchematicWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	pan();
	zoom();
	drawGrid();
	drawOrigin();

	renderSchematic(m_sch);
	renderSchematic(&m_bufsch);

	setFocus();
}

void SchematicWindow::mousePressEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::MiddleButton) {
		panStart(event->x(), event->y());
	}
	int x, y;
	screenToWorld(event->x(), event->y(), &x, &y);
	switch (m_tool) {
	case TOOL_NET: {
		m_netTool->mousePressed(x, y, event);
		break;
	}
	}
	updateGL();
}

void SchematicWindow::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::MiddleButton) {
		panEnd(event->x(), event->y());
	}
	if (event->button() == Qt::LeftButton) {
		int x, y;
		screenToWorld(event->x(), event->y(), &x, &y);
		switch (m_tool) {
		case TOOL_NET: {
			m_netTool->mouseReleased(x, y, event);
		}
		}
	}
	updateGL();
}

void SchematicWindow::mouseMoveEvent(QMouseEvent *event)
{
	int x, y;
	screenToWorld(event->x(), event->y(), &x, &y);
	if (event->buttons() & Qt::MiddleButton) {
		panMove(event->x(), event->y());
	}
	switch (m_tool) {
	case TOOL_NET: {
		m_netTool->mouseMoved(x, y, event);
	}
	}
	updateGL();
}

void SchematicWindow::mouseDoubleClickedEvent(QMouseEvent *event)
{
	int x, y;
	screenToWorld(event->x(), event->y(), &x, &y);
	switch (m_tool) {
	case TOOL_NET: {
		m_netTool->mouseDoubleClicked(x, y, event);
		break;
	}
	}
}

void SchematicWindow::wheelEvent(QWheelEvent *event)
{
	setZoom(event->x(), event->y(), event->delta());
	updateGL();
	event->accept();
}

void SchematicWindow::keyPressEvent(QKeyEvent* event)
{
	if (m_tool == TOOL_NET) {
		m_netTool->keyPressed(event);
	}
	switch(event->key()) {
	case Qt::Key_Equal:
	case Qt::Key_Plus:
		setZoom(m_width/2, m_height/2, 120);
		break;
	case Qt::Key_Minus:
		setZoom(m_width/2, m_height/2, -120);
		break;
	case Qt::Key_Left:
		panStart(m_width/2, m_height/2);
		panMove(m_width/2 + 10, m_height/2);
		panEnd(m_width/2 + 10, m_height/2);
		break;
	case Qt::Key_Right:
		panStart(m_width/2, m_height/2);
		panMove(m_width/2 - 10, m_height/2);
		panEnd(m_width/2 - 10, m_height/2);
		break;
	case Qt::Key_Up:
		panStart(m_width/2, m_height/2);
		panMove(m_width/2, m_height/2 + 10);
		panEnd(m_width/2, m_height/2 + 10);
		break;
	case Qt::Key_Down:
		panStart(m_width/2, m_height/2);
		panMove(m_width/2, m_height/2 - 10);
		panEnd(m_width/2, m_height/2 - 10);
		break;
	case Qt::Key_Escape:
		m_tool = TOOL_NONE;
		break;
	default:
		event->ignore();
		break;
	}
	updateGL();
}

void SchematicWindow::panStart(double x, double y)
{
	m_pansx = x;
	m_pansy = y;
	m_panex = x;
	m_paney = y;
}

void SchematicWindow::panMove(double x, double y)
{
	m_panex = x;
	m_paney = y;
}

void SchematicWindow::panEnd(double x, double y)
{
	m_panex = x;
	m_paney = y;
	m_panx += m_panex - m_pansx;
	m_pany += m_pansy - m_paney;
	m_pansx = 0;
	m_pansy = 0;
	m_panex = 0;
	m_paney = 0;
}

void SchematicWindow::pan()
{
	double xd = m_panex - m_pansx;
	double yd = m_pansy - m_paney;
	glTranslatef(m_panx + xd, m_pany + yd, 0);
}

void SchematicWindow::zoom()
{
	double zN = sqrt(m_zoom);

	glTranslatef(m_zoomX, m_zoomY, 0);
//	gluOrtho2D(-m_width/2*m_zoom, -m_width/2*m_zoom, -m_height/2*m_zoom, -m_height/2*m_zoom); // set origin to center of screen
	glScalef(1.0f/zN, 1.0/zN, 1);
	glTranslatef(-m_zoomX, -m_zoomY, 0);
}

void SchematicWindow::setZoom(double x, double y, int delta)
{
	getGLPos(x, y, &m_zoomX, &m_zoomY);
	if (delta < 0) {
		m_zoom += m_zoomDist;
	} else
		if (!(m_zoom - m_zoomDist <= 0))
			m_zoom -= m_zoomDist;
}

void SchematicWindow::screenToWorld(double x, double y, int *ox, int *oy)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)x;
	winY = m_height - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	*ox = (int)(posX/m_gridWidth);
	*oy = (int)(posY/m_gridWidth);
}

void SchematicWindow::worldToScreen(int x, int y, double *ox, double *oy)
{
	*ox = x * m_gridWidth;
	*oy = y * m_gridWidth;
}

void SchematicWindow::getGLPos(double x, double y, double *ox, double *oy)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)x;
	winY = m_height - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

	*ox = posX;
	*oy = posY;
}

void SchematicWindow::renderSchematic(Schematic *sch)
{
	std::vector<SchematicElement *> elements = sch->getElements();
	unsigned int i;
	
	for (i = 0; i < elements.size(); i++) {
		switch (elements[i]->getSchematicElementType()) {
		case SE_NET_ENDPOINT: {
			break;
		}
		case SE_NET_SEGMENT: {
			break;
		}
		case SE_NET: {
			SENet *net = static_cast<SENet*>(elements[i]);
			m_renderer->renderNet(net);
			break;
		}
		default:
			break;
		}
	}
}

void SchematicWindow::setTool(unsigned int p_tool, int layer = 0)
{
	m_tool = p_tool;
	if (layer)
		m_clayer = layer;
	switch (p_tool) {
	case TOOL_NET:
		m_netTool->selected(layer);
	}
}
