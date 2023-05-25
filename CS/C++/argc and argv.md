```c++
int main(int argc, char** argv) {
	// some code
}
```
`argc` (argument count) signifies the number of command-line arguments
`argv` (argument vector, of type `char**`) is a pointer to a pointer to a character.
`char*` can be used to refer to an array of characters (i.e. a string) by pointing to the first character in an array. From there, we can use the memory address to navigate to the next memory blocks, until the null terminator `'\0'` signifies the end of the array.
In a similar way, `char**` can be used to refer to an array of `char*`, each of which represents a string.


![[char pointer pointer.jpg]]