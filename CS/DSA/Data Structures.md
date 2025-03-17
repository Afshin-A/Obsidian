# Graphs
### Directed Graphs

#### Directed Acyclic Graph (DAG)
Used by git to store commits.


# Binary Heap
A heap is a complete binary tree (the tree is filled from left to right in order) and that follows the heap invariant (for a max heap, the parent node is larger than or equal to the child nodes). There are two types of heaps: max heap, and a min heap. 

Total number of nodes in a full binary tree
$$
n = 2^{H+1}-1
$$
where $H$ is the height of the tree. For a complete binary tree, the last level isn't guaranteed to be full, so we can say the number of nodes in a complete binary tree is approximately equal to that of a full tree.

In a complete binary tree, approximately half of the nodes are leaf nodes and the other half are internal nodes. The exact numbers can be calculated as:
- Number of leaf nodes in a complete binary tree:
$$
\lceil {{n}\over{2}} \rceil
$$
- Number of internal nodes in a complete binary tree:
$$
\lfloor {{n}\over{2}} \rfloor
$$

By the way, 
$$
\lceil {{n}\over{2}} \rceil + \lfloor {{n}\over{2}} \rfloor = n
$$

A binary heap can be represented via an array. If a parent is at index `i`, the left child `l` is at index $2i+1$ and the right child `l` is at index $l+1$

## Creating a max heap from an array

`max_heapify`: if a parent node is larger than either of its children, we bubble it down. We keep repeating this until the heap invariant is reached, i.e. parent is greater than or equal to its children.  

given the index of a node, we compare which is the greatest: the node itself, the left child, or the right child. If either of the children are the largest, swap the parent with that child. Then repeat the same process for that node we swapped.

```python
    def max_heapify(heap: list[int], heap_size: int, i: index):
        l = i * 2 + 1
        r = l + 1
        largest = i
       # This check ensures we don't go out of bounds
        if l < heap_size:
            if heap[l] > heap[largest]:
                largest = l
        if r < heap_size:
            if heap[r] > heap[largest]:
                largest = r

        if i != largest:
            heap[i], heap[largest] = heap[largest], heap[i]
            max_heapify(largest)
```

This operation has a time complexity of $O(log(n))$ because, at the worst case, a root node will need to be bubbled down all the way down to the bottom of the heap. There are $\lfloor \log_{2}n \rfloor$ levels and swapping has a constant time complexity. So the worst time complexity is $O(log(n))$.

`max_heapify` works for only 1 node. We need to call this function for all internal nodes. Leaf nodes already follow the heap invariant property and plus they have no children, so it doesn't make sense to call.

We start from the bottom and make our way up

```python
def build_max_heap(heap: list[int]):
    heap_size = len(heap)
    internal_nodes = range(heap_size // 2, -1, -1)
    for i in internal_nodes:
        max_heapify(heap, heap_size, i)
```

The `//` operation in python returns the floor of the quotient.

This function actually has a worst case time complexity of $O(n)$, not $O(n \ log(n))$. The log is as follows: the deeper we go into the binary tree, the fewer times we can bubble down a node. However, we can also mathematically calculate the worse case time complexity using summations. At level 0, there are $2^0=1$ nodes that we can bubble it down $H$ times. If we had a tree with height 3, we can at most bubble it down 3 times. At level 2, there are $2^1$ nodes and we can bubble down each node $3-1=2$ times at most. To find the worse case time complexity, we need to find how many operations (bubbling down, in this case) we can to in total. 
$$\begin{align}
\text{\# of swaps}& \approx \sum^{H}_{h=0}{2^h(H-h)} \\
&=H\sum_{h=0}^{H}{2^h} \ - \ \sum^{H}_{h=0}{h2^h} \\ \\
&=(\log_{2}n)(\frac{\cancelto{n}{2^{\log_{2}n}}-1}{2-1})-\frac{2(\log_{2}n-2)+(1-\log_{2}n)\cancelto{n}{2^{\log_{2}n}}}{(2-1)^2} \\
&=n\log_{2}n-\log_{2}n-2n\log_{2}n+2n-2 \\ \\ \\
\end{align}
$$
A more detailed proof of how we reached this can be found in [[Geometric Series#Arithmetic geometric series]]. 

The largest term here is $2n$, which means the worst time complexity is $O(n)$.
$$
O\Big( n\log_{2}n-\log_{2}n-2n\log_{2}n+2n-2 \Big)=O(n)
$$

# Hash Tables
An object goes through a hashing function which links that object to an index on an array. 
$$
F(o) \to i \in \mathbb{Z}
$$
Array functions always use the modulo operation to confine the result in the bounds of the array. Here's an example that adds up the integer equivalent of all characters in 

A good hashing function should minimize collisions. 

A **collision** happens when the hashing function links multiple objects to the same index. In such a case, i.e. when there's a collision, we can append the element to a linked list at that index. We can also do what's called **linear probing**, which means we keep looking at the next index (`i += 1`) until we find an empty spot. 

## What's hashable?
Immutable objects. Objects that cannot be changed in memory, like strings, sets, tuples, etc.. are hashable. An object should only be hashed to 1 number, just like how in a dictionary a key can only point to 1 value. That is the definition of a function after all. If the object is mutable, then we can change it and it would be hashed to a different value. 

Python has a built in function `hash()` 

## Probing function
In the linear probing method, If a collision occurs in our table, we need to find another slot. This can be calculated using a linear function in the form of $P(x)=ax+b$. 

First, we have:
$$
h(k)\mod{N} 
$$
where 
- $k$ is the object we want to insert/hash, 
- $h$ is the hashing function
- and $N$ is the size of the table. 
This gives us the index where we first attempt to insert an element. If this index is occupied, we add to it a number given to us by the linear proving function, and take the modulo again to find a new index. 
$$\begin{align}
H(k,x)=\big(h(k)+ax\big) \mod{N}  \\
x \in \{ 0,1,2, \dots \}
\end{align}
$$

For each $x$, the we're moving  $a \mod{N}$ indices ahead in the table. 
$$
\begin{align}
H(k,x)-H(k,x+1) \\
=
\end{align}
$$

However, there is a chance we get stuck in an infinite loop if $H(k,x)$ yields the same indices over and over in a cycle (loop). In other words, we need to make sure that $H(k,x)$ can produce every possible number in range $[0,N)$.
This is only possible if a and N are relatively prime. That is, if their [[Euclidean Algorithm|greatest common divisor]] is 1.




# Union Find Data structure



## Union


### Path Compression




# Trees
- A tree is an undirected graph, meaning we can travel up or down the tree. 
- There are no cycles in a tree, which also means that there is only one unique path that connects two nodes. If there were more than one path, that means there is a cycle in the data structure and it would not be a tree. 
- A connected graph with N nodes has N-1 edges

A tree where every node only has 1 node is called a **degenerate tree**.
# Binary Search tree
For each node, all nodes on the left subtree are less than or equal to (we can choose to not allow duplicate values in the tree) the parent node, and all nodes on the right child tree are larger. 
Note that a binary tree doesn't have to be complete. That means internal nodes far up may just have 1 node instead of 2, or they could be leaf nodes. They're not necessarily filled from left to right like they are in heaps. 


Unlike in a heap, we can't guarantee the shape of a binary search tree. Which is why the worst case time complexity of its operations is `O(n)`. In theory, the tree could just be a linked list. However, on average, the time complexity is `O(log(n))`.

## Node removal
First we need to find the disposable node.
```python

class Node:
	def __init__(self, val, left=None, right=None):
		self._val = val
		self._left = left
		self._right = right

class BST:
	def __init__(self, root):
		self._root = root

	def insert(self, n):
		current = self._node
		

```


There are 4 possible cases we need to account for.
### Leaf node
If `node.right is None and node.left is None`

The disposable node is a leaf node (it has no children), so we simply set it to `None`. This is the easiest of the cases.

### No left subtree
If `node.right is None` 
The disposable node only has a left child subtree with no right subtree.
The successor for that node is the left child.

```python
if node.left is None:
	

```
## Tree Traversal

# Balanced Binary Search Tree

