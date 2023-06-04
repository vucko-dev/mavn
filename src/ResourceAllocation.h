#pragma once
#ifndef __RESOURCE_ALLOCATION__
#define __RESOURCE_ALLOCATION__

#include "InterferenceGraph.h"

#include <stack>

//This function does resource allocation
//Returns true if no spill is detected during resource allocation, false otherwise
bool doResourceAllocation(std::stack<Variable*>* simplificationStack, InterferenceGraph* ig);

#endif