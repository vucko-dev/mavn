#include <iostream>
#include <exception>
#include <iomanip>
#include <fstream>


#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"
#include "Instruction.h"
#include "LivenessAnalysis.h"
#include "InterferenceGraph.h"
#include "Simplification.h"
#include "ResourceAllocation.h"

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

	cout << "NAME\t\tVALUE\t\tASSIGNMENT\n";

	for (Variable* variable : variables) 
	{
		cout << variable->getName() << "\t\t";
		if (variable->getType() == Variable::VariableType::MEM_VAR)
		{
			cout << variable->getValue();
			cout << "\t\t-";
		}

		if (variable->getType() == Variable::VariableType::REG_VAR)
		{
			cout << "-\t\t";
			cout << variable->getAssignment();
		}

		cout << endl;
	}
}


bool printInFile(string fileName, Instructions& instructions, Variables& variables)
{
	ofstream output(fileName);

	if (output.is_open() == false)
	{
		return false;
	}

	output << ".globl ";

	for (auto x : instructions)
	{
		if (x->getType() == I_NO_TYPE)
		{
			Label* label = x->getLabel();
			if (label->m_type == Label::FUNCTION_ID)
			{
				output << label->m_name<<endl;
				break;
			}
		}
	}

	output << endl;

	output << ".data" << endl;
	for (auto x : variables)
	{
		output << x->getName() << ":\t.word " << x->getValue() << endl;
	}


	output << endl;

	output << ".text" << endl;

	bool mainFunctionPrinted = false;

	for (auto x : instructions)
	{
		if (x->getType() == I_NO_TYPE)
		{
			Label* label = x->getLabel();
			if (label->m_type == Label::FUNCTION_ID)
			{
				output << label->m_name << ":" << endl;
				mainFunctionPrinted = true;
			}
		}
		Label* label = x->getLabel();
		InstructionType type = x->getType();


		if (mainFunctionPrinted == true)
		{


			switch (type)
			{
			case I_NO_TYPE:
				if (label->m_type == Label::ID)
				{
					output << label->m_name << ":";
				}
				break;
			case I_ADD:
				output << "\tadd";
				break;
			case I_ADDI:
				output << "\taddi";
				break;
			case I_SUB:
				output << "\tsub";
				break;
			case I_LA:
				output << "\tla";
				break;
			case I_LI:
				output << "\tli";
				break;
			case I_LW:
				output << "\tlw";
				break;
			case I_SW:
				output << "\tsw";
				break;
			case I_BLTZ:
				output << "\tbltz";
				break;
			case I_B:
				output << "\tb";
				break;
			case I_NOP:
				output << "\tnop";
				break;
			case I_SEQ:
				output << "\tseq";
				break;
			case I_REM:
				output << "\trem";
				break;
			case I_BEQ:
				output << "\tbeq";
				break;
			default:
				output << "\tno_type";
				break;
			}


			output << "\t\t";


			if (x->getDst().empty() == false)
			{
				Variable* destination = *(x->getDst().begin());

				if (destination->getType() == Variable::REG_VAR)
				{
					output << "$t" << destination->getAssignment() << ", ";
				}

				if (x->getDst().size() > 1)
				{
					destination = *(next(x->getDst().begin()));
					output << "$t" << destination->getAssignment() << ", ";
				}

			}
			
			Variables sources = x->getSrc();

			Variables::iterator i = sources.begin();

			for (; i != sources.end(); i++)
			{

				if ((*i)->getType() == Variable::NO_TYPE)
				{

					if (i == prev(sources.end()))
					{
						output << (*i)->getValue();
					}

					else
					{
						output << (*i)->getValue() << "(";
						i++;
						if ((*i)->getType() == Variable::REG_VAR)
						{
							output << "$t" << (*i)->getAssignment();
						}
						else
						{
							output << (*i)->getName();
						}

						output << ")";
					}
				}
				else
				{
					if ((*i)->getType() == Variable::REG_VAR)
					{
						output << "$t" << (*i)->getAssignment();
					}
					else
					{
						output << (*i)->getName();
					}

					if (i != prev(sources.end()))
					{
						output << ", ";
					}
				}

			}

			

		}

		if (type == InstructionType::I_B || type == InstructionType::I_BLTZ || type == InstructionType::I_BEQ)
		{
			if (type != InstructionType::I_B && type!= InstructionType::I_BEQ)
			{
				output << ", ";
			}
			output << x->getLabel()->getName();
		}
		output << endl;



	}

	output.close();
	return true;
}

int main()
{
	try
	{
		std::string fileName = ".\\..\\examples\\simple.mavn";
		bool retVal = false;

		LexicalAnalysis lex;

		if (!lex.readInputFile(fileName))
			throw runtime_error("\nException! Failed to open input file!\n");

		lex.initialize();

		retVal = lex.Do();

		if (retVal)
		{
			cout << "Lexical analysis finished successfully!" << endl;
			lex.printTokens();
		}
		else
		{
			lex.printLexError();
			throw runtime_error("\nException! Lexical analysis failed!\n");
		}

		cout << setfill('-') << setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << endl;
		cout << setfill(' ');
		cout << "Starting syntax analysis . . ." << endl;
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

		cout << setfill('-') << setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << endl;
		cout << "Instructions: " << endl;

		livenessAnalysis(&instructions);
		printInstructions(instructions);

		InterferenceGraph interferenceGraph(&instructions, &registerVariables);

		interferenceGraph.doInterferenceGraph();
		stack<Variable*>* stack = doSimplification(&interferenceGraph, __REG_NUMBER__);
		if (stack == NULL) 
		{
			cout << "Error (Spill): It is not posible to do Simplification with just " << __REG_NUMBER__ << " registers" << endl;
			interferenceGraph.freeInterferenceGraph();
			return 1;
		}



		if (doResourceAllocation(stack, &interferenceGraph) == true)
		{
			cout << "Resource allocaton finished successfully!" << endl;
			cout << setfill('-') << setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << endl;

			cout << "Memory Variables: " << endl;
			printVariables(memoryVariables);
			cout << setfill('-') << setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << endl;

			cout << "Register Variables: " << endl;
			printVariables(registerVariables);
			cout << setfill('-') << setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << endl;

			cout << "Interference Graph" << endl;
			interferenceGraph.printInterferenceGraph();

			cout << setfill('-') << setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << endl;


			int index = fileName.find(".mavn");

			fileName = fileName.substr(0, index);
			fileName = fileName + ".s";


			printInFile(fileName, instructions, memoryVariables);

		}
		else
		{
			cout << "Error during resource allocation!" << endl;
			interferenceGraph.freeInterferenceGraph();
			return 1;
		}



		interferenceGraph.freeInterferenceGraph();


	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}
