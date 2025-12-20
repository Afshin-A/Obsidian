Given an $m\times n$  array, find the number of battle ships.
A battleship's body is consisted of adjacent (left, right, up, down) x blocks.
```
x 0 0 x
x 0 x x
0 0 0 x
x x 0 0
```

One approach is to do a breadth first search for every element. We keep track of unvisited elements in a set

But the more efficient approach is to identify the start of each battleship. 
We iterate through each element. If it is the start of a ship, we increment the count. If not, then it must already be part of a ship and we pass that element.
An element is the start of a battleship if it doesn't have any elements above or to its left.
The time complexity of this approach is $O(m\times n)$. Space complexity is $O(1)$