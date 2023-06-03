#include <iostream>
#include <exception>
#include <iomanip>


#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"
#include "Instruction.h"
#include "LivenessAnalysis.h"

using namespace std;


void printInstructions(Instructions &instructions) 
{
	for (Instruction* instruction : instructions)
	{
		cout << setfill('-') << setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << endl;
		cout << (*instruction) << endl;
		cout << setfill('-') << setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << endl;

	}
}

void printVariables(Variables &variables) 
{
	for (Variable* variable : variables) 
	{
		cout << variable->getName() << " ";
		if (variable->getType() == Variable::VariableType::MEM_VAR)
		{
			cout << variable->getValue();
		}
		cout << endl;
	}
}

int main()
{
	try
	{
		std::string fileName = ".\\..\\examples\\multiply.mavn";
		bool retVal = false;

		LexicalAnalysis lex;

		if (!lex.readInputFile(fileName))
			throw runtime_error("\nException! Failed to open input file!\n");

		lex.initialize();

		retVal = lex.Do();

		if (retVal)
		{
			cout << "Lexical analysis finished successfully!" << endl;
			//lex.printTokens();
		}
		else
		{
			lex.printLexError();
			throw runtime_error("\nException! Lexical analysis failed!\n");
		}

		cout << setfill('-') << setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << endl;
		cout << setfill(' ');
		cout << "Starting syntax analysis . . ." << endl;
		cout << setw(LEFT_ALIGN) << left << "Type:";
		cout << setw(RIGHT_ALIGN) << right << "Value:" << endl;
		cout << setfill('-') << setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << endl;
		cout << setfill(' ');

		Instructions instructions;
		Variables memoryVariables, registerVariables;
		SyntaxAnalysis syntaxAnalysis(lex, &instructions, &memoryVariables, &registerVariables);
		
		retVal = syntaxAnalysis.doSyntaxAnalysis();

		if (retVal)
		{
			cout << "Syntax analysis finished successfully!" << endl;
		}
		else
		{
			throw runtime_error("\nException! Syntax analysis failed!\n");
		}

		livenessAnalysis(&instructions);
		printInstructions(instructions);
		printVariables(memoryVariables);
		printVariables(registerVariables);


	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}
