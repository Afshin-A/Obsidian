
Every function gets their own **stack frame** that is pushed into the **call stack**.
The **stack frame** stores things like parameters passed by the caller, local function variables, return address to the caller.
The **call stack**, just like the data structure, is FIFO (first in, first out). Newer functions get popped first because they need to be resolved first. When the function returns, its stack frame gets popped from the call stack.

A **stack pointer** points to the top of the call stack

The call stack has a fixed, pre-defined size

**Each thread gets its own call stack. But threads in a process share the heap memory for that process.** ==NEED to elaborate further on this

Each process gets its own [[Virtual Memory|virtual memory space]]. 


The **heap** is memory that is managed by the operating system and it persists during the entire runtime of an application
Heap memory is not related to heap data structure.
memory allocation in Heap is dynamic, and therefore slower. It needs to look for empty memory block 
it handles garbage collection
heap memory is only limited by the available memory in the system

in C++, objects created using the `new` or `malloc` (in C), as well as static values, are stored in the heap.
It is the programmer's responsibility to explicitly de-allocate memory from the heap using `delete` and `free` (in C) functions.



==Actual objects are stored in the heap while their references are used in the stack.==

**Memory fragmentation**. The heap is not a continuous block of memory. As we allocate and de-allocate memory, we might end up with many small empty blocks that are not big enough for a new object. It's like playing TenTrix, a variation of the game Tetris. There may be lots of empty blocks, but not enough space for new objects. 

Other problems with heaps include 
- Dangling pointers - pointers that point to freed memory
- Memory leaks, forgetting to deallocate memory from the heap before the function returns, for example. It's when no pointers point to persistent memory, that memory becomes inaccessible.

The stack moves downwards, while the heap moves upwards 


### References
<iframe width="560" height="315" src="https://www.youtube.com/embed/9loizVWAk1M?si=HqDPEkC78SlNuo4v" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
