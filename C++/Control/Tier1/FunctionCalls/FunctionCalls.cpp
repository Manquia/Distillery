#include <cstdio>;


// Example forward declaration called "PrintText"
// Parameters(1): const char* text (C-style string)
// Return: empty/void (nothing)
// Notes: C++ requires that every function is declared before being referenced within the .cpp (object) file. This means that its signature known but does not requires that its definition (code) is known.
void PrintText(const char* text);

// Example function definition called "HelloWorld"
// Parameters(0): void
// Return: empty/void (nothing)
void HelloWorld()
{
	// We can call a function by typing the function's name then a '(' followed by a comma seperated list for its parameters and then a ')'. The ';' at the end is not part of the function call, and in this case simply finishes the statement.
	PrintText("HelloWorld"); // We can call this because we have the foward declaration above even though there is no definition yet.
}

// Example function definition called "PrintText"
// Parameters: const char* text (C-style string)
// Return: empty/void (nothing)
void PrintText(const char* text)
{
	// printf takes 1 or more arguments with the first being a "format" string and the rest being information to be added into the format. This is an example of a variadic function.
	printf("Printing Text %s", text);
	printf("\n");
}

// Example function definition called "AddNumbers"
// Parameters(2): int number0, int number1
// Return: int (resulting number)
int AddNumbers(int number0, int number1)
{
	return number0 + number1;
}

// Example function definition called "foo", "bar", "magic", and "king" are appended with "Linear", "Resurcive", "Cycle" to show the corresponding concepts

// Linear example
void fooLinear();
void barLinear();
void magicLinear();
void kingLinear();

void fooLinear()
{
	barLinear();
}
void barLinear()
{
	magicLinear();
}
void magicLinear()
{
	kingLinear();
}
void kingLinear()
{
	printf("kingLinear\n");
}

// Recursive example
void fooRecursive(int value)
{
	if (value > 10)
		return;
	else
	{
		fooRecursive(value + 1);
		printf("fooLinear %d\n", value);
	}
}

// Cycle example
void fooCycle(int value);
void barCycle(int value);

void fooCycle(int value)
{
	if (value > 12)
	{
		printf("fooCycle %d\n", value);
		return;
	}
	else
		barCycle(value - 2);
}
void barCycle(int value)
{
	fooCycle(value + 3);
}

// Hybrid example
void fooHybrid(int v);
void barHybrid(int v);
void magicHybrid(int v);
void kingHybrid(int v);


void fooHybrid(int v)
{
	barHybrid(v + 3);
}
void barHybrid(int v)
{
	if (v % 2 == 1) // v is odd, call magic
		magicHybrid(v - 5);
	else            // v is even, call king
		kingHybrid(v + 1);
}
void magicHybrid(int v)
{
	fooHybrid(v + 1);
}
void kingHybrid(int v)
{
	if (v > 100)
	{
		printf("kingHybrid %d\n", v);
		return;
	}
	else
	{
		printf("building kingHybrid %d\n", v);
		fooHybrid(v * 2);
	}
}

// Note: Most C++ projects have ".h" header files which contain only forward declarations so that functions can be called across .cpp (object) files. This is because of the One Definition Rule (ODR) which does not allow more than 1 definition of a function in the final executable. However, you may have any number of declarations. By using the #include "FileNameHere.h" we can include the text of these header files in our .cpp files so that we do not need to duplicate the forward declarations for functions, structs, classes, and unions.
int main(void); // Valid C++
int main(void); // Valid C++
int main(void); // Valid C++ (does nothing new)


// Alternate way to forward declare and define functions using the "auto" keyword was introduced in the C++11 update.
// Example function forward declaration (alternate syntax)
// Parameters(3): int seconds, int minutes, int hours
// return: bool
auto IsMagicalMoment(int seconds, int minutes, int hours) -> bool;
// Example function definition (alternate syntax)
// Parameters(3): int seconds, int minutes, int hours
// return: bool
auto IsMagicalMoment(int seconds, int minutes, int hours) -> bool
{
	if (seconds == minutes &&
		minutes == hours)
		return true;
	else
		return false;
}


// a function called "main" with signature is the program's entry point. "main" does not require a forward declaration but must be in an object file used to create the final executable.
int main(void)
{
	// This is the entry point of the "FunctionCalls" program. This means we start our executing instructions here.
	HelloWorld();

	printf("3 + 8 = %d\n", AddNumbers(3, 8));

	fooLinear();
	magicLinear();

	fooRecursive(-3);
	fooRecursive(3);

	fooCycle(3);
	// fooCycle(-2147483647); // max negative 32-bit int. Cycle will run for billions of times before completion. This will crash the program because our stack which holds the variables for the function calls doesn't have enough memory to hold the values needed to complete. This sort of crash is called a stack overflow.

	fooHybrid(4);
	magicHybrid(10);

	bool magicalMoment = IsMagicalMoment(10, 10, 10);
	printf("Magical Moment: %s\n", magicalMoment ? "true" : "false");


	// Lambda Capture function
	// Syntax: auto lambdaName = []()-> ReturnType {};
	// "[]" encapsulates what the function will capture from the definition site's local or global scope
	// "()" is the functions parameter list
	// Optional: "-> ReturnType" The return type will be infered if not explicity specified.
	// '{}" is the functions body
	// ";" must go at the end to complete the statement.

	// Example Lamdba Capture function
	// Capture(2)

	const char* leprechaun = "Timmy the Tumbler";

	auto FindGold = [leprechaun](int time) -> bool 
	{
		if (leprechaun && time > 5)
		{
			printf("Found the Gold! Thanks %s!\n", leprechaun);
			return true;
		}
		else
		{
			printf("No gold found.\n");
			return false;
		}
	};

	// leprechaun is captured by value so we can change this and still find gold.
	leprechaun = 0;

	// Call lambda "Find Gold".
	FindGold(8);
	FindGold(1);

	// You can capture by reference or by value in a varity of ways with specific syntax.

	return 0;
}
