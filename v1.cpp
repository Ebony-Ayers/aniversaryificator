#include "pch.h"
#include "common.hpp"
#include "debug_tools.hpp"
#include "tester.hpp"


Constant getNextConstant(Expression& e)
{
	const uint32_t constantMask = (1 << CONSTANT_BIT_WIDTH) - 1;
	Constant c = e & constantMask;
	e >>= CONSTANT_BIT_WIDTH;
	return c;
}

float evaluateExpression(Expression e, float* /*unused*/)
{
	//the accumulator works like in cpus
	float accumulator;
	//the 6th and 7th operands are not used. The 8th operand is where stored values are stored with the push instruction.
	float operands[1 << CONSTANT_BIT_WIDTH] = {
		2.71828182845904523536f,
		3.14159265358979323846f,
		1.61803398874989484820f,
		1.41421356237309504880f,
		1.0f,
		0.0f,
		0.0f,
		0.0f,
	};
	const size_t pushPopIndex = (1 << CONSTANT_BIT_WIDTH) - 1;
	Expression instructionStack = e;
	Expression constantStack = e >> (OPERATOR_BIT_WIDTH * MAX_NUM_OPERATIONS);
	
	//cache the masks
	const uint32_t instructionMask = (1 << OPERATOR_BIT_WIDTH) - 1;
	const uint32_t constantMask = (1 << CONSTANT_BIT_WIDTH) - 1;
	
	//as each operation acts on the accumulator and one other the first operations needs the first value already in the accumulator
	accumulator = operands[getNextConstant(constantStack)];
	
	for(int i = 0; i < MAX_NUM_OPERATIONS; i++)
	{
		//get the next operation
		const Operation op = instructionStack & instructionMask;
		instructionStack >>= OPERATOR_BIT_WIDTH;
		
		//perform the operation
		switch(op)
		{
			case Operators::noop:
				break;
			case Operators::push:
				operands[pushPopIndex] = accumulator;
				accumulator = operands[getNextConstant(constantStack)];
				break;
			case Operators::addition:
				accumulator += operands[getNextConstant(constantStack)];
				break;
			case Operators::multiplication:
				accumulator *= operands[getNextConstant(constantStack)];
				break;
			case Operators::exponentiation:
				accumulator = powf(accumulator, operands[getNextConstant(constantStack)]);
				break;
			case Operators::factorial:
				accumulator = tgammaf(accumulator + 1.0f);
				break;
			default:
				break;
		}
	}
	
	return accumulator;
}

int main(int /*argc*/, const char* /*argv*/[])
{
	testEvaluation();
	
	return 0;
}
