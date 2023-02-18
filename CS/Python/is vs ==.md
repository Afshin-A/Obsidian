In python, `is` is an equality operator in python that checks memory addresses
`==` checks if the contents of two objects are the same.
```python
dict_1 = dict("one": 1, "two": 2, "three": 3)
# Alt way of initializing a dictionary (map in java) in python
# dict_1 = {"one": 1, "two": 2, "three": 3} 
dict_2 = dict1
dict_3 = dict_1.copy()

print(dict_1 is dict_2) # True
print(dict_1 == dict_2) # True

print(dict_1 is dict_3) # False
print(dict_1 == dict_3) # True
```

In java, it's the opposite: `==` checks if two objects refer to the same memory address. We could also compare the hashcodes of the two objects: `System.identityHashCode(a) == System.identityHashCode(b)` to check if `a` and `b` point to the same object. 
To compare contents,  some classes have an `.equals()` method, or implement the `Comparable` interface and override the `compareTo()` method.