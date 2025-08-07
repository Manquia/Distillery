This page is focused on useful development practices that may help you create better programs.

Tier 2.00: Logs
============================================

For any large program it can be useful to log out text or other information for later reading. This can inform you of the order in which your program executed or, in most useful cases, failed to execute.

Example: Consider a program that connects to a server when running and how at any point the network connection might fail. Having a log to indicate a loss of signal can help a programer identify how a program reached a specific state.

A good logging system may incorperate verbosity levels which can be used to filter out certain types of messages.

Usual verbosity levels:
* Verbosity_Log: Record order of program execution, expected behavoir.
* Verbosity_Warning: Record order of program execution, handled, but non-standard behavoir.
* Verbosity_Error: Unhandled or exceptional behavoir that will dramatically change the program behavoir.

**Example Log**: Expected behavoir
```
Initialized graphics system
Connected to home server at 192.168.0.1:9001
All assets loaded.
Starting simulation.
```

**Example Warning**: Non-standard, but recoverable.
```
Failed to connect with home server at 192.168.0.1:9001.
Audio thread sample queue was empty, audio blip possible.
Failed to compile shader "Shaders/RopeParticle.glsl" using default fallback.
```

**Example Error**: No easy recovery path. Program might be terminated or paused.
```
Entity sytem block allocation failed!
OS Thread for task "UpdateParticles" failed to start.
Level file "Levels/MainGameplay.lvl" contained invalid format.
```

In large programs, especially if multi-threaded or multi-process, additional general information is often added to add clarity on the order, log operating thread, and context.

**Example**: Detailed log file
```
Format:
[sec:ms:us, Filename:lineNumber] Verbosity_Type: Message

Sample log file:

...
[1923:030:542, connection.c:1924] Warning: Connection with server time out.
[1923:039:145, connection.c:2150] Log: Attempting to connect with server 192.168.0.1
[1928:001:642, packet.c:643] Error: Message block allocator out of memory.
[1928:005:132, error.c:241] Error: System memory access violation at 0x00000004.
[1928:006:533, error.c:245] Log: Freezing all threads.
[1928:008:754, error.c:257] Log: Attempting graceful shutdown.
[1928:101:155, init.c:530] Log: Program shutdown complete
```

**Additional logging tricks**

* Push and pop tabs or insert arrow tokens to visually group blocks of log statements together.
**Example**: Level startup
```
Starting Level "DarkLevel0.lvl"
  Loading Assets
    Sprites Loaded
    Meshes Loaded
    Sounds loaded
    Scripts loaded
  Asset Load complete
Level Started
```
**Example**: Data driven modular gameplay effect
```
Updating gameplay effect: Bomb Effect
  On Update
    Check Time: Loop 0.5s
      Spawn Object: Bomb Beep SFX
    Check Time: Single 10s
      Trigger Event: On Impact
  On Impact
    Effect Shape: Sphere
      Apply Impulse
      Apply Status: Frost
      Apply Damage: Type[Piercing, Frost]
    Spawn Object: Frost Bomb Explosion VFX
    Spawn Object: Frost Bomb Explosion SFX
    Destroy: Self
```

* Adding a thread number or thread name to logging help find issues whereby a thread is executing code erroneously.
**Example**:
```
Without thread names: Looks like player is randomly getting updated twice in a single frame.
[015:100]: Updating player movement
[015:120]: Updating player movement
[015:123]: Updating player movement
[015:140]: Updating player movement

With thread names: Very obvious the audio thread, perhaps a callback, is doing something wrong.
[TH:Game :015:100]: Updating player movement
[TH:Game :015:120]: Updating player movement
[TH:Audio:015:123]: Updating player movement
[TH:Game :015:140]: Updating player movement
```

* If a program uses extensive logging it might be useful to add categories that divide logging into specific domains or sections of the program.

Tier 2.01: Runtime Asserts
============================================
Asserts are runtime development build checks to ensure the program's state is valid. Asserts help programers make small and large changes to a program because these checks will alert the programer of any invalid state that is accidentally created.

Asserts are a development tool and are often partially or completly disabled in release/shipped builds of a program.

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