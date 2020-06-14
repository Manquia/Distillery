#Incomplete

Tier 5.00: Math as control (Subtle technique/idea)
==================================================
When writing a program is often easy to overuse control statements. If you find yourself writing many 'if' statements you should ask if rather the answer can be instead derived from a data transformation or mapping. The idea is to use a transformation instead of explicit control.

**Example**: Mapping Lookup

In this example we will be converting a MachineId to get its PowerLevel.



**Example**: AngleToDirection (Using a linear transformation versus control)

In this example we convert a 2D vector of x and y coordinate to an 8 directional enum. 

Shared types:
```
enum Direction
{
	None      = 0,
	
	North     = 1,
	NorthEast = 2,
	East      = 3,
	SouthEast = 4,
	South     = 5,
	SouthWest = 6,
	West      = 7,
	NorthWest = 8,
}

// Function to impliment: Converts an angle into a direction. The Direction returned should be the closest to the direction. 
Direction GetDirection(f32 angleFromNorth_degrees); // Clockwise is positive
```

Control Heavy method: The following code contains bugs in a few edge cases which may not initially be obvious. Additionally this code is very brittle and presents a non-trivial control path for CPU. This code also does
not handle negative angles or angles above 385.5 degrees and will always return North incorrectly in both cases.
```
Direction GetDirection(f32 angleFromNorth_degrees)
{
	f32 ang = angleFromNorth_degrees; // Shorten name
	f32 halfAng = 22.5; // Half a direction's angle
	if (ang > (halfAng * +15) || ang < (halfAng * +1))  return Direction::North;
	if (ang > (halfAng * +1)  && ang < (halfAng * +3))  return Direction::NorthEast;
	if (ang > (halfAng * +3)  && ang < (halfAng * +5))  return Direction::East;
	if (ang > (halfAng * +5)  && ang < (halfAng * +7))  return Direction::SouthEast;
	if (ang > (halfAng * +7)  && ang < (halfAng * +9))  return Direction::South;
	if (ang > (halfAng * +9)  && ang < (halfAng * +11)) return Direction::SouthWest;
	if (ang > (halfAng * +11) && ang < (halfAng * +13)) return Direction::West;
	if (ang > (halfAng * +13) && ang < (halfAng * +15)) return Direction::NorthWest;
	
	return Direction::None;
}
```

Math as control method:
1) Consider if the input can be reduced/altered to simplify the problem space.
2) Make a series of transformation that compute the output value/result from the input.
2a) A nonlinear transformation may require a lookup table.
3) Profit!

// @TODO @TEST
```
Direction GetDirection(f32 angleFromNorth_degrees)
{
	f32 angle = angleFromNorth_degrees; // shorten name
	f32 directionHalfAngle = 22.5;
	// 1) Reduce input space (Properties of Angles):
	// Angles over +-360 degrees can be reduced. (540 degrees = 180 degrees)
	// Any negative angle also has positive representation. (-30 degrees = 330 degrees)

	// Reduce: (Force Input into range between +-360 degrees)
	f32 loops = Mathf.Floor(angle / 360); // Floor() rounds down.
	f32 sign = Mathf.GetSign(angle);      // (-1,0,1)
	angle = angle - (loops * sign * 360); // reduce (between +/-360 degrees)
	
	// Force positive and reduce: (Input is now between +0 and 360)
	angle += 360;
	loops = Mathf.Floor(angle / 360); // Floor() rounds down.
	angle = angle - (loops * 360);    // reduce (between 0-360 degrees)
	
	// 2) Series of transformations: (Consider output enum)
	// North is unique: North has 2 slices 337.5-360 and 0-22.5 degres.
	// Direction enum counts clockwise with angle.
	// Each enum should map to exactly 45 degrees of angle. (East is 45 degrees slice between 67.5 and 112.5 degrees)
	
	// Fix north case: Shift degrees by 22.5 degrees and reduce. This also rotates all degrees by 22.5.
	angle += directionHalfAngle;      // rotate/shift angle by 22.5 degrees.
	loops = Mathf.Floor(angle / 360); // Floor() rounds down.
	angle = angle - (loops * 360);    // reduce (Between 0-360 degrees)
	
	// Now that the angle has been rotated 22.5 degrees and reduced we no longer have the unique North case.
	// This means the directions are evenly split between the angles 0-360 with North matching 0-45 degrees.
	// Since our enums count clockwise we can do a direct conversation to direction by dividing by 45.
	
	// Convert to direction:
	u32 directionNumber = Mathf.Floor(angle / 45.0);
	
	// North starts a 1
	directionNumber += 1;
	
	return (Direction)directionNumber;
}
```

The function above can be reduced to the following:

// @TODO @TEST
```
Direction GetDirection(f32 angleFromNorth_degrees)
{
	f32 directionHalfAngle = 22.5;
	f32 angle = angleFromNorth_degrees + directionHalfAngle; // rotate 22.5 degrees

	f32 loops = Mathf.Floor(angle / 360); // Floor() rounds down.
	f32 sign = Mathf.GetSign(angle);      // (-1,0,1)
	f32 isNeg = Mathf.IsNeg(angle);       // (0.0, 1.0)
	
	// Reduce (between +/-360 degrees) AND Add 360 degrees when angle is negative
	angle = angle - (loops * sign * 360) + (isNeg * 360);
	
	// Convert to direction:
	u32 directionNumber = Mathf.Floor(angle / 45.0) + 1; // North starts a 1
	
	return (Direction)directionNumber;
}
```

**Example**: AngleToDirection (simple)
@Calculate operations in lookup tables
@Lookup results/control in tables
@Transform data to permute control flow.

@TODO @TODO @TODO @INCOMPLETE

@Data as control (Sequence, This is what an interpreted language is!)

(extra) Computers love linear code without any control as it is extremely fast. Removing control can be a valuable optimization.

Tier 5.01: Container(s) as control @Review @Incomplete
==================================
Certain containers can be used to give us iterative control over a given data set. The order of a container is logically useful because it allows us to view/use an item in some relation to other items within the container.

Common Containers used for their ordering property
```
stack: first in last out (FILO, push-pop state, graph traversal depth-first) 
queue: first in first out (FIFO, graph traversal breadth-first)
heap: min/max in a collection of items (graph traversal priority)
tree: various (behavior trees, rules, logic, composition)
graphs: various (pathfinding, parsing, state machine)
```



Tier 4.11: Performance multithread programming
==============================================
Above are many useful primitives to enable multi-threaded programming as a paradigm. These are very useful for a variety of system tasks but are not particularly fast in terms of performance.

Common areas to optimize multithreaded programming:
- Creating performance multithreaded code is all about dividing up the data such that there is no need to synchronize it in the first place. When you must synchronize between threads do so at stages in the data pipeline which has the smallest amount of data to synchronize.
- Expending extra memory to create a local and a shared copy of values which must be synchronized can improve performance because we can reduce the synchronization between threads.
- Instrument threading primitives (Mutex, semaphore, Conditional Variable) to log directly to a profiler. This is important since using most thread primitives lead to threads waiting in sleep so the cost may be hidden otherwise.
- @TODO @Incomplete add more wisdom once I have become wiser to the ways of multithreaded programming. Ask people who have more experience in this area.



@TODO

* Moore's Law - CPU "power" progression
* Amdahl's law - Multi-core speedup limits
* Little's Law - How everything uses queues and what it means. This is a really long article/section which is more a ramifications of how the internet/hardware does high throughput communication.

