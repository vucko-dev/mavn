#include "Label.h"

void Label::checkLabel()
{
	if (isalpha(m_name[0]))
		return;
	throw std::runtime_error("Label " + m_name + "not named correctly!");
}

std::string Label::getName() const
{
	return m_name;
}