#pragma once

#ifndef __INSTRUCTION__
#define __INSTRUCTION__

#include "Variable.h"
#include "Types.h"
#include "Label.h"

/**
* This class represents one instruction in program code.
*/
class Instruction
{
private:
	int m_position;
	InstructionType m_type;

	//This attribute is for instructions only with a label, like a _func or just a label
	Label* m_label;

	Variables m_dst;
	Variables m_src;

	Variables m_use;
	Variables m_def;
	Variables m_in;
	Variables m_out;
	std::list<Instruction*> m_succ;
	std::list<Instruction*> m_pred;

public:

	Instruction() : m_position(0), m_type(I_NO_TYPE) {}
	Instruction(int pos, InstructionType type, Variables& dst, Variables& src) :
		m_position(pos), m_type(type), m_dst(dst), m_src(src) {}
	Instruction(InstructionType type, int position) :m_type(type), m_position(position) {}

	//If instruction has a I_NO_TYPE, than this method is gonna be used to add label
	void addLabel(Label* label);

	//Adding source variables
	void addSrc(Variables variables);

	//Adding destination 
	void addDest(Variables variables);

	//Getters
	int getPosition() const;
	InstructionType getType() const;
	Label* getLabel() const;
	Variables getDst() const;
	Variables getSrc() const;
	Variables getUse() const;
	Variables getDef() const;
	Variables getIn() const;
	Variables getOut() const;
	std::list<Instruction*> getSucc() const;
	std::list<Instruction*> getPred() const;

	//Next six functions add items in each of class list
	void addSucc(Instruction* instruction);
	void addPred(Instruction* instruction);
	void addIn(Variable* variable);
	void addOut(Variable* variable);
	void addDef(Variable* variable);
	void addUse(Variable* variable);


	//Setters
	void setSucc(std::list<Instruction*> instructions);
	void setPred(std::list<Instruction*> instructions);
	void setIn(std::list<Variable*> variables);
	void setOut(std::list<Variable*> variables);

	//For output instruction information
	friend std::ostream& operator<<(std::ostream& os, const Instruction& i);

};


/**
* This type represents list of instructions from program code.
*/
typedef std::list<Instruction*> Instructions;
#endif // !__INSTRUCTION__
