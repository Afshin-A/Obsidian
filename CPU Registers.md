# RBX
historically used to store the memory address of the head of an array or the top of a stack—both of which are contiguous in memory. We can then use an offset to find any location in these data structures.

but it is a general purpose memory, and like any others, it can technically be used to store anything: arithmetic and bitwise operation results, memory addresses,  
That means other register can be used to store a base pointer as well



# Virtual memory segments




```cardlink
url: https://youtu.be/2htbIR2QpaM
title: "Memory Segments in C/C++"
description: "A brief overview of memory segmentation in C and C++."
host: youtu.be
favicon: https://www.youtube.com/s/desktop/1dd30f43/img/favicon_32x32.png
image: https://i.ytimg.com/vi/2htbIR2QpaM/maxresdefault.jpg
```

An applications memory is divided into 2 main parts:
- **Code** (or text) is where the CPU instructions loaded from the binary file are stored. This section is read-only in order to prevent source code from modifying itself.
- **Data** - this is where the application data lives, and it is categorized into static and dynamic sections:
	- **Static** is divided into initialized and uninitialized sections:
		- **Initialized** (`.data` section). This sub-section stores initialized static and global variables. These variables are explicitly initialized by the developer in the source file, so they exist in the compiled binary file. This section is read and writable, and has a fixed size.
		- **Uninitialized**, also known as the `.bss` (Block Started by Symbol) section, this subsection stores uninitialized global and static variables. The compiled binary file only stores their size (the size of their data type), and they get initialized when the memory stack is created. We can strategically use this in order to keep the binary file small. Imagine storing an array of 100,000 0s in the file. This also section is read and writable, and has a fixed size.
	- **Dynamic**
		- **Heap** stores user defined objects that we after instantiating classes. This section is variable in size. This is also where memory leaks happen. 
		- **Stack** stores local variables for function calls. Each function call gets placed on top of the stack, and when the function returns, it is popped off the stack. Last in, first out. 



Read more about [[Stack vs. Heap in System Memory]] 

Does every process get a memory segment, or does every thread?
What is virtual memory?
https://youtu.be/fGP6VHxqkIM

