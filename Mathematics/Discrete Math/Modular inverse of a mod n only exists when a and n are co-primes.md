### Theory:
The modular inverse of $a \mod{n}$ exists if and only if $\gcd(a,n)=1$

### Background
The multiplicative inverse of $a$ in $\mod{n}$ is some number such that:
$$
ab \equiv 1 \mod{n}
$$

We also use the fact that the [[Integer Linear combination of two integers is the set of multiples of its gcd]].
### Proof
By definition, this means:
$$
\begin{align}
n |(ab-1)   \\
\implies ab-1=kn \quad k \in \mathbb{Z} \\
ab-kn=1  \\
ab-kn=l \cdot \gcd(a,n) \\ \\

l \cdot \gcd(a,n) = 1 \\
\end{align}
$$
For the last identity to be true, that means both $l$ and $\gcd(a,n)$ must be 1 or -1. But because $\gcd(a,n)>0$, that means $\gcd(a,n)=1 \quad\blacksquare$ 

Note that here, $a$ and $n$ are fixed, while $k$ and $b$ are arbitrary. We're trying to find $b$, so it's arbitrary: it could be anything. So $ab-kn$ really is a linear combination. 

This proof was only for the forward direction. We also need to prove the theorem going backwards, but I feel like that's too much going down the rabbit hole. This is sufficient for our purposes of cs algorithms. 

Next, how do we find integer solutions for the equation $ab-kn=1$? This is done with the [[Extended Euclidean algorithm]]