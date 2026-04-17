Ordered hashmap
lookup, add, delete all have `O(log(n))` time complexity


Red-black tree
it is a specific type of a balanced binary search tree, where the height of the tree is guaranteed to be $\lfloor\log_{2} n \rfloor$

1. all red nodes have black children
2. the root and the null nodes are black
3. all paths from a node to its decedents will have the same number of black nodes (not counting the root)
the longest path (from the root to any null) in the tree is at most twice the length of the shortest path (from the root to the nearest null)
the shortest node has all black nodes
the longest path has alternating red and black nodes

