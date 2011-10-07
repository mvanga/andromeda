#include "NetTool.h"

#include <iostream>

NetTool::NetTool(Schematic *p_sch, Schematic *p_buf)
	: SchematicTool(p_sch, p_buf)
{
}

void NetTool::selected(Layer *layer)
{
	m_layer = layer;
	m_state = 0;
}

void NetTool::unselected()
{
}

void NetTool::mousePressed(double x, double y, QMouseEvent *e)
{
	if (m_state == 0 && (e->buttons() & Qt::LeftButton)) {
		SENetEndpoint *p = new SENetEndpoint(m_layer, x, y);
		m_tmpsch.addElement(p);
		m_state = 1;
	} else if (m_state == 1) {
		if (e->buttons() & Qt::LeftButton) {
			SENetEndpoint *p = new SENetEndpoint(m_layer, x, y);
			SENetEndpoint *q = static_cast<SENetEndpoint*>(m_tmpsch.getElements().front());
			SENetSegment *s = new SENetSegment(m_layer, q, p);
			SENet *n = new SENet(m_layer, s);

			m_bufsch->addElement(n);
			m_tmpsch.clear();
			m_tmpsch.addElement(p);
			m_netsch.addElement(n);
		} else if (e->buttons() & Qt::RightButton) {
			m_tmpsch.clear();
			m_sch->merge(&m_netsch);
			m_bufsch->clear();
			m_tmpsch.clear();
			m_state = 0;
		}
	}
}

void NetTool::mouseReleased(double x, double y, QMouseEvent *e)
{
	e = 0;
	x = y = 0;
}

void NetTool::mouseMoved(double x, double y, QMouseEvent *e)
{
	if (m_state == 1) {
		SENetEndpoint *p = new SENetEndpoint(m_layer, x, y);
		SENetEndpoint *q = static_cast<SENetEndpoint*>(m_tmpsch.getElements().front());
		SENetSegment *s = new SENetSegment(m_layer, q, p);
		SENet *n = new SENet(m_layer, s);

		m_bufsch->clear();
		m_bufsch->addElement(n);
		m_bufsch->merge(&m_netsch);
	}
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
		m_tmpsch.clear();
		m_sch->merge(&m_netsch);
		m_bufsch->clear();
		m_tmpsch.clear();
		m_state = 0;

	}
}
