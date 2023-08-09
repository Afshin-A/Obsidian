We usually think about vectors as arrows in space. But we can also think of them as points. This makes it easier to visualize them (is it easier to draw a million arrows that span a 2D plane, or a million points on that plane?). So instead of drawing a vector that comes from the origin, we just draw the other end point of that vector.

Applying a linear transformation to a spanning space like the 2D coordinate system means transforming every vector in that span, including the basis vectors like $\hat i$  and $\hat j$, the same . So if we were able to use these to represent a vector $\hat v=\begin{bmatrix}x \\ y\end{bmatrix}$ before transformation, we ought to be able to use the transformed versions $\hat i_t$ and $\hat j_t$ to represent $\hat v_t$ because they were all transformed the same way.
$$
\begin{bmatrix}
x \\
y
\end{bmatrix} = x \hat i + y \hat j
$$
$$
T(
\begin{bmatrix}
x \\
y
\end{bmatrix}) = x \hat i_t + y \hat j_t
$$
In a sense, a linear transformation is like a function: we input a vector and it outputs a transformed vector. If we feed it every possible vector in a spanning space, then we transform that space.

So we can represent every transformation with just two vectors ($\hat i_t$  and $\hat j_t$). We will take the coordinates of these two vectors, put them next to each other inside brackets, and create a concise way of representing a linear transformation. We will call this... a matrix. 
$$
T(
\begin{bmatrix}
x \\
y
\end{bmatrix}) = 
\begin{bmatrix}
a & b\\
c & d
\end{bmatrix}
\begin{bmatrix}
x \\
y
\end{bmatrix}
$$
where $a$ and $c$ are the components to $\hat i_t$ and $b$ and $d$ are to $\hat j_t$
In a sense, the matrix can be thought of as a function applied to an arbitrary vector $\begin{bmatrix} x \\ y \end{bmatrix}$.
Now, what if we apply a transformation to a transformation? First we apply one transformation $T_1$ to a spanning space, then we apply a second transformation $T_2$ to the transformed space.
$$
T_2\Big(T_1\Big(\begin{bmatrix}x \\ y \end{bmatrix}\Big)\Big)
=\begin{bmatrix}e & f \\ g & h\end{bmatrix}\begin{bmatrix}a & b\\ c & d \end{bmatrix}\begin{bmatrix}x \\ y \end{bmatrix}
$$
where $\begin{bmatrix}e & f \\ g & h\end{bmatrix}$ represents the second transformation. Remember that $\begin{bmatrix} a \\ c \end{bmatrix}$ represents $T_1(\hat i)$ and $\begin{bmatrix} b \\ d \end{bmatrix}$ represents $T_1(\hat j)$. These are the basis vectors to the newly transformed space, and we are going to apply another transformation them, just like we did for $T_1$. We'll first apply $T_2$ to $\begin{bmatrix} a \\ c \end{bmatrix}$, then to $\begin{bmatrix} a \\ c \end{bmatrix}$.
We just multiplied two 2x2 matrices together.
$$
\begin{align}
&\begin{bmatrix}e & f \\ g & h\end{bmatrix}
\begin{bmatrix}a & b\\ c & d \end{bmatrix} \\
= & \begin{bmatrix}
	\begin{bmatrix}e & f \\ g & h\end{bmatrix}\begin{bmatrix}a \\ c\end{bmatrix} & 
	\begin{bmatrix}e & f \\ g & h\end{bmatrix}\begin{bmatrix}b \\ d\end{bmatrix}	
\end{bmatrix} \\
= & \begin{bmatrix}
	a \begin{bmatrix}e \\ g\end{bmatrix} + c \begin{bmatrix}f \\ h\end{bmatrix} & 
	b \begin{bmatrix}e \\ g\end{bmatrix} + d \begin{bmatrix}f \\ h\end{bmatrix}
\end{bmatrix} \\
= & \begin{bmatrix}
ae+cf  & be+df \\ ag+ch & bg+dh
\end{bmatrix}
\end{align}
$$
Thinking of matrix multiplication as a composition of linear transformation functions (in other words, applying a linear transformation to another linear transformation) also explains why the order in matrix multiplication matters because in general, $f \circ g(x) \neq g \circ f(x)$
So matrix multiplication is not commutative.

This way of thinking also shows us why matrix multiplication is associative:
$$
A(BC) = (AB) C
$$
This is because compositional functions are associative.
<iframe width="560" height="315" src="https://www.youtube.com/embed/mCnjpnhLeDU" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>


The logic behind using Gaussian Elimination to finding if two vectors are linearly dependent.
If we can show that a vector $\vec u$ is a linear combination of two other vectors $\vec v$ and $\vec w$, well that means $\vec u$ is linearly dependent on those vectors. In other words, $\vec u$ already exists in the spanning space created by $\vec v$ and $\vec w$ and does not add an extra dimension to that spanning space.
$$
\begin{bmatrix}
\vec u & \vec v & \vec w \\
1.0 & 0.0 & 1.0 \\
0.5 & 1.0 & 1.5 \\
1.0 & 0.0 & 1.0
\end{bmatrix}
$$
Gaussian elimination works by manipulating rows (scalar multiplication and adding/subtracting rows to and from each other). But we've learned to think of matrices as grouped vectors: each column is a vector that represents the transformed basis vector for a new transformed space. So if you look closely at the matrix above, we can see that $\vec w = \vec u + \vec v$ which means $\vec w$ is linearly dependent.
But also look at the 1st and third rows in the matrix. They're identical!