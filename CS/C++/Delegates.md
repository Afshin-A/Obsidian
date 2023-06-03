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

It is possible to use function pointers for member functions, but we would have to call the function pointer an a class instance independently:
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
Delegates help by also encapsulating the object on which we want to call the function.

An obvious question here might be, since we are literally storing a lambda function in `delegate`, and lambda functions can encapsulate an object and a function, and can be passed as variables, why on earth would we need delegates? 

The answer is because lambdas do not have a specific type in C++. The compiler implicitly generates the types for these inline functions. Even though it is possible to use the `auto` keyword to store lambda functions or use templates to pass lambda functions to other methods, the latter is not always successful. C++ uses a feature called "template argument deduction" to automatically deduce the template types being passed to a generic method, without having to explicitly specify the types in the angle brackets. But this may not always be successful, especially when the types are too complex. 
```c++
template <typename Function>
void PerformOperation(Function operation) {
	operation();
}

int main() {
	int x = 1;
	int y = 2;
	PerformOperation([&x, &y]() {
		std::cout << "Sum: " << (x+y) << std::endl;
	});
}
```
Sometimes, we have to explicitly specify the types. 

### Benefits of abstraction: 
1. Abstraction
Here's a full program I wrote:
```c++
#include <iostream>
#include <functional>
#include <vector>
#include <string>

// Delegates can help with implementing abstraction.
// This function doesn't need to know anything about the body of "operation". As long as the argument type matches the parameter, "ProcessVector" will perform an "operation" on every element inside.
template <typename T>
void ProcessVector(const std::vector<T*>& vector, std::function<void(T*)> operation) {
	for (auto element : vector) {
		operation(element);
	}
}

int main() {
	// Using string pointers because I wanted to modify the strings while keeping the lambdas simple.
	std::string* afshin = new std::string("Afshin");
	std::string* macario = new std::string("Macario");
	std::string* tracy = new std::string("Tracy");
	std::string* nick = new std::string("Nick");
	std::string* cassandra = new std::string("Cassandra");
	std::string* lillian = new std::string("Lillian");
	std::vector<std::string*> stringPtrVector{ afshin, lillian, tracy, macario, cassandra, nick };
	
	// This delegate represents a function that returns void and takes in a string ptr
	// It is set to a lambda. The lambda takes no elements from the environment. It has a string ptr as parameter, and returns void. The body simply dereferences the pointer and prints the string to the console.
	std::function<void(std::string*)> printDelegate = [](std::string* element) { 
		std::cout << *element << std::endl;
	};


	// "ProcesVector" uses generics because we want the vector to be able to hold any type of variables. Here, we use <std::string>
	ProcessVector<std::string>(stringPtrVector, printDelegate);

	std::function<void(std::string*)> halveLengthDelegate = [](std::string* elementPtr) {
		// cuts the length of a string in half	
		std::string temp(*elementPtr);
		*elementPtr = temp.substr(0, temp.size() / 2);
	};

	//std::cout << halveLengthDelegate("Afshin") << std::endl;

	ProcessVector<std::string>(stringPtrVector, halveLengthDelegate);
	std::cout << std::endl;
	ProcessVector<std::string>(stringPtrVector, printDelegate);

	return 0;
}
```
2. Delegates act as event handlers in [[Event Driven Programming]]. They allow us to have loose-coupling (abstraction) between events and event handlers, such that one handler can respond to multiple events.
