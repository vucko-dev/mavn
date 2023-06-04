#pragma once
#ifndef __SIMPLIFICATION__
#define __SIMPLIFICATION__

#include "InterferenceGraph.h"
#include "Variable.h"
#include <map>

Variable* findVariableByPosition(Variables* variables, int position);

//This function looks all nodes and if all nodes have equal or higher rank than numberOfRegisters, then returns false, otherwise true
bool isSimplificationPossible(std::map<Variable*, int> nodes, int numberOfRegisters);


//This function make new map that contains information about rank of every node in graph
std::map<Variable*, int> makeNewNodeMap(InterferenceGraph* ig, std::vector<std::vector<int>>& graph);


//This function returns itterator of map that points to a Variable that needs to be pushed next on Variable* stack
std::map<Variable*, int>::iterator findVariable(std::map<Variable*, int>& nodes);

//Checks is simplification over; Simplification is over when whole graph is filled by zeros
bool isSimplificationOver(std::vector<std::vector<int>>& graph, int size);

//Removes node from graph
void removeNode(std::vector<std::vector<int>>& graph, int size, int position);

//This function implements simplification (an important step for resource allocation)
//Returns pointer to stack<Variable*> or NULL if simplification is impossible
std::stack<Variable*>* doSimplification(InterferenceGraph* ig, int numberOfRegisters);


#endif