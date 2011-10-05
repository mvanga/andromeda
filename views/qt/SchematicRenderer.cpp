#include <QMouseEvent>
#include "SchematicRenderer.h"

#include <cstdio>
#include <cmath>

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
	glColor3f(0.8, 0.8, 0.8);
	glBegin(GL_LINES);
	/* Horizontal lines. */
	for (i=-m_height/2; i<=m_height/2; i++) {
		glVertex2f(-m_width/2, i*m_gridWidth);
		glVertex2f(m_width/2, i*m_gridWidth);
	}
	/* Vertical lines. */
	for (i=-m_width/2; i<=m_width/2; i++) {
		glVertex2f(i*m_gridWidth, -m_height/2);
		glVertex2f(i*m_gridWidth, m_height/2);
	}
	glEnd();
}

void SchematicRenderer::paintGL()
{
	double zN = sqrt(m_zoom);

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(m_panx + m_panex - m_pansx, m_pany + m_pansy - m_paney, 0);
	glScalef(1.0f/zN, 1.0/zN, 1);

	if (showGrid())
		drawGrid();
	
	glColor4f(1,0,0, 0.5);
	glBegin(GL_POLYGON);
	glVertex2f(0,0);
	glVertex2f(100,500);
	glVertex2f(500,100);
	glEnd();

#if 0
	glColor4f(0,0,1, 0.5);
	glBegin(GL_POLYGON);
	glVertex2f(100,100);
	glVertex2f(200,600);
	glVertex2f(600,200);
	glEnd();
#endif
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

void SchematicRenderer::zoom(int delta)
{
	if (delta < 0) {
		m_zoom += m_zoomDist;
	} else
		if (!(m_zoom - m_zoomDist <= 0))
			m_zoom -= m_zoomDist;
}

void SchematicRenderer::wheelEvent(QWheelEvent *event)
{
	zoom(event->delta());
	updateGL();
	event->accept();
}
