And all odd numbers end with 1.

This is because all bits (except the last) in a number are a power of two and are therefore even. And when we add them all together, we get an even number. Only the last bit can be potentially 1 (because we have either $1 \times 2^0$ or $0 \times 2^0$). When it's 1, we're adding 1 to an even sum and the result is an odd number.

Using this, we can use the bit wise operations to determine if a number is even or odd:
```python
def isEven(num: int):
	return (num & 1) == 0
```


Alternatively we can use the more readable approach: 
```python
def isEven(num: int):
	return (num % 2) == 0
```
Apparently, the compiler/interpreter automatically converts this to the bitwise method for more computation efficiency anyways.