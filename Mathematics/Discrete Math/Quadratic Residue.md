$$
x^2 \equiv c \mod{p}
$$If $x$ exists, then $c$ is a quadratic residue
If $x$ does not exist, $c$ is a non-quadratic residue

Example:
$$
\begin{align}
x^2 \equiv c \mod{5}
\end{align}
$$
>Yeah, that's not going to scale. In practice you test whether the number is a quadratic residue mod a few small integers. The first stage is to look at the number mod 256 i.e. examine the least significant byte. Then, for a 64-bit machine, test mod 5, 7, 9, 13, 17 and 97. This catches 99.62% of perfect squares very quickly. If the number passes the test you still need to verify it's a square which is expensive, but you only have to do it 0.38% of the time

