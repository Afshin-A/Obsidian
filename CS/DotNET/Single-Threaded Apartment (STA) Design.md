# Application binary interface
A strict set of rules that dictates how that compiled binary code interacts with the operating system, the hardware, or other compiled libraries.
For example, the GCC compiler follows these rules when outputting a binary file (executable, `.dll` library); the operating system knows how to parse and load CPU instructions into memory; the processor in turn knows how to load instructions and variables into which registers. The ABI defines data types and their sizes, OS system calls (e.g. I/O calls, etc.)

If the ABI is unchanged, your compiled application will still run, even after the operating system is updated, for example, 
Compiled applications are built for a specific ABI.

An ABI isn't created by a specific group of people. It has layers. Each layer is built on top of another by a different group. 
1. First there is the **hardware layer**: CPU manufactures define the **Instruction Set Architecture (ISA)**, including the exact instructions the CPU can do (`ADD`, `SUB`, `MOV`, etc.); the number of CPU registers, their names, sizes, and their primary purpose; data types the CPU supports; rules for how to access memory (also called **accessing mode**)
2. The system layer is where the OS lives and defines things like system calls, executable formats, and the **calling convention**, which is a set of rules that define exactly which CPU registers hold the first, second, and third arguments of a function, among other things. 
3. The language (compiler) layer: specification so that object files compiled by the *same* compiler can link together and understand each other's complex memory structures.

The rules for how the _execution environment_ (the CPU and Operating System) handles the _compiled machine code_.

TLDR; code must be compiled (prepared) in a way so the machine can blindly execute it. 
Okay. So it's understandable why there must be an ABI for the hardware and the OS, because the compiler needs to prepare machine code instructions according to a set of rules. But why does there need to be an ABI for compilers?
What does it mean for two applications to be "compiled together"?





#. thread affinity and its benefits
A thread gets bound to a specific CPU core
Reduces [[Cache Replacement Policies|cache misses]] and context switching


WPF enforces strict thread affinity. There is only one main UI thread. 
Only the thread that creates a UI element can modify that element.
So other threads, for example created by background tasks, cannot modify UI elements or else WPF will throw an exception
Instead, the background thread must return data to the main thread using a *`Dispatcher`* and UI elements are subsequently updated. 


This solves concurrency problems.
