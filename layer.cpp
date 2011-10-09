#include <andromeda/layer.h>

Layer::Layer(int p_num, std::string p_name) : m_num(p_num), m_name(p_name)
{
}

int Layer::getNumber()
{
	return m_num;
}

std::string& Layer::getName()
{
	return m_name;
}

void Layer::setNetColor(unsigned int p_netcolor)
{
	m_netcolor = p_netcolor;
}

void Layer::setNetWidth(unsigned int p_netwidth)
{
	m_netwidth = p_netwidth;
}

unsigned int Layer::getNetColor()
{
	return m_netcolor;
}

unsigned int Layer::getNetWidth()
{
	return m_netwidth;
}
