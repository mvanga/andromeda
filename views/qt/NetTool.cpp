#include "NetTool.h"
#include "LayerManager.h"
#include "ObjectManager.h"

#include <iostream>

NetTool::NetTool(Schematic *p_sch, Schematic *p_buf)
	: SchematicTool(p_sch, p_buf), m_type(NET_TYPE_90), m_flip(false)
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

void NetTool::toggleFlip()
{
	m_flip = !m_flip;
}

void NetTool::toggleType()
{
	m_type++;
	if (m_type > NET_TYPE_STRAIGHT)
		m_type = NET_TYPE_90;
}

void NetTool::setType(int p_type)
{
	m_type = p_type;
}

void NetTool::startNet(int x, int y)
{
	SENetEndpoint *p = ObjectManager::instance()->createNetEndpoint(m_layer, x, y);
	m_prev = p;
	m_state = 1;
}

void NetTool::drawNet(int x, int y, bool add)
{
	SENetEndpoint *p, *q, *r;
	SENetSegment *s1, *s2;
	SENet *n;
	int dx, dy;
	int dxm, dym;
	int x0, y0;

	x0 = m_prev->getX();
	y0 = m_prev->getY();

	if (x == m_prev->getX() && y == m_prev->getY()) {
		std::cout << "Zero length net ignored\n";
		return;
	}

	dx = x - m_prev->getX();
	dy = y - m_prev->getY();
	dxm = dx < 0 ? -dx : dx;
	dym = dy < 0 ? -dy : dy;

	int dmin = dxm < dym ? dxm : dym;
	int xs = dx < 0 ? -1 : 1;
	int ys = dy < 0 ? -1 : 1;

	if (!dx || !dy || m_type == NET_TYPE_STRAIGHT) {
		p = ObjectManager::instance()->createNetEndpoint(m_layer, x, y);
		q = static_cast<SENetEndpoint*>(m_prev);
		s1 = ObjectManager::instance()->createNetSegment(m_layer, q, p);
		n = ObjectManager::instance()->createNet(m_layer, s1);
	} else {
		p = ObjectManager::instance()->createNetEndpoint(m_layer, x, y);
		switch (m_type) {
		case NET_TYPE_90:
			if (m_flip)
				q = ObjectManager::instance()->createNetEndpoint(m_layer, x - dx, y);
			else
				q = ObjectManager::instance()->createNetEndpoint(m_layer, x, y - dy);
			break;
		case NET_TYPE_45:
			if (m_flip) {
				if (dxm > dym)
					q = ObjectManager::instance()->createNetEndpoint(m_layer, x0 + xs * (dxm - dym), y0);
				else
					q = ObjectManager::instance()->createNetEndpoint(m_layer, x0, y0 + ys * (dym - dxm));
			} else {
				q = ObjectManager::instance()->createNetEndpoint(m_layer, x0 + dmin*xs, y0 + dmin*ys);
			}
			break;
		};
		r = static_cast<SENetEndpoint*>(m_prev);
		s1 = ObjectManager::instance()->createNetSegment(m_layer, r, q);
		s2 = ObjectManager::instance()->createNetSegment(m_layer, q, p);
		n = ObjectManager::instance()->createNet(m_layer, s1);
		n->addSegment(s2);
	}

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
	m_lastx = x;
	m_lasty = y;
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
	m_lastx = x;
	m_lasty = y;
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
	if (e->key() == Qt::Key_Escape && m_state == 1) {
		endNet();
	} else if (e->key() == Qt::Key_Space && e->modifiers() & Qt::ShiftModifier) {
		toggleType();
	} else if (e->key() == Qt::Key_Space) {
		toggleFlip();
	}
	if (m_state == 1)
		drawNet(m_lastx, m_lasty, false);
}
