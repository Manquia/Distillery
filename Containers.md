Pre-Requisite: types.txt Tier 1, Memory.txt Tier 1, Pointers.txt Tier 1

Summary: A quick overview of common to exotic containers and their usefulness. This gives a more practical use of the containers whereas DataStructues.txt goes in depth on how the given containers work. This will NOT go into any sorting techniques, see sort.txt.

Tier 1.00: Why Containers?
==========================
Containers are general solutions to store, sort, and access data in a way to solve problems. In general there are 2 highly used containers because they are the best for most applications, but in reality, there are dozens of valid and potentially more optimal containers for a given task. Tier 1 will go over the most highly used containers.

Container Performance specification from fastest to slowest
```
O(c)      <- constant time operation
O(logn)   <- scales with log(n) items in the container
O(n)      <- scales with n items in the container
O(nlogn)  <- scales with n * log(n) items in the container
O(n^2)    <- scales with n^2 items in the container
```
Tier 1.01: Array aka: Vector, String
====================================
```
specs   Sorted   Unsorted   Description
Add     O(n)     O(c)       Add an item to an array which is large enough to hold the item
Remove  O(n)     O(c)       Remove an item from an array at a known index.
Find    O(logn)  O(n)       Find an item within the array
Grow    O(n)     O(n)       Increase the size of the array, to fit more items
```

The array is an ordered container which stores items in a contiguous block of memory. An item refers to any type in the program that has a non-zero memory footprint and can be created. 

Arrays tend to either be static or dynamic. A static array will never grow its memory footprint automatically and has a set capacity, whereas a dynamic array will usually grow automatically when add is called and can no longer fit the new item into the array.

Arrays can also differ in how they store the item's data within the memory block. The 2 common layout patterns are an array of structs (AOS) and a struct of arrays (SOA). Note: struct is a common name for a user-defined type.

An array of structs (AOS) places each item next to each other, like a slotted bookshelf.

**Example**: 'ITEM' <- single item in AOS array
```
 ITEM|ITEM|ITEM|ITEM|____|____   <- array of structs (AOS) of type ITEM, with capacity 6 and size 4
```
A struct of arrays (SOA) takes each sub-item within the item and places them within its own array such that each sub-item it next to each other.

**Example**: 'ITEM' <- single item in SOA array
```
 IIII__|TTTT__|EEEE__|MMMM__     <- struct of arrays (SOA) of type ITEM, with capacity 6, and size 4
```
In some cases, one layout pattern can be more performant than another, but this highly depends on the task. In general, use AOS. You may consider using SOA if your access patterns only use a small part of the item. see Memory.txt Tier 4 for more details.


Tier 1.02: Hash Table aka: Map, Dictionary
==========================================
```
specs  Unsorted Description
Add    O(c)     Add an item to a hash table which is large enough to hold the item.
Remove O(c)     Remove an item from a hash table of a known key or index
Find   O(c)     Find an item within the container with a known key.
Grow   O(n)     Increase the size of the hash table, to fit more items
```
A Hash Table is an unordered collection which stores key-value pairs (KVP). It then uses a hash function on the key to get a search index which is then used to place and get the KVP. Two common hash-table layouts include linear probing or chaining to set and get the KVP.

Bother linear probing and chaining may have collisions in which multiple keys' hash to the same index. The layout then allows the items to be found even if the search index was filled.

**Example**: Linear Probing

Search Array
```
Index: [0]             [1]             [2]            [3]             [4]
KVP:   |key,value,flags|key,value,flags|___,_____,____|key,value,flags|___,_____,____
```
The flags use used to inform the linear probing if the space is empty/filled if we are adding a KVP or if we should continue probing the array for the key in a linear fashion.

**Example**: Chaining Hash Table

Search Array    Nodes in a linked list (see Tier 2: Linked List)
```
Index        | Linked List of KVPs
[0] ---------> Key,Value -> Key,Value -> Key,Value
[1] ---------> 
[2] ---------> Key,Value -> Key,Value
[3] ---------> Key,Value
```
Collisions are handled by having each index hold a linkd list of all KVPs so that when multiple keys map to the same index they can still be added and found later.

(extra) A hash function is simply a function which takes either fixed or variable length input of data and outputs a fixed size as a search index. A good hash function will try to distribute all keys to the search space.

Tier 2.00: Linked List aka: List
================================
```
specs  Sorted Unsorted Description
Add    O(n)   O(c)     Add an item to a linked list of any size.
Remove O(n)   O(n)     Remove an item from a linked list.
Find   O(n)   O(n)     Find an item within the linked list
Grow   O(c)   O(c)     Increase the size of the linked list, to fit more items
```
A Linked list is an ordered collection of items in which each item is stored on its own node which has one or more pointers to other nodes (s). Linked lists are extremely slow on modern CPUs and should be avoided if possible, but they are excellent practice with pointers and it is highly recommended for new programmers to make your own implementation to learn.

**Example**: Single/Forward linked list Layout (1 pointer: next)
```
 |ITEM|-> |ITEM|-> |ITEM|-> ...
```
**Example**: Double/bi-directional linked list layout (2 pointers: previous and next)
```
 <-|ITEM|->  <-|ITEM|-> <-|ITEM|-> <-|ITEM|->  <-...
```
Note: the first node of a linked list is called the "head" and the last node is called the "tail"

(extra) Be aware that a linked list can be circular in that the node item can point to the first node leading to cycles.

Tier 2.01: Trees
================
```
Specs   Sorted (balanced)    Unsorted   Description
Add     O(logn)              O(c)       Add an item to a tree of any size.
Remove  O(logn)              O(n)       Remove an item from a tree
Find    O(logn)              O(n)       Find an item within the tree
Grow    O(c)                 O(c)       Increase the size of the tree, to fit more items
```
A tree is an ordered collection of items stored on nodes which point to one another. Tree nodes can have 2 or more pointers to other nodes and will never form a cycle (i.e. node0 -> node1 -> node0)


**Example**: Tree node layout
```
node        <- A node contains 1 or more items and pointers which can be set to children and parent nodes
child node  <- A node which is logical to the left/right of the node pointing to it
parent node <- A node which is logically the root of the sub-tree
root node   <- A node which is logically the highest node in the tree and is the parent/ancestor of all nodes.
leaf node   <- A node which has no children

Binary Tree (2/3 pointers: left, right, parent(optional) )

               root             <- Only a parent, level 0
              /    \
          node     node         <- Child nodes, level 1
         /    \        \
     leaf     node     leaf     <- Child nodes, level 2
             /
           leaf                 <- Child nodes, level 3
```
(extra) The example above has 2 children and is often times useful for the logical collection of objects. However, if a tree is only used for lookups the structure of the tree, the number of children and number of items per node will change to improve performance.

(extra) Inserting and removing nodes from a sorted tree can leave it unbalanced which when sorted can h

(extra) A Tree can also be implemented in an array with the left/right nodes being a set offset multiply the level number into the array. This will use more space if the tree is sparse, but for a balanced tree it will be much faster and more efficient for memory overhead since we don't need a left/right pointer since the address of the left/right is calculated by depth.

Tier 2.02: Graph
================
A graph is an ordered collection of logically connected nodes which can be traversed. Unlike a tree, a graph can have cycles and will often have a variable number of connections between nodes. Graphs can be used to represent connections, state, and much more.

**Example**: Node-based graph

Pointer-based graph (Each ITEM has a collection of 0 or more pointers to other nodes)
```
        +--+
        |  V
        +-ITEM0->  <-ITEM1
          ^         ^  |
          |         |  |
          |         |  V
          ITEM2 -> ITEM3
```

**Example**: Array-based graph

Each ITEM has a value denoting if it is connected to another item which is then accessed by index/id. The following array-based graph has the same logically connections to the node-based example above.
```
                        ITEM0 ITEM1 ITEM2 ITEM3
Item0's Connections to  Yes   Yes   No    No
Item1's connections to  Yes   No    No    Yes
Item2's connections to  Yes   No    No    Yes
Item3's connections to  No    Yes   No    No
```
NOTE: Teir 3 and above are specialization of the containers above whose implimentation solve a specific problem. 

Tier 3.00: Queue (conceptual container)
=======================================
A Queue can logically push/add and pop/remove items whereby an item pushed into the container will be poped from the container in a first-in-first-out (FIFO) ordering. A queue can be implemented with an ordered container.

**Example**: Queue layout usage
```
Command    Container (capacity 4)      Description
Initial    |_____|_____|_____|_____|   Container starts empty
Push       |Push0|_____|_____|_____|   Add value Push0
Push x3    |Push0|Push1|Push2|Push3|   Add value Push1, Push2, Push3
Pop        |_____|Push1|Push2|Push3|   Removed/Get value Push0
Pop  x2    |_____|_____|_____|Push3|   Removed/Get value Push1, Push2
Pop        |_____|_____|_____|_____|   Removed/Get value Push3
```
(extra) To traverse a graph in a breadth-first approach, a queue can be used.

Tier 3.01: Stack (conceptual container)
=======================================
A Stack can logically push/add and pop/remove items whereby an item pushed into the container will be poped from the container in a last-in-first-out (LIFO) ordering. A stack can be implemented in an ordered container.

**Example**: Stack layout usage
```
Command    Container (capacity 4)      Description
Initial    |_____|_____|_____|_____|   Container starts empty
Push       |Push0|_____|_____|_____|   Add value Push0
Push x3    |Push0|Push1|Push2|Push3|   Add value Push1, Push2, Push3
Pop        |Push0|Push1|Push2|_____|   Removed/Get value Push3
Pop  x2    |Push0|_____|_____|_____|   Removed/Get value Push2, push1
Pop        |_____|_____|_____|_____|   Removed/Get value Push0
```
(extra) to traverse a graph in a depth-first approach a stack can be used.

Tier 3.02: Circular Buffer (conceptual container) aka: Ring Buffer
==================================================================
A circular buffer can push/add an infinite number of items but will overwrite items that were added first once the container has reached its capacity. A circular buffer can be implemented in an ordered container.

**Example**: Circular buffer usage
```
Command    Container (capacity 4)      Description
Initial    |_____|_____|_____|_____|   Container starts empty
Push       |Push0|_____|_____|_____|   Add value Push0
Push x3    |Push0|Push1|Push2|Push3|   Add value Push1-3
Push       |Push4|Push1|Push2|Push3|   Add value Push4
Push x5    |Push8|Push9|Push6|Push7|   Add Value Push5-9
```
(extra) Circular buffers may be used for various limited history records or data-streams in which the data is processed in-place.

Tier 3.03: Heap (conceptual container) aka: Priority Queue 
==========================================================
```
Specs (best)    Sorted   Description
Add             O(c)     Add an item to a heap of any size
Remove min/max  O(logn)  Remove min/max item from heap
Find min/max    O(c)     Find min/max an item within the heap
Remove          O(n)     Remove an item from the heap
Find            O(n)     Find an item within the heap
Merge Heaps     O(c)     Merge two Heaps of any size
```

A heap uses an ordered container in a loose ordering which can add items and sort them according to any given ordered condition to give the current min/max of all the items in the container.

**Example**: For a max of an integer value
```
Command      Container (capacity 4)    Description
Initial      Max: None, Size: 0        Container starts empty
Add 3,5,2    Max: 5,    Size: 3        Add 3,5,2 to the heap
Pop Max      Max: 3,    Size: 2        Remove/Get Current Max: 5
Add 10,12,1  Max: 12,   size: 5        Add 10,12,1 to the heap
Pop Max      Max: 10,   size: 4        Remove/Get current Max: 12
```
(extra) A heap can get the max/min of any logically ordered types. The example above uses integers, but this can also be applied to floats, strings, and anything else logically ordered.

(extra) A heap/priority queue in combination with a calculated cost to the end point (heuristic) is basically how A-star path pathfinding works.

Tier 4.00: Bucket Array (hybrid container)
================================
B <- Max of Bucket Size and Bucket Count
```
specs     Sorted   Unsorted   Description
Add       O(B)     O(c)       Add an item to an array which is large enough to hold the item
Remove    O(B)     O(c)       Remove an item from an array at a known index.
Find      O(logn)  O(n)       Find an item within the array
Subscript O(c)     O(c)       Get value at a given array index in a given bucket index
Grow      O(B)     O(B)       Increase the size of the array, to fit more item
```
A bucket array is an ordered container which consists of an array of arrays of items. To look up an item in a bucket array, we both its bucket index and the array index. We use the bucket index to select the array, and then the array index to select the item within that array/bucket.

**Example**: bucket count: 2, bucket size: 3
```
 array of arrays       Bucket (array of items) 
 
 [0] ----------------> |ITEM|ITEM|ITEM|
 [1] ----------------> |ITEM|ITEM|____|
```

(extra) A bucket array gives similar performance benefits as an array.

(extra) A bucket array may contain large amounts of data since we no longer need to worry about exceeding the max allocation size of contiguous memory. This is its main advantage over arrays and that if sorted Adding and removing is O(B) at worst instead of O(n).

Tier 4.01: B-List (hybrid container)
====================================
B <- array size

@TODO I think these specs arn't quite quite right...
```
specs     Sorted   Unsorted   Description
Add       O(B)     O(c)       Add an item to a B-List which is large enough to hold the item
Remove    O(B)     O(c)       Remove an item from a B-List at a known index.
Find      O(B)     O(n)       Find an item within the B-List
Subscript O(B)     O(c)       Get value at a logical index into the B-List
Grow      O(c)     O(c)       Increase the size of the B-List, to fit more item
```
A B-List is an ordered container which consists of a linked list whereby each node contains a static array of items. In a sorted B-List the items are logically sorted across nodes so each node quickly 

**Example**: array size: 3, node count: 2
```
  <-|ITEM|ITEM|ITEM|-> <-|ITEM|ITEM|____|->
    \              /     \              /
     \____Node____/       \____Node____/
```
(extra) For performance: The size of the node should often correlate to the CPU's cache size. In the case, it is larger than the CPU cache the first and last item in the array may physically be at the beginning of the node while logically being sorted to avoid a second cache miss.

(extra) B-List and bucket array are similar. A reason to use a B-List over a bucket array is that a B-List that is being accessed by multiple threads simultaneously will have a lower synchronization cost as a maximum of 3 nodes need to be synchronized to add an item.

Tier 5.00: Bloom Filter
=======================
A bloom filter is used to probabilistically determine if a key has been added to a container. The filter can let you know for certain that a key has not been added or maybe has been added. It cannot tell you for certain that key has been added. This data structure is great for file systems which vast quantities of files and text within that may have many different layers of bloom filters which can search for keys to narrow down the search space.

A bloom filter usually works by using a bit-field of a hash value. Upon adding value to the filter, those bit-fields are set. We can know for certain that a key has not been added if any of its bit-fields have not to be set.

**Example**: 16-bits field
```
Initial State   00000000 00000000
Add Hash        10000101 01101110
Add Hash        10110101 11101110
Add Hash        10111101 11101111  <- final bit-field to compare against
Look for        01111001 11011111  <- key's hash can't have been added
Look for        10000101 01101110  <- key's hash may have been added
```
**Example**: tree traversal of bloom filters

Let's assume that the key has never been added to this tree of bloom filters. At each successive node there is a 25% chance that it will let us know it has not been added to this node or any sub-nodes. This means we have an expected value of 4 nodes before we find that we have not been added to this node or any sub-nodes. In a full tree, this means we look at 1,2,4,8 or 15 total nodes as our expected cut-off point for our search.

(extra) The math isn't quite as simple as the example above, but the principle is that we can eliminate vast swaths of data probabilistically from a search or operation.

Tier 5.01: Skip List
====================
```
specs     Sorted  Description
Add       O(logn) Add an item to a B-List which is large enough to hold the item
Remove    O(logn) Remove an item from a B-List at a known index.
Find      O(logn) Find an item within the B-List
Subscript O(logn) Get value at a logical index into the B-List
Grow      O(c)    Increase the size of the B-List, to fit more item
```
A skip list is a probabilistic linked list whereby the first node has n levels of pointers to other nodes in the linked-list in addition to the next/previous pointers of the node. When adding a node to our skip-list we randomly determine its height and assign pointers from nodes with previous levels and lastly use the first node of the list with n-levels of pointers as our root.

This structure probabilistically gives us the ability to do a binary search of sorts on a linked list by the layout of our nodes.

**Example**: skip list example: ">","->" represent pointers to the next node on that level, "=" represent bi-directional (aka previous, next pointers) between nodes.
```
       .
       .
       .
       |---------------------->|
       |------------>|-------->|
       |-------->|-->|-------->|
       |-->|---->|-->|---->|-->|>|
       |>|>|-->|>|>|>|>|-->|-->|>|
       +=+=+=+=+=+=+=+=+=+=+=+=+=+=+
Level  n 1 2 0 1 3 1 4 1 0 2 0 5 2 0
```
**Example**: node creation
```
Level| Percent chance to create
0    | 50%
1    | 25%
2    | 12.5%
3    | 6.25%
...  | ...
6    | 0.78125%
...  | ...
12   | 0.01220703125%
...  | ...
```
**Example**: Find 'I' in skip list: '->' pointers used in the search, '*' node is looked at in search.
```
       .
       .
       .
Start->|---------------------->|
       |------------>|-------->|
       |         |   |-------->|
       |   |     |   |---->|   | |
       | | |   | | | |>|   |   | |
       +=+=+=+=+=+=+=*=*=+=*=+=*=+=+
value  A B C D E F G H I J K L M N O
```
(extra) The node creation often has a max level that we can randomly roll for practical reasons and item count.

Tier 5.02: Trie (aka digital, radix, or prefix tree)
====================================================
Trie is an ordered container and a kind of search tree usually used with strings. Each tree node is a letter which implicitly takes all parent nodes as a prefix.

**Example**: Tree layout

The '*' indicates that this is the end of a string which was added to the trie. 
```
               root
              /    \
          ( a*)     ( i*)
         /     \        \
     ( t*)     ( b )    ( c )
      at      /         /    \
          ( e*)     ( e*)     ( b )
           abe       ice           \
                                   ( m*)
                                   icbm
```
This tree could find the strings: a, i, at, abe, ice, and icbm. 

This is a common container to use for simple text completion as you may traverse the tree from the current last character to reveal valid characters to complete the string.

(extra) This container is best when many strings share a common prefix.

Tier 5.03: DFA (aka DFSA, DFSM, finite state machine)
=====================================================
deterministic finite automaton (DFA) or deterministic finite state automaton (DFSA) or Deterministic finite state machine (DFSM) is a container used to find strings or symbols within a larger buffer. Unlike a trie, DFAs allow cycles so string recognition does not need to backtrack and can do many logical tricks while traversing with the external state to save even more time and memory.

**Example**: Find "nininam" in "nininininininam"
```
Start   -> (n) -> (i) -> (n) -> (i) -> (n) -> (a) -> (m)
                   |     /|     /
                   |<---/ |<---/ 
```                       
Finding a string looks through the given string letter by letter. If the current node you are on has a connection with the next letter goto it, otherwise go back to the start.

If not connected nodes have the letter we are looking for we go back to the beginning.

(extra) DFAs are great when you are trying to find a specific string in a much larger buffer since you never need to look at a character more than once. The costly part for a very small search space is building the DFA which may take longer than the search itself.

Tier 5.04: Quad and Oct Trees (conceptual containers)
=====================================================
Quad and Oct trees are used for spatial partitioning in 2D and 3D space respectively.

A quadtree divides a 2d space into 4 bounding squares with each square being further divided into smaller bounding squares in its child nodes.

**Example**: QuadTree
```  
Level 0                1                2
      +-----+-----+   /+-----+-----+   /+-----+-----+
      |  0  |  1  |  / |  |___ \   |  / |     | *## |
      |     |     | /  |    __) |  | /  |     |  ## |
      +-----+-----+/   +---|__ <---+/   +-----+--##-+
      |  2  |  3  |    |   ___) |  |    |   __|_##  |
      |     |     |    |  |____/   |    |   ##|##   |
      +-----+-----+____+-----+-----+____+-----+-----+
```

Oct trees devide 3d space into 8 cubes with each cube being further divided into smaller groups of 8 cubes.

Tier 6.00: pinned vector
========================
```
specs   Sorted   Unsorted   Description
Add     O(n)     O(c)       Add an item to an array which is large enough to hold the item
Remove  O(n)     O(c)       Remove an item from an array at a known index.
Find    O(logn)  O(n)       Find an item within the array by value
Grow    O(n)     O(n)       Increase the size of the array, to fit more items (OS dependent)
```
A pinned vector is an ordered container that utilizes the 64-bit address space and virtual memory to be infinite in size. It does this by reserving a large (anywhere from a few GBs-TBs) address space in virtual memory, then growing into that address space as the container needs the memory. The performance characteristics of a pinned vector are similar to an array, but give the advantage of never needing to resize.

**Example**: Reserve address 0-1,000,000,000 (1 gb)
```
Address:            0     524,288      1,000,000,000
                    |     |            |
actual memory used: |XXXXX|            |
address space used: |XXXXXXXXXXXX...XXX|
```
From the user's perspective, a pinned vector is just a massive array that only has random access on added/pushed items within the container. That is to say, you cannot access a reserved address which has not been first committed to memory. By adding an item, the pinned vector will commit the needed memory within the reserved address space.

(extra) In 64-bit computers, the address space in bytes is 1.84467441 × 10^10 gigabytes.

(extra) At the application layer, memory is always virtual, so the cost is already paid. The difference is that by explicitly informing the OS you can get contiguous memory. It should also be noted that not all OSs will support explicit virtual memory in such a way to allow for this sort of behavior.

(extra) One major benefit of a pinned vector is that pointers are stable and you never need to copy the items once they have been constructed to grow the array which often leads to massive performance gains on large (MBs) collections.

Tier 6.01: hash table array hybrid (Find a name) @INCOMPLETE
================================================
```
specs    Sorted   Description
Find     O(c)     Find item within the hybrid container
Add      O(n)     Add an item to the container which is large enough to hold the item
Remove   O(c)     Remove an item from the container.
Iterate  O(n)     Iterate over items in contiguous memory
Grow     O(n)     Grow the size of the container
```

@@@@   TODO TODO TODO @INCOMPLETE
```
in hashtable 0:  { *value, bucket index }
in hashtable 1:  { key, bucket index}
in bucket array: { key + value }
```

(extra) With a pinned vector grow can become O(c).
(extra) A reason why we don't use this everywhere is that even though it is O(c) for everything, it is much more expensive

Tier 6.02: Region allocator (aka Arena allocator)
=================================================
An arena or region allocator is a type of rapid allocator which assumes allocated types either have no external allocations or use the same arena allocator for the objects it owns. There are 2 basic operations in an arena allocator:

int allocate(int size): returns a block of memory of the requested size, returns an integer to make were in the arena this allocation started.
drop(int mark): deallocate all allocations after this mark, use 0 to deallocate everything.

Common Uses:
- Temporary allocator: An allocator whose contents it is logically illegal to keep a pointer to beyond some point in the program (usually a frame boundary, or event expiration, or scope lifespan).
- Node Allocator: Used by chaining hashtable, tree, DFA to quickly allocate and deallocate nodes quickly.
- String construction: Quickly construct dynamically sized strings for file paths or logging both of which are rapidly cleaned up after use using the mark function.

Tier 6.03: Intrusive Data Structures
====================================
An intrusive data structure is a containers in which the elements themself have access the container they are within. This sort of design of common for node based containers such as linked lists, trees, and graphs. A reason why you may want to use an intrusive data structure is for simpler threading synchronization, minimizie iteration over large list of objects/classes, and graph traversal optimizations. (ex. Jump Point Search, deterministic finite automaton (DFA), Game AI Behavior Trees)

Tier 6.04: Free List
====================
A free list is a list constructed within a pre-allocated block of memory. The idea is that you can keep track of a list of unallocated/unused items within memory by constructing a list where the item would normally exist in memory. This is great for memory and used by many allocators.

**Example**: Freelist in array

"ptr#" is where the pointer's data is held within the array.
```
Free list head-------->|
                       v
Array: |ITEM|ptr2|ptr3|ptr0|ITEM|ptr1|ITEM|ITEM|ptr4|
             ^  v_^  v v_________^  v           ^
             |_______|______________|           |
                     |__________________________|
```
Order of in-place free list: ptr0, ptr1, ptr2, ptr3, ptr4

References
==========
pinned_vector - https://www.youtube.com/watch?v=Ke1mJiGO-pU




# Incomplete 

@Array + HashTable hybrid for constant time fun stuff
@ DONE Pinned_vector (useful for games/ECS, "Infinite" vector on 64-bit OS using Virtual memory) <- https://www.youtube.com/watch?v=Ke1mJiGO-pU
@Colony (plf::colony) Look at this <- https://www.youtube.com/watch?v=wBER1R8YyGY
+

#4
@Set

#5


#6
@Multiset
@ Threaded. Local and Global lookup optimization. Use mutexes less
@ Pools https://www.cs.tau.ac.il/~shanir/concurrent-data-structures.pdf 1.4 Can give perf benefits for threads