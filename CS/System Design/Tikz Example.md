A LaTeX package used for drawing. It has several libraries like *graphdrawing* which we will use to draw graphs.

First, we need to install Tikz from the community plugins for Obsidian. Then make sure to restart Obsidian.

A few notes:
- `node distance` is how apart the nodes will be.
- `very thick` has to do with how bold the node borders will be. 
- `out` is where on the node exterior the edge goes out, and `in` is where in returns. `looseness` is how curvy the edge is. 
- For a weighted edge, we're basically placing an invisible node between the nodes 2 and 3.
- It looks like the parameter `midway` has no effect.

```
\begin{document} 
\begin{tikzpicture}[node distance={15mm}, very thick, main/.style={draw, circle}, every node/.style={scale=2}] 

\node[main] (1) {$x_1$}; 
\node[main] [above right of=1](2) {$x_2$};
\node[main] [below right of=1](3) {$x_3$};
\node[main] [above left of=1](4) {$x_4$};
\node[main] [below left of=1](5) {$x_5$};
\node[main] [right of=2](6) {$x_6$};

\draw (2) -- (4);
\draw[->] (3) to (6);


\draw[->] (1) to [out=180, in=270, looseness=5] (1);

\draw[->] (2) -- node[midway, above, sloped, pos=0.5] {+1} (3);

\end{tikzpicture} 
\end{document}
```


```tikz 
\begin{document} 
\begin{tikzpicture}[node distance={15mm}, very thick, main/.style={draw, circle}, every node/.style={scale=2}] 

\node[main] (1) {$x_1$}; 
\node[main] [above right of=1](2) {$x_2$};
\node[main] [below right of=1](3) {$x_3$};
\node[main] [above left of=1](4) {$x_4$};
\node[main] [below left of=1](5) {$x_5$};
\node[main] [right of=2](6) {$x_6$};

\draw (2) -- (4);
\draw[->] (3) to (6);


\draw[->] (1) to [out=180, in=270, looseness=5] (1);

\draw[->] (2) -- node[midway, above, sloped, pos=0.5] {+1} (3);

\end{tikzpicture} 
\end{document}
```



[Source](https://www.baeldung.com/cs/latex-drawing-graphs)
```tikz
\begin{document} 
\begin{tikzpicture}[node distance={15mm}, thick, main/.style = {draw, circle}] 
\node[main] (1) {$x_1$}; 
\node[main] (2) [above right of=1] {$x_2$}; 
\node[main] (3) [below right of=1] {$x_3$}; 
\node[main] (4) [above right of=3] {$x_4$}; 
\node[main] (5) [above right of=4] {$x_5$}; 
\node[main] (6) [below right of=4] {$x_6$}; 
\draw[->] (1) -- (2); 
\draw[->] (1) -- (3); 
\draw (1) to [out=135,in=90,looseness=1.5] (5); 
\draw (1) to [out=180,in=270,looseness=5] (1); 
\draw (2) -- (4); 
\draw (3) -- (4); 
\draw (5) -- (4); 
\draw[->] (5) to [out=315, in=315, looseness=2.5] (3); 
\draw[->] (6) -- node[midway, above right, sloped, pos=1] {+1} (4); 
\end{tikzpicture} 
\end{document}
```
