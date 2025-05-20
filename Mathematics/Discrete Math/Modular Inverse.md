The modular number of $a$ in the world of $\mod{n}$ is some number $b$ such that
$$
ab \equiv 1 \mod{n}
$$
We can use the extended Euclidean algorithm to solve this when we write this equation as
$$
\begin{align}
(ab+kn=1)\mod{n} \\
ab \mod{n} + \underbrace{  kn \mod{n}}_{0} \equiv 1 \mod{n} \\
ab \equiv 1 \mod{n}
\end{align}
$$
So we solve for $b$ and $k$ in $ab+kn=1$ using the extended Euclidean algorithm, and just discard $k$.

Another note is that the extended Euclidean algorithm solves $ab+kn=\gcd(a,n)$, which we said is one. That means this only works only when $a$ and $n$ are co-primes. In fact, the modular inverse of $a$ only exists if $\gcd(a,n)=1$
