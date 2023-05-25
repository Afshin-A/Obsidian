As the name suggests, these are pointers to functions and can be passed as arguments to other functions. The general syntax looks like the following:
```
returnType(*pointerName)(param type1, param type2, ...)
```

```c++

int getNumber() {
	return 5;
}

int add(int a, int b) {
	return a + b;
}

int main() {
	int(*funcPtr1)() = getNumber;
	std::cout << funcPtr1 << std::endl; // prints a memory address
	std::cout << funcPtr1() << std::endl; // prints 5

	int(*funcPtr2)(int, int) = add;
	std::cout << add(2, 3) << std::endl;
	std::cout << funcPtr2(2, 3) << std::endl;
}
```


## Why Use Function Pointers?
The following sorting methods, the aptly named `sortDescending` and `sortAscending`, sort a given vector in descending and ascending order. You will notice the **only difference between the two is when we compare the adjacent elements in the vector.** 
In `sortDescending`, we check if an element is smaller than the next element. If it is, we swap their places. So the larger element comes before the smallest element, creating a descending order when the algorithm is finished.
```c++
#include <functional> // For std::swap()

template <typename T>
void sortDescending(std::vector<T>& vector) {
	// Note that the  &  means vector is passed by reference, not copied. i.e. function performs operations on original vector, not a copy.
	for (size_t i = 0; i < vector.size(); i++) {
		for (size_t j = i + 1; j < vector.size(); j++) {
			if (vector[i] < vector[j]) {
				// Eliminates the need to write a separate swap method.
				std::swap(vector[i], vector[j]);
			}
		}
	}
}

template <typename T>
void sortAscending(std::vector<T>& vector) {
	for (size_t i = 0; i < vector.size(); i++) {
		for (size_t j = i + 1; j < vector.size(); j++) {
			if (vector[i] > vector[j]) {
				std::swap(vector[i], vector[j]);
			}
		}
	}
}
```

We can eliminate the redundancy by having only one method. As an argument, this method will take in a function that will do the comparison.

```c++
template <typename T>
bool ascendingCheck(T a, T b) {
	return a > b;
}

template <typename T>
bool descendingCheck(T a, T b) {
	return a < b;
}

template <typename T>
void printVector(std::vector<T>& vector) {
	// When the compiler is parsing the template, it doesn't know if  std::vector<T>::iterator  is a type or a variable.
	// So we use the keyword  typename  to explicitly tell the compiler this is a type.
	// We can also use  auto  to allow the compiler to automatically deduce the type and make things simpler.
	for (typename std::vector<T>::iterator iter = vector.begin(); iter != vector.end(); ++iter) {
		std::cout << *iter << "\t";
	}
	std::cout << std::endl;
}

/*
* Just a simple (and inefficient), sorting algorithm to demonstrate the use of function pointers.
* This method uses function pointers as argument, which determines the direction of the sort (ascending or descending).
* Without the use of the function pointers, we would have to write this function twice and implement the comparison checks differently, twice.
*/
template <typename T>
void sort(std::vector<T>& vector, bool(*sortingOrder)(T, T)) {
	for (size_t i = 0; i < vector.size(); i++) {
		for (size_t j = i + 1; j < vector.size(); j++) {
			if (sortingOrder(vector[i], vector[j])) {
				std::swap(vector[i], vector[j]);
			}
		}
	}
}

int main() {
	bool(*ascendingFuncPtr)(int, int) = ascendingCheck;
	bool(*descendingFuncPtr)(int, int) = descendingCheck;

	//sort in ascending order
	sort(testVector, ascendingFuncPtr);

	// sort in descending order
	sort(testVector, descendingFuncPtr);

	return 0;
}
```