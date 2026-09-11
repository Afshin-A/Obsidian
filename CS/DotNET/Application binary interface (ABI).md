# Application binary interface (ABI)
An ABI includes a strict set of rules for how compiled binary code interacts with the operating system, the hardware, and other compiled libraries.
For example, the GCC compiler follows these rules when outputting a binary file (e.g. an executable like `.exe` on Windows or an elf file on Linux, and `.dll` library files). The operating system knows how to parse and load CPU instructions into memory; the processor in turn knows how to load instructions and variables into which registers. All key players in the system—the compiler, the OS, and the hardware—follow the same rules

The ABI defines the rules for how the _execution environment_ (the CPU and Operating System) handles the _compiled machine code_.

Compiled applications are built for a specific ABI. Therefore, if the ABI is unchanged, the compiled application will continue to run, even after the operating system is updated.

**TLDR**; Code must be compiled (prepared) in a specific way so the machine can blindly execute it. 
## Who Creates an ABI?
An ABI isn't created by a specific group of people. It has layers, where each is built on top of another layer created by a different group. 
1. First there is the **hardware layer**: CPU manufactures define the **Instruction Set Architecture (ISA)**, including the exact instructions the CPU can do (`ADD`, `SUB`, `MOV`, etc.); the number of CPU registers, their names, sizes, and their primary purpose; data types the CPU supports; rules for how to access memory (also called **accessing mode**)
2. The system layer is where the OS lives and defines things like system calls, executable formats, and the **calling convention**, which is a set of rules that define exactly which CPU registers hold the first, second, and third arguments of a function, among other things. 
3. The language (compiler) layer: specification so that object files compiled by the *same* compiler can link together and understand each other's complex memory structures.


## What does it mean for two applications to be "compiled together"?


Okay. So it's understandable why there must be an ABI for the hardware and the OS, because the compiler needs to prepare machine code instructions according to a set of rules. But why does there need to be an ABI for compilers?









[[WPF#Single-Threaded Apartment (STA) Design in .NET WPF|Read about the role of the ABI in Single-Threaded Apartment (STA) design in .NET WPF.]]

