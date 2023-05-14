# String Literals `const char*`
```c++
const char* message = "Hello world!";
```
This is a string literal. It is stored in read-only memory as constant and immutable. Since they have known values at compile time, we do not need to initialize it for use in the source code: for example, we can just pass `"Hello world!"` as a function argument. 

```c++
#include <string>
...
std::string message = "Hello world!";
message += " My name is Afshin.";
```

# Strings `std::string`
This is a string. It is stored in the heap of the application and is mutable, with much more functionality provided by the string library.

So, a string not defined as `std::string` is a string literal.

Behind the scenes, C++ initializes a temporary string (`std::string`) using the string literal (`const chat*`), and uses a copy constructor to initialize `message`.

```c++
std::string message = "Hello world!";
```

But we can also directly initialize `message` without the temporary object:
```c++
std::string message("Hello world!");
```

# C-Style Strings `char*`

Null terminated sequence of characters inherited from the C programming language. These are mutable. It's similar to [[Strings and String Literals in C++#Character Array `char[]`|character arrays]], but it doesn't carry any information about the array, like size. It's simply a pointer to the first character in the sequence of characters, so we can initialize it with a pointer. **An array variable without the brackets is considered a pointer.**
But be warned that we cannot assign string literals to them, because literals are immutable. Consider the following:
```c++
const char* stringLiteral = "Hello"; //valid
char* cString1 = "Hello"; //invalid
char* cString2 = stringLiteral //invalid
char[] charArray = "Hello"; //valid
cString = charArray //valid because an array variable (without the brackets) is considered a pointer.
```

# Character Array `char[]`
Fixed size, mutable members, carries some information about its constituents like indices and size (unlike `const char*` and `char*`).