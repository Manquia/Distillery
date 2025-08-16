Summary
=======
Overview of intrinsic types and common user-types seen in computer programming.

Pre-Requisite: [Memory.md:1.XX](Memory.md)

Note: See [Containers.md](Containers.md) for collection types.

Tier 1.00: Integers (Signed and Unsigned)
=========================================
CPU hardware computes _integer_ values in binary (base 2). In order to represent negative _integers_, Two's Compliment is used.

Common intrinsic integer operations:

* '+' Addition       - Adds 2 signed or unsigned _integers_ together.
* '-' Subtraction    - Subracts 1 signed or unsigned _integer_ from another.
* '*' Multiplication - Multiply 2 signed or unsigned _integers_ together.
* '/' Division       - Divides 1 signed or unsigned _integer_ by another. The mathimatical floor is applied to the result.

Note: If an operations _integers'_ signed-ness does not match, usually the unsigned _integer_ will be converted to signed before doing the operation.

Note: Examples below use 8-bit _integers_, but also apply to 16, 32, 64, 128 bit signed/unsigned _integer_ types just add more value (V) bits.

_Integer_ Memory Layout:
```
S <- signed bit (most significant) determines if integer is positive or negative.
V <- value bit in base 2.

unsigned 8-bit integer: VVVVVVVV
signed 8-bit integer:   SVVVVVVV

8 bit unsigned integer examples: 00110110 = 54,   11111100 = 252
8-bit signed integer examples:   00110110 = 54,   11111100 = -4
```

Signed _integer's_ use Two's Compliment: If you want to invert the sign of an integer then you flip all bits and add 1.
```
2's compliment example: 54 = 00110110 -(flip bits)-> 11001001 -(add 1)-> 11001010 = -54
2's Compliment example: -4 = 11111100 -(flip bits)-> 00000011 -(add 1)-> 00000100 = 4
```

Teir 1.01: Floating Point/Real Numbers
======================================
Floating Point or Real numbers have a level of precision proportional to the bits in the format. This means the format has a limited precision based on the number of bits the format uses. For 32-bit IEEE floats the precision level is ~7 decimals (ie. 1.234567) near 0-1 values and gets progressivly worse as you increase in magnitude. This means that if we have a number which becomes more precise then 7 decimals during its calculation that precision will be lost when we store the number back into memory.

Examples will be for 32-bit IEEE floating point. Floating point numbers with 16-bit and 64-bit have different ratios for each secton but follow the same general guidelines.

 - S <- Signed bit (most significant). 0 = positive, 1 = negative.
 - E <- Exponent bits. An exponent of 0 is the value 127
 - F <- Fraction bits. Hold a fractional value based on bit position (ie. 1/2, 1/4, 1/8...)

32-bit IEEE floating point (single-precision floating-point format)
```
 S EEEEEEEE FFFFFFFFFFFFFFFFFFFFFFF
 ^ \      / \                     /
 | exponent  \______fraction_____/
 |
 Signed bit
 
value = (-1 * Signed bit) * (2^(exponent-127)) * (1 + fractional value sum)
```

Note: The above is simplified and does not hold true for subnormal numbers. [Wikipedia IEEE Float 32](https://en.wikipedia.org/wiki/Single-precision_floating-point_format)

(extra) floating point numbers can represent the following values and have unique bit-representations: +0, -0, -NAN (Not a Number), -NAN, +INF (Infinity), -INF. These values may need special handing/checking in your code.

(extra) While doing floating point number operations the CPU may use much wider registers between floating point operations to reduce rouding errors. This means that the CPU may use a 76-bit wide float format internally and once its operations are completed in the registers it will round down to a 64-bit format to save to memory.

Tier 1.02: Pointers
===================
Pointers store an address value which can be used to access memory. The pointer's type determines how the memory is interpreted and its stride when doing arithmatic operations. See [Pointers.md](Pointer.md) for more details.

Teir 1.03: enums and enum flags
===============================
An _enum_ is a named bit pattern of a specified length which represents some information about your program.

**Example:** _Enum_ used to represent an engine's status
```c
enum EngineStatus : u8   // 'u8': Use unsigned integer operations and bit pattern length of 8 bits
{
  None = 0,    // Pattern: 00000000
  Off = 1,     // Pattern: 00000001
  On  = 2,     // Pattern: 00000010
  Broken = 3,  // Pattern: 00000011
}
```

An _enum_ flag is an _enum_ in which each bit may have an implied additive property with all other bits in the bit pattern's length.

**Example**: Emum Flags used to represent a goblin's state
```c
enum GoblinState : u8   // 'u8': Use unsigned integer operations and bit pattern length of 8 bits
{
  NoState  = 0,  // Bit: 00000000
  Alive    = 1,  // Bit: 00000001
  Burning  = 2,  // Bit: 00000010
  Frozen   = 4,  // Bit: 00000100
  Poisoned = 8,  // Bit: 00001000
  Leader   = 16, // Bit: 00010000
  Elite    = 32, // Bit: 00100000
  Fighter  = 64, // Bit: 01000000
  Archor   = 128 // Bit: 10000000
{
```

This means we could have a GoblinState have in 256 different states all of which may have different meaning to our program.
```
GoblinState Value:

 Value| Bits set         | Represented Meaning                       |
------+------------------+-------------------------------------------+
  163 = 128 | 32 | 2 | 1 = (Archor) | (Elite) | (Burning) | (Alive)  |
  113 = 64 | 32 | 16 | 1 = (Fighter) | (Elite) | (Leader) | (Alive)  |
------+------------------+-------------------------------------------+
```

Teir 1.04: Custom/User-defined Types (struct/class)
===================================================
A user-defined type is a collection of named types (ie. member variables) packed in a specific memory layout. Most languages use the keyword **struct** and/or **class** to indicate the begining of a user defined type's definition.

**Example**: Person struct example
```cpp
struct Person
{
	int age;
	float height;
	float weight;
	int money;
	string name;
};
```

(extra) User defined types often have their own namespace which may contain additional items such as global variables, constants, functions. See [Types.md:2.05 Namespaces](Types.md#tier-205-namespaces-and-type-namespaces) for details.

(extra) Some languages allow for user-defined types to inherit or include another types' namespace. See [Control.md:3.09 Inheritance](Control.md#teir-309-inheritance) for details.

Tier 2.00: Type Conversion: Implicit and Explicit
=================================================
Most programming languages will allow type conversion between intrinsic types (ie. Integer -> float: 1 -> 1.0). These conversions may result in loss of precision, loss of signness (+/-), or even undefined behavior depending on the language/compiler/hardware used. This behavior is useful, but may be dangerious if unanticipated.

Most languages handle this issue by using implicit and explicit conversion casts. Explicite conversion casts have the programmer write code detailing the conversion while implicit conversions are automatic.

Safe type conversions may occure as a result of an implicit conversion cast. In the case of a non-trivial type conversion, the programming language may require an explicit conversion cast to be written to enable their usage.

(extra) The distinction between implicit and explicit conversion casts is to give the programmer more control and inform the program of abnormal behavior.

Tier 2.01: Type Casting (exclicit type conversions)
===================================================
Pre-Requisite: Pointer.txt Teir 2

Type casting is the process of taking some memory and interpreting it as a different type. The case itself may modify the memory depending on the language and conversion of type. Most languages have 1 casting operator which can do 1 of 3 different basic logical casts. The 3 basic logical casts are static/safe, dynamic/object, and reinterpret/raw.

static/safe cast - This takes a type and logically casts it to another type and may change the underlaying data layout/format. This is the sort of cast you may use to convert a floating point number into an integer since there is a transformation of the bits to represent the information differently.

dynamic/object cast - This cast takes in a pointer/reference to a user-defined type/object and will try and cast it to a pointer/reference to any other user-defined type/object which derives from it. Therefore, we can take a basePointer and cast it to derivedPointer and vise versa.

Reinterpret/raw cast - This cast does no modification to the data and will simply start treating the memory as a different type without consideration for the needs of the conversion. This means a raw cast from 1.234 float to integer will not be 1, but instead 1067316150 since the bit representation for floating point numbers and Integers do not match. Also most languages will force you to to a raw cast via pointer so that if you are moving between types of different size the programer excplicity "gives" the pointer value.

Tier 2.02: Operator Overloading
===============================
Operator overloading is a programming language feature whereby a user-defined types can have operators defined on how certain operators interact with other types/operand(s).

**Example**: Vector2

Vector2 has elements x and y. If I overload binary operator '+' , I can define it to add the left and right operands's x and y values and return the resulting Vector2 value.

Having this operator overloaded enables Vector2, v0 and v1, to be added and then stored into v3: v3 = v0 + v1;

The operand(s) and resulting type do not need to match. Operator Overloading is a fancy way to make a function call


Tier 2.03: Constructors and Destructors
=======================================

In higher level programming languages most user-defined types have an implicit (must be called) and overridable pair of functions called the **constructor** (ctor) and **destructor** (dtor). The ctor is used to allocate the required resources and initialize the memory before normal operation of the type. The ctor is used to cleanup any allocated resources owned by the type. The concept of a ctor/initialize and dtor/finalize functions are extremely useful and exist in almost all programs from high-level to low-level in one form or another.

(extra) In low-level high performance programs ownership of a resources is often shared or managed internally to meet the program's specific needs. This makes the implicit nature of constructors less useful in these situations but are often still used for system level initialize and finalize as normal functions.


Tier 2.04: Iterators
====================

An **iterator** is a type used to traverse a collection of items often held within a container. Languages often provide a standard method/interface to get and operate iteration over a collection.

**Example**: C++ Iterators
```cpp
// Pass in MySpecialContainerType specialized to integers.
void DoThing(MySpecialContainerType<int> collection)
{
    // Iterate over all items in the collection and add 1.
    // This is only possible if the definition of MySpecialContainerType<Type>
    // impliments the needed methods/interface to iterate through its collection.
    for(auto& item : collection)
    {
        item += 1;
    }
}
```

Tier 2.05: Namespaces and Type Namespaces
=========================================

The concept of a **namespace** gives the programmer a way to catagorize code into artibrary referencable sections.

User-defined types in many programing languages have variables and functions in their definition which may be free (global/static) or member (access/using 'this' pointer). These variables and functions may then be accessed by using the type's name simular to how you might use a namespace.

Tier 3.00: Generics (aka templates, plymorphism)
================================================
Generics contain a set of functionality specialized to a specific type. The generic has its own set of instructions per function and each specialization is its own unique user-defined type. (@See Control.txt Teir 3 for more details).

Teir 3.01: Intrinsic Type Conversion Behavior
=============================================

Intrinsic type conversion behavior may change between languages and/or compilers. So it is good to be aware of how one intrinsic will be converted to another. In general, most languages handle the conversaions as follows.

General type conversion behavior:
```
Legend:
 * s: signed Integer
 * u: unsigned Integer
 * f: floating point number
 * zero: bit-length remains the same between the type conversion
 * positive: bit-length increases
 * negative: bit-length decreases

Source Type -(intrinsic type size delta)-> Resulting type : Behavior

u -(zero)-----> u: Nominal conversion (no op)
u -(positive)-> u: Nominal conversion
u -(negative)-> u: Conversion loses uppermost bits.

u -(zero)-----> s: Nominal conversion if u <= s's max positive. Otherwise number becomes negative.
u -(positive)-> s: Nominal conversion
u -(negative)-> s: Conversion loses uppermost bits. The resulting number may be positive or negative.

s -(zero)-----> s: Nominal conversion (no op)
s -(positive)-> s: Nominal conversion
s -(negative)-> s: Conversion loses uppermost bits. The resulting number may be positive or negative.

s -(zero)-----> u: Nominal conversion if s >= 0. Otherwise @See @TODO Two's compliment
s -(positive)-> u: Nominal conversion if s >= 0. Otherwise @See @TODO Two's compliment
s -(negative)-> u: Conversion loses uppermost bits.

s,u -(ANY)----> f: Approximate conversion. Conversion to any langth floating point number always results in a fractional representation. The fractional representation may not align to a whole interger value.
f ---(ANY)----> s: Floor/Ceiling conversion. If f > 0.0, then s = floor(f); if f < 0.0, then s = ceil(f); 
f ---(ANY)----> u: Convert as signed, then convert signed to unsigned.

```

Tier 3.02: Getters/Setters
==========================
Getters and Setters use value-like syntax to get and set data within an object. This allow the internal data representation of a value to be modified by many different input/output formats while its internal representation remains the same. It may also be helpful for debugging because we can add breakpoints, asserts, and trace/logging within a get or set function to provide information about who is accessing the value.

**Example**: C# Temperature
```csharp
class Temperature
{
  // internal data representation may be different than the user
  // facing value getter and setter.
  private Kelvin k;

  public float celcius
  {
    get { return k.ToCelcius(); }
    set { k.SetInCelcius(value); }
  }
  public float fahrenheit
  {
    get { return k.ToFahrenheit(); }
    set { k.SetInFahrenheit(value); }
  }
}

void UpdateWeather(Temperature temp, Weather weather)
{
  if(weather == Weather.Cold)
    temp.celcius -= 3; // access celcius getter/setter and use the "-=" operator
  if(weather == Weather.Hot)
    temp.fahrenheit += 10; // access fahrenheit getter/setter and use the "+=" operator
}
```
**Example**: C# Clock
```csharp
class Clock
{
  private Time t;  // Internal data representaion.
  
  public int seconds
  {
    get{ return t.GetSeconds(); }
    set
    {
      int overflowMinutes = value / 60;
      t.SetSeconds(value % 60);
      if(overflowMinutes > 0)
        minutes += overflowMinutes;   // calls the getter + setter for minutes
      trace("Clock's seconds set to " + value % 60 + "\n");
    }
  }
  public int minutes // Get and Set the minutes on the clock
  {
    get{ return t.GetMinutes(); }
    set
    {
      int overflowHours = value / 60;
      t.SetMinutes(value % 60);
      if(overflowHours > 0)
        hours += overflowHours;
      trace("Clock's minutes set to " + value % 60 + "\n");
    }
  }
  public int hours
  {
    get{ return t.GetHours(); }
    set
    {
      t.SetHours(value % 24); // clock wraps around
      trace("Clock's hours set to " + value % 24 + "\n");
    }
  }
}

void UpdateClock(Clock clock, int secondsPassed)
{
  clock.seconds += secondsPassed;
  if(Date.current.weekday == Weekday.Monday)
  {
    // stop looking at the clock!
    clock.seconds /= 2;
  }
}
```
(extra) You may choose to not impliment both a Getter and a Setter, or make the Setter private and the Getter public. This gives you some added control over how a value is modified to provide intent to the user of the object.

Tier 4.00: Single Instruction Multiple Data (SIMD)
==================================================
Types often relate directly to a set of specific CPU instructions/operations. One such set of CPU operations are Single Instruction Multiple Data (SIMD) also refered to as vector instructions. SIMD instructions use special wide registers (128, 256, 512, 1024 bit) and compute a single operation as if that one register held many of a single type. This allows us to run a single instruction on multiple types to quickly transform data.

Because of how wide registers work, there are often requirements on the memory alignment and count of data being used by a given operation. These wide registers cannot do every instruction that smaller registers might, but the list of instructions grows daily.

**Example**: SIMD operation
```
__m256 wideRegisterType;
```
function "__mm256_fadd" turns into a single instruction at compile-time.
```
__m256 __mm256_fadd(__m256 src0, __m256 src1)
```
This SIMD instruction uses a wide register (256-bits wide) and divides it into 8 32-bit floating point numbers to add src0 + src1 and return the resulting wide register.

Visualization of wide register add instruction:
```
src0   [0.1|0.2|0.3|0.1|0.6|1.0|1.2|0.2]
src1   [0.8|0.2|1.2|2.1|0.4|0.1|2.3|0.1]
result [0.9|0.4|1.5|2.2|1.0|1.1|3.5|0.3]
```

Tier 4.01: Register keyword
===========================
Adding "register" into a local variable suggests to the compiler that this value be stored in a register instead of on the stack.

Tier 4.02: Volatile keyword
===========================
A "volatile" type indicates to the compiler that this value may be modified by other threads/programs and should assume it has changed between each access. This is useful for lockless propogation of state across threads.

Teir 4.03: Restrict keyword
===========================
A "restrict" keyword may be given to pointer parameter type to indicate that this pointer's address is unique to other passed parameters. This may enable certain read/write optimizations whereby multiple pointers of the same type are passed to a function and restrict indicates that the pointer values do not need to be reloaded after writing to any another pointer's memory.

Tier 4.04: Fast Integer
=======================
When compiling a program, the language may allow you to use a "fast" integer type. What this means is that the compiler can choose which integer types would be fastest but must atleast have a minimum specification of length.

**Example**: Fast Integer uint_fast16_t

The type "uint_fast16_t" specifies that the compiler must use atleast a 16 bit unsigned integer operations. However, if using a 32 or 64 bit unsigned integer would be faster it may upgrade to the fastest type.

Tier 4.05: Swizzling
====================
Swizzling is the functionality of rearranging the elements of a vector. This is most commonly seen in computer graphics linear algebra libraries for Vector types.

Example:
```
Vector4 contains elements: x, y, z, w
Vector3 contains elements: x, y, z
Vector2 contains elements: x, y

"v4.ww"   constructs a Vector2 from v4 with elements x,y holding v4's w value.
"v3.xyy"  constructs a Vector3 from v3 with elements x holding the v3's x value and y,z holding v3's y value.
"v2.zzzz" constructs a Vector4 from v2 with elements x,y,z,w holding v2's z value.
"v2.xyxy" constructs a Vector4 from v2 with elements x,z holding v2's x value and y,w holding v2's y value.
```

Tier 4.05: Compound Struct Assignment
=====================================
Some programming languages support assigning a value to member variables of a struct or class by name. This can provide some nice utility as only part of the object may be configured with specialized values while the rest are provided some default value.

**Example**: C99 Text UI Options
```c
typedef struct {
  float x;
  float y;
} Vec2;

typedef struct { 
  Vec2 position;
  Vec2 size;
  Vec2 anchor;
  float corner_radius;
  
  const char* text;

  // Note: unnamed union to provide multiple names for the same option
  // this can make renaming an option or deprecating an old name easier.
  union {
    int layer;
    int display_layer;
  };

} TextElementOptions;

void _DrawText(TextElementOptions opts) { /* ... */ }

// A macro further simplifies the call and provides default values.
#define DrawText(...) _DrawText((TextElementOptions){   \
  .size = (Vec2){ .x = 100.0f, .y = 50.0f },            \
  __VA_ARGS__})

int main(void)
{
  // function call
  _DrawText((TextElementOptions){
    .size = (Vec2){ 325, 150 }, // Order matters (Vec2){ x,y }
    .text = "Big Worlds",
    .layer = 1
  });
  
  // macro
  DrawText(
    .text = "Hello Macros!",
    .corner_radius = 2.0f);

  return 0;
}
```
