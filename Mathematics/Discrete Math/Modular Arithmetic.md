
By definition, when two integers $a$ and $b$, are mod congruent, it means there exist an integer $n$ such that:
$$
\begin{align}
a \equiv b \mod{n} \to \space n | a-b \\
\frac{a-b}{n}=k \in \mathbb{Z} \\
a=kn+b
\end{align}
$$
This further leads to the following:
$$
\begin{align}
a=q_{1}n+r_{1} \\
b=q_{2}+r_{2} \\
a-b=\big(q_{1}-q_{2}\big)n+(r_{1}-r_{2}) \\ 
a-b=kn\\
0\leq r_{1}, r_{2} < n \\
\therefore r_{1}-r_{2}=0 \\
\therefore r_{1}=r_{2} 
\end{align}
$$
Therefore, when $a$ and $b$ are mod n congruent, that means the remainders of both integers when divided by n are equal.



 that no two different values of x can produce the same result when multiplied by a and taken modulo n

we have x_1 and x_2. suppose x_2=ax_1. in other words, x_2 is the next index we get to if x_1 is occupied.


$$
a+b \mod{N} = \Big(a \mod{N} + b \mod{N}\Big) \mod{N}
$$