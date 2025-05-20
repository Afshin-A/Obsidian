The Euclidean algorithm is about replacing the problem of finding the greatest common divisor (factor) of two numbers with a simpler problem. And that stems from the fact that $a$, $b$, and the remainder after taking a factor of $b$ from $a$ all have the same largest factor.

Let's suppose we have two piles of stones. In the larger pile, there are $a$ stones, and in the smaller pile, there are $b$ stones. Now assume both piles share a common factor, $g$. $g$ is then also a factor of all the stones, given by $a+b$.

Let's group all the stones in the two piles into groups of $g$. When we take a multiple of $b$ from $a$, we're left with groups of $g$ in the remainder. 

Mathematically, we can show this as follows:
$$
\begin{align}
b,\ a \in \symbb{Z} \\
g|a \\
g|b \\
g|a-k\cdot b=r \\
\therefore g|r
\end{align}
$$
