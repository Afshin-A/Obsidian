This was a very interesting question that was posted on YouTube.
You have a list of integers. All but 1 integer are repeated 2 times. Find the integer that is listed only 1 time. But you cannot store any data.

We know that the [[XOR Encryption#XOR Logic|XOR operator is commutative and associative]].
We also know that $a \oplus a = 0$ and $a \oplus 0 = a$
$$\begin{align}
L=[1, 3, 2, 1, 2, 4, 4] \\
1 \oplus 1 = 0 \\
2 \oplus 2 = 0 \\
4 \oplus 4 = 0 \\
1 \oplus 0 = 1
\end{align}
$$

As you can see, if we loop around the list and perform the xor operation on all and add it up, we get the unique number in the list.

```python

result = 0
for num in L:
	result ^= num
return result
	
```