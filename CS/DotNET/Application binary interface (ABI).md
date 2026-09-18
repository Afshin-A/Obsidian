# Application binary interface (ABI)
An ABI includes a strict set of rules for how compiled binary code interacts with the operating system, the hardware, and other compiled libraries.
For example, the GCC compiler follows these rules when outputting a binary file (e.g. an executable like `.exe` on Windows or an elf file on Linux, and `.dll` library files). The operating system knows how to parse and load CPU instructions into memory

The CPU is fundamentally a "dumb" execution engine—it simply fetches binary instructions and does exactly what they say. It does not actually "know" anything about the ABI, nor does it autonomously decide which registers to use for variables or function arguments based on ABI rules. *It is the **compiler** that knows the ABI rules.* The compiler generates an instruction (MOV a value to this register), and the processor blindly executes it later. 

An interface is a two way street. It's an agreement between two parties. The machine blindly applies the ABI rules to the code, which means the compiled machine code _must be actively formatted_ by the compiler to comply with those rules

~~; the processor in turn knows how to load instructions and variables into which registers.~~ All key players in the system—the compiler, the OS, and the hardware—follow the same rules

The ABI defines the rules for how the _execution environment_ (the CPU and Operating System) handles the _compiled machine code_.

Compiled applications are built for a specific ABI. Therefore, if the ABI is unchanged, the compiled application will continue to run, even after the operating system is updated. 

You can change the internal implementation of a function inside a library our application depends on. As long as the ABI hasn't changed, our application will continue to run without having to recompile the application.


**TLDR**; Code must be compiled (prepared) in a specific way so the machine can blindly execute it. 

If two pieces of code are compiled with different ABIs, Function A might put its arguments in the CPU registers, but Function B might be looking for them on the stack. Function B will read garbage data, and the program will likely crash.
## Who Creates an ABI?
An ABI isn't created by a specific group of people. It has layers, where each is built on top of another layer created by a different group. 
1. First there is the **hardware layer**: CPU manufactures define the **Instruction Set Architecture (ISA)**, including the exact instructions the CPU can do (`ADD`, `SUB`, `MOV`, etc.); the number of CPU registers, their names, sizes, and their primary purpose; data types the CPU supports; rules for how to access memory (also called **accessing mode**)
2. The system layer is where the OS lives and defines things like system calls, executable formats, and the **calling convention**, which is a set of rules that define exactly which CPU registers hold the first, second, and third arguments of a function, among other things. 
3. The language (compiler) layer: specification so that object files compiled by the *same* compiler can link together and understand each other's complex memory structures.


## What does it mean for two applications to be "compiled together"?













[[WPF#Single-Threaded Apartment (STA) Design in .NET WPF|Read about the role of the ABI in Single-Threaded Apartment (STA) design in .NET WPF.]]

