First, we must include the `<memory>` header in our program to use smart pointers.

## Unique Pointers
Memory is automatically deallocated at the end of the scope of the pointer. Helps avoiding memory leaks.
```c++
	// Creating
std::unique_ptr<int> unPtr1 = std::make_unique<int>(25);
std::cout << unPtr1 << std::endl;
	
// Dereferencing
std::cout << *unPtr1 << std::endl;
```

Unique pointers cannot be shared, so the following will cause compilation error:
```c++
std::unique_ptr<int> unPtr2;
// This will cause an error
unPtr2 = unPtr1;
```
In other words, only one unique pointer can represent a memory address at a time. However, it is possible to move ownership from one pointer to another:
```c++
unPtr2 = std::move(unPtr1);
```
This makes `unPtr1` to be `null` and an exception will be thrown for dereferencing it:
```c++
std::cout << *unPtr1 << std::endl;
```
As mentioned, memory will be freed and the object will be destroyed as soon as we leave the pointer's scope:
```c++
{ // This creates a custom scope
	std::unique_ptr<MyClass> unPtr3 = std::make_unique<MyClass>();
}
// unPtr3 is null when we reach here
```


## Shared Pointers
Unlike unique pointers, multiple shared pointers can point to the same memory location.
```c++
{
	std::shared_ptr<MyClass> shPtr1 = std::make_shared<MyClass>();
	/* code to be continued below */
```
Shared pointers can keep track of how many pointers to a memory location exist. That number can be found by using the `std::shared_ptr::use_count()` function.
Individual shared pointers are un-usable when they reach the end of their scopes. At that point, the use count is reduced by 1. The memory is deallocated when there are no more pointers to that memory location, i.e. when the count is 0.
```c++
/*  ... code from above ... */
	// prints 1
	std::cout << "Shared count: " << shPtr1.use_count() << std::endl;
	{
		std::shared_ptr<MyClass> shPtr2 = shPtr1;
		// prints 2
		std::cout << "Shared count: " << shPtr1.use_count() << std::endl;
	}
	// prints 1
	std::cout << "Shared count: " << shPtr1.use_count() << std::endl;
}
// Shared pointer should be deallocated at this point
```


## Weak Pointers
Weak pointer are used to observe objects. Where a shared pointer will add to an object's total number of pointers, and thus keep that object alive, a shared pointer does not keep objects alive because it doesn't add to the pointer count.
```c++
/* code from above */
std::weak_ptr<int> wePtr1;
	{
		std::shared_ptr<int> shPtr1 = std::make_shared<int>(25);
		wePtr1 = shPtr1;
	}
```


## Full Source Code
```c++
#include <iostream>
#include <string>
#include <memory>

class MyClass {
public:
	MyClass() {
		std::cout << "MyClass object created." << std::endl;
	}
	~MyClass() {
		std::cout << "MyClass object destroyed." << std::endl;
	}
};

int main(int argc, char** argv) {
	std::unique_ptr<int> unPtr1 = std::make_unique<int>(25);
	std::cout << unPtr1 << std::endl;
	// Dereferencing
	std::cout << *unPtr1 << std::endl;
	// Cannot share pointers. 
	std::unique_ptr<int> unPtr2;
	// This will cause compilation error
	// unPtr2 = unPtr1;
	// Moving ownership of pointers
	unPtr2 = std::move(unPtr1);
	std::cout << *unPtr2 << std::endl;
	// unPtr1 will now be null and an exception being thrown for dereferencing it.
	// std::cout << *unPtr1 << std::endl;
	{
		//Object will be destroyed as soon as leaving the scope
		std::unique_ptr<MyClass> unPtr3 = std::make_unique<MyClass>();
	}

	{
		// Shared pointers
		std::shared_ptr<MyClass> shPtr1 = std::make_shared<MyClass>();.
		std::cout << "Shared count: " << shPtr1.use_count() << std::endl;
		{
			std::shared_ptr<MyClass> shPtr2 = shPtr1;
			std::cout << "Shared count: " << shPtr1.use_count() << std::endl;
		}
		std::cout << "Shared count: " << shPtr1.use_count() << std::endl;
	}
	std::cout << "Shared pointer should be deallocated before this message appears" << std::endl;
	// Weak pointer
	std::weak_ptr<int> wePtr1;
	{
		std::shared_ptr<int> shPtr1 = std::make_shared<int>(25);
		wePtr1 = shPtr1;
	}

	return 0;
}
```

## Smart Pointer Methods
1. `.get()` returns the underlying raw pointer.
2. `.reset()` releases the memory by deleting the object pointed to, and sets the pointer to null..
3. `.use_count()` returns the total number of shared pointers to an object.
4. `.expired()` checks if a weak pointer has expired (if the object it points to has been deallocated).
5. `.lock()` converts a weak pointer to a shared pointer.

In addition, smart pointers override  `operator bool()` and can be directly used as Boolean statements in `nullptr` checks. Recall that `nullptr` evaluates to `false`.
Smart pointers also support comparison operators. You can check if they point to the same memory location by using `==` or `!=` operators. 