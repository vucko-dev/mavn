#include "Variable.h"

std::string Variable::getName() const
{
	return m_name;
}

int Variable::getPosition() const
{
	return m_position;
}

int Variable::getValue() const
{
	return m_value;
}

Variable::VariableType Variable::getType() const
{
	return m_type;
}

void Variable::setName(std::string name)
{
	m_name = name;
}

void Variable::setPosition(int position)
{
	m_position = position;
}

void Variable::setValue(int value)
{
	m_value = value;
}

void Variable::setType(Variable::VariableType type)
{
	m_type = type;
}

void Variable::isVariableCorrect()
{
	if (m_type == Variable::VariableType::MEM_VAR && m_name[0] == 'm')
		return;
	else if (m_type == Variable::VariableType::REG_VAR && m_name[0] == 'r')
		return;
	else if (m_type == Variable::VariableType::NO_TYPE)
		return;

	throw std::runtime_error("Variable " + m_name + "not named correctly!");
}