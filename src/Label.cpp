/* Autor: David Vucenovic Datum: 03.06.2023. */


#include "Label.h"

void Label::checkLabel()
{
	if (isalpha(m_name[0]))
		return;
	throw BadLabelName(m_name);
}

std::string Label::getName() const
{
	return m_name;
}