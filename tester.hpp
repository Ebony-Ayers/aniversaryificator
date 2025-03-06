#ifndef TESTER_HEADER_GUARD
#define TESTER_HEADER_GUARD

#include "pch.h"
#include "common.hpp"
#include "debug_tools.hpp"

//this is a forwards declarion for a function that will be defined in the file including this header
float evaluateExpression(Expression e, float* dataStack);

void testEvaluation();

#endif //TESTER_HEADER_GUARD
