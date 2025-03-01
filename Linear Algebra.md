 **It's important to know that most of operations in linear algebra can be extended to higher dimensions because when we go to a higher dimension, we just add a component to the vector, which is independent of other components.**


A matrix represents the linear transformation of the basis vectors
$$\begin{align}
\vec{v}=\left[ \matrix{x \\ y} \right] =x\hat{i}+y\hat{j} \\
L(\vec{v})&=L\left(x\hat\imath+y\hat\jmath\right) \\
&=xL\left(\hat\imath\right)+yL\left(\hat\jmath\right)

\end{align}
$$
In a linear transformation, when we transform the basis vectors, every resulting vector (i.e. the entire spanning space) will follow the transformation. It's like applying a function to every vector. But because every vector can be represented in terms of the basis vectors, we only need to know where the basis vectors will land after the transformation.

In a sense, a linear transformation is moving space.

For a transformation to be linear, two things need to true:
- The origin does not move
- The grid lines remain parallel to each other

We can represent the transformation of the basis vectors in a matrix:
$$
\underbrace{
\left[ 
	\matrix{a & b \\ c & d}
\right]}_{L}
\underbrace{\left[ \matrix{x \\ y} \right]}_{(\vec{v})}=x\left[ \matrix{a \\ b}\right]+y\left[ \matrix{c \\ d} \right]
$$
The above operation is called matrix-vector multiplication.


# Matric multiplication
Just as we can have function composition, we can have transformation composition: applying one transformation after another. In matrix form, this is written as:
$$
\underbrace{\left[ \matrix{1 & 1 \\ 0 & 1} \right]}_{\text{Shear}}
\left( \underbrace{\left[ \matrix{0 & -1 \\ 1 & 0} \right]}_{\text{Rotation}}
\left( \left[ \matrix{x \\ y} \right] \right) \right)
$$
The overall effect is finding one matrix that represents the ultimate transformation (in other words, where the basis vectors land). 
In the example above, first we apply the rotation transformation. Then, we apply the shear transformation. Think of it as applying functions. For that reason, matrices are multiplied from right to left.

First, we apply the transformation to $\vec{\imath}$ 
$$\begin{align}
\left[ \matrix{e & g \\ f & h} \right] \left[ \matrix{a & c \\ b & d} \right] \left[ \matrix{1 \\ 0} \right] \\
=\left[ \matrix{e & g \\ f & h} \right] \left[ \matrix{a \\ b} \right] \\
=a \left[ \matrix{e\\ f} \right]+b\left[ \matrix{g\\ h} \right] \\
=\left[ \matrix{ae+bg \\ af+bh} \right]
\end{align}
$$
Then, we transform $\vec{\jmath}$
$$\begin{align}
\left[ \matrix{e & g \\ f & h} \right] \left[ \matrix{a & c \\ b & d} \right] \left[ \matrix{0 \\ 1} \right] \\
=\left[ \matrix{e & g \\ f & h} \right] \left[ \matrix{c \\ d} \right] \\
=c \left[ \matrix{e\\ f} \right]+d\left[ \matrix{g\\ h} \right] \\
=\left[ \matrix{ce+dg \\ cf+dh} \right]
\end{align}
$$

So the final transformation matrix is
$$
\left[ \matrix{ae+bg & ce+dg \\ af+bh & cf+dh} \right]
$$


## Order of matrix multiplication matters
The order in which we apply transformations can drastically change the end results.


# A note about transformations
A matrix represents how the shape of a vector space is transformed. 
It tells us where the basis vectors will end up. But based on my findings, this is true only if the basis vectors $\hat\imath$ and $\hat\jmath$ are in their standard positions of $(1,0)$ and $(0,1)$ respectively. For example, let's say we want to rotate the 2D space $90\degree$ counter clockwise. The transformation matrix is:
$$
\begin{bmatrix}
0 & -1\\
1 & 0
\end{bmatrix}
$$
The inverse of this transformation is rotating the space $90\degree$ clockwise. If you reference the newly transformed basis vectors, you might think the transformation matrix is $\left[ \matrix{1 & 0 \\ 0 & 1}\right]$, because that's where you would want the basis vectors to go. But that's not the correct inverse. You get the correct matrix if we imagine rotating the space $90\degree$ clockwise from the standard positions of i and j. So the inverse is:
$$
\begin{bmatrix}
0 & -1\\
1 & 0
\end{bmatrix}
$$
# Determinants
The ratio by which area of volume of transformed space has changed
A negative determinant means that space has flipped (Like flipping a sheet of paper)

$$
\det(M_1M_2)=\det(M_1)\det(M_2)
$$
On the left side, we find the change in area/volume after applying two transformations. On the right ride, we find the change in ratio after applying the transformations, and multiply them together. Is there a difference? No. Because in the end, we transform transform the matrices to the same thing. 

## Determinant = 0
If we flatten a 3D space into a 2D plane, the determinant would be 0. 
Similarly, if we reduce space to a line, or a point, the determinant would be 0. In general, a 0 determinant means we're doing down in dimension. Such a transformation can't be undone. A function can only give one output for each input. We can't un-squish a line back to a plane. At least, a function can't do that.

In the case of 3D to 2D, an entire plane was squished to a line. If the vector we're trying to find happened to be along this plane, then we can find it.
## Formula to calculate determinants
### 2x2
$$
\det\left(\left[ \matrix{x & a \\ y & b} \right]\right)=xb-ay
$$
### 3x3
This formula is non-traditional, but it's basically derived after algebraically rearranging the traditional formula, which you can find online (I have it memorized anyways).
$$
\det\left(\left[ \matrix{x & v_1 & w_1\\ y & v_2 & w_2 \\ z & v_3 & w_3} \right]\right)=x\det\left(\left[ \matrix{v_2 & w_2 \\ v_3 & w_3} \right]\right)-y\det\left(\left[ \matrix{v_1 & w_1 \\ v_3 & w_3} \right]\right)+z\det\left(\left[ \matrix{v_1 & w_1 \\ v_2 & w_2} \right]\right)
$$

# Solving systems of linear equations using matrices
An interesting application of matrices
$$
\begin{align}
6x-3y+2z=7 \\
x+2y+5z=0 \\
2x-8y-z=-2 \\
\\

\underbrace{
\left[
\matrix{
6 & -3 & 2 \\
1 & 2 & 5 \\
2 & -8 & -1 \\
}
\right]
}_{A}
\underbrace{
\left[
\matrix{
x \\
y \\
z \\
}
\right]
}_{\vec{X}}
=
\underbrace{
\left[
\matrix{
7 \\
0 \\
-2 \\
}
\right]
}_{\vec{V}}
\end{align}
$$
From this perspective, the problem becomes this: what vector $\vec{X}$ can we transform using $A$ to get $\vec{V}$?

$$
\vec{X}=A^{-1}\vec{V}
$$
If the determinant isn't 0, then there's at least one solution. There could be multiple solutions. After the transformation, it's possible that multiple vectors landed on $\vec{V}$.

Let's say we squish a 2D plane into a line. The determinant is 0. There is no inverse, but a solution is still possible. All the vectors that already existed along the line before the transformation.

# Column Space
The set of all possible vectors out of a matrix transformation. The name comes from each column of the matrix, which defines the transformed basis vectors.

# The null space (kernel) of a matrix
The set of all vectors that land on the 0 vector (at the origin) after the transformation with a determinant of 0 

If you have a $3\times3$ matrix with only 1 linearly independent column (the other two are dependent), that means the 3D space is getting squished into a line, which implies an entire plane is getting squished into the 0 vector.
If space was getting squished to a 2D plane, then the null space would be a line.


# Non-square Matrices
## $2\times3$ Matrix
This represents a transformation from the 2D space to 3D space. The end result is still a plane. We can only span a 2D plane using two basis vectors.
$$
\left[
\matrix{
6 & -3 \\
1 & 2 \\
2 & -8 \\
}
\right]
$$
## $3\times2$ Matrix
This represents a transformation from the 3D space to 2D
$$
\left[
\matrix{
6 & -3 & 2 \\
1 & 2 & 5 \\
}
\right]
$$
Three basis vectors are being projected into the 2D world.

## $1\times2$ Matrix
$$
\left[
\matrix{
6 & -3 
}
\right]
$$
This represents transforming a 2D plane into a 1D line.

# Dot Product
When we take the dot product of two vectors, one of those vectors can be thought of as a transformation matrix.

one of those vectors contains the coordinates of some unit vector, along which a one dimensional line exists.

Notice the similarity between the following operations

$$\begin{align}
& \text{Dot product} &&\left[\matrix{u_x \\ u_y}\right] \cdot \left[\matrix{v_x \\ v_y}\right] =u_xv_x+u_yv_y \\ \\
& \text{matrix multiplication} &&\left[\matrix{u_x & u_y}\right] \left[\matrix{v_x \\ v_y}\right] =u_xv_x+u_yv_y 
\end{align}
$$
The dot product can be thought of as transforming a 2D vector $\vec v$ onto the number line tilted so that it lies along some unit vector we'll name $\vec{u}$. Where along that line do $\vec\imath$ and $\vec\jmath$ land on? Think of a linear function that takes in the coordinates of  $\vec v$ and spits out a number along this number line. Where ever they land, that would be transformation matrix from 2D to 1D. Both $\vec u$ and $\vec\imath$ are unit vectors and have the same length (of 1). By symmetry, the projection of $\vec u$ along $\vec\imath$ ($\vec u_x$) has the same length as the projection of $\vec\imath$ along $\vec u$, which we need in order to define our transformation matrix. The same reasoning is can be applied to $\vec\jmath$. Overall, the transformation matrix is $[\matrix{u_x & u_y}]$ . Now let's say we scale $\vec u$ by a factor of some real number we call $n$.  $\vec\imath$ and $\vec\jmath$ are transformed to $n$ times before, because the transformation is linear. Also for that reason, we're able to transform $\vec\imath$ and $\vec\imath$, and then multiply by $n$. So we project a vector onto $\vec u$, then multiply it by the length of $\vec u$. That's the geometrical interpretation of the dot product. 

The dual vector is some vector $\vec u$ that can be used to transform our vector to the 1 dimensional line after performing the dot product (or matrix multiplication if we flip u onto its side).

And the dot product is associative. When we do the dot product between two vectors, we can imagine either of those vectors is the unit vector, and it will not make a difference. 
Dot product can be performed on vectors with more components. That can still be thought of as transforming the vector to a 1 dimensional line.

We have justified why the dot product of two vectors equals the projection of vector 1 onto vector 2, times the length of vector 2. Using some trigonometry, we get:
$$
\vec u \cdot \vec w=|\vec u||\vec w|\cos(\theta)
$$

# Duality
> ... the idea of duality is that anytime you have a linear transformation from some space to the number line, it is associated with a unique vector in that space, in the sense that performing the linear transformation is the same as taking a dot product with that vector. [3Blue1Brown](https://www.3blue1brown.com/lessons/cross-products-extended)

> when \[...\] you find a linear transformation to the number line, you will be able to match it to some vector, which is called the "dual vector" of the transformation, so that performing that linear transformation is the same as taking the dot product with that vector.
# Cross Product
$$
\vec v \times \vec w=- \vec w\times \vec v
$$
Order matters in cross product

$$
\vec v \times \vec w=\det\left(\left[\matrix{v_x & w_x \\ v_y & w_y}\right]\right)
$$
Furthermore, the area of the resulting parallelogram can be calculated as follows:
$$
\vec v \times \vec w=|\vec v||\vec w|\sin(\theta)
$$

The cross product of two vectors can therefore be thought of the change in area in space after transforming the basis vectors to to v and w

Remember that determinant is negative if space is flipped. So if a cross product corresponds with flipping space (in other words, if v falls to the left of w), the cross product will also be negative.

If you scale a vector, the area will also be scaled by that factor. So,
$$
\vec v \times (n\vec w)=n(\vec v \times \vec w)
$$

$$
\vec v \times \vec w=- \vec w\times \vec v
$$



In reality, the cross product is a 3D operation. We use the right hand rule to find the direction of the resulting vector. The resulting vector is orthogonal to v and w.
$$
\vec v \times \vec w=\left[\matrix{v_x \\ v_y \\ v_z}\right]\times \left[\matrix{w_x \\ w_y \\ w_z}\right]=\det\left(\left[\matrix{i & v_x & w_x \\ j & v_y & w_y \\ k & v_z & w_z}\right]\right)
$$


## Reasoning why the cross product formula works
Consider the following. 
$$
f(\vec u)=\det\left(\left[\matrix{u_x & v_x & w_x \\ u_y & v_y & w_y \\ u_z & v_z & w_z \\}\right]\right)
$$
$f$ is a transformation. The vectors $\vec v$ and $\vec w$ are constant. It takes in a 3D vector $\vec u$ and outputs a number. In addition, this is a linear transformation because calculating the determinant of a 3x3 matrix is a linear operation. 

What is the matrix that represents this transformation of 3D $\vec u$ onto the number line?
$$
\left[\matrix{x & y & z}\right]\left[\matrix{u_x \\ u_y \\ u_z}\right]=\det\left(\left[\matrix{u_x & v_x & w_x \\ u_y & v_y & w_y \\ u_z & v_z & w_z \\}\right]\right)
$$
Furthermore, what is the dual vector of $\vec u$? What is the vector that when we perform the dot product, we get the same results as the transformation above? Let's call this vector $\vec p$
$$
\left[\matrix{p_x \\ p_y \\ p_z}\right]\cdot\left[\matrix{u_x \\ u_y \\ u_z}\right]=\det\left(\left[\matrix{u_x & v_x & w_x \\ u_y & v_y & w_y \\ u_z & v_z & w_z \\}\right]\right)
$$
Expanding the right side and left side, we find the coordinates of $\vec p$ to be:
$$
\left[\matrix{p_x \\ p_y \\ p_z}\right]=\left[\matrix{v_yw_z-v_zw_y \\ v_zw_x-v_xw_z \\ v_xw_y-v_yw_x}\right]
$$
This looks just like the formula for finding a cross product vector
$$
\det\left(\left[\matrix{i & v_x & w_x \\ j & v_y & w_y \\ k & v_z & w_z}\right]\right)
$$
Finding the cross product of two vectors $\vec v$ and $\vec w$ is the equivalent of asking the following question:
>What vector $\vec p$​ has the special property that when you take a dot product between $\vec p$​ and $\vec u$, it gives the same result as plugging in $\vec u$ to the first column of a matrix whose other two columns have the coordinates of $\vec v$ and $\vec w$, then computing the determinant?

Now, how do we show that $\vec p$ is orthogonal to $\vec v$ and $\vec w$, and that its length equals the parallelogram spanned by those vectors? 


So we have two constant vectors v and w. We have some arbitrary vector u. We just found some vector $\vec p$ that when we take the dot product of u and p, we get the volume of the parallelepiped that is spanned by the vectors u, v, and w.  
The geometric interpretation of the dot product is the length of projection of u onto p, times the length of p:
$$\begin{align}
p\cdot u=\text{Volume of parallelepiped} \\
\text{base} \times \text{height} = \text{Volume of parallelepiped} \\
\end{align}
$$
This would only work if $\left|\vec p\right|$ is is perpendicular to the base, which is spanned by $\vec v$ and $\vec w$. Thus, $\vec p$ is  orthogonal to $\vec v$ and $\vec w$. 
If the component of u along$\vec p$is the height, then $\vec p$ is the base. Thus, 
$$
\left|\vec p\right|=\det\left(\left[\matrix{v_x & w_x \\ v_y & w_y}\right]\right)
$$
# Cramer's Rule
In most cases, the dot product of two vectors before and after the transformation will not be the same. In rare cases, however, when the angle between the vectors and the ratio of their lengths do not change, the dot products remain the same.
Such transformations are called **orthonormal**, and mostly include rotations.

This can be used to solve systems of linear equations.
$$
\left[\matrix{a & c \\ b & d}\right]\left[\matrix{x\\ y}\right]=\left[\matrix{e \\ f}\right]

$$
$$
\begin{align}

\left[
	\matrix{x\\ y}
\right] \cdot
\underbrace{
	\left[
		\matrix{1\\ 0}
	\right]}
_{\hat\imath}
=
T\left(\left[\matrix{x\\ y}\right]\right)
\cdot
T\left(\left[\matrix{1\\ 0}\right]\right)
=x 
\\
\left[\matrix{e \\ f}\right] \cdot \left[\matrix{a \\ b}\right]=x

\end{align}
$$

A similar procedure can be done to find $y$.
$$
\left[\matrix{x\\ y}\right]\cdot \underbrace{\left[\matrix{0\\ 1}\right]}_{\hat\jmath}=T\left(\left[\matrix{x\\ y}\right]\right)\cdot T\left(\left[\matrix{0\\ 1}\right]\right)=y
$$







$$
x = \det\left( \begin{bmatrix} x & 0 & 0 \\ y & 1 & 0 \\ z & 0 & 1 \end{bmatrix} \right)
$$
We have a paralepidid whose base is spanned by $\hat\imath$ and $\hat k$ with an area of 1. This, multiplied by the length of the paralepidid along the x axis gives us its volume, which equals x. 

![[ParallelepipedVJK.light.svg]]

After the transformation, the entire space gets scaled by the determinant of the transformation matrix. So we have  
$$\begin{align}
\text{Area before} \times \text{factor} = \text{new area}
\end{align}
$$

To put it in other words, we're able to represent an area/volume of space in terms of a component of the vector we're solving for. If we divide the area/volume after the transformation by the factor we're scaling it by, we get the original area/volume, which is the variable we're trying to solve for.

$$
\begin{align}
6x-3y+2z=7 \\
x+2y+5z=0 \\
2x-8y-z=-2 \\
\\

\underbrace{
\left[
\matrix{
6 & -3 & 2 \\
1 & 2 & 5 \\
2 & -8 & -1 \\
}
\right]
}_{A}
\underbrace{
\left[
\matrix{
x \\
y \\
z \\
}
\right]
}_{\vec{X}}
=
\underbrace{
\left[
\matrix{
7 \\
0 \\
-2 \\
}
\right]
}_{\vec{V}}
\end{align}
$$
$$
\begin{align}
x \ \det(A) = \det\left(\begin{bmatrix}V & T(\hat\jmath) &  T(\hat  k)\end{bmatrix}\right) 
\\
\end{align}
$$

We can do the same logic for finding $y$ and $z$

$$
y=\det\left(\begin{bmatrix}
1 & x & 0 \\ 0 & y & 0 \\ 0 & z & 1
\end{bmatrix}\right)
$$
$$
y \ \det(A)= \det(\begin{bmatrix}
T(\hat{\imath}) & V & T(\hat{k})
\end{bmatrix})
$$

# Change of Basis
How do we represent a vector $\vec{v}$ that's defined in terms of $\hat{\imath}$ and $\hat{\jmath}$, in terms of arbitrary basis vectors, say $a$ and $b$?
Well, it's very simple. It's like we're transforming $\hat{\imath}$ and $\hat{\jmath}$ to $a$ and $b$.
$$
\begin{bmatrix}
a_{1} & b_{1} \\
a_{2} & b_{2}  \\
\end{bmatrix}
\begin{bmatrix}
v_{1}  \\
v_{2}
\end{bmatrix}
$$
We're going from our grid to the other grid. But, when we multiply the vector by the matrix, we get a vector that's in terms of our grid.

Let's say we have two coordinates, S (standard) and T (which is transformed by some matrix)

$$
\overbrace{ A }^{ \text{S to T transformation} }\underbrace{ \vec{x} }_{ \text{Vector in T} }=\underbrace{ \vec{y} }_{ \text{Vector in S} }
$$
$$
\underbrace{ \vec{x} }_{ \text{Vector in T} }=A^{-1}\underbrace{ \vec{y} }_{ \text{Vector in S} }
$$
Now, how do we transform T? Transformations are tied to the basis vector. The same transformation will have different effect on S and T. Let's say have a transformation in terms of S. How do we apply it to a vector in terms of T?
So we're given a vector in terms of T. First, we convert the vector to be in terms of S. Then, we apply the transformation. And finally, we convert the vector back to T.
$$A^{-1}MAV$$

# Eigenvectors and Eigenvalues
Eigenvectors are vectors that simply get scaled after a transformation. They do not move out of their span. They remain on the line they span. 
The scale factor is called the eigenvalue of that vector.

Eigenvalue can be negative, meaning the vector was flipped. Does this mean the determinant of the transformation is negative?

Eigenvectors are important in 3D. We can think of it as an axis of rotation.
> It's much easier to think about a 3d rotation in terms of an axis of rotation, and an angle by which it is rotating, rather than thinking about the full 3x3 matrix associated with such a transformation.

