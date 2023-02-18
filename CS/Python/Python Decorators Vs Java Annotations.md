## Python Decorators
When we decorate a function in Python, we are adding more functionality to that function. Let's explore this with an example:
```python
@timer
def my_function():
	# some code
```
`timer` is an ordinary Python function. Furthermore, executing the above code is equivalent to executing the `timer` function with `my_function` as its argument.
```python
import time

def timer(function):
	def wrapper(*args, **kwargs):
		start_time = time.time()
		results = function(*args, **kwargs)
		stop_time = time.time()
		print(f"Execution time: {execution_time}" % stop_time - start_time)
		return results
	return wrapper

@timer
def my_function():
	time.sleep(2)
```

To summarize, in actuality, we're executing `timer(my_function)`. `timer` takes in `my_function`, defines a new function that adds more functionality to it, then returns the new function--all without modifying the contents of the original function.

## Java Annotations