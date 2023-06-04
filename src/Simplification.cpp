#include "Simplification.h"


Variable* findVariableByPosition(Variables* variables, int position)
{
	std::list<Variable*>::iterator i = variables->begin();

	for (; i != variables->end(); i++)
	{
		int currentPosition = (*i)->getPosition();

		if (currentPosition == position)
		{
			return *i;
		}
	}

	return NULL;
}

std::map<Variable*, int> makeNewNodeMap(InterferenceGraph *ig)
{
	std::map<Variable*, int> nodes;

	int** graphValues = ig->getValues();
	int graphSize = ig->getSize();

	for (int i = 0; i < graphSize; i++)
	{
		int rankOfCurrentNode = 0;

		for (int j = 0; j < graphSize; j++)
		{
			if (graphValues[i][j] == __INTERFERENCE__)
			{
				rankOfCurrentNode++;
			}
		}

		Variable* currentVariable = findVariableByPosition(ig->getVariables(), i);

		if (currentVariable == NULL)
		{
			return {}; //It is error if somehow variable cannot be found by position
		}

		nodes[currentVariable] = rankOfCurrentNode;

	}
	return nodes;
}

std::map<Variable*, int>::iterator findVariable(std::map<Variable*, int>& nodes)
{

	std::map<Variable*, int>::iterator returnValue = nodes.begin();
	std::map<Variable*, int>::iterator i = nodes.begin();

	for (; i != nodes.end(); i++)
	{
		if (i->second >= returnValue->second)
		{
			returnValue = i;
		}
	}

	return returnValue;

}


bool isSimplificationOver(int** graph, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (graph[i][j] == __INTERFERENCE__)
			{
				return false;
			}
		}
	}

	return true;
}

bool isSimplificationPossible(std::map<Variable*, int> nodes, int numberOfRegisters)
{

	std::map<Variable*, int>::iterator i = nodes.begin();

	for (; i != nodes.end(); i++)
	{
		if (i->second < numberOfRegisters)
		{
			return true;
		}
	}

	return false;
}

void removeNode(int **graph, int size,int position)
{
	for (int i = 0; i < size; i++)
	{
		graph[i][position] = __EMPTY__;
		graph[position][i] = __EMPTY__;
	}
}


std::stack<Variable*>* doSimplification(InterferenceGraph* ig, int numberOfRegisters)
{
	std::stack<Variable*>* stack = new std::stack<Variable*>();
	
	int **graph = ig->getValues();
	int size = ig->getSize();

	std::vector<bool> pushedNodes(size, false);

	while (isSimplificationOver(graph, size) == false)
	{
		//This map represents node(Variable*) and node rank pair
		std::map<Variable*, int> nodes = makeNewNodeMap(ig);

		if (nodes.empty() == true)
		{
			return NULL;
		}

		if (isSimplificationPossible(nodes, numberOfRegisters) == false)
		{
			return NULL;
		}

		std::map<Variable*, int>::iterator variableToPush = findVariable(nodes);


		if (variableToPush->second >= numberOfRegisters)
		{
			return NULL;
		}

		stack->push(variableToPush->first);

		pushedNodes[variableToPush->first->getPosition()] = true;;

		removeNode(graph, size, variableToPush->first->getPosition());

	}

	if (stack->size() != size)
	{
		for (int i = 0; i < size; i++)
		{
			if (pushedNodes[i] == false)
			{
				Variable* variable = findVariableByPosition(ig->getVariables(), i);
				stack->push(variable);
			}
		}
	}


	return stack;
}

