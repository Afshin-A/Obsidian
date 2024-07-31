cpus have thousands and thousands of built in object codes (sequences of binary bits), which are instructions for a cpu to do something. cpus have different architectures, so these codes are different across different cpus, which is why software is not always cross compatible. 
there are also different assembly syntaxes, but here we focus on ATT syntax on intel 32 bit x86 assembly because it is very popular. majority of 32 bit machines follow this arcihtecture.
object code is a sequence of operation codes 
assembly is basically the human readable version of object code
compilers optimize code to run faster, making it harder to decipher assembly

software reverseing is done at 2 levels
- operating system - identidying program structures as they interact with os (by means of io, etc)
- code - literally going through assembly code

so you need to understand os, cpu architecture, assembly syntax, compilers, linkers, assemblers and deassemblers, etc.

modern IA-32 processors execute code in parallel for more efficiency, but assembly (machine code) was designed to run sequentially

