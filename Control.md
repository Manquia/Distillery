Control.txt

Pre-requisite: Types.txt tier 1

Tier 1.00: Executing Statements
==============================
A statement is a section of code that is evaluated by the rules of the language. A statement may have:
 - 0 or more sub-statements (AND)
 - 0 or more expressions (AND)
 - 0 or more declarations nested within.

**Example**: Statement Evaluation

```
// Mathimatical operation evaluation order follows the programming languages' rules.
// The ordering is called the operator precedence.
value  = x + 2;        // Evaluated first.
value += x + 1 - y/2;  // Evaluated second. 
value /= value - x;    // Evaluated third.
```

Tier 1.01: Conditional Expressions
==================================
Programs can make a choice based on expressions which evaluate to a boolean of true or false. The selection of a section of code to run based on the value of the boolean is called a branch. To create a useful expression which evaluates to true or false there are many useful operators we can use.

**Example**: List of common conditional operators
```
Operator  Name             Result
                          
e0 == e1  Equals(E)        True when e0 and e1 are equal, else false.
e0 != e1  Not Equals       True when e0 and e1 are not equal, else false.
e0 >  e1  Greater Than(GT) True when e0 is greater than e1, else false.
e0 <  e1  Less Than (LT)   True when e0 is less than e0, else false.
e0 >= e1  GT or E          True when e0 is GT or E to e1, else false.
eo <= e1  LT or E          True when e0 is LT or E to e1, else false.
!e0       Not              True when e0 is false. False when e0 is true.
e0 <=> e1 Three way        0 when e0 and e1 are E. LT 0 when e0 LT e1. GT 0 when e0 GT e1.
e0 && e1  Logical AND      True when e0 and e1 are true, else false. See Short Circuit below.
e0 || e1  Logical OR       True when e0 or e1 are true, else false. See Short Circuit below.
e0 &  e1  Bit-wise AND     True when e0 and e1 are true, else false. See Bit-wise Conditionals.
e0 |  e1  Bit-wise OR      True when e0 or e1 are true, else false. See Bit-wise Conditionals.
```
Most languages allow conversion from integer values into boolean. Most languages evaluate 0 as false, and non-zero integer values as true.

(extra) Three-way comparison '<=>' is sometimes called the "spaceship" operator.


Tier 1.02: Grouping operator: '( ... )'
=======================================
The grouping operator may be used to denote the order in which an expression is evaluated. The order an expression is evaluated is otherwise language dependent based on the operators and sometimes types used in the expression.

**Example**: Below the expression '1)' may evaluate to either expression '2)' or '3)' depending on the language and type of e0,e1,e2.
```
1)   e0 || e1 == e2    // Language dependent behavior
2)   e0 ||(e1 == e2)   // (e1 == e2) will be executed before e0 || (result)
3)  (e0 || e1)== e2    // (e0 || e1) will be executed before (result) == e2
```

Tier 1.03: Scope: '\{ ... \}'
===========================
Scope is a section or block of code denoted by some language semantics with a definite start and end.

Common scope semantics:
* Curly bracket: Newlines, Spaces, Tabs do not affect the scope
* '{' is the start or opening of a new scope
* '}' is the end or closing of the last open scope.
```
{ 
  // Scope 1a
  {
    // Scope 2a
  }
  // Scope 1a
  {
    // Scope 2b
    { /* Scope 3a */ } // Note: Start and end may be on the same line.
  }
  // Scope 1a
}
```
* Tab/space-based: Tabs denote scope begin/end
```
Scope 1a
    Scope 2a
Scope 1a
Scope 1a
    Scope 2b
        Scope 3a
```

Tier 1.04: Variables
====================

A variable is a referencable section of memory that is associated with a type. 

**Example**: Declaring a **local** variable common syntax
```
{
  // By declaring 'myVariable' as an int we get memory from the stack of size int and then assign it the value 4.
  int myVariable = 4; 
  
  
  // Other language syntax
  myVariable : int = 4;
  var myVariable = 4;   // int type is infered by assigning the integer value of 4
}
```
* The stack is a block of memory used by functions as a sketch pad. See Tier 4.00 for more details.
* The memory size of a variable is often the same as the type but may vary depending on alignment requirements of the CPU instructions being used by the type.

In most programming languages the location or scope in which you declare a variable defines that variable's **lifetime** and where its **memory is stored**. Once a variable goes beyond its lifetime,  accessing that variable results is undefined behavior (UB).

**Example**: Declaring a variable in a function's scope or sub-scopes makes it a **local** variable with a lifetime lasting till the end of the scope. Memory is stored on the **stack**.
```
// Example 1
void DoThingy0()
{
  int myVar = 0; // Declare local variable 'myVar' as an integer
  {
    myVar = 1;   // Accessing 'myVar' is fine
  }
  myVar = 2;     // Accessing 'myVar' is fine
  // 'myVar' is destroyed before the end of this scope
}

// Example 2
void DoThingy1()
{
  {
    int myVar = 0; // Declare local varaible 'myVar' as an integer
	
    // 'myVar' is destroyed before the end of this scope
  } 
  myVar = 1; // ERROR: 'myVar' is beyond its lifetime, accessing it is UB.
}
```

**Example**: A variable may reference another variable in memory by pointer or reference. We may use the operating system to allocate persistent memory often called **heap** allocations.
```
// Example 1
void DoThingy0()
{
  int* myVarPtr = nullptr; // Declare local variable 'myVarPtr' as a pointer to integer that points to 0 address in memory.
  {
    myVarPtr = new int(1); // Allocate an integer on the heap and assign our pointer with its address.
  }
  *myVarPtr = 2;           // Accessing the interger that 'myVarPtr' is pointing to is fine.
  
  // We must explicitly delete the allocation otherwise it will not be cleaned up until the end of the program.
  // Failures to clean up is called a **memory leak** and can result in severe performance degradation and failure in non-managed programming languages.
  delete myVarPtr;
  
  // 'myVarPtr' is destroyed before the end of this scope
}
```

**Example**: A variable may be declared as a **global** in which case its lifetime matches the program. A global variable is created/allocated on program startup and destroyed/cleaned up when the program terminates.
```
// To declare a global variable, programming languages often either use a keyword like static or global or they are located outside of a function or object scope.

// declare 'g_myGlobalVar' as a global variable in the global namespace.
static int g_myGlobalVar = 0;

struct Penguin`2
  // Declare a global variable inside 'DoThingy' function.
  static int g_Thingy = 0;
  
  // Example of accessing global variables
  g_myGlobalVar += 1;
  Penguin::g_cuteFactor += 1;
  g_Thingy += 1;
}
```
* The 'g_' prefix is not required, but it is often good practice because global variables can be accessed from everywhere so its a warning to be careful.

**Example**: Declaring a variable in an object/class's scope bind's the variable's lifetime with that of the object. The object or type may be a local variable on the **stack**, memory in the **heap**, or a **global** variable.

```
struct Ship
{
  Sailor Julee;
  
  // The pointer address value lifespan is bound to this object. We will NOT clean up whatever
  // we are pointing at. See Smart Pointers @Pointer.md 2.02 if automatic cleanup is desired.
  Ship* enemyShip;
}

// Declare ship as a global. Julee's lifespan matches the program.
Ship g_TheLongGame;

void DoThingy0()
{
  
  Ship* shipInHeap = new Ship(); // shipInHeap's Julee allocated/created
  delete shipInHeap              // shipInHeap's Julee cleaned up/destroyed
  
  Ship shipOnStack;              // shipOnStack's Julee created
  
  // 'shipOnStack' is destroyed before the end of this scope Julee with it.
}
```

(extra) A namespace is similar to a folder/category. Its a way of organizing types and functions.
(extra) Some programming languages make it is possible to hide variables in a higher scope if the variables' names match. This is called a **shadow variable** and often the compiler will print a warning and/or choose the variable which is the least number of scope jumps away.

Tier 1.05: Functions
========================
Functions encapsulate code and take inputs and outputs. Functions can be called in any order enabling linear calls, recursion, and cycles.

Most programs have a special entry point function, often called main, which is the logical starting point of the program.

**Example**: Call Hierarchy structure examples

'foo', 'bar', 'magic', and 'king' are all functions
```
Linear     foo() -> bar() -> magic() -> king()
Recursion  foo() -> foo() -> foo() -> foo() -> foo()
Cycle      foo() -> bar() -> foo() -> bar() -> foo() -> bar()
hybrid     foo() -> bar() -> king() -> foo() -> bar() -> magic()
```

functions have a return point, local variables, inputs, or outputs per function call which are stored on the current thread's stack. Calling a function may cause the stack to run out of memory resulting in a stack overflowing.

A function may be in a user-defined or in a namespace in which case you may need to reference the namespace or type to call the function. **Member functions** are often defined inside the user-defined type's scope and take a pointer or refernce called 'this' or 'self' to the object they are inside.

(extra) main is rarely the 'start' of the program's execution as other parts of the program require execution to before the main entry point function is called. Some languages and compilers will include ways to modify the program's setup with other specially marked function that the programmer has access to modify/add.

(extra) Function overloading allows the same function name to have multiple versions for different input types. This means that foo() and foo(int) are not the same functions. When calling the "foo" function the compiler will choose which overload is most appropriate. The compiler's choice can be unexpected if there are many reasonable choices, so it is advised to not overload too much on similar types (ie. The choice between u64,s64,size_t,uint_fast8_t would be hard to know without expert knowledge of the compiler and environment).

(extra) Functions may exhibit some of the following some qualities:
* Pure: Function only modifies input and return values
* Free: Function is not connected to any class/object and may be called from anywhere.
* Member: Function is connected to a class/object and may use an implicit this pointer to access the class/object.
* Lambda Capture: Creates an implicit class/object in a function when declared which then may be accessed when the function runs. The class/object may be allocated on the stack or heap depending on the limitations of the language and compiler and use-case.


Tier 1.06: Control Statements
=============================
A control statement branches to a section of code (often a new scope) based on the result of its conditional expression.
```
'...' <- Shorthand for insert code to run here
{ }   <- Curly bracket pair often denote begin and end of a scope
```
**Example**: if

```
if (cond)      // if 'cond' evaluates to true,
{ ... }        // then this scope will run.
```

**Example**: if else
```
if (cond)      // if 'cond' evaluates to true,
{ ... }        // then this scope will run.
else           // if the previous 'if' statement evaluates to false,
{ ... }        // then this scope will run.
```
**Example**: Chaining if else
```
if(cond0)      // if cond0 is true,
{ ... }        // then run this scope.
else if(cond1) // if cond0 was false AND cond1 is true,
{ ... }        // then this scope will run.
else if(cond2) // if cond0 and cond 1 were false AND cond 2 is true,
{ ... }        // then this scope will run.
```
Chaining if else may chain as many conditions as you like, there is no limit.

**Example**: Switch (Basic)
```
if(cond0)      // conditional expression
{
  case 0: { ... } // when cond0 equals 0, then this scope will run.
  case 1: { ... } // when cond0 equals 1, then this scope will run.
  case -1:{ ... } // when cond0 equals -1, then this scope will run.
  case 50:{ ... } // when cond0 equals 50, then this scope will run.
}
```
Note: Inside a switch "case:", most languages continue to run linearly through the code until a "break" is called to jump out of the switch statement. "case 0: { ... } break;" is commonly used to prevent the execution from falling through to other cases. @see Break

(extra) Some languages impliment switch statements for other types such as strings or even expressions. These sorts of switch statements are not as fast as an integer-based solution, but can improve code readability and reduce complexity.

- strings: "case "Hello World":{ ... }"
- expressions: "case value > 2:{ ... }"

Tier 1.07: Loops
================
A loop contains a section of code (often a new scope) which the program may repeat 0 or more times depending on a given conditional expression.
```
'...' <- Shorthand for insert code to run here
```
**Example**: while
```
while(cond)   // while cond is true, 
{ ... }       // then run this scope again.
```

**Example**: foreach (index)

Used all index or items in a logical order or container whereby each index or item is used in the scope of the loop.
```
foreach 1..5   // for each index starting at 1 rising to 5 (1,2,3,4,5)
{ ... }        // evaluate scope with index untill all selected index have run.
```
**Example**: foreach (item in container)
```
foreach (item in Container) // for each item in the container, (defaults to order when possible) @See types.md: iterators for more details
{ ... }                     // run scope with every item in the container.
```
**Example**: for(init;cond;loop)

- "init" expression will run ONLY once upon entering the "for" statement
- "loop" expression will run after the scope has finished.
- "cond" conditional expression will run after loop's scope, while true, the scope will run again.
```
for(init;cond;loop) // when cond is true,
{ ... }             // then this scope will run.
```
**Example**: do while loop
```
do                <- always execute scope atleast once.
{ ... }           <- scope to run.
while(cond);      <- while cond is true, run scope again.
```
(extra) do while loops sometimes have the cond always false and then use break statements to skip to the end of the scope.

Tier 1.08 Arithmatic Operators
===============================

Computers have many useful arithmetic operators to give us greater control of our program.

Common Operator symbols:
```
Arithmatic Operator
 Name     |  Usage  | Description
----------+---------+----------------------
 Add      | e0 + e1 | Add e0 and e1
 Subtract | e0 - e1 | Subtract e1 from e0
 Multiply | e0 * e1 | Multiply e0 and e1
 Divide   | e0 / e1 | Divide e0 by e1 (When done with integers, the result is rounded down)
 Modulo   | e0 % e1 | Calculate the remainder of e0 divided by e1
```
Tier 2.00: Short Circuit
========================
The logical AND: '&&' and logical OR: '||' operators often support short-circuiting whereby not all expressions will be evaluated if the statement can no longer evaluate to true or false respectively.

**Example**: 

Conditional expression evaluated:
```
    Must run Up to here|    |not run, logically can be skipped
                       V    V
                    true || false || true   // Cannot become false
 false || false ||  true || true  || true   // Cannot become false
                   false && true            // Cannot become true
           true && false && true && true    // Cannot become true
(true && false) || (true || false) || false // Cannot become false
```
Tier 2.01: bit-wise Conditionals
================================
The bit-wise AND: '&' and bit-wise OR" '|' can be used in a conditional, but must have both conditionals using the same bit in the flags. bit-wise AND will not use short-circuit logic and for this reason, can be faster for small expressions. Most languages use the value of 0 (binary: 00000000) to represent false and any non-zero value to represent true (binary: 11110000, 00000001, 11100011). We can use this behavior with bit-wise operations for logic.

Note: Bit-wise AND and bit-wise OR will operator on a per-bit basis doing the operation below to every bit between e0 and e1.
```
bit-wise AND  e0    bit-wise OR  e0      
            |0|1|              |0|1|
0&0=0      -+-+-+   0|0=0     -+-+-+
0&1=0      0|0|1|   0|1=1     0|0|1|
1&0=0    e1-+-+-+   1|0=1   e1-+-+-+
1&1=1      1|1|1|   1|1=1     1|1|1|
           -+-+-+             -+-+-+
```
**Example**: using common true/false (T/F) values
```
T/F     true       true       true
binary  00000001 & 00000001 = 00000001
T/F     false      true       false
binary  00000000 & 00000001 = 00000000
T/F     false      false      false
binary  00000000 & 00000000 = 00000000

T/F     true       false      true
binary  00000001 | 00000000 = 00000001
T/F     true       true       true
binary  00000001 | 00000001 = 00000000
T/F     false      false      false
binary  00000000 | 00000000 = 00000000
```
**Example**: using uncommon true/false (T/F) values may lead to unexpected results
```
T/F     true       true       false
binary  00000010 & 00000001 = 00000000
T/F     true       true       false
binary  11110000 & 00001111 = 00000000
T/F     true       true       true
binary  00000001 | 11111111 = 11111111
T/F     true       true       true
binary  10000001 | 00011001 = 10011001
```
(extra) it should also be noted that we can use even more bit-wise operators in our conditionals so long as we understand and expect non-zero to evaluate to true and 0 to evaluate to false. Other bit-wise operations which may prove helpful are: bit-wise XOR, bit-wise NOT, Shift bits left/right, Count left/right side's number of consecutive zero/one bits, total count zero/one bits (popCount/hamming weight), Circular shift (rotation), 2's compliment, etc...

Tier 2.02: Label
================
Labels are constant compile-time referenceable markers in code. We can branch to a label with a type of control statement's often called jumps. All control statements use labels under the hood to branch to scopes or other sections of code and some languages let you access these created labels to use with jumps.


Tier 2.03: Jump Statements
==========================
Jump statements are control statement statements which use a label to branch. Jump statements can branch to any label within the function and as such can also create loops. 

**Example**: goto (jump to the label)

Using jump statements and labels directly can create extremely flexible and complex code so they are often avoided when possible.
```
MyLabel:               // Lebel
goto MyLabel;          // jump to level called "MyLebel"
```
The statement above is the same as the following:
```
while(true) { }        // always, do nothing. 
```
Both statements will run the thread to forever doing nothing but jumping back to MyLebel and the conditional expression respectively.

**Example**:  break (jump out of the loop)
```
foreach (item in Container) // for each item in the container
{
  if(item.value == 0)       // condition
    break;                  // break out of the current loop, do not continue to next item. 
}
...                         // After break OR every item in the container, run the following code
```
**Example**:  break (jump out of multiple loops to named loop)
```
foreach outer:(bucket in buckets) // for each bucket in buckets
{                                 
  foreach inner:(item in bucket)  // for each item in bucket
  {                               
    if(item.value == 0)           // condition
      break outer;                // break out of the inner loop and outer loop, do not continue to next bucket or item. 
  }
}
...                               // After break OR every item in the container, run the following code
```
**Example**: continue (skip to the end of loop's scope)
```
for(int i = 0; i < 10; ++i)   // for i values 0-9
{
  if(i == 2 || i == 5)        // conditional
    continue;                 // skip to end of loop's scope

  print(i);                   // print i. Will print: 01346789
}                             // end of scope that we skip to in continue
```
**Example**: (extra) Switch (advanced)

Preface: Labels are treated as a complete statement which can be placed anywhere within the function. Switch statements are often implemented to use labels. '%' is the modulo operator in the following examples (ex. 5 % 4 = 1, 7 % 4 = 3).
```
switch(cond % 4)     // Switch conditionaly jumps to lebels below.
{
  case 0:
  while(i > 0)
  {
            i -= 1;     
    case 3: i -= 1;  // after 'i -= 1' statement, we fallthrough to the next statement
    case 2: i -= 1; 
    case 1: i -= 1;
  }
}                    // at this point i will always be less than or equal to 0
```
(extra) Above is an example of a Duff's device. Probably you never write this, but knowing it exists can lead to some amazing optimizations and control.

Tier 2.04: Iterators
====================

An **iterator** is generally a user-defined type used to traverse a collection of items often held within a container. The iterator type is a lightweight stateful object containing the needed data to traverse the data structure.

Other purposes:
* Providing Hints: Some search algorithms can be improved with a hint for closely related searches.
* Safety Check: Many iterators will do safety checks when in a debug compile of the problem. These checks often include out of **bounds checks** (arrays), **iterator invalidation**
 
An iterator may become invalidated for various reasons, depending on the container, but often is a result of adding or removing an item from the container or destruction of the container while iterating. (extra) The iterator invalidation is because by adding or removing an item the container may need to reallocate the memory used which means all current iterators may be referencing invalid memory resulting in undefined behavior.

**Example**: Iterate though array 
```
int main(void)
{
    std::array<int, 8> myArray = GetArray();
    
    // Many languages have syntactic sugar to utilize iterators.
    for(auto& item : myArray) // get object by reference
    {
        item += 10; // Add 10 to item
    }
}
```


Tier 2.05: Method Chaining
==========================

The design pattern of **Method Chaining** (aka. named parameter idiom) allows you to chain multiple methods calls to configure or specialize 1 or more objects. This is done by implementing the methods to return their "this" object reference so it may be used by the next call in the chain.

**Example**: Method Chaining
```
struct GUIIcon : GUIElement  // (extra) Inheritance used here, see 3.09 for more details.
{
    GUIIcon& SetSize(int x, int y);
    GUIIcon& SetDepth(int z);
    GUIIcon& SetIcon(const string& iconName);
    GUIIcon& SetColor(int red, int green, int blue);
    GUIIcon& SetParent(GUIElement& parent);
    ...
}

GUIcon CreatePlayMovieIcon()
{
    GUIIcon icon;
    
    // Chain method calls to cusomize icon
    icon.SetSize(150,100)
        .SetDepth(1)
        .SetIcon("PlayMovie")
        .SetColor(255, 255, 255);
    return icon;
}

void CreateMenu()
{
    ...
    GUIIcon icon = CreatePlayMovieIcon();
    icon.SetParent(menuPanel);
    ...
}
```

(extra): In combination with virtual methods and inheritance this can provide a lot of customizability and code reuse for simple independent configurations and is often used for highly configurable objects such a GUI.

Tier 3.00: defer
================
defer takes an expression or scope and executes it when the scope it is declared in ends. This happens in reverse order the defer statements appear in the scope.

**Example**: Order explanation
```
{
  defer print(3);
  defer { print(1); print(2); }
  print(7);              // prints 7
}                        // end of scope. prints: 7123
```
**Example**: Common use case
```
{
  thing1 = CreateThing();
  defer DestroyThing(thing1);
  ...                    // Code uses thing1, lots of code.
}                        // thing1 is destroyed here after use.
```
(extra) defer can greatly reduce code complexity of a loop that uses "break" or "continue" and improve code legibility of large functions.

Tier 3.01: Polymorphism
=======================
Polymorphism is a catch-all term and can be broken down into compile-time (often zero-cost) and runtime (cheap) abstractions. Polymorphism, in general, is about changing forms/shapes to meet the needs of the program. It is worth noting that how these concepts work is highly language dependent.

Compile-time Polymorphism: The addition, removal, modification, and generation of code and data at compile-time in a way that permutes the existing code of the program.

Runtime Polymorphism: hidden or inaccessible data added to the program which direct's program control at runtime.

Tier 3.02: Generics
===================
Generics (aka templates) are a compile-time polymorphism language feature which allows a collection of code to specialize on a type and/or value. When specializing on a type it may have requirements (aka concepts) on its operations. When specializing on a value it must be of a specific type.

**Example**: function specialize on type
```
The function Add is a polymorphic function which is specialized on a given type T. A requirement of T is that it supports the binary '+' Operator.

T Add<T>(T in0, T in1, T in2)
{
  return in0 + in1 + in2;
}
```
Specialization by type at call site:
```
Add(1,2,3);             // specialize to integers, returns 6
Add(1.5, 2.5, 3.5);     // specialize to floats, returns 7.5
Add("I", "Love", "U\n");// specialize to strings, returns "ILoveU\n"
```
(extra) Often generics will let you specify the type explicitly at the call site to avoid ambiguity and for certain type conversions.

**Example**: struct specialize on value
```
struct LeatherPouch<int CoinSlots, int ItemSlots>
{
  CoinType coins[CoinSlots];
  Item items[ItemSlots];
}
```
Specialization by value at instantiation:
```
LeatherPouch<3,1> pouch;         // pouch is a value of type LeathPouch<3,1>
pouch.coins[2] = CoinType.Gold;  // we can access the last coin and make it gold
pouch.items[0] = MakeSwordItem();// Only 1 item, lets make it a sword.
```
(extra) It is important to note, that struct specialization creates a new type per set of specialization values and/or types.

Tier 3.03: Macros
=================
Macros range in functionality between languages, but effectively give the programmer compile-time methods to add, remove, generate code depending on values and/or types. Macros, in general, stamp copy-paste of code with varying degrees of intelligence.

**Example**: Add/Remove code using pre-processor blocks
```
#define USE_HARDWARE

#if defined(USE_HARDWARE)  // USE_HARDWARE is defined above, so this is true
...                        // Code will be compiled and run
#else                    
...                        // Code will not be compiled or run.
#endif                     // end point for #if's #else
```
(extra) This sort of logic is common to support building a program on multiple platforms. In a Linux build, any windows code would fail to compile and vise versus on windows build.

**Example**: Generating code
```
'\'  continues the macro onto the next line
'#'  Stringify turns the macro into a string.
'##' Concatenates the left and right names into a single name.

#define ValueType(type, valueName)                \ // define takes text type, and valueName
type valueName;                                   \
string valueName##GetName() { return #valueName; }\ // generate a function to get the valueName's name as a string
int valueName##GetSize() { return sizeof(type); } \ // generate a function to get the valueName's size in bytes.
int valueName##GetOffset() { return &((this^this)->valueName); } // generate a function to get the valueName's offset into the structure in bytes. This assumes ValueType is used inside a struct.
```
This macro means the use of ValueType(int, MyInt) will unroll to generate:
```
int MyInt;
string MyIntGetName() { return "MyInt"; }
int MyIntGetSize() { return sizeof(int); }
int MyIntGetOffset() { return &((this^this)->MyInt); }
```
Code generation usage:
```
struct Character
{
  ValueType(int, health)
  ValueType(int, energy);
  ValueType(StatusFlags, status);
}
```
(extra) This example shows how to create some meta-data (information about the data) that may help in a variety of tasks such as serialization, data layouts, profiling, and more depending on your needs. In general, macros are a great way to generate simple code but are very bad at generating complex code.

@TODO @INCOMPLETE investigate macros in rust/D and see if I should add a section here to talk about their particular varieties.

Tier 3.04: String Compilation
=============================
You may generate a string programmatically at compile-time that is then compiled into the program's runtime. This is extremely flexible and a relative niche language feature and sometimes is a special compiler feature.

Tier 3.05: Tags
===============
You may mark parts or sections of our code with tags (aka attributes, notes) which are then passed to a compile-time program that can generate and/or modify the tagged function. This often supports string compilation but also grants access to the compiler's internal abstract syntax tree for the purpose of code injection.

**Example**: tags for targeted profiling
```
void foo()  // function foo
{
  ...
} @profile  // tags this function with the profile tag
```
A compile-time program may then add some logic the beginning and end of every function tagged with "profile" to record how long they took.

**Example**: tags for meta-data creation
```
struct Mage
{
  ...         // Lots of data we want to serialize
}; @Serialize // tag this struct with the serialize tag
```
A compile-time program may then add some logic to the serialization system to allow for loading and saving of the Mage struct to file.

(extra) One advantage of using a compile-time program to make meta-data over a macro is that you may recurse through sub-elements of the struct and even through pointer values. Macros are very simple copy and paste sorts of operations, but a tag may include a meta program of arbitrary complexity.

Tier 3.06: Any Pointer
======================
The Any Pointer is a runtime polymorphic type which can point to any type. @See Types.md for more details.

**Example**:
```
void print(AnyPointer any)
{
  switch(any.GetTypeId())
  {
    case typeid(int):   printInteger(any.GetPointer()); break;
    case typeid(float): printFloat(any.GetPointer()); break;
    case typeid(string):printString(any.GetPointer()); break;  
  }
}
```
Tier 3.07: Sum Type
===================
The Sum Type (aka variant, Tagged union, duck typing) is a fixed sized runtime polymorphic type which stores 1 or more possible types at a time.

**Example**: Variant containing a string or integer value
```
Variant<int, string> value = 1; // value is set to an int of value 1
value = "Hi!\n";                // value is set to a string of value "Hi!\n"
```
(extra) size of value's type is fixed and is equal to the hidden data plus the max size of int, and string.

Branching based on contents:
```
if(value.IsType(int))
{ ... }                     // execute this code when value is an int type
else if(value.IsType(string))
{ ... }                     // execute this code when value is a string type
```
(extra) Python is a duck typed language which heavily revolves around this idea of interchangeability. However, unlike above, Python hides all of the checks it does to ensure the correct operations are executed.

Tier 3.08: Dynamically Sized Types
==================================
There are a variety of instances whereby the size of a type is not known at compile-time and its size is dynamically calculated at runtime. The array/vector container is one such type whose size is variable depending on the count of items it contains. This becomes more interesting when the concept is applied to a type with both compile-time known size and also logically contains dynamically sized types.

**Example**: 2 allocation vector vs 1 allocation vector

2 allocation vector: Allocate memory to store TwoAllocArray struct. Then allocate memory to store the items in a separate buffer.
```
struct TwoAllocVector
{
  u32 size;             // number of items in the vector
  u32 capacity;         // total capacity of vector
  u8* itemBuffer;       // pointer to buffer in which the items are stored
}
// sizeof(TwoAllocVector) = 32 + 32 + 64 = 128 bits
// sizeof(*itemBuffer) = capacity * itemSize = run-time size
```

1 allocation vector: Allocate memory to store TwoAllocArray struct + (capacity * sizeof(item)).
```
struct OneAllocVector
{
  u32 size;             // number of items in the vector
  u32 capacity;         // total capacity of vector
  u8 itemBuffer[0];     // vector of 0 size simply gives us a pointer to the memory directly after the "capacity" variable.
}
// sizeof(OneAllocVector) = 32 + 32 + (capacity * itemSize) = run-time size
```
(extra) Often the two allocation array/vector design is favored because pointers to the vector are not invalidated when the vector is grown in capacity.

(extra) Often the one allocation array/vector design is favored when the capacity does not grow. The 1 allocation dynamic array/vector is going to be much faster because of CPU cache and the additional allocation costs.

Teir 3.09: Inheritance
======================
When a struct (aka class/object) inherits another struct it includes its functions (public and all of its data at the beginning of struct's data region. This allows the inherited struct to operate independently within the struct which inherited it. The struct we inherit is called our base-class (aka parent) while we become the derived-class (aka super, child).

One of the ramifications of including the base class's public functions is that it may be overridden by the base class.

**Example**: inheritance function overridden
```
struct BaseClass
{
  void foo() { print("BaseClass,"); }
}
struct SuperClass : public BaseClass // publically inheret BaseClass
{
  void foo() { print("SuperClass,"); }
}

void example()
{
  SuperClass superClass;
  
  BaseClass* pBaseClass = &superClass;
  SuperClass* pSuperClass = &superClass;
  
  pBaseClass->foo();   
  pSuperClass->foo();
  superClass.foo();
}
```
example() prints: BaseClass,SuperClass,SuperClass,

By the type we use to call foo, this is what chooses the function.

(extra) Function overriding is a zero-cost compile-time choice.

Tier 3.10: Interface
====================
In the inheritance example above, we see that we use the type we called foo from to choose which function to call when the derived-class overrides a base class's function. An interface is a way to ensure that the derived-class overrides 1 or more functions and upon calling the function from a pointer to the base-class we will choose the derived class's function.

Most interface implementations cannot have any data of their own.

**Example**:
```
interface Door // interface called Door
{
  void Open();  // interface requires derived-class to impliment Open
  void Close(); // interface requires derived-class to impliment Close
}
interface Powered
{
  void TogglePower(bool on); 
}

struct GarageDoor : Door, Powered // inherit interface: Door and Powered
{
  void Open() override { ... }
  void Close() override { ... }
  
  void TogglePower override (bool on) { ... }
}

void example()
{
  GarageDoor garageDoor;
  Door* door = garageDoor;
  Powerd* powered = garageDoor;
  
  door->Open();
  door->TogglePower(false);
}
```
(extra) the 'override' is likely optional, but it will give us a compile-time error if we are not overriding an interface/base-class with a virtual function.


Tier 3.11: Virtual
==================
Virtual is similar to an interface but more flexible toward struct composition (aka object composition, class composition). virtual is applied to individual functions within a struct and must provide a base implementation. It is not required that a derived-class write an override for a virtual function, but it may and will be called when appropriate. Also, you may have the base-class with virtual functions contain data.

**Example**: Garfield is a Cat which is an Animal
```
struct Animal
{
  int age;
  virtual void Eat() { print("Eat | "); }     // must provide base implimentation
  virtual void Sleep() { print("Sleep | "); } // must provide base implimentation
}

struct Cat : public Animal
{
  int lives;
  virtual void Eat() override { print("Cat eat | "); }  // overrides Animal's Eat
}

struct Garfield : public Cat
{
  float obesityIndex;
  virtual void Sleep() override { print("Garfield sleep | "); } // overrides's Animal's Sleep
}

void example()
{
  Animal animal;
  Cat cat;
  Garfield garfield;
  
  Animal* pAnimal0 = &animal;
  Animal* pAnimal1 = &cat;
  Animal* pAnimal2 = &garfield;
  
  pAnimal0->Eat();
  pAnimal0->Sleep();
  pAnimal1->Eat();
  pAnimal1->Sleep();
  pAnimal2->Eat();
  pAnimal2->Sleep();
}
```
example prints: Eat | Sleep | Cat eat | Sleep | Eat | Garfield sleep |

Tier 3.12: Event Systems (aka. message systems)
===============================================
Event systems are used to notify the program about specific events or triggers that have happened in the program. These notifications may be internal to the program, such as a shutdown message, or external, such as the OS indicating that the keyboard key 'K' was pressed. Event systems are extremely varied but have some common configurable segments of functionality which are described below. In general, all event systems basically call a function at a specific time. 

* A "listener" refers to a function and/or function and associated data (object) that logically "receives" the event.
* An "event type" refers to a specific event in the program (ie. Key Pressed, Mouse Moved) that may also relate to a specialized listener function signature.

- Signaling Models: How control is handed with respect to signaling the event.
  1) Broadcaster: The broadcasting event system has a list of listeners which will be called when events happen. This list may be static or dynamic with relation to the number of listeners but every listener function will be called when its corresponding event is triggered.
  2) Subscription: A subscription-based event system allows for listeners to connect and disconnect from events dynamically irrespective of the listener's lifespan in the program.
- Subscription-based specific features:
  1) Auto Disconnect: It may be difficult to reason the lifespan of a listener in memory so many subscription-based event systems are integrated into a general object model for listeners by which the lifespan is understood by the greater system. By using this object model we can automatically disconnect listeners from the event system when their associated object's lifespan ends.
- Data Transfer Methods: The method by which the information is transferred to the called function. It is common to see both static and dynamic polymorphism used to disseminate the data to the listener.
  1) Pure Callbacks: The listening function's signature contains all information or references to the information sent by the event system.
  2) Global or Thread Local Storage: The listener function is expected to access some global or thread local storage to access the data of the event.
- Event Designation: Event systems may send hundreds of event types to thousands of listeners so we employ a variety of techniques to distinguish between event types with the event system.
  1) Data-driven/Runtime Designations: Different events often employ different input types/data so data-driven event systems often employ runtime polymorphism to call listeners.
      * Integer/Enum-based: Each event type has an associated integer value which is used to lookup listeners and send the data to the listeners.
     * String-based: Each event type correlates to a logical string of characters (ie. "KeyPressed" string may correlate to a key pressed event type). (extra) String-based event systems are slow, but may employ compile-time optimizations such as pre-computed string hashing or pre-generated string->integer mapping which may improve performance up to the performance of integer-based implementations.
  2) Static/Compile-time Designations: The distinction between event types is baked into the program's executable. These systems are often implemented using compile-time polymorphism for each event type.
      * Type-based: A user-defined type directly or indirectly maps to an event type. Everything from the generated event system code to the listener's function signature is derived from the type.
      * Tag-based: The event type is based on compile-time tag attributed to the listener's functions. (extra) This idea is common for user commands which take various inputs in count and type.
      * Declarative-based: Listeners are called based on their name and signature. (extra) This is similar to how the entry point of a program is called (ie. main() is a special function because of its name and signature).
  3) Hybrid Designation: Event systems uses both compile-time and data-driven configurations for various aspects of the whole system. Most mature event systems utilize a mixed approach because of the limitations of each.
      * Data-driven limitations: For events which must send millions of times per second or send to millions of listeners the performance characteristics are significant so using a compile-time system with potentially zero-cost is ideal.
      * Compile-time limitations: Adding additional events require recompiling the executable which may take hours and does not allow for runtime generation of events.
- Advanced features:
  1) Delayed Send: The event system may allow an event to be triggered than then delay some amount of time before the listeners are called.
  2) Disable Event: Events may be disabled, preventing all listeners from receiving the event even if it would otherwise be triggered.
  2) Consume/Handle: A listener may consume/handle an event such that the triggered event will stop calling any further listeners. Consume may be implemented as a counter or objective list such that multiple listeners may contribute to handling the event.
  3) Event Propagation: Events may be sent abstractly to a group or groups of listeners which related to one another. Example object relationships:
  * Listener Hierarchies Propagation: Trigger an event to listeners based on a logical relationship
    * SendUp: Send an event to all parents from a listener node (may include the node).
    * SendDown: Send an event to all children of a node (may include the node).
    * SendToAll: Send an event to all connected objects in the tree or graph. (may include the node)
  * Spacial Propagation: Trigger an event to listeners based on a 2D/3D spacial relationship.
    * SendRaycast: Any listener whose's geometry intersects the cast ray receives an event
    * SendBoundingArea/volume: Any listeners enclosed or outside the area/volume receives an event
    * Collision Detection: A physics simulation may send an event to notify an object/listener it has collided with another physics object.
  * Inheritance Propagation: Inheritance hierarchies may employ specialize event propagation to base-class or derived-class depending on their needs.
  4) Retransmission: A listener may repackage or retransmitted a received event to another listener. Some event systems may restrict this feature to allow for certain threading optimizations.

Tier 3.13: Action System
========================
An action system is similar to an animation system for programmers. Its functionality resembles that of an event system, state machine, and animation suite wrapped into one. An action system creates a sequence. This sequence is a queue of actions which then execute concurrently (usually sequential execution) to modify data. A sequence may "sync" such that all previous actions in the queue must finish before any newly added actions are executed.

Common action system features:
 * Property: Interpolate a value from its initial value to a final over a period of time. The scope of change between initial and final value is often defined by an ease function or user-generated point graph.
 * Delay: Creates an action which waits a specified period of time to complete.
 * Call: Call a given function once.
 * CallTillSync: call a given function each update until the next sync point.
 * Sync: Delimits the end of an execution queue. (ie. All previously given actions must be completed before any future actions beyond this point will execute).
 
Tier 4.00: Execution Stack
==========================
The stack refers to a block of memory that is used during execution to store local variables and return addresses all calls. A stack's size can range from a few hundred bytes to dynamically expanding to infinite size depending on your environment.

The main thread (the execution line which calls the entry point) has a stack whose properties are often defined by the compiler.

(extra) On modern CPU's the stack's memory is often a block of contiguous memory in RAM. Nothing special about it aside from its purpose.

Teir 4.01: Long Jump
====================
A long jump is a way to jump between functions. Long jump, unlike jumps with labels, uses memory to store the location in code and is stored as a variable. Upon jumping into the other function, often we get a value to make a choice.

**Example**:
```
jmp_buf env;

void Juggle()
{
  ...
  longjmp(env, 1);  // long jump where env was set, return 1
}
void Dance()
{
  ...
  longjmp(env, 2);  // long jump where env was set, return 2
}
void Sing()
{
  ...
  longjmp(env, 0);  // long jump where env was set, return 0
}

int main()     // Juggle, Dance, and Sing forever
{
  switch(setjmp(env))
  {
    case 2: Sing();
    case 1: Dance();
    case 0: Juggle(); // start case, repeats
  }
  return 0;
}
```
The return of setjmp when first called is always 0, but when it returns as a result of the longjump in Juggle, Dance, and Sing it will return other values.

(extra) longjump should be avoided when possible because it increases code complexity and is not commonly used.


Tier 4.02: Coroutine
====================
A coroutine is a mechanism to run one or more sets of code in a multi-task single line of execution. This works by assigning each task its own mini-stack and jumping between stacks and functions once a task is ready to yield to another. This is useful for when you have many tasks which require you to wait between usage. Common examples include file I/O, Networking, and device polling.

* May be used for creating generator design patterns.
* Provides some of the functionality of multi-threading without needing multiples lines of execution.
* Implementations may provide quicker context switches then threads. See Fibers @Tier 4.10.

If your language supports long Jump, then it is likely that you could implement a coroutine to multi-task on a single line of execution.

Teir 4.03: Thread
=================
A thread is a logical line of execution which may run concurrently with other threads. Threads do not have any implicit ordering (ie. If we start thread 1 and then start thread 2, there is no guarantee that 1 will start before 2).

Thread Properties:
- Priority: Low, Normal, High, Urgent, Highest priorities are used to loosely inform ordering between threads. Often the highest priority thread will run first till it sleeps before lower priority threads run when the CPU has extra time.
- CPU Affinity: Choose which CPU's core you would like the thread to run on.
- Mode (user, kernel, other): The mode of the thread enforces certain rules and behavior on execution (e.x. user/application mode cannot access other application's memory).
- Joinable: Joining is when another thread waits on the completion (i.e. return from the thread's entry point) of another thread and may be enabled/disabled at the threads creation.

Threads often have the following data which could prove useful to programmers. Reading from memory that has 1 or more other threads writing to it creates undefined behavior and requires synchronization for reliable access.
- Thread id: An integer number to uniquely identify the thread.
- thread name: A string which can often be customized to indicate the thread's purpose
- thread state: The current state of the thread (Wait, Sleep, running, etc...)

(extra) A "fiber" is a lightweight thread with all of its resources at the application level.

Tier 4.04: Threads and data
===========================
threads may run different hardware threads, cores, or even CPUs all of which may have access to different copies of the same memory. This means that an operation taken on the same memory address may not be correctly applied if done from multiple threads simultaneously.

**Example**: 
```
void example()        // called by multiple thread simultaniously
{
  for(1..100)
    g_intValue += 1;
}
```
We have a global integer which is incremented by 2 threads at the same time. If g_intValue starts at 0 you may expect the end value would be 200, but in reality, it is undefined behavior and will likely be 100 <= number <= 200. This is because the most CPU instructions to not take the most recent value from memory, but use a local copy stored in a register or the CPU cache which gets written back to memory at a later time.

Tier 4.05: Mutex (aka. critical section)
========================================
A mutex is a thread synchronization mechanism.

Mutex functionality:
- Lock: Locks the mutex so that any other thread who attempts to lock it will wait until this thread has unlocked.
- Unlock: Unlocks the mutex awaking any other threads waiting on it.
- Try Lock: Try and lock the mutex, but do not wait if the lock cannot be acquired.

Mutex properties:
Ownership: While a mutex is locked it may only be unlocked by the thread which owns it.
Recursive: A mutex may be recursive which allows a single thread to lock the same mutex multiple times.
Lock Level: A mutex may allow a maximum recursion lock level which will error if the repeat lock count exceeds a certain count.

**Example**:
```
void example0()   // called by many threads
{
  dataMutex.Lock();
  ...                // code will not be execuded by any other thread (aka. critical section)
  dataMutex.Unlock();
}

void example1()   // called by many threads
{
  dataMutex.Lock();
  ...                // code will not be execuded by any other thread (aka. critical section)
  dataMutex.Unlock();
}
```
The code in example0 and example1 have their access patterns are synchronized because only 1 may be changing the data between the Lock/Unlock pair. Mutex's guarantee all accessed memory from a thread will be completely written to memory by the time another thread has acquired the lock.

Tier 4.06: Spinlock (aka: Mutex)
================================
A spinlock is a mutex which does not yield to the OS's execution in a sleep/wait routine when the lock cannot be acquired but instead attempts repeatedly to acquire the mutex in the loop. The loop may run millions of times and often have a timeout feature. A spinlock implementation may be the same as a mutex but include the added functionality to TryLock in a loop. 

Tier 4.07: Semephore
====================
A semaphore is a thread synchronization mechanism. It is often used in combination with a mutex. The semaphore's counter

Semaphore functionality:
- Acquire: When a counter is non-zero, decrement the semaphore's counter, otherwise wait.
- Release: Increment the semaphore counter.

Semaphore properties:
Ownerless: A semaphore is ownerless and can be acquired/released by any thread.
Counter: A semaphore has a given start counter which can be set to any number.

(extra) A semaphore is called "binary semaphore" when its counter is 1. This makes it very similar to a mutex, except that any thread may release the semaphore which would be an illegal operation on a mutex.

**Example**:
```
void exampleStartDoingWork()    // may be called by many threads, but supports a maximum of workerSemephore's counter.
{
  workerSemephore.Aquire();  // Ensure our thread is not above max supported.
  
  {                       // Get some work to do
    workMutex.Lock();     // ClaimWork requires we hold this lock. (often inside ClaimWork)
    ClaimWork();          // Claim some work to do.
    workMutex.Unlock();   // Unlock lets other threads ClaimWork
  }
  
  CompleteClaimedWork();      // Do given work, keep workspace
  workerSemephore.Release();
}
```
Tier 4.08: Conditional Variable
===============================
A conditional variable (CV) is a thread synchronization mechanism which wraps around a mutex to provide signaling to other threads.

Conditional Variable functionality:
- WaitOnCV: Wait for another thread to signal the conditional variable, often has an optional timeout.
- NotifyCV: If a thread is waiting on the CV, signal it to start in a first in first out order.
- NotifyCVAll: Any threads waiting on the CV are signaled to start.

Conditional Variable Properties:
- WaitOnCV requires that we first hold the CV's associated mutex. Upon waiting we also atomically unlock the mutex. Upon waking we try an lock the associated mutex.
- NotifyCV AND NotifyCVAll require that we first hold the CV's associated mutex.

**Example**: In the example below, all CVs share 1 mutex
```
int g_waiters = 0;                         // writing to g_waiters is protected by the cvMutex
void exampleWait(ConditionalVariable& cv)
{
  cvMutex.Lock();
  g_waiters += 1;
  cv.WaitOnCV();
  g_waiters -= 1;
  cvMutex.Unlock();
}

void exampleNotify(ConditionalVariable& cv)
{
  while(g_waiters < 5) { } // do nothing (spin) untill we have 5 or more threads waiting on the CV
  
  cvMutex.Lock()         // Lock the shared mutex
  for(1..5)              // Iterate 5 times.
    cv.NotifyCV();       // notify thread to wake up.
  cvMutex.Unlock();      // threads have been signaled, let them lock the mutex to finish waking up.
}
```
Tier 4.09: Atomics
==================
Atomics are a handful of fast-ish operations which are synchronized across threads. This parallel programming paradigm is called wait-free, but ironically can be slower than the other mechanisms above. It can be slower because in general, it works by allowing 1 thread to make progress while the others deal with the fallout.

**Example**: Common atomic operations (all if this can be emulated with a mutex which is how some libraries get around lacking CPU support)
```
Name             Description (All atomic operations)
Increment        Increment an integer value.
Decrement        Decrement an integer value.
Add              Add 2 integers and store the result.
Subtract         Subtract an integer from another and store the result. 
Bit-wise AND     bit-wise AND 2 integers and store the result
Bit-wise OR      bit-wise OR 2 integers and store the result
```

@Incomplete
CompareAndExchangeWeak
CompareAndExchangeStrong

Tier 4.10: Threading Models
===========================

Multitasking is when you have multiple tasks being executed concurrently (ie. threads, processes). 
- **Cooperative** multitasking refers to a threading model in which a process/thread chooses when to yield to other processes.
- **Preemptive** multitasking refers to a threading model in which a process/thread may be interrupted at any time by the operating system.

Almost all modern operating systems use a preemptive multitasking for their applications.

(extra) A fibers is a light weight thread in terms of system resources and may implement cooperative multitasking at the user-level.

Teir 4.11: Job System
=====================
A Job system is a formal way to manage thread execution such that minimal synchronization is needed. These are often in well-defined software whereby much of the functionality can be broken into meaningful blocks.

**Example**: Simple Game Engine Job system

The blocks below do not need to synchronize with each other but may depend on data from a previous task. For example, the Input Manager must run before Gameplay Logic, so we run the Network Tick and Graphics Post Process while we get the Input Manager run. Often this job system is dynamically generated via a dependency graph made by a programmer and recorded times for how long

Job System
```
Timeline(ms)0---------1---------2---------3---------4---------5---------6--------7---...
Thread 1:   |Network Tick|Physics|Gameplay Logic|Network Tick|Physics|Gameplay Logic|...
Thread 2:   |Graphics Pump|Graphics Post Process|Graphics Pump|Graphics Post Process|...
Thread 3:   |Input Manager|Audio Pump|----------|Input Manager|Audio Pump|----------|...
Thread 4:   |~~~~~~~~~~~~~~~~~~~~~~Background file I/O~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~...
```
(extra) Game Engine job systems may work on multiple frame's worths of tasks simultaneously to maximize the throughput of the hardware. This adds additional latency from the user's input, but better utilizes the CPU and often GPU's performance characteristics.

Tier 5.00: Inter Process communication (IPC)  @TODO @TODO @Incomplete
============================================
Inter process communication is the process of programs communicating with eachother through vaious means.

Signals/Messages: See signal.h C file
Pipes: stdin, stdout, FILE *
Shared Memory: Memory Mapping between processes

Tier 5.01: Mutex Hierarchical (Architecture)
============================================
A mutex which is used to synchronize an object and all of its sub-objects' memory. This tecnhique is often used with containers and systems which need to be thread-safe. A condiquence of this technique is that all other threads which try to use this container or system are blocked and must wait.

**Example**: Example Network Client ManagerSystem

We see the following example which is a network client manager system which can add clients and initialize their state. To do this we need to first synchronize the Client Manager to add the client. Then we must Initialize the sub-objects. 

By locking the Manager we ensure we can Add or Remove clients.
By locking the Client we ensure we can initialize, modify, or finalize the client's state
```
(#) '#' Refers to the order of evaluation within the function

Lock    - Lock mutex held by the object
Unlock  - Unlock mutex held by the object
Add     - Add the client object into the Client Manager System making it reachable by other threads.
Remove  - Remove the client object from the Client Manager System making it unreachable by other threads.
Setup   - Initalize the object's state
Clean   - Cleanup state or other resources associated with object


ManagerSetupClient() Calls    |    AddClient()  |  SetupClient()   |
------------------------------+-----------------+------------------+
Client Manager Sustem (Mutex) |(1)Lock (4)Unlock|                  |
Client Object (Mutex)         |(2)Add  (3)Lock  |(1)Setup (3)Unlock|
Client Resources              |                 |(2)Setup          |
------------------------------+-----------------+------------------+


ManagerDestroyClient() Calls  |  RemoveClient()   | CleanupClient()  |
------------------------------+-------------------+------------------+
Client Manager Sustem (Mutex) |(1)Lock   (3)Unlock|                  |
Client Object (Mutex)         |(2)Remove (4)Lock  |(2)Clean (3)Unlock|
Client Resources              |                   |(1)Clean          |
------------------------------+-------------------+------------------+		
```

With a hierarchical design we can not only ensure sychronization but with careful design can ensure that higher level locks may be released while the child objects are still locked. In the example above this means that even if ```Init()``` takes a long time to complete other threads may use the Client Manager Sustem while work is being done. If they attempt to access the newly created client they will have to wait, but for all other clients they can continue running.

(extra) In the example above you MUST be careful on the order in which you lock/unlock because improper lock/unlock order may lead to a deadlock. 
(extra) A good thought experiment for the example above to think about what should happen when the Setup step fails.



Tier 5.02: Mapped Mutexes and Mapped Mutex Arrays (Optimization)
============================================
Most use cases for mutexes are what I'd call a **mapped mutex**. This means a mutex is maped to a section of memory that it is synchronizing across threads. A mutex may be maped to one or more sections of memory that you wish to synchronize. The relationship between a mutex and its synchronized memory is deterministic and is simply an offset or a pointer usually.

A **mapped mutex array** specifically refers to a memory optimization for a large number of objects that you wish to synchronize across mulitple threads. This optimization has an object keep a semi-random key or index to reference into an array of mutexes. This results in any mutex in the array synchronizing multiple objects simultaniously as it is locked/unlocked reguardless of if the locking thread is accessing all of the objects. The downside to this optimization is when a thread is mistakenly blocked because the keys map to the same mutex in the array. This leads to a probabalistic collision which is related to the number of threads simultaniously running. This means an optimal mapped mutex array size is proportional to the number of simultaneously running threads times the number of mutexes each thread holds and NOT the number of objects that could be synchronized.

Semi-random key or index
- Every object holds a random index into the mapped mutex array. (costs a little more memory)
- Every object uses its memory address which is then hashed to get an index. Since memory addresses are unique and have a massive range, using fibbonacci hash isn't uncommon.

(extra) In the case in which some objects are locked more often than others (ie non-uniform distribution of work) and that you've choosen to have every object hold a random index there is an additional optimization you may apply which dynamically changes the index of an object upon unlocking the mutex depending on its use.
- Add a count of the number of times each mutex is locked and the total number of mutexes locked in the array.
- Logic Changes:
-- Pre-Unlock: Determine if our mutex's lock count is above the average. If it's CF above the average, we semi-randomly select another index that is less than the average number of locks and set that as our index.
-- Pre-Lock: Store the current index value
-- Post-Lock: Check for a changed index value. If changed unlock and lock the new index else increment mutex lock count and total mapped mutex array count.

CorrectionFraction(CF): Ideal value will depend on your access patterns and thread count. Maybe 1/3?
 
Tier 5.03: Reader-writer locks (aka rwlock, reader-writer mutex)
============================================
A reader-writer lock is a specialized implimentation of a mutex which allows the locking thread to specify if it intends to read or write to the memory protected by the mutex. Most OS/CPUs support multple threads to read from the same address in memory in parralell and at less than or equal to cost the cost of a serial read. In contrast it is expensive for most CPU's to synchronize a write across multiple threads and may result in CPU stalls and/or write failures depending the CPU/OS architecture. This type of mutex is highly valued in the case that a mutex's protected memory is read frequently and written to infrequently.

**Example**: Reader-writer mutex

We can see below an example of 4 threads using a reader-writer lock. The readers may all read in parralell while the writers work in serial.
```
LR = Lock as reader
UR = Unlock as reader
R = Reading (lock held)
LW = Lock as writer
UW = Unlock as writer
W = Writing (lock held)

Time              0   1   2   3   4   5   6   7   8   9  10  11
------------------+---+---+---+---+---+---+---+---+---+---+---+     
rwlock Mode       |   |LR |LR |LR |   |LW |LW |LW |LW |LW |LW |
Thread 0 lock for |LR |R  |R  |UR |LW |LW |LW |LW |W  |UW |UW |
Thread 1 lock for |   |LR |R  |UR |   |   |   |   |   |   |   |
Thread 2 lock for |   |LR |R  |UR |   |   |   |   |   |   |   |
Thread 3 lock for |   |LW |LW |LW |LW |W  |W  |UW |   |   |   |
------------------+---+---+---+---+---+---+---+---+---+---+---+
```

(extra) Programming flow is counter intuative and before implimenting a reader-write mutex the program should be instumented to see the ratio of read to writes. The ratio at which the performance of a reader-writer mutex and a normal mutex intersect is highly dependent on their implimentations.


# Incomplete
#1
#2
#3
 
@Exceptions & Exception Handling
@Regex Search Format

#4

@Promise/Future & Async compute model
@Futex (https://en.wikipedia.org/wiki/Futex) (Performant on low contention locks)
@Thin lock                                   (Performant on high contention locks)


#5
@Program wide Signals (kill) See signal.h C header file for API details
@Generator/stream & Consumer model
@Errno messaging model


#6
@Lazy Linkage <--- I think this should go somewhere else, not sure where though...
@Hazard Pointer <- very specific technique. Maybe move it into technique.txt if we ever make that