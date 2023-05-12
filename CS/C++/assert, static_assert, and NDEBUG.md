# assert
Used for run time checks. If the assertion condition is `false`, the program would terminte. You can optionally include an error message:
```
#include <cassert>
#include <string>
int main() {
	bool condition = false;
	string errorMessage = "Error";
	assert(condition, errorMessage);
	return 0;
}
```

# static_assert
Used for compile time checks. So the conditions used for this type of assertion must be available during compile time (like [[constexpr||constant expressions]] denoted by `constexpr`).

# NDEBUG
Also known as **[[Conditional Compilation]]**.
By defining this macro in our code before the `<cassert>` header, we can basically enable and disable assertions in our code. The code in `cassert` is written in a way that if `NDEBUG` is not defined, then assertions will not run. This is particularly useful for releasing final builds of our program, so we would not have to manually remove all assertions from the code.
```c
#define NDEBUG // Defining this will disable all assert and static_assert checks in the code. NOTE: must define it BEFORE cassert

#include <cassert>

int main() {
	// code
	assert(false, "Error message 1");

	// code
	assert(false, "Error message 2");

	// code
}
```