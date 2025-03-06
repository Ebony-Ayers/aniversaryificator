#include "debug_tools.hpp"

Expression debugCreateExpression(Operation op1, Operation op2, Operation op3, Operation op4, Constant c1, Constant c2, Constant c3, Constant c4, Constant c5)
{
	Expression e = 0;
	
	e |= op1 << (OPERATOR_BIT_WIDTH * 0);
	e |= op2 << (OPERATOR_BIT_WIDTH * 1);
	e |= op3 << (OPERATOR_BIT_WIDTH * 2);
	e |= op4 << (OPERATOR_BIT_WIDTH * 3);

	e |= c1 << ((OPERATOR_BIT_WIDTH * MAX_NUM_OPERATIONS) + (CONSTANT_BIT_WIDTH * 0));	
	e |= c2 << ((OPERATOR_BIT_WIDTH * MAX_NUM_OPERATIONS) + (CONSTANT_BIT_WIDTH * 1));
	e |= c3 << ((OPERATOR_BIT_WIDTH * MAX_NUM_OPERATIONS) + (CONSTANT_BIT_WIDTH * 2));
	e |= c4 << ((OPERATOR_BIT_WIDTH * MAX_NUM_OPERATIONS) + (CONSTANT_BIT_WIDTH * 3));
	e |= c5 << ((OPERATOR_BIT_WIDTH * MAX_NUM_OPERATIONS) + (CONSTANT_BIT_WIDTH * 4));
	
	return e;
}

void debugPrintBinary(uint32_t val)
{
	int i = 0;
	for(int j = 0; j < MAX_NUM_OPERATIONS; j++)
	{
		for(int k = 0; k < OPERATOR_BIT_WIDTH; k++)
		{
			printf("%d", (val >> i) & 1);
			i++;
		}
		printf(" ");
	}
	printf("| ");
	for(int j = 0; j < MAX_NUM_CONSTANTS; j++)
	{
		for(int k = 0; k < CONSTANT_BIT_WIDTH; k++)
		{
			printf("%d", (val >> i) & 1);
			i++;
		}
		printf(" ");
	}
	printf("\n");
}

void debugPrintExpressionPolish(Expression e)
{
	const uint32_t opertionMask = (1 << OPERATOR_BIT_WIDTH) - 1;
	const uint32_t constantMask = (1 << CONSTANT_BIT_WIDTH) - 1;
	
	for(int i = 0; i < MAX_NUM_OPERATIONS; i++)
	{
		const Operation op = (e >> (OPERATOR_BIT_WIDTH * i)) & opertionMask;
		printf("%s ", OperatorStrings[op]);
	}
	
	printf("| ");
	
	for(int i = 0; i < MAX_NUM_CONSTANTS; i++)
	{
		const Operation op = (e >> ((OPERATOR_BIT_WIDTH * MAX_NUM_OPERATIONS) + (CONSTANT_BIT_WIDTH * i))) & constantMask;
		printf("%s ", ConstantStrings[op]);
	}
	
	printf("\n");
}
