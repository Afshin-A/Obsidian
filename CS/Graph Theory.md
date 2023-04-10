# Types of Graphs

- **Undirected graphs**. Edge direction does not matter.
- **Directed graphs (digraphs)**
- **Weighed graphs**
- **Trees**
An undirected graph with no cycles. If a tree has $N$ vertices, then it will have $N-1$ edges.
- **Rooted tree**
One vertex is designated as the root. Other vertices all either point towards tp or away from the root.
-  **Directed Acyclic Graph (DAG)**
It is widely used to represent dependency relationships. A directed graph that contains no directed cycles. All trees are DAGs, but not all DAGs are trees. This is because of the difference between directed and regular cycles.
Example of a directed cycle:
$$
A \to B \to C \to D \to A
$$
Not a directed cycle:
$$\begin{align}
A \to B \to C \to D \\
\text{But instead of } D \to A \text{ we have } A \to D
\end{align}
$$
This would be a cycle, but not a directed one. So it's possible to have a DAG with a non-directed cycle, which would not be a tree.
- **Biparatite graphs**
If you can divide the nodes such that there edges are only from group 1 to group 2, then we have a bipartite graph. Fact: bipartite graphs cannot have cycles with odd lengths.
- __Complete graphs__
A graph where all nodes are connected to each other. So it would have the maximum number of edges. These are denoted by $K_n$ where $n$ is the number of vertices.

# Graph Representation
Consider a graph $G=(V, E)$ where $V$ is the set of vertices and $E$ edges. This is one way to represent a graph.
Let's say $G$ has $N$ vertices. The maximum number of edges in an undirected graph, $M$, equals:
$$
M = (N-1)+(N-2)+\dots+2+1=\sum_{k=1}^{N-1}{N-k}={N(N-1)\over2}
$$
For directed graph, there'd be twice as many edges, so we would simply multiply $M$ by 2 and get $N(N-1)$

## Graph Density
Graph density is the ratio of the number of edges to the maximum possible number of edges. So a graph with more edges is called **dense** and a graph with fewer edges is __sparse__.


## Adjacency Matrix
-|A|B|C|D
-|-|-|-|-
A|0|4|1|9
B|3|0|6|11
C|4|1|0|2
D|6|5|-4|0
This matrix represents a sparse graph; it contains many 0s, which indicates there are few edges. The numbers in the matrix represent the weight of each edge. So, for example, vertex $B$ edges to $A$  weighing 3, to $C$ valuing 6, and to $D$ for 11. No vertex edges to itself, which is why the diagonal values of the matrix are all 0.

### Pros
The adjacency matric simple, is efficient for sparse graphs with many 0s, and the time complexity to look up single values is constant $O(1).

### Cons
But it takes lots of space. The number of entities is directly proportional to the square of the number of vertices (because it's a suare table, duh). So space complexity is $O(V^2)$ where $V$ is the number of vertices. In addition, time complexity to iterate over all values is also $O(V^2)$, which is inefficient.


## Adjacency List
This is a map that links each vertice to a list of edges that go out from that vertex. So for example, for vertex $B$ we'd have:
$$
B \to \big[(A, 3),\ (C,6), \ (D, 11)\big]
$$
### Pros
It is more space efficient than the adjacency matrix (because it excludes the 0s). That also makes it more efficient at iterating over the vertices. Overall, it's good for sparse graphs.

### Cons
For dense graph where are more edges, the lists also get longer. So the adjacency list is not as efficient as the matrix for dense graphs; with the matrix, you can instantly look up an edge whereas with the list, you would have potentially iterate through an entire list to find an edge.

## Edge List
This is basically a list of tuples:
$$
\big[(A, B, 4), \ (A,C,1), \ (A,D,9), \ (B,A,3), () \dots \big]
$$
It is definitely not space efficient or time efficient. Therefore it is rarely used for its simplicity in a few algorithms.


# Common Graph Theory Problems
- **The shortest path problem**. In a weighted graph, how do we get from node A to node B using the least number of edges and with minimal cost?
- **Connectivity problem**. Does a path from node A to B exist?
- **Detecting negative cycles**. In such a cycle, the costs add up to a negative value.
- **The Traveling Salesman problem**. It is similar to the shortest path problem, but you have to visit all nodes and return to the starting node. In other words, what is the shortest and most cost effective way to visit each note exactly once and return to the starting node?
- **Finding bridges**. A bridge is an edge that if we remove it, the graph dissolves into separate components. A bridge often signifies weak points and vulnerabilities.
- **Finding articulation points**. Similar to the finding bridges problem, but with nodes instead of edges.
- **Finding the minimum spanning tree (MST)**. MST is a set of edges that connect all the vertices with minimal cost, and has no cycles (which makes it a tree). A graph can have multiple different minimum spanning trees.
- **Network flow problems**

# Depth First Search (DFS)
This is a recursive, traversal algorithm.
Time complexity of $O(V+E)$, directly proportional to size of graph

## Pseudocode and Explanation
Starting at the root, for each child of the node, we arbitrarily (by arbitrary I mean there's no definite method; pick something and repeat it consistently) pick a child node that is not yet visited. This is continued recursively until all the nodes are visited. 

![](https://www.codesdope.com/staticroot/images/algorithm/dfs.gif)



```

define graph
define visited = [false, false, ... false]

function dfs(Node currentNode):
	if (currentNode is visited):
		return;
	else:
		visited[currentNode.id] = true;
		for each node in neighboring nodes
			dfs(node)

call dfs(root)

```

## Applications
### Identifying Connected Components
Example of a disconnected graph with several connected components. We can use the DFS algorithm to group them.
```tikz
\begin{document} 
\begin{tikzpicture}[node distance={15mm}, very thick, main/.style={draw, circle}, every node/.style={scale=1}] 

\node[main] (0) {$0$}; 
\node[main] [above left of=0](4){$4$};
\node[main] [right of=0](9){$9$};
\node[main] [below right of=0](3){$3$};
\node[main] [below left of=0](8){$8$};

\draw (0) -- (4);
\draw (0) -- (9);
\draw (0) -- (3);
\draw (0) -- (8);
\draw (8) -- (4);
\draw (8) -- (3);
\draw (3) -- (9);

\node[main] [left of=8](6) {$6$}; 
\node[main] [below of=6](7){$7$};
\node[main] [left of=6](11){$11$};

\draw (6) -- (7);
\draw (6) -- (11);
\draw (7) -- (11);

\node[main] [below left of=7](12){$12$};

\node[main] [below left of=3](1){$1$};
\node[main] [below left of=1](5){$5$};
\node[main] [below left of=5](2){$2$};
\node[main] [below of=1](10){$10$};

\draw (1) -- (5);
\draw (5) -- (2);
\draw (5) -- (10);

\end{tikzpicture} 
\end{document}
```
Basically, we begin to a DFS at node 0. Any node visit during this search would be labeled as group 1. Then, we begin a new DFS at node 1, but only if it has not been already visited during a previous DFS. We continue this cycle until all nodes have been visited. The number of performed DFS equals the number of components in the graph.