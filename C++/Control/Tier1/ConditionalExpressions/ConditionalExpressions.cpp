#include <cstdio>

// Macros will be gone over later in tier 3 but we use one here to evalutate and print the expression.
#define EvalAndPrint(expression) \
printf("%s     %s\n", (expression) ? "true :" : "false:", #expression)

int main(void)
{
	// Evaluate as bool
	EvalAndPrint(0);              // false: 0 evaluates to false in C/C++
	EvalAndPrint(1);              // true: any non-zero value evaluates to true in C/C++
	EvalAndPrint(-42);            // true
	EvalAndPrint(nullptr);        // false: nullptr is just the integer 0
	EvalAndPrint(-3.423453f);     // true
	EvalAndPrint(0.0f);           // false 
	EvalAndPrint(-0.0f);          // false

	// Equals (bools)
	EvalAndPrint(true == true);   // true
	EvalAndPrint(false == true);  // false
	EvalAndPrint(true != true);   // false
	EvalAndPrint(false == true);  // true
	// Equals (integer values) (pointers work the same way)
	EvalAndPrint(1 == 1);         // true
	EvalAndPrint(1 == 0);         // false
	EvalAndPrint(-1 != -1);       // false
	EvalAndPrint(-10 != 99);      // true

	// Equals (floats)
	EvalAndPrint(10.0f == 10.0f);                    // true
	EvalAndPrint(1.4f + 0.3f != 1.7f);    // false: float operations have rounding errors and may have hardware dependent behavior.
	


	return 0;
}