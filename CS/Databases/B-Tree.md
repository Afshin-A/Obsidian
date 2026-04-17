Integer comparison is significantly faster than memory de-referencing.
The CPU uses digital circuits inside its ALU component to perform arithmetic and bitwise operations extremely fast (0.5 to 1 nanosecond). 
Memory access gets progressively slower from L1 to L2, and L3 caches, to RAM



In Postgress Each block can hold up to 8 KB on disk
Data is loaded from disk into memory
Without indexing, querying takes O(n)
But we use B Trees to optimize querying to O(log(n))

# How a B-Tree Works
```cardlink
url: https://youtu.be/K1a2Bk8NrYQ
title: "Understanding B-Trees: The Data Structure Behind Modern Databases"
description: "B-trees are a popular data structure for storing large amounts of data, frequently seen in databases and file systems. But how do they really work? What make..."
host: youtu.be
favicon: https://www.youtube.com/s/desktop/0203efec/img/favicon_32x32.png
image: https://i.ytimg.com/vi/K1a2Bk8NrYQ/maxresdefault.jpg
```


A node is basically an array of size N. 
A node would have $N+1$ children

```tikz
\usepackage{circuitikz}
\begin{document}
\begin{circuitikz}
\tikzstyle{every node}=[font=\fontsize{18.2pt}{23.7pt}\selectfont]
\draw  (12.5,14.5) rectangle (16.25,13.25);
\node [font=\fontsize{18.2pt}{23.7pt}\selectfont, inner xsep=0.080cm, inner ysep=0.085cm, rounded corners=0.020cm] at (13.125,13.875) {12};
\node [font=\fontsize{18.2pt}{23.7pt}\selectfont, inner xsep=0.080cm, inner ysep=0.085cm, rounded corners=0.020cm] at (14.375,13.875) {27};
\node [font=\fontsize{18.2pt}{23.7pt}\selectfont, inner xsep=0.080cm, inner ysep=0.085cm, rounded corners=0.020cm] at (15.625,13.875) {43};
\draw  (10,12) rectangle (13.75,10.75);
\draw  (5,12) rectangle (8.75,10.75);
\draw  (15,12) rectangle (18.75,10.75);
\draw  (20,12) rectangle (23.75,10.75);
\draw [short] (12.5,13.25) -- (6.75,12);
\draw [short] (13.75,13.25) -- (11.75,12);
\draw [short] (15,13.25) -- (17,12);
\draw [short] (16.25,13.25) -- (22.125,12);
\node [font=\fontsize{18.2pt}{23.7pt}\selectfont, fill={rgb,255:red,255; green,255; blue,255}, fill opacity=1, text opacity=1, inner xsep=0.080cm, inner ysep=0.085cm, rounded corners=0.020cm] at (5.625,11.375) {3};
\node [font=\fontsize{18.2pt}{23.7pt}\selectfont, fill={rgb,255:red,255; green,255; blue,255}, fill opacity=1, text opacity=1, inner xsep=0.080cm, inner ysep=0.085cm, rounded corners=0.020cm] at (8.125,11.375) {10};
\node [font=\fontsize{18.2pt}{23.7pt}\selectfont, fill={rgb,255:red,255; green,255; blue,255}, fill opacity=1, text opacity=1, inner xsep=0.080cm, inner ysep=0.085cm, rounded corners=0.020cm] at (10.625,11.375) {15};
\node [font=\fontsize{18.2pt}{23.7pt}\selectfont, fill={rgb,255:red,255; green,255; blue,255}, fill opacity=1, text opacity=1, inner xsep=0.080cm, inner ysep=0.085cm, rounded corners=0.020cm] at (11.875,11.375) {19};
\node [font=\fontsize{18.2pt}{23.7pt}\selectfont, fill={rgb,255:red,255; green,255; blue,255}, fill opacity=1, text opacity=1, inner xsep=0.080cm, inner ysep=0.085cm, rounded corners=0.020cm] at (13.125,11.375) {25};
\node [font=\fontsize{18.2pt}{23.7pt}\selectfont, fill={rgb,255:red,255; green,255; blue,255}, fill opacity=1, text opacity=1, inner xsep=0.080cm, inner ysep=0.085cm, rounded corners=0.020cm] at (15.75,11.375) {30};
\node [font=\fontsize{18.2pt}{23.7pt}\selectfont, fill={rgb,255:red,255; green,255; blue,255}, fill opacity=1, text opacity=1, inner xsep=0.080cm, inner ysep=0.085cm, rounded corners=0.020cm] at (16.875,11.375) {34};
\node [font=\fontsize{18.2pt}{23.7pt}\selectfont, fill={rgb,255:red,255; green,255; blue,255}, fill opacity=1, text opacity=1, inner xsep=0.080cm, inner ysep=0.085cm, rounded corners=0.020cm] at (18.125,11.375) {41};
\node [font=\fontsize{18.2pt}{23.7pt}\selectfont, fill={rgb,255:red,255; green,255; blue,255}, fill opacity=1, text opacity=1, inner xsep=0.080cm, inner ysep=0.085cm, rounded corners=0.020cm] at (20.625,11.375) {48};
\node [font=\fontsize{18.2pt}{23.7pt}\selectfont, fill={rgb,255:red,255; green,255; blue,255}, fill opacity=1, text opacity=1, inner xsep=0.080cm, inner ysep=0.085cm, rounded corners=0.020cm] at (21.875,11.375) {50};
\node [font=\fontsize{18.2pt}{23.7pt}\selectfont, fill={rgb,255:red,255; green,255; blue,255}, fill opacity=1, text opacity=1, inner xsep=0.080cm, inner ysep=0.085cm, rounded corners=0.020cm] at (23,11.375) {53};
\node [font=\fontsize{18.2pt}{23.7pt}\selectfont, fill={rgb,255:red,255; green,255; blue,255}, fill opacity=1, text opacity=1, inner xsep=0.080cm, inner ysep=0.085cm, rounded corners=0.020cm] at (6.875,11.375) {4};
\end{circuitikz}
\end{document}
```
Item look up works very similar to a regular binary tree. Suppose we want to look up value 39. We start at the root node and see that $27 < 39 < 43$. So we go down the child node between those values. Then we do a linear scan and see that 39 is between 34 and 41. We attempt to travel further down, but we're already at a leaf node. So we conclude 39 does not exist in this B-tree.

Nodes can have a set, arbitrary maximum number of elements. The actual number of nodes is $\left\lfloor \frac{Max}{2} \right\rfloor \leq N \leq Max$
We can have any number of elements in that range. The minimum allowed is `Max//2` (floor division). The exception is the root, which can have less elements.



An AVL tree was the first kind of balanced binary tree discovered. It works by storing a balance factor, which is the difference of the height of the left and right subtrees. If this balance factor is outside of the acceptable range of {-1, 0, 1}, we correct it by doing a tree rotation.
```cardlink
url: https://youtu.be/q4fnJZr8ztY
title: "Balanced binary search tree rotations"
description: "Learn about balanced binary search tree rotationsPracticing for interviews? I have used, and recommend `Cracking the Coding Interview` which got me a job at ..."
host: youtu.be
favicon: https://www.youtube.com/s/desktop/0203efec/img/favicon_32x32.png
image: https://i.ytimg.com/vi/q4fnJZr8ztY/maxresdefault.jpg
```
```embed
title: "AVL tree insertion"
image: "https://i.ytimg.com/vi/1QSYxIKXXP4/maxresdefault.jpg"
description: "Related videos:AVL tree intro: https://www.youtube.com/watch?v=q4fnJZr8ztYAVL tree insertions: https://www.youtube.com/watch?v=1QSYxIKXXP4AVL tree removals: ..."
url: "https://youtu.be/1QSYxIKXXP4"
favicon: ""
aspectRatio: "56.25"
```

From a YouTube comment from the *Understanding B-Trees*
> most databases use a B+tree, which is different in that the values are stored only in the leaves; keys in upper nodes just point to lower nodes. When a node splits, you don’t move the middle value up, it stays in one leaf or the other. * B-trees I’ve looked at, like SQLite, don’t have a fixed number of keys in a node. In real usage, keys and/or values are variable size, like strings, and the nodes are fixed-size disk pages (often 4kb.) The number of keys or values that fit in a node is highly variable. So instead you keep adding to a node until its size in bytes overflows a page, and then split. Some nodes might have a hundred keys, some might have only four. It doesn’t matter; the algorithms still work.

So what's a B+ tree? Is it just a modified B-tree where all the values are stored in the leaf nodes, and leaf nodes are connected via pointers? If that is true, then how can we route to the leaf nodes without values also being stored in the internal nodes? No. We need to distinguish between *keys* and *values*.
The B+ tree lives on the database 

Why is a B+ tree faster? If you look at a B+ tree as a data structure on memory RAM, it looks unnecessarily over engineered. But this design overcomes the bottleneck imposed by disk I/O. 
To understand this, we first need to understand [[Postgres#How and Where PostgreSQL Stores Data|how and where PostgreSQL Stores Data]] on disk.

So a B+ tree in Postgres is literally:
> a file where each page is one B+ tree node


```cardlink
url: https://youtu.be/ITcOiLSfVJQ
title: "Clustered vs. Nonclustered Index Structures in SQL Server"
description: "Clustered and nonclustered indexes share many of the same internal structures, but they're fundamentally different in nature. Watch Microsoft Certified IT Pr..."
host: youtu.be
favicon: https://www.youtube.com/s/desktop/af4a6a17/img/favicon_32x32.png
image: https://i.ytimg.com/vi/ITcOiLSfVJQ/maxresdefault.jpg
```
