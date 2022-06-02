### Upper Bound

Let 
$$
P(x)=a_n\ x^n+a_{n-1}x^{n-1}+a_{n-2}\ x^{n-2} + \cdots + a_{1}x^{1}+a_{0}
$$
be a polynomial. Assume $b>0$ is a zero of $P(x) \ \therefore P(b)=0$
We can rewrite $P(x)$ as
$$
P(x)=(x-b)Q(x)+r
$$
where $Q(x)$ is the quotient and $r$ is the remainder.
Now suppose $z>b \to z>0$ and that all coefficients of $Q(x)$ are non-negative $(\ge0)$
$$
\begin{alignat*}{3}
P(z)=&(z-b) && Q(z) + &&r \\
& > 0 && > 0 && \geq0 \\
\therefore P(z) > 0
\end{alignat*}
$$
$P(z)$ will always be greater than $0$, never equal to $0$, and therefore $z$ cannot be a zero of $P$. Hence, $b$ is the largest zero of $P$.


### Lower Bound
