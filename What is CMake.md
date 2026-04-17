# The C++ Compilation Process
Unlike interpreted programming languages like Python and JavaScript, where an interpreter converts code to machine code line by line, C++ compilation involves a few more intermittent steps:
1. **Preprocessor** resolves macros and include statements. These are simply replaced by their definitions. Entire files are merged together to produce one temporary file in memory.
2. **Compiler** converts the file to assembly code.
3. **Assembler** converts assembly to machine code (`.o` files). 
4. **Linker** resolves cross-file function calls, standard library, and external libraries.
5. Finally, we get an executable file (`.exe` or `.out`)

The reason the compilation process is broken into separate steps is because of efficiency and scale ==(Explain?)==

For Java, the JVM does the linking dynamically at runtime.

For C++, however, all the linking is done at build time by the developer. We need to define the following:
- Which `.cpp` files to compile
- Which `.o` files to link
- Which libraries to include
- Which flags to pass

But in a real-life project with many source code files, manually entering commands for each step quickly becomes challenging.  
So, we need a **build automation tool** that essentially reads a build file and runs the necessary shell commands in the correct order for us.
Tools like *Ninja* and Make *track* which `.cpp` produced which `.o`, which headers affect which files, and what needs rebuilding after a change.

The C++ compiler (g++ by GNU, clang++, and cl.exe from Microsoft Visual C++) is what actually compiles compiles code in the aforementioned steps. 
CMake basically creates configuration for these automation tools.

- Incremental builds
- Cross-platform builds
- Dependency tracking
- Automation

