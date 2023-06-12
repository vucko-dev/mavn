/* Autor: David Vucenovic Datum: 04.06.2023. */

#include "IR.h"

std::string Variable::getName() const
{
	return m_name;
}

int Variable::getPosition() const
{
	return m_position;
}

int Variable::getValue() const
{
	return m_value;
}

Variable::VariableType Variable::getType() const
{
	return m_type;
}

Regs Variable::getAssignment() const
{
	return m_assignment;
}

void Variable::setName(std::string name)
{
	m_name = name;
}

void Variable::setPosition(int position)
{
	m_position = position;
}

void Variable::setValue(int value)
{
	m_value = value;
}

void Variable::setType(Variable::VariableType type)
{
	m_type = type;
}

void Variable::setAssignment(Regs assignment)
{
	m_assignment = assignment;
}

void Variable::isVariableCorrect()
{
	if (m_type == Variable::VariableType::MEM_VAR && m_name[0] == 'm')
		return;
	else if (m_type == Variable::VariableType::REG_VAR && m_name[0] == 'r')
		return;
	else if (m_type == Variable::VariableType::NO_TYPE)
		return;

	throw BadVariableName(m_name);
}



void Instruction::addLabel(Label* label)
{
	m_label = label;
}

void Instruction::addDest(Variables destVars)
{
	m_dst = destVars;
}

void Instruction::addSrc(Variables srcVars)
{
	m_src = srcVars;
}

int Instruction::getPosition() const
{
	return m_position;
}

InstructionType Instruction::getType() const
{
	return m_type;
}

Label* Instruction::getLabel() const
{
	return m_label;
}

Variables Instruction::getDst() const
{
	return m_dst;
}

Variables Instruction::getSrc() const
{
	return m_src;
}

Variables Instruction::getUse() const
{
	return m_use;
}

Variables Instruction::getDef() const
{
	return m_def;
}

Variables Instruction::getIn() const
{
	return m_in;
}

Variables Instruction::getOut() const
{
	return m_out;
}

std::list<Instruction*> Instruction::getSucc() const
{
	return m_succ;
}

std::list<Instruction*> Instruction::getPred() const
{
	return m_pred;
}

void Instruction::addSucc(Instruction* instruction)
{
	m_succ.push_back(instruction);
}

void Instruction::addPred(Instruction* instruction)
{
	m_pred.push_back(instruction);
}

void Instruction::addIn(Variable* variable)
{
	m_in.push_back(variable);
}

void Instruction::addOut(Variable* variable)
{
	m_out.push_back(variable);
}

void Instruction::addDef(Variable* variable)
{
	m_def.push_back(variable);
}

void Instruction::addUse(Variable* variable)
{
	m_use.push_back(variable);
}

void Instruction::setSucc(std::list<Instruction*> instructions)
{
	m_succ = instructions;
}

void Instruction::setPred(std::list<Instruction*> instructions)
{
	m_pred = instructions;
}

void Instruction::setIn(std::list<Variable*> variables)
{
	m_in = variables;
}

void Instruction::setOut(std::list<Variable*> variables)
{
	m_out = variables;
}

std::ostream& operator<<(std::ostream& os, const Instruction& i)
{
	os << "TYPE: ";
	switch (i.getType())
	{
	case I_NO_TYPE:
		os << "\t\tno_type";
		break;
	case I_ADD:
		os << "\t\tadd";
		break;
	case I_ADDI:
		os << "\t\taddi";
		break;
	case I_SUB:
		os << "\t\tsub";
		break;
	case I_LA:
		os << "\t\tla";
		break;
	case I_LI:
		os << "\t\tli";
		break;
	case I_LW:
		os << "\t\tlw";
		break;
	case I_SW:
		os << "\t\tsw";
		break;
	case I_BLTZ:
		os << "\t\tbltz";
		break;
	case I_B:
		os << "\t\tb";
		break;
	case I_NOP:
		os << "\t\tnop";
		break;
	case I_SGE:
		os << "\t\tsge";
		break;
	case I_OR:
		os << "\t\tor";
		break;
	case I_BNE:
		os << "\t\tbne";
		break;
	default:
		os << "\t\tno_type";
		break;
	}
	os << std::endl;
	os << "POSITION:\t" << i.getPosition() << std::endl;
	os << "PRED:\t\t";

	for (Instruction* instruction : i.getPred())
	{
		os << instruction->getPosition() << " ";
	}

	os << std::endl;
	os << "SUCC:\t\t";

	for (Instruction* instruction : i.getSucc())
	{
		os << instruction->getPosition() << " ";
	}

	os << std::endl;

	os << "USE:\t\t";
	for (Variable* variable : i.getUse())
	{
		os << variable->getName() << " ";
	}
	os << std::endl;

	os << "DEF:\t\t";
	for (Variable* variable : i.getDef())
	{
		os << variable->getName() << " ";
	}
	os << std::endl;

	os << "IN:\t\t";
	for (Variable* variable : i.getIn())
	{
		os << variable->getName() << " ";
	}
	os << std::endl;

	os << "OUT:\t\t";
	for (Variable* variable : i.getOut())
	{
		os << variable->getName() << " ";
	}
	os << std::endl;

	return os;
}