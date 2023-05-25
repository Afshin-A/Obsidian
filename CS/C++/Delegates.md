A feature of C#, delegates are not native in C++ and are used via the header `functional`.
Delegates are like more advanced function pointers that can store all types of functions, like lambdas, function objects, or standalone functions. For example, for member functions (i.e. functions from a class that depend on fields from that class), delegates are ideal because they can store both the function pointer and the object to call the function on.
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