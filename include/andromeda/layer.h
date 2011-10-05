#ifndef ANDROMEDA_LAYER_H
#define ANDROMEDA_LAYER_H

#include <string>

class Layer {
	int m_num;
	std::string m_name;
public:
	Layer(int p_num, std::string p_name) : m_num(p_num), m_name(p_name) {}
	int getNumber() { return m_num; }
	std::string& getName() { return m_name; }
};

#endif
