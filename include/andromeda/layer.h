#ifndef ANDROMEDA_LAYER_H
#define ANDROMEDA_LAYER_H

#include <string>
#include <iostream>

class Layer {
	int m_num;
	std::string m_name;

	/* Properties for nets */
	unsigned int m_netcolor;
	unsigned int m_netwidth;
public:
	Layer(int p_num, std::string p_name);
	int getNumber();
	std::string& getName();
	void setNetColor(unsigned int p_netcolor);
	void setNetWidth(unsigned int p_netwidth);

	unsigned int getNetColor();
	unsigned int getNetWidth();
};

#endif
