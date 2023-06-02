#pragma once

#include "LexicalAnalysis.h"
#include "Token.h"


class SyntaxAnalysis {

private:


	// Reference to lexical analysis module
	LexicalAnalysis& m_lexicalAnalysis;

	//Iterator to the token list which represents the output of the lexical analysis 
	TokenList::iterator m_tokenIterator;

	//Current token for analyize
	Token m_currentToken;

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

public:

	//Constructor that recieves reference of the lexical analysis module which is go to be used for creating token iterator
	SyntaxAnalysis(LexicalAnalysis &lexicalAnalysis);

	//Method that performs syntax analysis; returns false if error found, otherwise true
	bool doSyntaxAnalysis();

	//Prints the token that caused the syntax error
	void printSyntaxError(Token& token);

	//Eats the current token if it's type is "t", otherwise reports syntax error; param - t - the expected token type
	void eat(TokenType t);

	//Returns the next token from the token list
	Token getNextToken();
};