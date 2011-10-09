#ifndef ANDROMEDA_QT_NET_TOOL
#define ANDROMEDA_QT_NET_TOOL

#include "SchematicTool.h"

#include <andromeda/schematic.h>

class NetTool : public SchematicTool {
public:
	NetTool(Schematic *, Schematic *);
	void selected(int layer);
	void unselected();
	void mousePressed(double x, double y, QMouseEvent *e);
	void mouseReleased(double x, double y, QMouseEvent *e);
	void mouseMoved(double x, double y, QMouseEvent *e);
	void mouseDoubleClicked(double x, double y, QMouseEvent *e);
	void keyPressed(QKeyEvent *e);

	void startNet(int x, int y);
	void drawNet(int x, int y, bool);
	void endNet();

private:
	int m_layer;
	Schematic m_netsch;
	SENetEndpoint *m_prev;
	int m_state;
};

#endif
