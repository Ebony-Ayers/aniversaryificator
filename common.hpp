#ifndef COMMON_HEADER_GUARD
#define COMMON_HEADER_GUARD

#define EXPRESSION_BIT_WIDTH 32
#define MAX_NUM_OPERATIONS 4
#define MAX_NUM_CONSTANTS 5
#define STACK_DEPTH 1

typedef uint32_t Expression;
typedef uint32_t Operation;
typedef uint32_t Constant;

#define OPERATOR_BIT_WIDTH 4
namespace Operators
{
	const Operation noop           = 0;
	const Operation push           = 1;
	const Operation addition       = 2;
	const Operation multiplication = 3;
	const Operation exponentiation = 4;
	const Operation factorial      = 5;
}
extern const char* OperatorStrings[];

#define CONSTANT_BIT_WIDTH 3
namespace Constants
{
	const Constant e      = 0;
	const Constant pi     = 1;
	const Constant phi    = 2;
	const Constant sqrt2  = 3;
	const Constant one    = 4;
	const Constant blank1 = 5;
	const Constant blank2 = 6;
	const Constant pop    = 7;
}
extern const char* ConstantStrings[];

#endif //COMMON_HEADER_GUARD
