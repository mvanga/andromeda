#include "NetTool.h"
#include "LayerManager.h"
#include "ObjectManager.h"

#include <iostream>

NetTool::NetTool(Schematic *p_sch, Schematic *p_buf)
	: SchematicTool(p_sch, p_buf)
{
}

void NetTool::selected(int layer)
{
	m_layer = layer;
	m_state = 0;
	m_prev = NULL;
}

void NetTool::unselected()
{
}

void NetTool::startNet(int x, int y)
{
	SENetEndpoint *p = ObjectManager::instance()->createNetEndpoint(m_layer, x, y);
	m_prev = p;
	m_state = 1;
}

void NetTool::drawNet(int x, int y, bool add)
{
	SENetEndpoint *p, *q;
	SENetSegment *s;
	SENet *n;

	if (x == m_prev->getX() && y == m_prev->getY()) {
		std::cout << "Zero length net ignored\n";
		return;
	}

	p = ObjectManager::instance()->createNetEndpoint(m_layer, x, y);
	q = static_cast<SENetEndpoint*>(m_prev);
	s = ObjectManager::instance()->createNetSegment(m_layer, q, p);
	n = ObjectManager::instance()->createNet(m_layer, s);

	m_bufsch->clear();
	if (add) {
		m_netsch.addElement(n);
		m_prev = p;
	} else {
		m_bufsch->addElement(n);
	}
	m_bufsch->merge(&m_netsch);
}

void NetTool::endNet()
{
	m_sch->merge(&m_netsch);
	m_bufsch->clear();
	m_prev = NULL;
	m_state = 0;
}

void NetTool::mousePressed(double x, double y, QMouseEvent *e)
{
	if (m_state == 0 && (e->buttons() & Qt::LeftButton)) {
		startNet(x, y);
	} else if (m_state == 1) {
		if (e->buttons() & Qt::LeftButton)
			drawNet(x, y, true);
		else if (e->buttons() & Qt::RightButton)
			endNet();
	}
}

void NetTool::mouseReleased(double x, double y, QMouseEvent *e)
{
	e = 0;
	x = y = 0;
}

void NetTool::mouseMoved(double x, double y, QMouseEvent *e)
{
	if (m_state == 1)
		drawNet(x, y, false);
	e = 0;
}

void NetTool::mouseDoubleClicked(double x, double y, QMouseEvent *e)
{
	x = y = 0;
	e = 0;
}

void NetTool::keyPressed(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Escape && m_state == 1)
		endNet();
}
