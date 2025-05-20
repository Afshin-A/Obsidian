Similar to the [[Fenwick Tree (Binary Indexed Tree)]], the segment tree is capable of performing an efficient O(log(n)) query in a range. For example: find the sum from in [i, j].
In addition to sum, segment tree is also used with other binary, **associative** functions.
These include XOR (and other bitwise operations), GCD, multiplication, etc..

An associative function is defined as follows:
$$
a \ast b \ast c = a \ast (b \ast c) = (a \ast b) \ast c
$$
How we group the elements doesn't change the outcome. That's called associativity.
Commutativity is changing the order of elements and still getting the same results.

**We don't care about commutativity because the order of elements in the array is fixed**. There's no swapping in segment trees.


Subtraction is not an associative function and we see that we can't use it in the segment tree. For example, if our segment is `[1, 0, 9, 2]`, subtracting all elements in order gives us `1-0-9-2=-10`. If we try this in a segment tree, the root node would be `(1-0)-(9-2)=-6`

So **segment tree only works with associative functions.**
