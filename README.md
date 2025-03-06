# aniversaryificator
This is part of something I'm working on with my partner to compute obscure aniversaries based on combinations of mathematical consonants.

## Expression representation and evaluation
Expressions are packed into a 32bit integer.
| Bits  | Use         |
| :---- | :---------- |
| 0-3   | Operation 1 |
| 4-7   | Operation 2 |
| 8-11  | Operation 3 |
| 12-15 | Operation 4 |
| 16-18 | Constant 1  |
| 19-21 | Constant 2  |
| 22-24 | Constant 3  |
| 25-27 | Constant 4  |
| 28-30 | Constant 5  |
| 31    | Unused      |

Operations and consonants are enums with the following mappings.
| value | Operation      |
| :---- | :------------- |
| 0     | Noop           |
| 1     | Push           |
| 2     | Addition       |
| 3     | Multiplication |
| 4     | Exponentiation |
| 5     | Factorial      |

| Value | Constant |
| :---- | :------- |
| 0     | e        |
| 1     | pi       |
| 2     | phi      |
| 3     | sqrt2    |
| 4     | 1        |
| 5     | Unused   |
| 6     | Unused   |
| 7     | Pop      |
Note that the "constant" pop means to use the stored value from pushing. While this is not a constant it is done this way from performance reasons.

To evaluate an expression start by setting the accumulator equal to the first constant. 

## Optimising evaluation
| Version | Time (ns) | Notes               |
| :------ | :-------- | :------------------ |
| v1      | 11.2      | Original version    |
| v2      | 9.7       | Basic optimisations |
