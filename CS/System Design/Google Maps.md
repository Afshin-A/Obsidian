first things first, let's identify the functional and non-functional requirements of the system



- Functional
	- The system should be pluggable. Adding a new feature shouldn't require us to overhaul the existing system. For example, we might start recommending paths by just considering distances; if we decide to improve recommendations by also considering traffic data, we shouldn't need to make significant changes to the system and the underlying algorithms.
	- Find the optimal path between two points
	- Find ETA

Google Maps supposedly has over 2 billion monthly users [source](https://9to5google.com/2024/10/29/google-maps-2-billion/). So we're designing a highly sought after system. 
- Non-functional
	- High availability
	- High accuracy
	- Fast response
	- Scalable



divide the map into $1 \times 1$ Km *segments*. We can give each segment an ID
We have to be able to find what segment a point falls in in O(1) time
We can find the distance between two points (or segments) using their latitudes and longitudes, and the *haversine formula*
We will divide the entire globe into segments
Roads are represented by a directed edge. Weights are the distance and the time it takes to travel.
The [[Graphs#Floyd-Warshall|Floyd-Warshall algorithm]] calculates the shortest path between all points in a graph, but it is expensive to run. As such, it's best to do this calculation once and cache the results: 
```json
{A→B: {10 Km, 1500s, [A, C, E, B]},
...
} 
```

A *junction* is the meeting point of two roads, i.e. a vertex on our graph. But we can find the distance between any two points $M$ and $N$ on the globe as long as we have the coordinates, even if they're not junctions. To do this, we find the distance between $M$'s nearby junctions to $N$'s. Then we add in the distance of the points to the junctions, and find the minimum value.

We can precompute the optimal paths. This would be ideal for short trips within a neighborhood
If we want to travel between segments, we only need to consider the segments' entry and exit points. We don't need to worry about the inner details of a segment. This would be ideal for trips in the city. 
We don't want to load all the segments in the world into our DAG because running path finding algorithms like Dijkstra's would be inefficient at such a large scale. So if the distance between point $A$ and $B$ is $10$ Km, and each segment is  $1 \times 1$ Km, then we can argue the optimal path between these points likely exists somewhere in, let's say, 40 segments surrounding these points. So we would only load 40 segments.

For longer, inter city trips, we can apply the same logic again and group segments into super segments. Each of these super segments could perhaps represent a city. 

How do we compare path efficiency? 
There are a lot of factors such as distance, time traveled, average speed, traffic data (crashes), weather data, construction, historical data, etc..
We need to give the edges in our DAG weights. 
However, using traffic data, weather data, construction, etc.. as weights is a bad idea. Each change we make as the application evolves should be contained, not impact the whole app. Changing the type of weights requires us to have to modify the underlying algorithm each time. It's also important to recognize these attributes affect our average speed. So we can instead make the average speed a function of these external factors. 
We also can't quantify something like traffic data easily. All that really matters is the distance, the approximate time it takes to get to point B (I suppose we can calculate that using the speed limit?), and the average speed of all the cars going from point A to B. A giant company like Google can get real time analytics from their users' phones. But if for whatever reason that's not possible due to lack of technology or because of legal issues, we can use fancy statistical methods on the data on hand to come up with an average speed for the typical driver going from A to B. Something else we can do is using historical data to estimate the time it takes to travel a road (a  directed edge on our graph) on a particular hour of a particular day of the week


bubble-up calculated values

If there is a sudden, significant change in the weights of an edge, at what point should we re-calculate and update the cache for the best entry and exit points of a segment? If the increase or decrease is by, say, 50%? If the change is insignificant, it might not even be worth the calculations to just shave off a few seconds off of a trip.   

A GIS (Geographical information systems)  is a framework that analyzes and visualizes spatial (aka geographic) data to understand patterns, relationships, and geographic context.
A spatial index is a data structure used for quickly querying  geographical data. Example is an **R-Tree**. The foundation for spatial extensions like PostGIS for PostgreSQ, enables answering queries like find every Whataburger within a 10-mile radius of your current location
It is a tree, so with each step, we can eliminate a large number of points that don't match our criteria
A higher node size means faster indexing and slower queries, and vice versa. **WHY?** 🤔
There are less updates than queries when it comes to geographical data, making r-trees efficient. **WHY?**🤨

POI, **Point of Interest**, referring to digital representations of real-world locations or specific data points in an application.
**Telemetry** refers to automated data collection from software or IoT devices (such as sensors) for monitoring and analysis purposes


### Solving the Nearest Neighbor Search using KD-tree data structure
```embed
title: "K-d Trees - Computerphile"
image: "https://i.ytimg.com/vi/BK5x7IUTIyU/maxresdefault.jpg"
description: "One of the cleanest ways to cut down a search space when working out point proximity! Mike Pound explains K-Dimension Trees.EXTRA BITS: https://youtu.be/uP20..."
url: "https://youtu.be/BK5x7IUTIyU"
favicon: ""
aspectRatio: "56.25"
```

What is a KD-tree?
A K-dimensional-tree is a way to organize points in 2D space.
Suppose we're given an array of 2D points that are scattered across the Cartesian coordinates. We start by finding the median $x$ value ($M_x$) of all the points and draw a vertical line $x=M_{x}$. Naturally, this divides points into 2 groups: those with $x<M_{x}$ fall to left of this line, and those with $x>M_x$ are on the right. Next, we split each group into 2 groups by the median $y$ value. At this point, we've divided the map into 4 quadrants, and we can tell which quadrant any point belongs to.
This is the start of a special binary tree that allows us to quickly query for points using both $x$ and $y$ values. The twist is that we alternate dividing points between x and y axes at each level of the binary tree (==rewrite this, poorly written==). 

The problem
Given an arbitrary point (not on the graph or data structure), we can use a KD-tree to find the nearest point on the graph to it. While we use it to find 2-D points, a KD-AKA K-Dimensions-tree works for any number of dimensions.

Example
```
(9,75)
(21,17)
(37,40)
(49,57)
(63,55)
(74,21)
(89,51)
(93,69)
```
![[KD-Tree-Example.png|600]]

### R-Trees data structure
KD-tree is excellent at finding points, but it falls short when 

problem: Find all gas stations within a 5 mile radius of your location.

R-tree is a data structure consisted of overlapping rectangles. 
R-trees are a type of a balanced tree. All leaf nodes are at the same level.  
Rectangles are recursively divided into smaller rectangles. Until we reach a **Minimum Bounding Rectangle**, the smallest rectangle that can hold a collection of points on the map. These are the leaf nodes in our tree. 
We can quickly eliminate big chunks of the map by traversing down the tree. 
Does the search circle overlap with the "North Texas" rectangle? No. We prune that tree branch. Does it overlap with the "West Texas" rectangle? Yes. We explore down that branch. 

Our goal when building the R-tree: minimize "dead space" (empty area inside a rectangle) and minimize overlap between rectangles
A single piece of data belongs to exactly _one_ parent rectangle. A fundamental property of trees. 
Every box/node has a minimum and maximum number of points (or polygons, collectively spatial entry). If a node becomes too large, we need to split it into two smaller boxes. This is referred to as the **Node Splitting Problem**

Why do boxes physically overlap, and why should we care? How does the overlap affect the logical tree?

We look at coordinates and see that it is physically inside two boxes. But logically, data can only belong to one node. So we have to search both boxes. Overlaps [vitiates](https://www.google.com/search?client=firefox-b-1-d&q=Vitiate) efficiency.
> Well, the search area is inside Box A. But it's also inside Box B. Since I don't know which box actually contains the specific data points in that region, I have to open and search both of them."

R-Tree is not allowed to just invent a new group out of thin air because it would unbalance the tree structure
	R-Trees are a compromise. The absolute fastest way to search data is to have perfect, zero-overlap grids. But the absolute fastest way to _insert_ new data is to just stretch existing boxes. We can't redraw all the rectangles to achieve perfect boundary boxes every time we insert new data, as that would take a lot of time. A point might be closest to Box A, but because it's full, it would be assigned to Box B. This would stretch Box B  and cause overlap.
Redrawing boundaries are usually done irrespective of other boxes. We don't consider them when we redraw. That's why overlapping occurs.
drawing rectangular boxes around irregular, real-world clusters inevitably leads to corners and edges bumping into one another.

Query time efficiency is $O(\log_{M}​N)$ where $M$ is 

#### How to find out if two boxes overlap
##### Approach 1
For each rectangle, we're given two points $P(x₁,y₁)$ on the top-left and $Q(x₂,y₂)$ bottom right.
We calculate the center point and $\frac{\text{height}}{2}$ and $\frac{\text{width}}{2}$ of each rectangle:
```
center_x = (x₁ + x₂) / 2.0
center_y = (y₁ + y₂) / 2.0

half_w = |x₁ - x₂| / 2.0
half_h = |y₁ - y₂| / 2.0
```

The two rectangles overlap if and only if two conditions are met:
```
|cx₁ - cx₂| < (half_w₁ + half_w₂)  
AND  
|cy₁ - cy₂| < (half_h₁ + half_h₂)
```
There are other ways of finding out if two boxes overlap, but doing it this way ensures we won't have to worry about the order of the arguments of our function. In other words, which rectangle is to the left and which one is to the right. 

*This approach works, but because it involves arithmetic operations (addition, subtraction, division), it consumes more CPU cycles than if it were just comparisons.*

##### Approach 2


```tikz
\begin{document}
\usetikzlibrary{backgrounds}
\begin{tikzpicture}[white, background rectangle/.style={fill=teal},framed,show background top, show background left, scale=1.25, transform shape] % Set the background color show background rectangle

% Axes
\draw[thick, ->] (-1,0) -- (8,0) node[right] {$x$};
\draw[thick, ->] (0,-1) -- (0,6) node[above] {$y$};

% Vertical guide lines
\draw[green] (1,-1) -- (1,6);
\draw[green] (4,-1) -- (4,6);
% Horizontal guide lines
\draw[green] (-1,1) -- (8,1);
\draw[green] (-1,4) -- (8,4);
% Line labels
\node[green, below] at (1,-1) {$y = A$};
\node[green, below] at (4,-1) {$y = B$};
\node[green, right] at (8,4) {$x = B$};
\node[green, right] at (8,1) {$x = A$};

% Rectangle A (white)
\draw[black, thick] (1,1) rectangle (4,4);
\fill[black] (4,4) circle (2.5pt) node[below right, scale=0.75]{$(B, B)$};
\fill[black] (1,1) circle (2.5pt) node[below right, scale=0.75]{$(A, A)$};

% Rectangle B (black)
\draw[thick] (3,2) rectangle (6,5);
\fill[] (3,2) circle (2.5pt) node[below, scale=0.75]{$(C, C)$};
\fill[] (6,5) circle (2.5pt) node[above, scale=0.75]{$(D, D)$};


\draw[thick, ->] (-1,-3) -- (8,-3) node[right]{$x$};
\foreach \x/\label in {1/A, 3/C, 4/B, 6/D} {
    % tick
    \draw[shift={(\x,-3)}] (0pt,3pt) -- (0pt,-3pt);
    % label
    \node[below] at (\x,-3) {$\label$};
};

\node[draw] at (3.5,-4.2) {$A \leq D \;\land\; C \leq B$};


\end{tikzpicture}
\end{document}

```



The R*-tree
