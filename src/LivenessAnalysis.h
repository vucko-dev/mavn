#pragma once

#ifndef __LIVENESS_ANALYSIS__
#define __LIVENESS_ANALYSIS__

#include "Types.h"
#include "Constants.h"
#include "Instruction.h"
#include "Variable.h"
#include "SyntaxAnalysis.h"


//Next four functions fills m_pred, m_succ, m_use and m_def lists in instruction

void fillPred(Instructions* instructions);

void fillSucc(Instructions* instructions);

void fillUse(Instructions* instructions);

void fillDef(Instructions* instructions);

//This function checks is Label exists in some instruction from the list
Instruction* getLabelInstruction(Instructions* instructions, Label* label);

//Checks existance of Variable& variable in provided list Variables &variables
bool variableExsists(Variables &variables, Variable &variable);

//This function runs Liveness Analysis
void livenessAnalysis(Instructions* instructions);

#endif