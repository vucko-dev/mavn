#include <iostream>
#include <exception>
#include <iomanip>


#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"

using namespace std;


int main()
{
	try
	{
		std::string fileName = ".\\..\\examples\\simple.mavn";
		bool retVal = false;

		LexicalAnalysis lex;

		if (!lex.readInputFile(fileName))
			throw runtime_error("\nException! Failed to open input file!\n");

		lex.initialize();

		retVal = lex.Do();

		if (retVal)
		{
			cout << "Lexical analysis finished successfully!" << endl;
			lex.printTokens();
		}
		else
		{
			lex.printLexError();
			throw runtime_error("\nException! Lexical analysis failed!\n");
		}

		cout << setfill('-') << setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << endl;
		cout << setfill(' ');
		cout << "Starting syntax analysis . . ." << endl;
		cout << setw(LEFT_ALIGN) << left << "Type:";
		cout << setw(RIGHT_ALIGN) << right << "Value:" << endl;
		cout << setfill('-') << setw(LEFT_ALIGN + RIGHT_ALIGN + 1) << " " << endl;
		cout << setfill(' ');

		SyntaxAnalysis syntaxAnalysis(lex);

		retVal = syntaxAnalysis.doSyntaxAnalysis();

		if (retVal)
		{
			cout << "Syntax analysis finished successfully!" << endl;
		}
		else
		{
			throw runtime_error("\nException! Syntax analysis failed!\n");
		}
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}
