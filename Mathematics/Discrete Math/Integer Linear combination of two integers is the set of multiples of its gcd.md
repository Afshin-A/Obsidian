This sounds complicated but it actually makes sense when you remember that $gcd$ is just the largest factor of two numbers.

This fact is used in proving that [[Modular inverse of a mod n only exists when a and n are co-primes]], i.e. $gcd(a, n) = 1$

Suppose we have two arbitrary integers s and t
$$
\begin{align}
&at+ns \\
= \ &gcd(a,n)\left( \frac{a}{gcd(a,n)} t + \frac{n}{gcd(a,n)}s\right)  \\
\frac{a}{gcd(a,n)},\ \frac{n}{gcd(a,n)} \in \symbb{Z} \\
s, \ t \in \symbb{Z} \\
\end{align}
$$
$\frac{a}{gcd(a,n)},\frac{n}{gcd(a,n)}, s, t$
All 4 of these are integers. So a linear combination of them is also an integer. (Adding and multiplying integers gives an integer.)
Thus, 
$$
\begin{align}
at+ns=k\ gcd(a,n) \quad k \in \symbb{Z} \\ 
\blacksquare
\end{align}
$$
We have just shown that the set of integer linear combination of two integers, are all multiples of the greatest common divisor of those two integers.