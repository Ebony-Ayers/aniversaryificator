#ifndef DEBUG_TOOLS_HEADER_GUARD
#define DEBUG_TOOLS_HEADER_GUARD

#include "pch.h"
#include "common.hpp"

Expression debugCreateExpression(Operation op1, Operation op2, Operation op3, Operation op4, Constant c1, Constant c2, Constant c3, Constant c4, Constant c5);
void debugPrintBinary(uint32_t val);
void debugPrintExpressionPolish(Expression e);

#endif //DEBUG_TOOLS_HEADER_GUARD
