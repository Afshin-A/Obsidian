We can print an argument-value dictionary of the function's parameters
```python
def example(parm1, parm2):
	print(locals())
```

# Is Python Pass by Value or by Reference?
In python, mutable objects are passed by reference, whereas immutable objects (i.e. literals) are passed by value.