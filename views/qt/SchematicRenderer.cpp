#include <QMouseEvent>
#include "SchematicRenderer.h"

#include <cstdio>
#include <cmath>

Position *SchematicRenderer::getGLPos(int x, int y)
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

	return new Position(posX, posY, posZ);
}

SchematicRenderer::SchematicRenderer(QWidget *parent, Schematic *p_sch) :
	QGLWidget(parent), m_sch(p_sch) {
	setMouseTracking(true);
	m_gridWidth = 5;

	setGrid(true);

	m_zoom = 1;
	m_zoomDist = 0.01;

	m_pansx = 0;
	m_pansy = 0;
	m_panex = 0;
	m_paney = 0;

	m_panx = 0;
	m_pany = 0;
}

void SchematicRenderer::initializeGL()
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glEnable(GL_POLYGON_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
	glClearColor(255, 255, 255, 0);
}

void SchematicRenderer::resizeGL(int w, int h)
{
	printf("Screen Size: %d %d\n", w, h);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w/2, w/2, -h/2, h/2); // set origin to center of screen
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	m_width = w;
	m_height = h;
}

void SchematicRenderer::setGrid(bool draw)
{
	if (draw)
		m_flags |= SCH_RENDER_SHOWGRID;
	else
		m_flags &= ~SCH_RENDER_SHOWGRID;
}

bool SchematicRenderer::showGrid()
{
	return m_flags & SCH_RENDER_SHOWGRID;
}

void SchematicRenderer::drawGrid()
{
	int i;

	if (!showGrid())
		return;

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

void SchematicRenderer::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	pan();
	zoom();
	drawGrid();
	
	glColor4f(1,0,0, 0.5);
	glBegin(GL_POLYGON);
	glVertex2f(0,0);
	glVertex2f(100,500);
	glVertex2f(500,100);
	glEnd();

	glColor4f(0,0,1, 0.5);
	glBegin(GL_POLYGON);
	glVertex2f(100,100);
	glVertex2f(200,600);
	glVertex2f(600,200);
	glEnd();
}

void SchematicRenderer::panStart(double x, double y)
{
	m_pansx = x;
	m_pansy = y;
	m_panex = x;
	m_paney = y;
}

void SchematicRenderer::panMove(double x, double y)
{
	m_panex = x;
	m_paney = y;
}

void SchematicRenderer::panEnd(double x, double y)
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

void SchematicRenderer::pan()
{
	glTranslatef(m_panx + m_panex - m_pansx, m_pany + m_pansy - m_paney, 0);
}

void SchematicRenderer::mousePressEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::MiddleButton) {
		printf("middle button pressed\n");
		panStart(event->x(), event->y());
	}
	updateGL();
}

void SchematicRenderer::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::MiddleButton) {
		printf("middle button released\n");
		panEnd(event->x(), event->y());
	}
	updateGL();
}

void SchematicRenderer::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::MiddleButton) {
		panMove(event->x(), event->y());
	}
	updateGL();
}

void SchematicRenderer::keyPressEvent(QKeyEvent* event)
{
	switch(event->key()) {
	case Qt::Key_Escape:
		close();
		break;
	default:
		event->ignore();
		break;
	}
}

void SchematicRenderer::zoom()
{
	double zN = sqrt(m_zoom);

	printf("%lf %lf\n", m_zoomX, m_zoomY);
	glTranslatef(m_zoomX, m_zoomY, 0);
	glScalef(1.0f/zN, 1.0/zN, 1);
	glTranslatef(-m_zoomX, -m_zoomY, 0);
}

void SchematicRenderer::setZoom(double x, double y, int delta)
{
	Position *p = getGLPos(x, y);
	m_zoomX = p->m_x;
	m_zoomY = p->m_y;
	delete p;
	if (delta < 0) {
		m_zoom += m_zoomDist;
	} else
		if (!(m_zoom - m_zoomDist <= 0))
			m_zoom -= m_zoomDist;
}

void SchematicRenderer::wheelEvent(QWheelEvent *event)
{
	setZoom(event->x(), event->y(), event->delta());
	updateGL();
	event->accept();
}
