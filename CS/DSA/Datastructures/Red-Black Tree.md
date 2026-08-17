The **red-black tree** is an example of a balanced binary search tree. *Balanced* means that for any node, the difference between height of the left and right subtrees is no bigger than $|1|$.
The red-black tree is not as strict as an **AVL tree**, meaning it requires less rotations to balance the tree. But it still guarantees a time complexity of `O(log(n))` for insert, lookup, and delete. It's fast and used in various applications, including [[TCP In Detail|storing out of order TCP packets in memory buffer]].
_The height of the tree is guaranteed to be $\lfloor\log_{2} n \rfloor$_ (need to verify)

## Definition 
Every red-black tree must follow these 5 rules:
1. Nodes are either black or red
2. The root node is always black
3. All leaf (null/nill) nodes are black
4. If a node is red, both of its children must be black
5. All paths from a node to its decedents will have the same number of black nodes (not counting the itself). This number is called the *black height (bh)*, a property for each node that is important when balancing the red-black tree.

These rules lead to the following properties of the red-black tree.

```tikz
\begin{document}
% ============ STYLE DEFINITIONS ============
% Tweak colors/sizes here once — it applies to every node in the tree.
\tikzset{
  every node/.style={circle, draw=black, thick, minimum size=9mm, align=center, text=white},
  red-node/.style={fill=red},
  black-node/.style={fill=black},
  nil-node/.style={fill=black}
}

% Shorthand macros — this is what makes adding nodes fast.
% Instead of typing "node[red-node] {value}" every time, just write \rnode{value}.
\newcommand{\rnode}[1]{node[red-node] {#1}}
\newcommand{\bnode}[1]{node[black-node] {#1}}
\newcommand{\nilnode}{node[nil-node] {NIL}}

\begin{tikzpicture}[
  level distance=16mm,
  sibling distance=40mm,
  edge from parent/.style={<->, thick, draw=gray!60!black}
]

% ============ TREE ============
\node[black-node] {13}
  child { \rnode{8}
    child { \bnode{1}
      child { \nilnode }
      child { \nilnode }
    }
    child { \bnode{11} 
	  child { \nilnode }
      child { \nilnode }
    }
  }
  child { \rnode{17}
    child { \bnode{15} }
    child { \bnode{25}
      child { \rnode{22} }
      child { \rnode{27} }
    }
  };

\end{tikzpicture}

% ============ LEGEND ============

\end{document}
```


```tikz

\begin{document}
\begin{tikzpicture}[
  every node/.style = {minimum size=9mm, draw, circle, thick},
  level/.style = {sibling distance = 30mm/#1}
  ]
  \node {51}
  child {node {12} 
        child {node {1}}
        child {node {43}
               child {node {36}}
               child {edge from parent[draw = none]}
              }
        }
  child {node {87}
         child {node {52}
                child {edge from parent[draw = none]}
                child {node {83}}
               }
         child {edge from parent[draw = none]}
        };
\end{tikzpicture}
\end{document}

```
### The Root has the Highest $bh$
The root is the parent of all nodes. You can reach every leaf/nil node from the root. The number of black nodes on all of these paths must be the same. Since any other node in the tree is a descendant of the root, its path to a leaf is a subsegment of the root's path, meaning its black height will always be less than or equal to the root's black height.
The roots children can also have the same bh as the root (if they're red)

This also means **the longest path in the tree will always start at the root.**
### The $2\times$ Path Limit
#### Axiom
The longest path in the tree (from the root to any null) cannot exceed twice the length of the shortest path (from the root to the nearest null)
The shortest possible path is all black nodes. 

#### Proof
As we already established [[Red-Black Tree#The root has the highest bh|above]], the root has the highest *black height*. Let's call this number $B$. The shortest path we can make is if we only use black nodes.  We also we can't change the number of the black nodes in a tree, as that would change the black height of the root (it could also change the bh of other nodes). But we can add red nodes, and that would not change the black height of the root. Recall that, by definition, red nodes must have black children. Therefore, the largest chain we can make is by alternating between red and black nodes. 
```
Root                        null
black → red → black → red → black 
```
In other words, for each black node, we can at most have 1 red node. This means the longest path possible:
- **cannot be any more than twice the shortest path**
- **has alternating red and black nodes**
### The $O(\log n)$ Height Bound
The longest path from the root to a leaf node is at most twice as long as the shortest path. 
$$
h \leq 2 \log_{2}(n+1)
$$
where $h$ is the height of the tree and $n$ is the number of nodes in the tree.

Suppose $x$ is an arbitrary node in the tree, and $bh(x)$ is the black-height of $x$
**The subtree rooted at $x$ has *at least* $2^{bh(x)}-1$ nodes**:
$$
n \geq 2^{bh(x)}-1
$$
Proof by reverse induction [^4]
Base case: $x$ is a leaf node, so $bh(x)=0$. A leaf node doesn't have a subtree, so there are 0 nodes.
$2^{0}-1=0$

Inductive step:
The children of $x$ will either have the same $bh$ as $x$ $bh(x)$ or $bh(x)-1$
If the child $c$ is red, $bh(c)=bh(x)$. [^1]
If the child is black, $bh(c)=bh(x)-1$.  [^2]

Assume $n \geq 2^{bh(x)}-1$ is true. This means the smaller the $bh$, the less nodes there will be. So we would get the fewest nodes in a subtree if both of the root's children are black. In that case, subtree rooted at $x$ will have at minimum:
$$\begin{align}
n &\geq (2^{bh(x)-1} - 1) + (2^{bh(x)-1} - 1) + \underbrace{1}_{\text{counting the root}} &&= 2 \cdot 2^{bh(x)-1} - 1 \\
& && = 2^{bh(x)} - 1 \\
\therefore n & \geq 2^{bh(x)} - 1
\end{align}
$$
$$
\large \boxed{\therefore n  \geq 2^{bh(x)} - 1}
$$



At most, half of the nodes on any path on the tree *can be* red. This is the equivalent of saying **at least half of the nodes *must be* black**.
The height[^3] of the tree $h$ is the length of the longest path from the node. Half of these nodes are black. Recall the count of the black nodes is the black height of the root. Therefore:
$$
bh(root) \geq \frac{h}{2}
$$
We can substitute this into the inequality above:
$$
\begin{align}
n  & \geq 2^{bh(x)} - 1 \\
n  & \geq 2^{ \frac{h}{2}} - 1 \\ 
n+1  & \geq 2^{ \frac{h}{2}} \\ 
\log_{2}(n+1) & \geq \frac{h}{2} \\
2\log_{2}(n+1) & \geq h
\end{align}
$$
$$
\large \therefore \boxed{h \leq 2 \log_{2}(n+1)}
$$
This shows the maximum height of a red-black tree is bound by the log of the number of nodes. 

# Inserting 
We follow the standard BST rules for insertion. If the value of the entry is less (or equal) than the current node, we go left. Else, we go right.
However, we must ensure the tree remains balanced by either rotating the tree around the node or recoloring it.

Red-black trees are binary search trees. So one way to balance them is by doing left or right rotations, which work exactly the same as in [[B-Tree#How a B-Tree Works|AVL trees]].
*Newly inserted nodes are always red*.
*Left and right children are pre-set to nil*.
We only have one nil node. So all empty nodes actually point to the same nil node.

We must also ensure the tree keeps its 5 main properties from its [[Red-Black Tree#Definition|definition]]. 
Rule 2 can be violated if the we're inserting into an empty tree. In this case, we simply change the node color from red to black.


## Recoloring




[^1]: The black height of the parent doesn't include the parent. Now suppose we go down by one level and the child is red. The black height wouldn't change because we haven't excluded the child.  

[^2]: The black height is the number of black nodes in all paths to leaf nodes, excluding the current child node. If the child is black, we have to exclude it. So we have to subtract 1 from the $bh$ of the parent. Hope that makes sense. 

[^3]: The height of the tree is the number of edges between the root and the nodes at the lowest levels in the tree.

[^4]: See [[Proof by Induction#Reverse Induction|here]] for more notes on this proof method.
