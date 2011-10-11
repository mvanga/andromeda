#ifndef ANDROMEDA_QT_NET_TOOL
#define ANDROMEDA_QT_NET_TOOL

#include "SchematicTool.h"

#include <andromeda/schematic.h>

#define NET_TYPE_90		0
#define NET_TYPE_45		1
#define NET_TYPE_STRAIGHT	2

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

	void toggleFlip();
	void setType(int);
	void toggleType();

private:
	int m_layer;
	Schematic m_netsch;
	SENetEndpoint *m_prev;
	int m_state;
	int m_type;
	bool m_flip;
	int m_lastx, m_lasty;
};

#endif
