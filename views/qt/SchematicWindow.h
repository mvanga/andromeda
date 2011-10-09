#ifndef ANDROMEDA_QT_SCHEMATICRENDERER_H
#define ANDROMEDA_QT_SCHEMATICRENDERER_H

#include "SchematicRenderer.h"
#include "NetTool.h"

#include <andromeda/schematic.h>

#include <QGLWidget>

#define SCH_RENDER_SHOWGRID	(1<<0)

enum {
	TOOL_NONE,
	TOOL_NET,
};

class SchematicWindow: public QGLWidget {
	Q_OBJECT;

public:
	SchematicWindow(QWidget *, Schematic *sch, SchematicRenderer *r);

	void setGrid(bool);
	void setZoom(double, double, int);

	void setTool(unsigned int, Layer *);
protected:
	/* QGLWidget related */
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

	/* Event Handlers*/
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void mouseDoubleClickedEvent(QMouseEvent *event);

	/* Grid management */
	bool showGrid();
	void drawGrid();
	void drawOrigin();

	/* Zooming */
	void zoom();

	/* Panning */
	void panStart(double x, double y);
	void panMove(double x, double y);
	void panEnd(double x, double y);
	void pan();

	/* Coordinate conversion (Qt -> OpenGL) */
	void getGLPos(double, double, double *, double *);
	void screenToWorld(double, double, int *, int *);
	void worldToScreen(int, int, double *, double *);

	/* Schematic rendering */
	void renderSchematic(Schematic *);
private:
	/* The main schematic */
	Schematic *m_sch;
	/* The drawing buffer schematic */
	Schematic m_bufsch;
	/* Temp holder */
	Schematic m_tmpsch;

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

	SchematicRenderer *m_renderer;

	unsigned int m_tool;

	Layer *m_clayer;

	NetTool *m_netTool;
};

#endif
