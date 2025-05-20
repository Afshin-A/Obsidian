This data structure was a pain in my ass to learn.

It's usually used for calculating prefix sums of an array: meaning the sum of all elements in a range (from i to j indices). Now, we can pre-compute a sum array and calculate the sum of that range in constant time:
```
Given j > i and

l = [ ... ]
s[j]   = l[0] + l[1] + ... + l[i-1] + l[i] + l[i+1] + ... + l[j]
s[i-1] = l[0] + l[1] + ... + l[i-1]

Then,
sum(i, j) = s[j] - s[i-1] = l[i] + l[i+1] + ... + l[j]
```

If we change an element in `l`, then we would have to recompute our prefix sum array from that point forward, which is pretty inefficient. Instead we use the **Fenwick tree data structure**, which calculates and updates prefix sums in O(log(n)) time.

We use a base 1 array, `f`, to represent the Fenwick tree. I.e. we ignore `f[0]` 


In a Fenwick tree, `f[i]` represents a range. This is called the range of responsibility for i. It's the sum of a contiguous number of elements in preceding `f[i]`.  How many elements, you ask? That depends on the least significant bit (LSB) in the binary representation of `i`. 

The least significant bit refers to the left most non-zero bit in `i`, and it is found by taking AND of `i` and `-i`. For example, if `i=10`,
```
 1010
&
 0110
 ____
 0010
```

So for example `f[7]` is only responsible for representing `l[7]`, while `f[8]` is responsible for representing `[1,8]` in `l`, 8 elements 
$$
\begin{align}
7_{2} = 011\underbracket{1} \\
8_{2} = \underbracket{1}000
\end{align}
$$
To find the sum, `s` from `[1,7]`, for example, we cascade our way down from 7 to 1. Here's how it works:
We know `f[7]` just represents `l[7]`
`f[6]` represents `l[6]+l[5]` because $6_{2}=0110$ and LSB of 6 is 2.
`f[4]` represents `l[4]+l[3]+l[2]+l[1]`
So, `s=f[7]+f[6]+f[4]`

From this example, we can come up with an algorithm for finding the sum `[1, j]` 

```python
def LSB(i):
	'''
	Returns the least significant bit of i
	'''
	return i & -i

def prefixSum(f: list[int], i: int) -> int:
	'''
	Return the sum of the range [1,i] inclusive
	'''
	sum = 0
	while i > 0:
		sum += f[i]
		i -= LSB(i) # cascading down
	return sum

def prefixSumRange(f, i, j):
	'''
	Return the sum of the range [i,j] inclusive
	'''
    # note how we substract from fenwick array at index i-1 instead of i
    # sum(i, j) = s[j] - s[i-1]
    # just like we did above, we have to use i-1 to make i inclusive
	return prefixSum(j) - prefixSum(i-1)
```


Worst case would be if the binary representation of `j` is all 1's. So the worst case time complexity of this method is O(log(n)) 


### Now, how do we update the Fenwick tree?
As we mentioned previously, if we change an element, we need to recompute all cells that are responsible (include) that cell. In other words, if we're updating a cell, we need to update all the cells that cover that cell we're updating too.



We do this by adding the least significant bit until we're out of bounds.
```python
def add(f, i, x):
	'''
	O(log(n))
	Add x to cell at index i in the femwick tree f
	'''
	while i < len(f):
		f[i] += x
		i += LSB(i)
```

### Okay, cool. But how do we even build the Fenwick tree?
The naive approach would be to use the `add` method to update each index in the Fenwick tree with the corresponding value from `l` (the original array). This would take `O(nlog(n))`, since there are `n` elements in `l` and each `add` will take `O(log(n))`. 

#### But we can do better in O(n)


![[Pasted image 20250516110230.png]]
Source: https://youtu.be/BHPez138yX8

```python
def construct(f):
	n = len(f)
	# create a copy because we're doing it inplace (?) 
	tree = f.copy()
	for i in range(n):
		j = i + LSB(i)
		if j < n:
			tree[j] += tree[i]
	return tree
```
### **Fenwick tree supports binary operations that are both associative and invertible.**
We cascade up to build the Fenwick tree. We cascade down to perform a range query. So as you can see, we go both ways. But these operations are independent. For each operation, the order of the operands is fixed and predetermined. So commutativity is not required.

Invertibility is also required for range queries. For summing, we had to calculate `s[j]-s[i-1]` to find the sum in `[i, j]` because we needed to cancel every element before `i`. So subtraction is required. Addition must be invertible. 

