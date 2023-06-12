/* Autor: David Vucenovic Datum: 07.06.2023. */

#include "Writter.h"

void printInFile(std::string fileName, Instructions& instructions, Variables& variables)
{
	std::ofstream output(fileName);

	if (output.is_open() == false)
	{
		throw InputError();
	}

	output << ".globl ";

	for (std::list<Instruction*>::iterator i = instructions.begin(); i != instructions.end(); i++)
	{
		if ((*i)->getType() == I_NO_TYPE)
		{
			Label* label = (*i)->getLabel();
			if (label->m_type == Label::FUNCTION_ID)
			{
				output << label->m_name << std::endl;
				break;
			}
		}
	}

	output << std::endl;

	output << ".data" << std::endl;


	for (std::list<Variable*>::iterator i = variables.begin(); i!=variables.end(); i++)
	{
		output << (*i)->getName() << ":\t.word " << (*i)->getValue() << std::endl;
	}


	output << std::endl;

	output << ".text" << std::endl;

	bool mainFunctionPrinted = false;

	for (std::list<Instruction*>::iterator i = instructions.begin(); i!= instructions.end(); i++)
	{
		if ((*i)->getType() == I_NO_TYPE)
		{
			Label* label = (*i)->getLabel();
			if (label->m_type == Label::FUNCTION_ID)
			{
				output << label->m_name << ":" << std::endl;
				mainFunctionPrinted = true;
			}
		}
		Label* label = (*i)->getLabel();
		InstructionType type = (*i)->getType();


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
			case I_SGE:
				output << "\tsge";
				break;
			case I_OR:
				output << "\tor";
				break;
			case I_BNE:
				output << "\tbne";
				break;
			default:
				output << "\tno_type";
				break;
			}


			output << "\t\t";


			if ((*i)->getDst().empty() == false)
			{
				Variable* destination = *((*i)->getDst().begin());

				if (destination->getType() == Variable::REG_VAR)
				{
					output << "$t" << destination->getAssignment() << ", ";
				}

				if ((*i)->getDst().size() > 1)
				{
					destination = *(next((*i)->getDst().begin()));
					output << "$t" << destination->getAssignment() << ", ";
				}

			}

			Variables sources = (*i)->getSrc();

			for (Variables::iterator j = sources.begin(); j != sources.end(); j++)
			{

				if ((*j)->getType() == Variable::NO_TYPE)
				{

					if (j == prev(sources.end()))
					{
						output << (*j)->getValue();
					}

					else
					{
						output << (*j)->getValue() << "(";
						j++;
						if ((*j)->getType() == Variable::REG_VAR)
						{
							output << "$t" << (*j)->getAssignment();
						}
						else
						{
							output << (*j)->getName();
						}

						output << ")";
					}
				}
				else
				{
					if ((*j)->getType() == Variable::REG_VAR)
					{
						output << "$t" << (*j)->getAssignment();
					}
					else
					{
						output << (*j)->getName();
					}

					if (j != prev(sources.end()))
					{
						output << ", ";
					}
				}

			}



		}

		if (type == InstructionType::I_B || type == InstructionType::I_BLTZ || type == InstructionType::I_BNE)
		{
			if (type != InstructionType::I_B && type != InstructionType::I_BNE)
			{
				output << ", ";
			}
			output << (*i)->getLabel()->getName();
		}
		output << std::endl;



	}

	output.close();

}

void printInstructions(Instructions &instructions)
{
	for (std::list<Instruction*>::iterator i = instructions.begin(); i != instructions.end(); i++)
	{
		std::cout << std::setfill('-') << std::setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << std::endl;
		std::cout << (**i) << std::endl;
		std::cout << std::setfill('-') << std::setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << std::endl;

	}
}

void printVariables(Variables &variables)
{

	std::cout << "NAME\t\tVALUE\t\tASSIGNMENT\n";

	for (std::list<Variable*>::iterator i = variables.begin();i != variables.end(); i++)
	{
		std::cout << (*i)->getName() << "\t\t";
		if ((*i)->getType() == Variable::VariableType::MEM_VAR)
		{
			std::cout << (*i)->getValue();
			std::cout << "\t\t-";
		}

		if ((*i)->getType() == Variable::VariableType::REG_VAR)
		{
			std:: cout << "-\t\t";
			std::cout << (*i)->getAssignment();
		}

		std::cout << std::endl;
	}
}


void printHorizontalLine() {
	std::cout << std::setfill(' ') << std::endl;
	std::cout << std::setfill('-') << std::setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << std::endl;
	std::cout << std::setfill(' ') << std::endl;
}


void printInterferenceGraph(InterferenceGraph& interferenceGraph)
{

	Variables interferenceGraphVariables = *interferenceGraph.getVariables();

	int size = interferenceGraph.getSize();
	int **values = interferenceGraph.getValues();

	std::cout << "    ";

	for (std::list<Variable*>::iterator i = interferenceGraphVariables.begin();i != interferenceGraphVariables.end(); i++)
	{
		std::cout << (*i)->getName() << " ";
	}

	std::cout << std::endl;

	int row = 0;

	for (std::list<Variable*>::iterator i = interferenceGraphVariables.begin(); i != interferenceGraphVariables.end(); i++)
	{
		std::cout << (*i)->getName() << " ";

		for (int column = 0; column < size; column++)
		{
			std::cout << " " << values[row][column] << " ";
		}

		std::cout << std::endl;
		row++;
	}

}
