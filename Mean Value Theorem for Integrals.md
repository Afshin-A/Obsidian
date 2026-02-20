Consider an arbitrary function $f(x)$ that is differentiable over the range $[a,b]$. 
The mean value theorem states that there exists a point $c$ in the range $[a,b]$ such that the slope of the tangent line to $f(x)$, i.e. the derivative, at that point is equal to the slope of the line connecting $f(a)$ to $f(b)$.

$$
f'(c)=\frac{f(b)-f(a)}{b-a}
$$
The numerator of this formula can be re-written as the definite integral of $f$ in the range $[a,b]$ as follows:
$$
f^{\prime}(c)=\frac{\int^{a}_{b}f'(x) \ dx}{b-a}
$$
This is nothing but the formula for the average value of $f'$ in the given range. In other words,
>Given a continuous function $f$ in range $[a, b]$, there exists a value $c$ such that the derivative at $c$ equals the average of all derivative values in that range.
