When using exceptions, it is necessary to include the header `<exception>` in the program. But, some other headers such as `<iostream>` and `<string>` already include `<exception>`.

## `noexcept` Keyword
`noexcept` assures the compiler that a function does not throw an exception. This can lead to optimizations. It can also be used to set the minds of users at ease. But a "noexcept" function can still throw exceptions, so be very careful when using the keyword in function headers.
`noexcept()` can be used as a method to determine if a function is marked as "noexcept". If so, it returns 1, otherwise 0.

## Types of Exceptions
Unlike Java, in C++, not all exceptions are derived from one base class. 
1. `std::exception`
2. `std::runtime_error`
3. `std::logic_error`
4. 

## Why Create Custom Exceptions
While it may seem that creating a separate class is unnecessary when we just use `std::exception` with a custom message, creating a custom exception allows us to distinguish different kinds of exceptions from the general types when using exception handlers. We may add more functionality to these classes. In addition, we can add clarity to the nature of the errors just by using a good class name.

```c++
#include <iostream>
#include <exception>

class CustomException : public std::exception {
public:
	// Constructor uses member initlaizer list
	CustomException(const char* message) : _message(message) {}
	// The order of the keywords (const, noexcept, and override) is absolute and cannot be changed 
	// We technically do not need to override this method because it does the same thing as it does in the parent class, which is returning the error message. So we rely on inheritance to port over the same functionality from the parent class.
	const char* what() const noexcept override {
		return _message;
	}
private:
	const char* _message;
}
```

## catch-all
```c++
int main() {
	try {
		// some code that may throw an exception
	}
	catch (const CustomException& ce) {
		std::cout << e.what() << std::endl;
	}	
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	// The "catch-all" handler handles any and all other exceptions not caught by above handlers
	catch (...) {
	
	}
}
```
