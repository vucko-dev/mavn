#pragma once
#ifndef __INTERFERENCE_GRAPH__
#define __INTERFERENCE_GRAPH__

#include "Types.h"
#include "Variable.h"
#include "Instruction.h"


class InterferenceGraph {

private:
	Instructions* m_instructions;
	Variables* m_variables;	///< all variables from instructions
	int** m_values;			///< matrix value
	int m_size;				///< size of square matrix

public:

	InterferenceGraph(Instructions* instructions, Variables* variables) :m_variables(variables), m_instructions(instructions) {}


	//This method creates pointer to interference graph using instruction list
	void doInterferenceGraph();

	//This method frees all interference graph resources provided as a parameter 
	void freeInterferenceGraph();

	//This method prints interference graph
	void printInterferenceGraph();

	//Getters
	Instructions* getInstructions() const;
	Variables* getVariables() const;
	int** getValues() const;
	int getSize() const;

};

#endif
