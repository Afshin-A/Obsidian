A feature of C#, delegates are not native in C++ and are used via the header `functional`.
Delegates are like more advanced function pointers that can store all types of function pointers, like lambdas, function objects, or standalone functions. For example, for member functions (i.e. functions from a class that depend on fields from that class), delegates are ideal because they can store both the function pointer and the object to call the function on.
There are a few different ways to instantiate delegates:

```c++
#include <iostream>
#include <functional>

class MyClass {
public:
	void MyMemberFunction() {
		std::cout << "MyMemberFunction called." << std::endl;
	}
};

int main() {
	MyClass obj;
	std::functional<void()> delegate = [&obj]() { obj.MyMemberFunction() };
}

```

#### Explanation of the Lambda Function
```c++
[&obj] () -> void { obj.MyMemberFunction() };
```
`[&obj]` captures the variable by reference from the environment to be used inside the lambda function.
`()` holds the argument types and names for the lambda function, but in this case, it is empty because there are no arguments.
`-> void` signifies the return type of the lambda function, and can usually be ignored.
`{}` enclose the body of the function. The closing curly bracket must be followed by a semicolon.

An obvious question here might be, since we are literally storing a lambda function in `delegate`, and lambda functions can encapsulate an object and a function, and can be passed as variables, why on earth would we need delegates? 


It is possible to use function pointers, but we would have to call the function pointer an a class instance independently:

```c++
#include <iostream>


int main() {
	MyClass obj;
	// Note: The use of & to retrieve memory address is mandatory for member functions, but not for standalone functions.
	void(MyClass::*memberFuncPtr)() = &MyClass::MyMemberFunction;
	(obj.*memberFuncPtr)();

	return 0;
}
```