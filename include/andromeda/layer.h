#ifndef ANDROMEDA_LAYER_H
#define ANDROMEDA_LAYER_H

#include <string>

class Layer {
	int m_num;
	std::string m_name;

	/* Properties for nets */
	unsigned int m_netcolor;
	unsigned int m_netwidth;
public:
	Layer(int p_num, std::string p_name) : m_num(p_num), m_name(p_name) {}
	int getNumber() { return m_num; }
	std::string& getName() { return m_name; }
	void setNetColor(unsigned int p_netcolor) { m_netcolor = p_netcolor; }
	void setNetWidth(unsigned int p_netwidth) { m_netwidth = p_netwidth; }

	unsigned int getNetColor() { return m_netcolor; }
	unsigned int getNetWidth() { return m_netwidth; }
};

#endif
