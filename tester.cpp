#include "tester.hpp"

#define NUM_TESTS 40000+16875+16875+16875

void testEvaluation()
{
	float dataStack[1 << CONSTANT_BIT_WIDTH] = {
		2.71828182845904523536f,
		3.14159265358979323846f,
		1.61803398874989484820f,
		1.41421356237309504880f,
		1.0f,
		0.0f,
		0.0f,
		0.0f,
	};

	Expression expressionQueue[NUM_TESTS];
	size_t queueIndex = 0;
	
	//expressions of the form (((c . c) . c) . c) where c is a constant and . is an operations
	for(uint32_t op1 = 2; op1 < 6; op1++)
	{
		for(uint32_t op2 = 2; op2 < 6; op2++)
		{
			for(uint32_t op3 = 2; op3 < 6; op3++)
			{
				for(uint32_t c1 = 0; c1 < 5; c1++)
				{
					for(uint32_t c2 = 0; c2 < 5; c2++)
					{
						for(uint32_t c3 = 0; c3 < 5; c3++)
						{
							for(uint32_t c4 = 0; c4 < 5; c4++)
							{
								expressionQueue[queueIndex] = debugCreateExpression(op1, op2, op3, Operators::noop, c1, c2, c3, c4, Constants::e);
								queueIndex++;
							}
						}
					}
				}
			}
		}
	}
	//expressions of the form (c . c) . (c . c) where c is a constant and . is an operations
	for(uint32_t op1 = 2; op1 < 5; op1++)
	{
		for(uint32_t op2 = 2; op2 < 5; op2++)
		{
			for(uint32_t op3 = 2; op3 < 5; op3++)
			{
				for(uint32_t c1 = 0; c1 < 5; c1++)
				{
					for(uint32_t c2 = 0; c2 < 5; c2++)
					{
						for(uint32_t c3 = 0; c3 < 5; c3++)
						{
							for(uint32_t c4 = 0; c4 < 5; c4++)
							{
								expressionQueue[queueIndex] = debugCreateExpression(op1, Operators::push, op2, op3, c1, c2, c3, c4, Constants::pop);
								queueIndex++;
							}
						}
					}
				}
			}
		}
	}
	//expressions of the form (c . (c . c)) . c where c is a constant and . is an operations
	for(uint32_t op1 = 2; op1 < 5; op1++)
	{
		for(uint32_t op2 = 2; op2 < 5; op2++)
		{
			for(uint32_t op3 = 2; op3 < 5; op3++)
			{
				for(uint32_t c1 = 0; c1 < 5; c1++)
				{
					for(uint32_t c2 = 0; c2 < 5; c2++)
					{
						for(uint32_t c3 = 0; c3 < 5; c3++)
						{
							for(uint32_t c4 = 0; c4 < 5; c4++)
							{
								expressionQueue[queueIndex] = debugCreateExpression(op1, Operators::push, op2, op3, c1, c2, c3, Constants::pop, c4);
								queueIndex++;
							}
						}
					}
				}
			}
		}
	}
	//expressions of the form c . ((c . c) . c) where c is a constant and . is an operations
	for(uint32_t op1 = 2; op1 < 5; op1++)
	{
		for(uint32_t op2 = 2; op2 < 5; op2++)
		{
			for(uint32_t op3 = 2; op3 < 5; op3++)
			{
				for(uint32_t c1 = 0; c1 < 5; c1++)
				{
					for(uint32_t c2 = 0; c2 < 5; c2++)
					{
						for(uint32_t c3 = 0; c3 < 5; c3++)
						{
							for(uint32_t c4 = 0; c4 < 5; c4++)
							{
								expressionQueue[queueIndex] = debugCreateExpression(op1, op2, Operators::push, op3, c1, c2, c3, c4, Constants::pop);
								queueIndex++;
							}
						}
					}
				}
			}
		}
	}
	

	typedef	std::chrono::time_point<std::chrono::high_resolution_clock> TimeType;
	TimeType startTime = std::chrono::high_resolution_clock::now();
	float results[NUM_TESTS];
	for(size_t i = 0; i < NUM_TESTS; i++)
	{
		results[i] = evaluateExpression(expressionQueue[i], dataStack);
	}
	TimeType endTime = std::chrono::high_resolution_clock::now();
	auto t1 = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();
	auto t2 = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
	double totalTimeTaken = static_cast<double>(t1-t2);
	double timePerIteration = (totalTimeTaken / static_cast<double>(NUM_TESTS)) * 1000.0;
	double iterationsPerSecond = 1000000000.0 / timePerIteration;
	printf("%.3fns per iteration\n", timePerIteration);
	printf("%.0f iterations per second\n", iterationsPerSecond);
}
