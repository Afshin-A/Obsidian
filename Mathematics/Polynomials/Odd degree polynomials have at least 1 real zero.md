One way to think about is this:
Suppose $P(x)$ is a polynomail with an odd degree $n$ and **all real coefficients**. We know that the [[Conjugate of a Complex Zero is also a Zero in Polynomials]]. So $P(x)$ could, hypotherically, have at most $n-1$ complex zeros at most:
$$
P(x)=(x-z)(x-\overline{z}) \dots (x-a)
$$
Thus in the most extreme case there will be a real zero $(x-a)$

Another approach:
Multiplying a complex number by its conjugate yields a real number:
$$
\begin{align}
(a+bi)(a-bi)&=a^2-b^2i^2 \\
&=a^2+b^2
\end{align}
$$
And multiplying a real number by a complex number yields a complex number.
Let's suppose $P(x)$ has $n-1$ complex zeros along with their conjugates. Multiplying all these conjugates will yield real coefficients. If the last zero was complex, somewhere in expanding the ploynomial we would be multiplying a real number by a complex number, resulting in complex coefficients, which cannot be per our assumptions.