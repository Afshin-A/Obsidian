---
~
---
First we convert the integers to bits by continuously dividing by two and saving the remainders.

For example, we have 13 and 5
```
1101
0101
```
When two bits are 1, the result is 0. When one bit is 1 and the other is 0, the result is 1. And of course adding two 0's is 0. This is the ==exclusive or== operation.
Now we can deal with the carries. When two bits are 1, we have to carry over a 1 to the next bit. This is done by first doing the bitwise and operation, followed by the bitwise right shift operation:
```
carry = (a & b) << 1
a = a ^ b
```

First we XOR a and b
Then we XOR the result with the carry
We continue this until the carry is 0


```python
def add(a, b):
    carry = b
    while carry != 0:
        carry = (a & b) << 1
        a = a ^ b
        b = carry
    return a
```

```
1101  15
0101  3
----
1000  result
1010  carry
----
00010
10000
-----
10010 18
```
This is exactly the adding logic