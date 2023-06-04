#include "InterferenceGraph.h"

void InterferenceGraph::doInterferenceGraph()
{
	m_size = m_variables->size();

	m_values = new int* [m_size];

	for (int i = 0; i < m_size; i++)
	{
		m_values[i] = new int[m_size];
	}

	for (int i = 0; i < m_size; i++)
	{
		for (int j = 0; j < m_size; j++)
		{
			m_values[i][j] = __EMPTY__;
		}
	}


	std::list<Instruction*>::iterator i = m_instructions->begin();

	for (; i != m_instructions->end(); i++)
	{
		if ((*i)->getType() == I_NO_TYPE)
		{
			continue;
		}
		

		Variables def = (*i)->getDef();
		std::list<Variable*>::iterator j = def.begin();

		Variables out = (*i)->getOut();
		std::list<Variable*>::iterator k = out.begin();

		for (; j != def.end(); j++)
		{

			if ((*j)->getType() == Variable::NO_TYPE || (*j)->getType() == Variable::MEM_VAR)
			{
				continue;
			}

			for (; k != out.end(); k++)
			{
				if ((*k)->getType() == Variable::NO_TYPE || (*k)->getType() == Variable::MEM_VAR || (*j)->getPosition() == (*k)->getPosition())
				{
					continue;
				}

				m_values[(*j)->getPosition()][(*k)->getPosition()] = __INTERFERENCE__;
				m_values[(*k)->getPosition()][(*j)->getPosition()] = __INTERFERENCE__;
			}
		}

	}

}

void InterferenceGraph::printInterferenceGraph()
{
	std::list<Variable*>::iterator i = m_variables->begin();

	std::cout << "    ";

	for (; i != m_variables->end(); i++)
	{
		std::cout << (*i)->getName() << " ";
	}

	std::cout << std::endl;

	int j = 0;

	i = m_variables->begin();


	for (; i != m_variables->end(); i++)
	{
		std::cout << (*i)->getName() << " ";

		for (int k = 0; k < m_size; k++)
		{
			std::cout << " " << m_values[j][k] << " ";
		}

		std::cout << std::endl;
		j++;
	}

}

void InterferenceGraph::freeInterferenceGraph() 
{
	for (int i = 0; i < m_size; i++)
	{
		delete[] m_values[i];
	}

	delete[] m_values;
}

Instructions* InterferenceGraph::getInstructions() const 
{
	return m_instructions;
}

Variables* InterferenceGraph::getVariables() const
{
	return m_variables;
}

int** InterferenceGraph::getValues() const
{
	return m_values;
}

int InterferenceGraph::getSize() const
{
	return m_size;
}