In the modular world, division does not really make sense. How would you, for example, define  half of $1 \mod{6}$ when the possible values for any number $x$ be $\{0, 1,2,3,4,5\}$. In fact, fractions make no sense in the modular arithmetic world. However, we can define and derive the modular inverse of a number. This has various applications, including the [[Rolling hash function]], as seen in the [[KMP algorithm]] for finding patterns in text.

When we say the inverse of some number $a \mod{m}$, we mean some number $b$ such that:
$$
a\times b \equiv 1 \mod{m}
$$
And this is only possible if a and b are co-primes, i.e.  $gcd(a, b) == 1$ as derived by the [[Euclidean algorithm]], which we can use to backtrack our way to find the modular inverse.

Let's find $gcd(3000, 197)$:
$$
\begin{align}
3000 \mod{197}=
\end{align}
$$


Two numbers $a$ and $b$ are mod $n$ equivalent if $a-b| \ n$ 
This makes sense because $a + nx=b$. suppose we're measuring time by counting hours going around a clock starting at 1. after 12 hours, we get to hour 13. 1 and 13 are mod 12 equivalent. going another 12 hours we get to hour 25. 
25 and 1 are also mod 12 equivalent. We get to these mod equivalent numbers by adding multiples of 12. In the modular arithmetic world, the number line is not infinite: we go in a circle eventually ending up back where we started. 
