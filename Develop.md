#incomplete: This page is still under development and will reach a finer level of completion in the future.
This page is focused on learned about useful development practices that you will commonly see programs use.

Tier 2.00: Logs
============================================

- Information: File, Line, Module (if applicable), Timestamps (helps with I/O race conditions)
- Level: Logs, Warning, Errors
@Verbosity
@Examples

Tier 2.01: Asserts
============================================
Asserts are  runtime development build checks to ensure the program's state is valid. Asserts help programers make small and large changes to a program because these checks will alert the programer of any invalid state they accidentally created.

Asserts are a development tool. Asserts are often partially or completly disabled in release/shiped builds of a program.

Assert statement format:
```
Assert(condition : bool, ...)
``` 

* condition: When this expression evaluates to false, the program is terminated/paused for debugging.
* ...: Often asserts allow the user to input a print statement to inform other programmers why this condition must be true or possibly why it is not.


**Example**: Resource allocation check
```
entity = CreateEntity();
Assert(entity != nullptr, "Memory allocation failed");
```

**Example**: Valid program check
```
Assert(GetPlayerCount() <= 32, "Server is configured to handle no more than 32 clients: %d clients found", GetPlayerCount());
```

**Example**: Deprecated code
```
Assert(false, "This code is deprecated. Go use the newer FroAudioSys.");
```

**Example**: Control flow not implimented
```
switch(code)
{
    case MagicNumber:
    ...
    default: // unhandled cases
    Assert(false, "New code case not handled (code: %d)", code);
}
```


Tier 2.02: Text Searching
============================================
When writing code it is importatn to take into accout how easily veriables or types can be found via text searches. This is important for future development as other developers may need to find all instances of a function call or must verify specific facets of it's usage.

Consider the following code which impliments an object Reflector with several methods. In this example we want to be able to find all instinces of the execute.

**Example**: 
* Variable names are not preditable
* Function/Method names cannot be easily found.
```
using namespace Meta; // Pulls in the Meta namespace
void Format1()
{
    Reflector myR;
    myR.push(...);   // Push an item to be reflected
    myR();           // execute the reflector using "operator ()"
}
```

If you were doing a search through all files it would be very hard to track down all the instances where the "operator ()" is called since that operator is used in a lot of syntax. There is also the issue that the variable names are not predictable or easy to find. In a more complicated piece of code you might elaborate on which Reflector this varible is refering, but when it's simple it is best to use a predictable name. 

For the purposes of comparison see the code below which has been reformated to be more easily searched.

**Example**: 
* Variable names are simple/predictable.
* Function/Method names are uniquely searchable.
```
void Format1()
{
    Meta::Reflector reflector;
    Meta::PushReflectorItem(&reflector);
    Meta::ExecuteReflector(&reflector);
}
```

This example remove the using namespace which will remove some possible text name collisons between other "Reflector" names. By changing the name to reflector it becomes a more predictable name and since it's a simple function there is not any lost meaning. By adding formal function names for "PushReflectorItem" and "ExecuteReflector" we have further increased the ability for this function to be found by future developers. You will also note that the comments are redundent since the function names help document what is happening.

Note:

I am not recommending all code should be excessivly verbose and there is a place for short code. However, in the cases where you are calling into non-standard library functions it is important to consider how easily their names may be found via text search.


@TODO 


@Test Searching
 * Wild Card "*"
 * Searchable Identifiers
 

#Incomplete

#???? Develop.md <- Idea is to highlight Development practices that are high-value. Probably make this sometime in the future.



Tier 3.00: Static Asserts
============================================
Static Asserts are asserts that are evaluated at compile-time. They ensure that the compilation state matches what the programer expects. See @Develop.md Assert for more details.

Since Static Asserts are evaluated at compile-time the expression must not evaluated any non-constant variables.


**Example**: Assert type size
```
struct AllocationNode
{
    const int MaxHeaderSize = 8;
    struct DebugHeader
    {
        ...
    }
    
    static_assert(sizeof(DebugHeader) <= MaxHeaderSize, "Debug Header is too large.");
}
```



#2
 
@Instumentation Tips
 * Options, Logging, Overhead, Meaning

@Static Print
@Debugger: Breakpoints
@IDE

# 3

@Debugger: data breakpoint, Conditional breakpoint

# 4
@Build systems
  @Linker (C++ specific build tools)
  @Object Files (C/C++ specific, but this is semi common. We should look into this more to see if this is common in C#)
  @Maybe move The static library/DLL stuff from Memory.txt to this file. Not sure where to put library linking...
  
@Static Print

@Debugger:  Dynamic (programmer set) data breakpoints.
# 5


@Development Tips
 * Opinion Opinion Opinion