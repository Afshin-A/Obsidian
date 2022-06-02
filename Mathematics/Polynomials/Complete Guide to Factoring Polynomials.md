This is mostly for polynomials with 3 or higher degree polynomials. Prabolas can easily be factored; quadratic equation can also be used.

$P(x)=a_n\ x^n+a_{n-1}x^{n-1}+a_{n-2}\ x^{n-2} + \cdots + a_{1}x^{1}+a_{0}$
In total, P has n real and complex factors.

Before identifying the possible zeros, check if the polynomial can be factored by grouping.
$$\begin{align}
P(x)&=x^3+2x^2+4x+8 \\
&=x^2(x+2)+4(x+2) \\
&=(x^2+4)(x+2)\\
&\therefore x=-2, \pm 2i
\end{align}
$$
Use Descartes' Rule of Signs to guess how many positive and negative zeros there are.

Use [[Rational Zeros Theorem]] to make a list of possible factors.

Start from the smallest positive candidate (if Descartes' rule shows there are any), testing factors using synthetic division. If a candidate is a factor, test that candidate again; it may have a multiplicity higher than 1. Any candidates that do not yield a zero remainder are not zeros of the polynomial and should be eliminated from the list. Repeat the process until all positive zeros are found.

If at any point, all terms at the bottom of the synthetic division are positive and the remainder is 0, then we've found the largest positive factor.

Start testing the negative candidates. If at any point, all terms at the bottom of the synthetic division are alternating between non-positive and non-negative, then we've found the smallest zero. Repeat until all negative zeros are found.

If there are still 2 or higher degree polynomials left in the decomposed $P(x)$, solve for imaginary zeros.

Keep in mind that [[Conjugate of a Complex Zero is also a Zero in Polynomials]].
