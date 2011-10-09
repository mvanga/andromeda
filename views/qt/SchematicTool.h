#ifndef ANDROMEDA_QT_SCHEMATIC_TOOL
#define ANDROMEDA_QT_SCHEMATIC_TOOL

#include <andromeda/schematic.h>

#include <QMouseEvent>

class SchematicTool {
public:
	SchematicTool(Schematic *p_sch, Schematic *p_buf) : m_sch(p_sch), m_bufsch(p_buf) {}
	virtual void selected(int) {}
	virtual void unselected() {}
	virtual void mousePressed(double, double, QMouseEvent *) {}
	virtual void mouseReleased(double, double, QMouseEvent *) {}
	virtual void mouseMoved(double, double, QMouseEvent *) {}
	virtual void mouseDoubleClicked(double, double, QMouseEvent *) {}
	virtual void keyPressed(QKeyEvent *) {}
protected:
	Schematic *m_sch;
	Schematic *m_bufsch;
};

#endif
