It works by first evaluating and implicitly creating a tuple from the expressions on the right-hand side of the equality, then unpacking the tuple into the variables on the left-hand side. For example, we can swap elements from a list without the use of a temporary variable:
```python
ul = [1, 10, 2, 4, 7]

ul[0], ul[1] = ul[1], ul[0]
# it's as if we're unpacking the tuple (10, 1) into ul[0] and ul[1] respectively
```

In python, a `,` alone is sufficient to denote a tuple; parenthesis are not required. So, `10, 1` is considered a tuple, and the following would print `True`:
```python
t = 1, 10
print(isinstance(t, tuple))
```