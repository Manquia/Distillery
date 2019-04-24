Pre-Requisite: Memory.md Tier 1
Summary: A basic overview of intrinsic types, and common user types seen in programming languages

Now we will go more in-depth to what the CPU will do foreach different type. The example below will investigate 8 bit integer types. For integer types of larger than 8 bits they work the same with more bits in the middle to represent more numbers.

unsigned integer (8 bit) holding the value of 15: 00001111


Tier 1.00: Integers (Signed and Unsigned)
=========================================
Examples are for 8-bit integers, but apply to 16,32,64,128 bit signed/unsigned integer types just add more value bits.

Unsigned integers are a base 2 number.

Unsigned Operation

+ Addition       - Adds 2 unsigned numbers. If one of the 2 numbers is signed, the unsigned number will usually be converted to signed before doing signed addition.
- Subtraction    - Subracts 1 unsigned number from another unsigned number. Often, programming languages will force a signed result, but both signed and unsigned results are possible.
* Multiplication - Multiply 2 unsigned numbers together. Results is also unsigned
/ Division       - Divides 1 usngiend number by another. Result is also unsigned and takes logical floor of the result.

unsigned Integer Memory Layout:

S <- signed bit (most significant) determines if integer is positive or negative.
V <- value bit in base 2
```
unsigned 8-bit integer: VVVVVVVV
signed 8-bit integer:   SVVVVVVV

8 bit unsigned integer examples: 00110110 = 54,   11111100 = 252
8-bit signed integer examples:   00110110 = 54,   11111100 = -4
```
Signed Integer's are 2's Compliment: If you want to invert the sign of the number then you flip all bits and add 1. This will give you the same number bit signed changed to match 2's compliment integers.
```
2's compliment example: 54 = 00110110 -(flip bits)-> 11001001 -(add 1)-> 11001010 = -54
2's Compliment example: -4 = 11111100 -(flip bits)-> 00000011 -(add 1)-> 00000100 = 4
```
Notice that negative integers numbers are still basically in base 2, with the the 0 and 1 are flipped and then we just add 1.

Teir 1.01: Floating Point/Real Numbers
======================================
Floating point or Real numbers have a level of precision proportional to the bits in the format. This means the format has a limited precision based on the number of bits the format uses. For 32-bit IEE floats the precision level is ~7 decimals (ie. 1.234567) near 0-1 values and gets worse as you incrase in magnitude. This means that if we have a number which becomes more precise then 7 decimals durring its calculation that precision will be lost when we store the number back into memory.

Examples will be for 32-bit IEE floating point. Floating point numbers with 16-bit and 64-bit have different ratios for each secton but follow the same guidelines.

 - S <- Signed bit (most significant). 0 = positive, 1 = negative.
 - E <- Exponent bits. An exponent of 0 is the value 127
 - F <- Fraction bit, Holds the fraction value

32-bit IEEE floating point (single-precision floating-point format)
```
 S EEEEEEEE FFFFFFFFFFFFFFFFFFFFFFF
 ^ \      / \                     /
 | exponent  \______fraction_____/
 |
 Signed bit
 
actual value = (-1 * signed bit) * (2^(exponent-127)) * (1 + 1/fraction)
```
Note: the fraction part is simplified a bit

(extra) Floats can represent these values which all have different bit-representations: 0, -0, NAN (Not a Number), -Nan, INF (Infinity), -INF. These values may need special handing/checking in your code.

(extra) While doing floating point number operations the CPU may use much wider registers between floating point operations to reduce rouding errors. This means that the CPU may use a 76-bit wide float format internally and once its operations are completed in the registers it will round down to a 64-bit format to save to memory.

Tier 1.02: Pointers
===================
Pointers are the simple types in that they are an address and a type. The type they are pointing to determines the stride when doing arithmatic operations and what the memory is intrepreted when the pointer is dereferenced. See Pointers.txt for more details.

Tier 1.03: void
===============
void (aka nothing) is a type used to indicate that there is not return or input type. Some languages have the input/return types become optional in the syntax so instead of "void" you write nothing. It is not possible to create a void value, it is nothing.

pointer to void however is valid and used frequently. This means that we have an address without any connected type. A void pointer cannot be dereferenced and must be cast to a type for the address to be accessed.

Teir 1.04: enums and flags
==========================
An enum is a bit pattern of a specified length which represents some abstract information about your program.

**Example:** enum to hold state
```
enum EngineState : u8   // use unsigned operations and bit pattern length of 8 bits
{
  None = 0,    // Pattern: 00000000
  Off = 1,     // Pattern: 00000001
  On  = 2,     // Pattern: 00000010
  Broken = 3,  // Pattern: 00000011
}
```
A flag is a specialized enum in which each bit may have an implied addative property with all other bits in the bit pattern's length.

**Example**: flags for complex state
```
enum GoblinState : u8  // use unsigned operations and bit pattern length of 8 bits
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

 Value| Bits set         | Meaning                                   |
------+------------------+-------------------------------------------+
  163 = 128 | 32 | 2 | 1 = (Archor) | (Elite) | (Burning) | (Alive)  |
  113 = 64 | 32 | 16 | 1 = (Fighter) | (Elite) | (Leader) | (Alive)  |
------+------------------+-------------------------------------------+
```
(extra) There is an implied addative nature to flags within the same enum which is done to improve readability. In memory tight environments such as networking you may decide to break this guideline and fit more flags within a smaller memory space to maximuse effeciency.

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

Tier 3.00: Generics (aka templates)
===================================
Generics contain a set of functionality specialized to a specific type. The generic has its own set of instructions per function and each specialization is its own unique user-defined type. (@See Control.txt Teir 3 for more details).

Teir 3.01: Intrinsic Type Conversion Behavior
=============================================
@TODO @Incomplete

General type conversion behavior:
```
Legend:
 * s: signed Integer
 * u: unsigned Integer
 * down: bit-length decreases
 * up: bit-length increases

Source Type -(size difference)-> Resulting type : Behavior

u -(equal)-> s: if u <= s's max positive then safe. Otherwise s = s's max negative
u -(up)----> s: safe
u -(down)--> s: 


s -(equal)-> u: if s >= 0 then safe. Otherwise u = 2^s'sbitLength + (s's first u'sbitsLength)
s -(up)----> u: if s >= 0 then safe. Otherwise u = 2^s'sbitLength + s
s -(down)--> u: if s >= 0 AND s < u's max value then safe. Otherwise u =  2^s'sbitLength + (s's first u'sbitsLength)
```
All floating point number conversions to and from signed or unsigned integers may lose precision if there is no exact fractional representation that can represent the integer value.

Tier 3.02: Getters/Setters
==========================
Getters and Setters use value-like syntax to get and set data within an object. This allow the internal data representation of a value to be modified by many different input/output formats while its internal representation remains the same. It may also be helpful for debugging because we can add breakpoints, asserts, and trace/logging within a get or set function to provide information about who is accessing the value.

**Example**: C# Temperature
```
class Temperature
{
  private Kelvin k; // internal data representation may be different than the user facing value getter and setter.
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
    temp.celcius -= 3; // I can refer to the celcius getter and setter here to use the "-=" operator
  if(weather == Weather.Hot)
    temp.fahrenheit += 10; // I can refer to the fahrenheit getter and setter here to use the "+=" operator
}
```
**Example**: C# Clock
```
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

# Incomplete

@Constructors + Destructors
@Iterators 
@Intrinsic type conversion Behavior
