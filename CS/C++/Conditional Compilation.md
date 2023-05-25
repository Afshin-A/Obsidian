# The `#define` Directive
The `define` directive is basically a text preprocessor. During compilation, it goes through the code and replaces all instances of the statement `Error_LOG` with `std::coud << message << std::endl;`. It can also take arguments.

```c++
#include <iostream>

#ifdef ERROR_LOG // if it is already defined
#define ERROR_LOG(message) std::cout << message << std::endl; // redefine it this way
#else
#define ERROR_LOG(message) // if it is not defined, empty definition means it does nothing.
#endif

int main() {

	ERROR_LOG("Could not calculate");
	
	return 0;
}
```

## Multi-line Macro
```c++
#define ERROR_LOG(message) do { \
		std::cout << "Error 1" << std::endl; \
		std::cout << "Error 2" << std::endl; \
		std::cout << "Error 3" << std::endl; \
} while (0);

```
Each line of code must end with a backslash. The reason we place the code in the do-while loop is to wrap the code inside and treat it as one statement, under one scope. We also avoid potential syntax issues.  The do-while loop is executed only once because the `while` condition (0) evaluates to false.

# `typedef`
Allows you to give an alias to a type name (or class name). For example, we could rename `std::string` to `str`. This comes in handy for longer names. `using` is preferred to `typedef`, which is mostly used because of compatibility with older, C code bases.
```c
#include <iostream>
#include <string>

typedef std::string str;

int main() {
	str message = "Hello World!";
	std::cout << message << std::endl;

	return 0;
}
```

# `using`
An alternate and preferred way to `typedef`, `using` has a slightly different syntax:
```c
#include <iostream>
#include <string>

using str = std::string;

int main() {
	str message = "Hello World!";
	std::cout << message << std::endl;

	return 0;
}
```