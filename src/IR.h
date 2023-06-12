/* Autor: David Vucenovic Datum: 05.06.2023. */

#pragma once
#ifndef __IR__
#define __IR__

#include "Types.h"
#include "Exceptions.h"
#include "Label.h"

/**
* This class represents one variable from program code.
*/
class Variable
{
public:
	enum VariableType
	{
		MEM_VAR,
		REG_VAR,
		NO_TYPE //const value
	};

	Variable() : m_type(NO_TYPE), m_name(""), m_position(-1), m_assignment(no_assign) {}
	Variable(std::string name, int pos) : m_type(NO_TYPE), m_name(name), m_position(pos), m_assignment(no_assign) {}

	//Constructor for REG_VAR
	Variable(std::string name, VariableType type) : m_name(name), m_type(type), m_position(-1), m_assignment(no_assign) {}

	//Constructor for MEM_VAR
	Variable(std::string name, VariableType type, int value) : m_name(name), m_type(type), m_value(value), m_position(-1), m_assignment(no_assign) {}

private:
	VariableType m_type;
	std::string m_name;
	int m_position;
	int m_value;
	Regs m_assignment;

public:

	//Getters for each class atribute
	std::string getName() const;
	int getPosition() const;
	int getValue() const;
	VariableType getType() const;
	Regs getAssignment() const;

	//Setters for some class atributes
	void setName(std::string name);
	void setPosition(int position);
	void setValue(int value);
	void setType(Variable::VariableType type);
	void setAssignment(Regs assignment);

	//Checks is variable name correct;
	//For example: MEM_VAR should start with m
	//			   REG_VAR should start with r
	//If name is okay, just return, else exepction
	void isVariableCorrect();
};


/**
* This type represents list of variables from program code.
*/
typedef std::list<Variable*> Variables;



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


#endif // !__IR__
