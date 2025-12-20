A partial derivative answers one question:
What is the rate of change of a function $f(x,y)$ as only $x$ changes? In this case, $y$ is unchanged: it's a constant, so we can treat it as a constant variable as we take the derivative. For example:
$$
\begin{align}
f(x,y)=x^2y+\sin(y) \\
{ \partial f \over \partial x } &= { \partial \over \partial x }(x^2y) + { \partial \over \partial x }(\sin(y)) \\
&=2xy
\end{align}
$$
https://www.desmos.com/3d/0hxavmbcsm


A second partial derivative with respect to the same variable is similar. Now we're calculating the rate of change of the slope 
![[partial_derivatives_1.png|500]] 


In this image, the green plane is $y=0.5$ 
y is constant everywhere in that plane
The partial derivative of f at y=0.5 would be the slope of that curve which is resulted from the intersection of f and the plane
The second partial derivative with respect to x would be the rate of change of the slope of that curve
The second partial derivative with respect to y would be the rate of change of the slope of that curve, as we move the green plane away or towards us 



# Gradients
Let's say we're standing on a point $A$ on a surface represented by the function $f(x,y)$. $\partial f \over \partial x$ tells us the direction of change (or the steepness) in the x-axes (east-west direction).
$\partial f \over \partial y$ tells us the direction of change in the y-axes (north-south) direction. 
These two can be thought of vectors. Each has a value and a direction. Together, they tell us the direction the function $f$ changes the most (i.e. the steepest slope) at point $A$
The components of this vector are functions themselves in terms of $x$ and $y$. Together, they span out a vector space, referred to as the gradient of $f$
$$
\nabla f(x,y, \cdots)=
\begin{bmatrix}
\partial f \over \partial x \\
\partial f \over \partial y \\
\cdots
\end{bmatrix}
$$
So the gradient tells us how fast and in what direction the value of $f$ increases.

But, what if we want to know the rate of change in any arbitrary direction? That is called a **directional derivative**.


# Contour plots
This is a way to represent 3D surfaces on a 3D plane. It's like slicing a cake horizontally 
Similarly, we slice through the shape and make our way up the z axes. Each contour line is the result of the intersection of the horizontal plane and the surface. The value of Z is written next to the contour lines. They can also be represented with a color map.
![[contour_plot_1.png|500]]
Top view (looking down the positive z axes)

![[contour_plot_white_bg.png|500]]

**An interesting fact about gradients is that they are often perpendicular to contour lines.** 


# Directional derivatives
$$\begin{align}
\nabla_{\vec{v}}f \\
\partial f \over \partial \vec{v} \\
\partial \vec{v}
\end{align}
$$

$$
\begin{align}
\nabla_{\vec{u}}f(x_{0},y_{0})=\lim_{h \to 0}\frac{f(x_{0}+h \vec{u_{1}},y_{0}+h \vec{u_{2}})-f(x_{0},y_{0})}{h}
\end{align}
$$
# Multivariable chain rule
$$
\begin{align}
\frac{dw}{dt}=\frac{\partial w}{\partial x}\frac{dx}{dt}+\frac{\partial w}{\partial y}\frac{dy}{dt}
\end{align}
$$
https://youtu.be/9yCtWfI_Vjg?list=PLHXZ9OQGMqxc_CvEy7xBKRQr6I214QJcd
https://www.khanacademy.org/math/multivariable-calculus/multivariable-derivatives/multivariable-chain-rule/v/multivariable-chain-rule-intuition


# Equation of 3D Planes
This is done using a point on the plane and the normal
$$
\begin{align}
\begin{bmatrix}
x-x_{0}\\
y-y_{0}\\
z-z_{0}
\end{bmatrix} 
\cdot
\begin{bmatrix}
n_{x} \\
n_{y} \\
n_{z}
\end{bmatrix}
= 0 \\
(x-x_{0})n_{x}+(y-y_{0})n_{y}+(z-z_{0})n_{z}=0
\end{align}
$$
We can rearrange this equation to get a linear equation in terms of x, y, and z. These are the only unknowns 