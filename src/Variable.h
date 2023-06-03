#pragma once
#ifndef __VARIABLE__
#define __VARIABLE__

#include "Types.h"

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
	Variable(std::string name, VariableType type, int value) : m_name(name), m_type(type), m_value(value) {}

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

	//Setters for some class atributes
	void setName(std::string name);
	void setPosition(int position);
	void setValue(int value);
	void setType(Variable::VariableType type);

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

#endif // !__VARIABLE__
