/* Autor: David Vucenovic Datum: 07.06.2023. */

#ifndef __WRITTER__
#define __WRITTER__

#include <string>
#include <fstream>
#include <iomanip>
#include "IR.h"
#include "Exceptions.h"
#include "InterferenceGraph.h"

//Output MIPS code in .s file
void printInFile(std::string fileName, Instructions& instructions, Variables& variables);

//Print provided instructions
void printInstructions(Instructions& instructions);

//Print provided variables
void printVariables(Variables& variables);

//Print horizontal line
void printHorizontalLine();

//Prints interference graph
void printInterferenceGraph(InterferenceGraph& interferenceGraph);


#endif