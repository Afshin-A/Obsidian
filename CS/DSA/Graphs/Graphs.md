Graphs are a wide topic that include trees. All trees are graphs. But not all graphs are trees. 

How to represent a graph.
```
graph = {
	node: [neighbors]
}
```
In a directed relationship like $a \to b$ , b is a neighbor of a, but not the other way around.

# Traversal Algorithms
Graph traversals are similar to trees. The two graph traversal algorithms are breath first and depth first. These work just like they do in trees. 

Time complexity of graph traversals would is $O(n^2)$
Space complexity is $O(n)$


## Breath first search (BFS)
For breath first, we use a queue. We start at a node. We pop that node and add all its neighbors so long as they haven't been visited. We can keep track of the visited notes using a hashset (because of fast lookups and also because all neighbor nodes are unique). Then we repeat that process for all the remaining nodes until the queue is empty.
## Depth first search (DFS)
Depth first is done in a similar way, but this time we use a stack. Nodes get buried in the stack and are revisited later. 

## Applications

### Has path
Find out if a destination node is reachable if we start from a source node in a DAG

# DAG (Directed Acyclic Graph)
No cycles, edges have directions.

# Maximum number of edges in a DAG
$$
\begin{align}
(n-1)+(n-2)+\dots+1 \\
=\boxed{\frac{n(n-1)}{2}}
\end{align}
$$
An undirected acyclic graph would therefore have a maximum of $n(n-1)$ edges. That's because in a DAG, each node would be associated with 2 edges at most. One in and one out. But in an undirected graph, there'd be only 1 edge for each node. So the maximum number of possible edges cuts by half. 



# Path finding algorithms
## Dijkstra's Algorithm

## Bellman-Ford SSSP Algorithm
Going from a starting node, it finds the shortest path to all other nodes in the graph.

Unlike Dijkstra's algorithm, the Bellman-Ford supports negative edges. But **it does not work with negative cycles**. You can imagine that such a cycle will keep reducing forever. 

If a graph has a total of $n$ nodes, then there are at most $n-1$ edges from the starting node to any other node in the graph in this algorithm.

If there are any more edges, that means there is a loop somewhere in the path. There can be no negative cycles. And positive cycles will add to the path cost, so we can ignore them.

So, there are $n$ or more edges in a path if and only if there exists a cycle in that path. 
$$
\text{There are $n$ or more edges in a path}  \iff \text{there exists a cycle in the path} 
$$


## Floyd-Warshall
Unlike Dijkstra's and the Bellman-Ford, this algorithm finds the best path between all nodes in the graph, not just two. It can also detect negative cycles.

It considers every possible edge. For each iteration (for each node $c$), it tries to find if a connection between nodes $a$ and $b$ would be more cost effective if it went through node $c$.

Time complexity is $O(n^3)$ and space complexity is $O(n^2)$. So, it's ideal for small graphs.



Suppose we're given a graph as an adjacency list. 
```python
	# First we need to convert the graph to an adjacency matrix
	nti = {node:index for index, node in enumerate(dictGraph.keys())}
    # index to respective node map. This is needed in the floyd warshal algorithm to convert indices back to
    itn = {index:node for index, node in enumerate(dictGraph.keys())}
    # cost matrix
    M = [[float('inf') for _ in dictGraph] for _ in dictGraph]
    # previous-node matrix. the node that comes second to last in the shortest path from A to B
    # it's used in re-creating the shortest path
    T = [[None for _ in dictGraph] for _ in dictGraph]
    for node, neighbors in dictGraph.items():
        i = nti[node]
        for neighbor, cost in neighbors:
            j = nti[neighbor]
            M[i][j] = cost
            T[i][j] = node
	
	# Assuming no node has an edge to itself
    for i in range(len(cMatrix)):
        cMatrix[i][i] = 0
        
    for k in range(n):
        # we go from node i to j through k: i -> k -> j
        # if the path is better than i -> j then we update the matrix
        for i in range(n):
            for j in range(n):
                if k == i or k == j:
                    continue
                # does i to j have a better path through k?
                if M[i][k] + M[k][j] < M[i][j]:
                    M[i][j] = M[i][k] + M[k][j]
                    T[i][j] = chr(k+)
```
## Summary

![[Pasted image 20250702171451.png]]


# bridges and articulation points

A bridge in a graph is an edge that if removed, it would cause more components in the graph. 
An articulation point in a graph is a node that if removed, it would create more components in the graph. 

These represent a bottleneck and a vulnerability. So finding and identifying them would be useful. 

If there is a bridge between u and v, then either node is an articulation point.
But articulation points can exist even when there are no bridges.


The lowlink value of a node is the id of the smallest node that is reachable from that node.

So when there are cycles, all nodes will have the same lowlink value because they're all connected to the starting node in the cycle.
So, if `id(n.from) == lowid(n.to)`, there is a cycle, and `n` is an articulation point.
Exceptions are if n has 0 or 1 outgoing node, in which case the node is not an articulation point. 

If the node has 2 outgoing edges, for example, it is indeed an articulation point.


# Traveling Salesman problem
## Bruteforce
Time complexity `O(n!)`

## Dynamic programming
Time complexity `O(2^n n^2`)

Interestingly, brute force is actually better for n up to n=7