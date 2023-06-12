/* Autor: David Vucenovic Datum: 08.06.2023. */
#include <iostream>
#include <exception>
#include <iomanip>
#include <fstream>
#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"
#include "IR.h"
#include "LivenessAnalysis.h"
#include "InterferenceGraph.h"
#include "Simplification.h"
#include "ResourceAllocation.h"
#include "Writter.h"
#include "Exceptions.h"


int main()
{
	try
	{
		std::string fileName = ".\\..\\examples\\simple.mavn";
		bool retVal = false;


		LexicalAnalysis lex;

		if (!lex.readInputFile(fileName))
			throw InputError();

		lex.initialize();

		retVal = lex.Do();

		lex.getTokenList();

		if (retVal)
		{
			std::cout << "Lexical analysis finished successfully!" << std::endl;
			lex.printTokens();
		}
		else
		{
			lex.printLexError();
			throw LexError();
		}

		printHorizontalLine();

		std::cout << "Starting syntax analysis . . ." << std::endl;

		Instructions instructions;
		Variables memoryVariables, registerVariables;
		SyntaxAnalysis syntaxAnalysis(lex, &instructions, &memoryVariables, &registerVariables);
		
		retVal = syntaxAnalysis.doSyntaxAnalysis();

		if (retVal)
		{
			std::cout << "Syntax analysis finished successfully!" << std::endl;
		}
		else
		{
			throw SyntaxError();
		}

		printHorizontalLine();

		std::cout << "Instructions: " << std::endl;

		livenessAnalysis(&instructions);

		printInstructions(instructions);

		InterferenceGraph interferenceGraph(&instructions, &registerVariables);

		interferenceGraph.doInterferenceGraph();
		std::stack<Variable*>* stack = doSimplification(&interferenceGraph, __REG_NUMBER__);
		if (stack == NULL) 
		{
			interferenceGraph.freeInterferenceGraph();
			throw Spill();
		}

		if (doResourceAllocation(stack, &interferenceGraph) == true)
		{
			std::cout << "Resource allocaton finished successfully!" << std::endl;
			std::cout << std::setfill('-') << std::setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << std::endl;

			std::cout << "Memory Variables: " << std::endl;
			printVariables(memoryVariables);
			std::cout << std::setfill('-') << std::setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << std::endl;

			std::cout << "Register Variables: " << std::endl;
			printVariables(registerVariables);
			std::cout << std::setfill('-') << std::setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << std::endl;

			std::cout << "Interference Graph" << std::endl;
			printInterferenceGraph(interferenceGraph);

			std::cout << std::setfill('-') << std::setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << std::endl;


			int index = fileName.find(".mavn");

			fileName = fileName.substr(0, index);
			fileName = fileName + ".s";


			printInFile(fileName, instructions, memoryVariables);

			std::cout << "All done! Check " << fileName  << std::endl;

		}
		else
		{
			interferenceGraph.freeInterferenceGraph();
			throw ResourceAllocationError();
		}

		interferenceGraph.freeInterferenceGraph();

	}
	catch (std::runtime_error e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
