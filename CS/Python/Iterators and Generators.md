iterators are exhaustive just like generators
generators are iterators, just a simpler implementation

memory efficient because we don't load all the data, just the data we need where the iterator left off when it was last used


Generators are a type of iterators. Generators are a more concise and pythonic form of an iterator. 


These are what make an object iterable in python. We need to implement a `__iter__()` method in the class.

First of all, an iterator has to be defined as a class.
```python
class HashMapIterator:
    def __init__(self, keys, values):
        self.keys = keys
        self.values = values
        self.index = 0

    def __iter__(self):
        return self

    def __next__(self):
        while self.index < len(self.keys):
            if self.keys[self.index] != None and not isinstance(self.keys[self.index], Tombstone):
				self.index += 1
				return self.keys[self.index], self.values[self.index]
            self.index += 1
        raise StopIteration

```

And then in our `HashMap` class we, we instantiate and return the Iterator class:
```python
class HashMap:

	...

	def __iter__(self):
		return MashMapIterator(self._keys, self._values)

```



```python
class HashMap:

	...

	# generator  
    def __iter__(self):
        for i in range(self._capacity):
            if self._keys[i] is not None and self._keys[i] != self._TOMBSTONE:
                yield (self._keys[i], self._values[i])
```
