#ifndef ANDROMEDA_QT_SCHEMATICRENDERER_H
#define ANDROMEDA_QT_SCHEMATICRENDERER_H

#include <andromeda/schematic.h>

#include <qt4/QtOpenGL/QGLWidget>

#define SCH_RENDER_SHOWGRID	(1<<0)

class SchematicRenderer: public QGLWidget {
	Q_OBJECT;

public:
	SchematicRenderer(QWidget *, Schematic *sch);

	void setGrid(bool);
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

	void zoom(int delta);

	void panStart(double x, double y);
	void panMove(double x, double y);
	void panEnd(double x, double y);
private:
	Schematic *m_sch;
	int m_gridWidth;
	int m_width;
	int m_height;

	/* Zoom properties */
	double m_zoom;
	double m_zoomDist;

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
