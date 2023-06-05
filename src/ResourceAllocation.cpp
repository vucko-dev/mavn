#include "ResourceAllocation.h"

bool doResourceAllocation(std::stack<Variable*>* simplificationStack, InterferenceGraph* ig)
{
	std::list<Regs> regs;
	std::list<Variable*> colored;
	int** values = ig->getValues();


	for (int i = 0; i < __REG_NUMBER__; i++) regs.push_back((Regs)i);

	while (!simplificationStack->empty()) 
	{

		Variable* temp = simplificationStack->top();

		bool interference = false;

		for (auto it = colored.begin(); it != colored.end(); it++)
		{
		
			if (values[temp->getPosition()][(*it)->getPosition()] == __INTERFERENCE__)
			{
				interference = true;
			}
		}

		if (interference == false) 
		{
			temp->setAssignment(regs.front());
		}
		else {
			if (regs.empty() == false) 
			{
				regs.pop_front();
				temp->setAssignment(regs.front());
			}
			else
			{
				return false;
			}
		}

		colored.push_back(temp);
		simplificationStack->pop();
	}

	return true;
}