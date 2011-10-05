#ifndef ANDROMEDA_QT_SCHEMATICRENDERER_H
#define ANDROMEDA_QT_SCHEMATICRENDERER_H

#include <andromeda/schematic.h>

#include <qt4/QtOpenGL/QGLWidget>

#define SCH_RENDER_SHOWGRID	(1<<0)

class Position {
public:
	float m_x;
	float m_y;
	float m_z;
	Position(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {}
	Position(Position& p) { m_x = p.m_x; m_y = p.m_y; m_z = p.m_z; }
	void operator=(Position& p) { m_x = p.m_x; m_y = p.m_y; m_z = p.m_z; }
};

class SchematicRenderer: public QGLWidget {
	Q_OBJECT;

public:
	SchematicRenderer(QWidget *, Schematic *sch);

	void setGrid(bool);
	void setZoom(double, double, int);
protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void wheelEvent(QWheelEvent *event);

	bool showGrid();

	void drawGrid();

	void zoom();
	void pan();

	void panStart(double x, double y);
	void panMove(double x, double y);
	void panEnd(double x, double y);

	Position *getGLPos(int x, int y);
private:
	Schematic *m_sch;
	int m_gridWidth;
	int m_width;
	int m_height;

	/* Zoom properties */
	double m_zoom;
	double m_zoomDist;
	double m_zoomX;
	double m_zoomY;

	/* Pan properties */
	double m_panx;
	double m_pany;

	/* Temporary pan properties */
	double m_pansx;
	double m_pansy;
	double m_panex;
	double m_paney;

	/* Flags */
	unsigned int m_flags;
};

#endif
