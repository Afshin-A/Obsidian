# Description
Attempting to traverse a cyclic linked list will result in an infinite loop. It is important to identify if a list is cyclic. 
This is a cycle detection algorithm in a singly linked lists with a time complexity of $O(n)$ and space complexity of $O(1)$ (because two only use 2 pointers). It's constant regardless of the size of the linked list. 

# How it works
We start by setting two pointers, slow and fast, to the head. Slow moves 1 node at a time, while fast moves by 2 nodes. If there's not a cycle, then fast will eventually reach `null`. But if there is a cycle, then, by the pigeonhole principle, both slow and fast will enter the cycle and will eventually meet at node. But rest assured the hare and the tortoise will not race forever in the loop, and at most will need $n$ (length of list) steps to reach each other.
We also want to know the last node leading to the cycle. It turns out, if we take the same number of steps that takes to get from the meeting point to the cycle starting point ($z$) from the head, we reach the entry point of the cycle.
# Why it works
![[Pasted image 20240527231228.png]]
*Inside code - YouTube*

---
Definitions:
- $x$ is the distance from head to where the cycle begins.
- $y$ is the distance from cycle start point to meeting point.
- $z$ is the distance from meeting point to cycle start point.
- $l$ is the distance for the loop, such that $l=y+z$
- $f$ is the distance traveled by fast (hare).
- $s$ is the distance traveled by slow (tortoise).
- $c_1$, $c_2$, and $c_3$ are constants that represent number of rotations around the cycle.

$$
\begin{align}
\text{known facts:}\\
y+z=l \\
f=x+c_1l+y  \\
s=x+c_2l+y \\
f=2s \\ \\
\text{Proof:} \\
x+c_1+y=2x+2c_2+2y \\
(c_1-2c_2)l-y=x \\
(c_1-2c_2-1)l+l-y=x\\
(c_1-2c_2-1)l+z=x\\
c_3l+z=x
\end{align}
$$
==To DO: Prove this claim==
>But rest assured the hare and the tortoise will not race forever in the loop, and at most will need $n$ (length of list) steps to reach each other.
# Implementation (Python)
```python
def class Node:
	def __init__(self, data, next=None):
		self.data = data
		self.next = next

def class LinkedList:
	def __init__(self, head: Node):
		self.head = head
		self.tail = self.head

	def append(self, node: Node):
		self.tail.next = node
		self.tail = node

	def prepend(self, node: Node):
		node.next = self.head
		self.head = node

	def __str__(self):
		nodes = []
		current = self.head
		while(current is not None):
			nodes.append(current)
			current = current.next
		return nodes.

	def findCycle(self, llist: LinkedList) -> Node:
		fast = list.head
		slow = list.head
		met = False
		# is there a cycle?
		while (fast.next is not None or fast.next.next is not None):
			# jumps by one
			slow = slow.next
			# jumps by two
			fast = fast.next.next
			if slow is fast:
				met = True
				break
		# if no cycle, return null
		if not met:
			return None
		# else, where is the cycle entry?
		else:
			slow = list.head
			while slow is not fast:
				slow = slow.next
				# note: fast is now moving node by node
				fast = fast.next
		return slow

```

# Space and Time Complexities

This algorithm has a time complexity of $O(n)$. That is, the time it takes to find a cycle depends on $n$, number of nodes. The space complexity is $O(1)$, because we only use two pointers to keep track of slow and fast. 
# Other Applications
The hare and tortoise algorithm can also be used to find duplicates in a list.
## Problem
Suppose we have $n+1$ values in list of length $n$. 

We create an imaginary $ll$ (linked list) from the elements of the $l$ (list).
$$
\begin{align}
ll_0 = l_0 \\

ll_1 = l[ll_0] \\

\dots \\

ll_n = l[ll_{n-1}]
\end{align}
$$
For example,
$$
\begin{align}
[&4 \ 7 \ 8 \ 3 \ 5 \  1 \ 1 \ 6 \ 2 \ 9] \\
\text{indices} = &0 \ 1 \  2 \  3 \  4 \  5 \  6 \  7 \  8 \  9 \\
\end{align}
$$
gives,
```tikz

\begin{document}
\begin{tikzpicture}[very thick, every node/.style={draw, circle, scale=2}]

\node (0) {4};
\node (1) [right of=0] {5};
\node (2) [right of=1] {1};
\node (3) [right of=2] {7};
\node (4) [right of=3] {6};

\draw[->] (0) edge (1);
\draw[->] (1) edge (2);
\draw[->] (2) edge (3);
\draw[->] (3) edge (4);
\draw[->, bend left=90] (4) edge (2);



\end{tikzpicture}
\end{document}
```
The remaining elements in $l$ cannot be added because $ll$ has entered an infinite loop.

**Note**: $l$ cannot contain 0, otherwise $ll$ would create a loop with its head, which is false because the head is not a duplicate in this example.



## Solution
```python
slow = fast = 0
while True:
	slow = l[slow]
	fast = l[l[fast]]
	if slow == fast:
        break

print('Duplicate element: ', slow)
```
# Resources
<iframe width="560" height="315" src="https://www.youtube.com/embed/PvrxZaH_eZ4?si=DwS4gEJyWSp2q9GJ" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
