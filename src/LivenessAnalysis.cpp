/* Autor: David Vucenovic Datum: 04.06.2023. */

#pragma once
#include "LivenessAnalysis.h"

void fillSucc(Instructions* instructions)
{
	std::list<Instruction*>::iterator i = instructions->begin();
	std::list<Instruction*>::iterator last = instructions->end();
	last--;

	for (; i != last; i++)
	{
		if ((*i)->getType() == I_B)
		{
			Label* label = (*i)->getLabel();
			Instruction* instruction = getLabelInstruction(instructions,label);
			if (instruction == NULL)
			{
				throw ErrorWithFindingLabel(label->getName());
			}
			(*i)->addSucc(instruction);
		}
		else if ((*i)->getType() == I_BLTZ || (*i)->getType() == I_BNE)
		{

			Label* label = (*i)->getLabel();
			Instruction* instruction = getLabelInstruction(instructions, label);
			if (instruction == NULL)
			{
				throw ErrorWithFindingLabel(label->getName());
			}
			(*i)->addSucc(instruction);
			(*i)->addSucc(*(std::next(i)));
		}
		else
		{
			(*i)->addSucc(*(std::next(i)));
		}
	}

	if ((*last)->getType() == I_B)
	{
		Label* label = (*last)->getLabel();
		Instruction* instruction = getLabelInstruction(instructions, label);
		if (instruction == NULL)
		{
			throw ErrorWithFindingLabel(label->getName());
		}
		(*last)->addSucc(instruction);
	}
	else if ((*last)->getType() == I_BLTZ || (*last)->getType() == I_BNE)
	{
		Label* label = (*last)->getLabel();
		Instruction* instruction = getLabelInstruction(instructions, label);
		if (instruction == NULL)
		{
			throw ErrorWithFindingLabel(label->getName());
		}
		(*last)->addSucc(instruction);
	}
}

void fillPred(Instructions* instructions)
{
	std::list<Instruction*>::iterator i = instructions->begin();

	for (; i != instructions->end(); i++)
	{
		Instructions succ = (*i)->getSucc();
		
		std::list<Instruction*>::iterator j = succ.begin();

		for (; j != succ.end(); j++)
		{
			(*j)->addPred(*i);
		}

	}
}

void fillUse(Instructions *instructions)
{
	std::list<Instruction*>::iterator i = instructions->begin();

	for (; i != instructions->end(); i++)
	{
		Variables src = (*i)->getSrc();
		std::list<Variable*>::iterator j = src.begin();

		for (; j != src.end(); j++)
		{

			if ((*j)->getType() != Variable::NO_TYPE)
			{
				(*i)->addUse(*j);
			}
		}

	}
}

void fillDef(Instructions *instructions)
{
	std::list<Instruction*>::iterator i = instructions->begin();

	for (; i != instructions->end(); i++)
	{
		Variables dst = (*i)->getDst();
		std::list<Variable*>::iterator j = dst.begin();

		for (; j != dst.end(); j++)
		{

			if ((*j)->getType() != Variable::NO_TYPE)
			{
				(*i)->addDef(*j);
			}
		}

	}
}

Instruction* getLabelInstruction(Instructions* instructions, Label* label)
{
	std::list<Instruction*>::iterator i = instructions->begin();

	for (; i != instructions->end(); i++)
	{
		if ((*i)->getType() == I_NO_TYPE)
		{
			if ((*i)->getLabel()->m_type == Label::ID)
			{

				if (label->getName() == (*i)->getLabel()->getName())
					return *i;
			}
		}
	}

	return NULL;
}

bool variableExists(Variables& variables, Variable* variable)
{
	std::list<Variable*>::iterator i = variables.begin();

	for (; i != variables.end(); i++)
	{
		if ((*i)->getName() == variable->getName())
		{
			return true;
		}
	}
	return false;
}


void livenessAnalysis(Instructions* instructions)
{
	fillSucc(instructions);
	fillPred(instructions);
	fillUse(instructions);
	fillDef(instructions);

	for (std::list<Instruction*>::iterator i = instructions->begin(); i != instructions->end(); i++)
	{
		(*i)->setIn({});
		(*i)->setOut({});
	}

	bool livenessEnd = false;

	while (!livenessEnd)
	{
		Instructions instructionsCopy;

		for (std::list<Instruction*>::reverse_iterator i = instructions->rbegin(); i != instructions->rend(); i++)
		{
			instructionsCopy.push_back(*i);
			(*i)->setIn({});
			(*i)->setOut({});

			Instructions succ = (*i)->getSucc();
			for (std::list<Instruction*>::iterator j = succ.begin(); j != succ.end(); j++)
			{
				Variables in = (*j)->getIn();
				for (std::list<Variable*>::iterator k = in.begin(); k != in.end(); k++)
				{
					(*i)->addOut(*k);
				}
			}

			Variables use = (*i)->getUse();
			for (std::list<Variable*>::iterator j = use.begin(); j != use.end(); j++)
			{
				(*i)->addIn(*j);
			}

			Variables out = (*i)->getOut();
			for (std::list<Variable*>::iterator j = out.begin(); j != out.end(); j++)
			{
				if (!variableExists((*i)->getDef(),*j) && variableExists((*i)->getOut(),*j))
				{
					(*i)->addIn(*j);
				}
			}

			std::list<Variable*> tempList = (*i)->getIn();
			tempList.sort();
			tempList.unique();

			(*i)->setIn(tempList);

			tempList = (*i)->getOut();
			tempList.sort();
			tempList.unique();

			(*i)->setOut(tempList);

		}

		//Can LivenessAnalysis be stoped?

		bool forEndedWithForce = false;
		std::list<Instruction*>::iterator i1 = instructions->begin();
		std::list<Instruction*>::reverse_iterator i2 = instructionsCopy.rbegin();
		for (; i1 != instructions->end(); i1++, i2++) 
		{
			if ((*i1)->getIn() != (*i2)->getIn() || (*i1)->getOut() != (*i2)->getOut())
			{
				forEndedWithForce = true;
				break;
			}
		}

		if (forEndedWithForce == false)
		{
			livenessEnd = true;
		}
		
	}
}
