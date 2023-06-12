/* Autor: David Vucenovic Datum: 08.06.2023. */

#pragma once

#ifndef __EXCEPTIONS__
#define __EXCEPTIONS__

#include <iostream>


class LexError : public std::runtime_error
{
public:
	LexError() : runtime_error("\nException! Lexical analysis failed!\n") {};
};


class InputError : public std::runtime_error
{
public:
	InputError() : runtime_error("Error while oppening input file!") {}
};

class SyntaxError : public std::runtime_error
{
public:
	SyntaxError() : runtime_error("\nException! Syntax analysis failed!\n"){}
};

class Spill : public std::runtime_error
{
public:
	Spill() : runtime_error("Error (Spill): Current number of registers is not enough for ResourceAnalysis ") {}
};


class ResourceAllocationError : public std::runtime_error
{
public:
	ResourceAllocationError() : runtime_error("Error during resource allocation!\n") {}
};


class VariableExistsError : public std::runtime_error
{
public:
	VariableExistsError(std::string varName) : runtime_error("Variable " + varName + "not exist\n") {}
};


class LabelExistsError : public std::runtime_error
{
public:
	LabelExistsError(std::string varName) : runtime_error("Variable " + varName + "already exist\n") {}
};

class VariableNotDefinedError: public std::runtime_error
{
public:
	VariableNotDefinedError(std::string varName) : runtime_error("Variable " + varName + "not defined\n") {}
};

class LabelNotDefinedError : public std::runtime_error
{
public:
	LabelNotDefinedError(std::string labelName) : runtime_error("Label " + labelName + "not defined\n") {}
};

class EndInputReached : public std::runtime_error
{
public:
	EndInputReached() : runtime_error("End of input file reached!\n") {}
};

class BadLabelName : public std::runtime_error
{
public:
	BadLabelName(std::string labelName) : runtime_error("Label " + labelName + "not named correctly!\n") {}
};

class ErrorWithFindingLabel : public std::runtime_error
{
public:
	ErrorWithFindingLabel(std::string labelName) : runtime_error("Error with finding label.\n" + labelName) {}
};

class BadVariableName : public std::runtime_error
{
public:
	BadVariableName(std::string varName) : runtime_error("Variable " + varName + "not named correctly.\n") {}
};


#endif