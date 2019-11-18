


#Incomplete


Tier 5.00: Math as control (Subtle technique/idea)
==================================================
In some cases immediately comparing a quantity is difficult because it is either multi-dimensional or hard to quantify. In such cases, it may prove helpful to use math to reduce the solution space to the point that no actual control is needed (aka. the task is linear). The following are 2 examples of how math can take a complex comparison example and make it much simpler.

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
stack: first in last out (FILO) 
queue: first in first out (FIFO)
heap: min/max item
tree: various (behavior trees, rules, logic)
graph: various (pathfinding, parsing, state machine)
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
* Little's Law - How everything uses queues and what it means.

