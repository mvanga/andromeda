#ifndef ANDROMEDA_QT_NET_TOOL
#define ANDROMEDA_QT_NET_TOOL

#include "SchematicTool.h"

#include <andromeda/schematic.h>

class NetTool : public SchematicTool {
public:
	NetTool(Schematic *, Schematic *);
	void selected(Layer *layer);
	void unselected();
	void mousePressed(double x, double y, QMouseEvent *e);
	void mouseReleased(double x, double y, QMouseEvent *e);
	void mouseMoved(double x, double y, QMouseEvent *e);
	void mouseDoubleClicked(double x, double y, QMouseEvent *e);
	void keyPressed(QKeyEvent *e);

private:
	Layer *m_layer;
	Schematic m_tmpsch;
	Schematic m_netsch;
	int m_state;
};

#endif
