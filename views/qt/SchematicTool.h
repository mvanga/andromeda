#ifndef ANDROMEDA_QT_SCHEMATIC_TOOL
#define ANDROMEDA_QT_SCHEMATIC_TOOL

#include <andromeda/schematic.h>

#include <qt4/QtGui/QMouseEvent>

class SchematicTool {
public:
	SchematicTool(Schematic *p_sch, Schematic *p_buf) : m_sch(p_sch), m_bufsch(p_buf) {}
	virtual void selected(Layer *layer) { layer = 0; }
	virtual void unselected() {}
	virtual void mousePressed(double x, double y, QMouseEvent *e) { x = y = 0; e = 0; }
	virtual void mouseReleased(double x, double y, QMouseEvent *e) { x = y = 0; e = 0; }
	virtual void mouseMoved(double x, double y, QMouseEvent *e) { x = y = 0; e = 0; }
	virtual void mouseDoubleClicked(double x, double y, QMouseEvent *e) { x = y = 0; e = 0; }
	virtual void keyPressed(QKeyEvent *e) { e = 0; }
protected:
	Schematic *m_sch;
	Schematic *m_bufsch;
};

#endif
