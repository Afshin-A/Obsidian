These are typically used for managing files or database connections. In general, its purpose is to ensure resources are properly managed and freed when they are no longer in use.

The general syntax for context managers is as follows. In this example, we're opening and reading from a file.
```python
with open(file) as f:
	f.read()
```
Internally, the context manager uses two methods `__enter()__` and `__exit()__`. The first method initializes the resources and returns the results, which is saved in the variable that comes after the `as` keyword.
Once the code inside the `with` statement is executed, the `__exit()__` method is called to release resources and clean up. 
If an exception is thrown in the `with` block, it is sent to the `__exit()__` method, meaning this method will execute regardless.

```python
class CustomContextManager:
    def __enter__(self):
        print("Entering the context")

    def __exit__(self, exc_type, exc_value, traceback):
        if exc_type is not None:
            # An exception occurred in the 'with' block
            print(f"Exception type: {exc_type}")
            print(f"Exception value: {exc_value}")
            # Handle the exception or perform cleanup
            # Returning True suppresses the exception and program execution will not halt. Returning False propagates the exception
            return True  # Exception is handled, and program continues execution

# Using the context manager with the 'with' statement
with CustomContextManager():
    print("Inside the context")
    # Uncomment the next line to simulate an exception
    # raise ValueError("An error occurred")

# If __exit__ returns False, this will not print
print("Outside the context")
```