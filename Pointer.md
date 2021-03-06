Pre-Requisite: Memory.txt Tier 1
Pre-Requisite: Types.txt Tier 1
Summary: An overview on the usage of pointers from basic to complex in low and high-level programming.

Teir 1.01: Pointers as address
==============================
Pointers are a programming language concept which is a number (an address in memory), and a type associated with it. The type determines how the arithmatic operators "add" and "subtract" (+,-, +=, -=, ++, --) modify the address value.

Using an arithmatic operator on a pointer will automatically use the type's size as its stride through memory. This means that if I have a pointer to an int, which has a size of 4 bytes, adding +1, or +2 will modify the address it is pointing to by +4, and +8. The same is true for subtraction in the other direction.

**Example**: Pointer arithmatic
```        
'#'    <- Represents a byte (a group of 8 bits) in memory
'####' <- Represents 4 bytes in memory
```
p0 through p5 are the pointers of various types
```

         p0             p1         p2    p3  p5         p4
          |              |         |      |   |          |
          #### #### #### #### #### #### #### #### #### #### #### ...
          |         |         |         |         |         |  |
address   0         8         16        24        32        40 |
          \______________________Memory________________________/ 
```
* Pointer Arithmatic Operations
```
p0 = 0      (Pointer is set to the address 0)
p1 = p0 + 3 (pointer moves as type of size 4 bytes)  // Math: 0  + (3 * 4)
p2 = p1 + 2 (Pointer moves as type of size 4 bytes)  // Math: 12 + (2 * 4)
p3 = p2 + 6 (pointer moves as type of size 1 byte)   // Math: 20 + (6 * 1)
p4 = p3 + 1 (Pointer moves as type of size 12 bytes) // Math: 26 + (1 * 12)
p5 = p4 - 3 (Pointer moves as type of size 3 bytes)  // Math: 38 - (3 * 3)
```

* The ++ and -- operators are the same as "pointer + 1" and "pointer - 1".
 
Teir 1.02: Pointers and Index/Offset
====================================
Often you will see pointers used in conjunction with an index of offset integer variable. This plays out the same as above with the pointer arithmatic. The index or offset are integers and provide a way to move through memory which is populated by one type.

**Example**: Sum array of integers
```
int SumArrayOfIntegers(int* array, int size)
{
  int returnSum = 0;
  for(int index = 0; index < size; ++index) // for every 'index' from 0 to size-1
  {
    int accum = *(array + index); // Add 'index' and derefernce memory as an integer stored in 'accum'
    returnSum += accum;           // Add 'accum' to our returnSum value
  }
  return returnSum;
}
```

Teir 2.00: Any Pointer
======================
An Any pointer, is usually 2 pointers. One points to the memory of the type (like a normal pointer) while the second points to information about the type. By using the second pointer to the information we can make choices on what to do with the information.

**Example**: Any pointer usage
```
anyPointer = GetTextObjectPointer(...);

if(anyPointer.IsType(typeof(Font)))
    ChangeFont(anyPointer);
else if(anyPointer.IsType(typeof(Text))
    WriteText(anyPointer);
else
    Print("Error: Unhandled Text Object");
```

Teir 2.01: Pointer to class/object
==================================
Adding into the pointer concept further we can specify pointers as pointing to a "class" or "Object" type. The class or object types can contain extra data at the begining of the memory, usually another pointer, which allows the program to run specialized code on that object.

Most programming languages call this sort of functionality a "virtual function", or an "interface".

Given a collection of objects which supports an interface may then generically run some function on without needing to know any specifics about the object's actual memory.

**Example**: Virtual Interface

I have three pointers to a type which supports the vehicle interface. One points to a car, another a truck, and the last a motorcycle. I want to run the function TurnOnEngine(...) on each through the pointers to vehicles. I can do this because the extra data on the car, truck, and motorcycle can then be used to select the correct instructions to call its version of TurnOnEngine(...)
```
for(pointerToVehicle in vehicleCollection)
    pointerToVehicle.TurnOnEngine(...);
	// Can call car's TurnOnEngine(...), or truck's TurnOnEngine(...), or motorcycle's TurnOneEngine(...)
```

Some languages/implimentations allow you to get and check the actual type of a pointer to a class.
* Common ways to get type info id/pointer from pointer to class: .GetType()
* Common ways to get specific pointer from base pointer: dynamic_cast<SpecificType>(pointerValue), pointerValue as SpecificType, (SpecificType)pointerValue <- will return an non null value when the pointerValue is pointing to the SpecificType.

Teir 2.02: Smart Pointers (Memory Managment)
============================================
1) Unique pointers (lifetime/Memory Managment)

When a unique pointer is destroyed/finalized the pointer also cleans up the object to which it points. Unique pointers cannot be coppied, but the single ownership principle may can be transfered.

2) Shared pointers or reference counted pointers (lifetime/Memory Managment)

Each occurace of the pointer to an objects adds 1 to a shared counter. Upon destroyed/finalized the pointer subtracts 1 from the shared counter. If the shared counter reaches zero, then the pointer will also clean up the object it pointed at.

3) Weak pointers or Handles or References (lifetime management)

Points to a given object until it has been cleaned up at which point, it is set to 0 or the null pointer value. (extra) This is usually done by using a pointer to a pointer to the object such that upon destruction/destroyed/finalized of the object the second pointer is set to 0. Then any number of other pointers can see the second pointer has been set to 0.

Teir 3.00: Relative Pointers
============================
Relative pointers are a more formalized method of using index/offsets to refernce memory. The key element to a relative pointer is that it has some origin point which we offset from. There are 2 general types of relative pointers that you may encounter.

1) Relative to a specialized address

Pointer requires some external address as its address space. This pointer cannot reference anything without its starting point. A file pointer is conceptually a relative pointer whose origin is the begining of the file.

@Incomplete: Add example

2) Relative to its own address

Pointer's offset is relative to its own address. That is to say, its origin is its own address in memory and its value is an offset before/after its own address.

@Incomplete: Add example

Benefits of using relative pointers
* They can be serialized/saved to disk/network whereas normal pointers cannot.
* They do not require 8 bytes, a relative pointer can be any size number of bytes which can dramatically improve performance. This is great so long as you know the limitations of the memory you wish to refernce is not too far away from the pointer's origin.
* They can make some code complex significantly more clear/understandable.
* Some implimentations will allow for automatic relative pointer to global pointer conversaions which may improve readability.

Tier 3.01: Stride
=================
Stride generally refers to the behavior of pointer arithmatic in the count of bytes that we move our address. We call it stride when it is an explicit, and often calculated, number of bytes we move our pointer's address by.

This can be very helpful to reduce code size and complexity for lots of tasks as effectivly stride uses math in what was traditionally logic. This is particularly common to see used with data streams that have a lot of configurability to the type of data they can process for graphics and audio.

Example: Audio processing @Cleanup @TODO

Lets say we have a function which applies an audio effect to a data stream. The operation is the same on each channel (left, right, base, etc...) but we need to support variable number of channel count. To do this we can use a union to address the specified types for the different channel types, and then instead of writing multiple different cases, we calculate the pointer's stride behore-hand.


```
  byte 0   byte 1   byte 2   byte 3   byte 4   byte 5   byte 6
 /      \ /      \ /      \ /      \ /      \ /      \ /      \
 01111110 10000001 10010001 01001110 01101101 01110101 01001101
 \                                                   /
  \______________________Memory_____________________/
```

# Incomplete

@Stride Audio Example @Relative pointer examples