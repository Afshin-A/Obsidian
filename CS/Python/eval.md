The `eval` method evaluates and executes strings as python expressions. So for example,
```python
eval("print('Hello world!')")
```
prints `Hello world!` to the console.

Suppose we're writing lists into a file to retrieve later. `file.read()` will retrieve a string. We can use the `eval` function to convert the string to a list, then save it to a variable.
```python
with open("lists") as file:
	list_var = eval(file.read())
```

I've seen this function be used in the Linux terminal when setting up git

WARNING: because `eval` can evaluate any expression, it is not safe to use, especially with untrusted data. 
A safer alternative is the `ast.literal_eval` function. It evaluates only literal values (like strings, numbers, tuples, lists, dictionaries, booleans, and None) and throws a `ValueError` if the evaluee is anything else (like function calls, control flow structures, or arbitrary code execution)