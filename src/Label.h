/* Autor: David Vucenovic Datum: 03.06.2023. */


#pragma once
#ifndef __LABEL__
#define __LABEL__

#include <string>
#include <list>
#include "Exceptions.h"


//Purpose of this class is just to represent one function name or some label for jump

class Label
{
public:
	enum labelType 
	{
		ID,
		FUNCTION_ID
	};
	labelType m_type;
	std::string m_name;

	Label(std::string name, labelType type) :m_name(name), m_type(type) {};
	
	//Checks is label name correct (starts with alpha)
	//If name is not correct - exepction
	void checkLabel();

	std::string getName() const;
};

typedef std::list<Label*> Labels;


#endif // !__LABEL__
