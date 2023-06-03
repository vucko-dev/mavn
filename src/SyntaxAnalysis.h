#pragma once

#include "LexicalAnalysis.h"
#include "Token.h"
#include "Variable.h"
#include "Instruction.h"
#include "Label.h"


class SyntaxAnalysis 
{

private:


	// Reference to lexical analysis module
	LexicalAnalysis& m_lexicalAnalysis;

	//Iterator to the token list which represents the output of the lexical analysis 
	TokenList::iterator m_tokenIterator;

	//Current token for analyize
	Token m_currentToken;

	//List of all instructions
	Instructions* m_instructions;

	//List of memory variables
	Variables* m_memVars;

	//List of register variables
	Variables* m_regVars;

	//List of labels 
	Labels m_labels;

	//Nonterminal symbol Q
	void q();

	//Nonterminal symbol S
	void s();

	//Nonterminal symbol L
	void l();

	//Nonterminal symbol E
	void e();

	//Syntax error indicator
	bool m_syntaxError;

	int m_instructionCounter;

	int m_variableCounter;

public:

	//Constructor that recieves reference of the lexical analysis module which is go to be used for creating token iterator
	SyntaxAnalysis(LexicalAnalysis& lexicalAnalysis, Instructions* instructions, Variables* memoryVariables, Variables* registerVariables);

	//Method that performs syntax analysis; returns false if error found, otherwise true
	bool doSyntaxAnalysis();

	//Prints the token that caused the syntax error
	void printSyntaxError(Token& token);

	//Eats the current token if it's type is "t", otherwise reports syntax error; param - t - the expected token type
	void eat(TokenType t);

	//Returns the next token from the token list
	Token getNextToken();

	//Checks variable existance
	bool variableExists(Variable* var);

	//Add variable in variable list
	void addVariable(Variable* var);

	//Checks label existance
	bool labelExists(Label* label);

	//Add label in label list
	void addLabel(Label* label);

	//Returns a Variable if it is added before, else exepction
	Variable* getVariable(std::string name);

	//Returns a Label if it is added before, else exepction
	Label* getLabel(std::string name);
};