These are primarily used to prevent naming conflicts and organize code in large projects.

```c
// defining the namespace
namespace group1 {
	// declaring the functions
	void function1();
	int function2();
}

// defining the functions outside for readability and maintainability
void group1::function1() {
	// function body
}
int group1::function2() {
	// function body
}
```
