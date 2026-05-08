# Bloom Filter
A **bloom filter** is a quick way to check if an item *does not* exists in the database, without having to run a query.
We initialize a bit array of size $m$ to 0 and store it in memory. We would then run each DB row element through $k$ hash functions. These functions are independent and produce a value in the range $[0,m)$. This value represents an index in our bit array, which we set the value to 1. 
To check if an element exists in the database, we run it through the same functions. If not all values at the resulting indices are 1, then the element doesn't exist. But if all are 1, the element *could* exist in the database. If we run a query and it turns out the element doesn't exist after all, that is what's called a *false positive.* The more false positives, the more unnecessary database queries are ran and the more inefficient this system becomes. So we need to pick values for $m$ and $k$ that lower the probability of getting a false positive. 
$$
\large p \approx (1 - e^{-\frac{kn}{m}})^k
$$
## Deriving the formula
After running an element through a hash function once, the probability that any one particular bit changes is set to 1 is:
$$
1 \over m
$$

Chances of that bit not changing (still being 0 is):
$$
(1-{1\over{m}})^{}
$$
We have $n$ items, and $k$ hash function we call for each. So the chance of a particular bit still not changing, after some algebraic manipulation, becomes:
$$
\large
\begin{align}
& \Big(1-{1\over{m}}\Big)^{nk} = \Big((1-{1\over{m}})^{m}\Big)^{nk \over m}
\end{align}
$$
We can take the limit of this function to see what happens if we let $m$ increase without bounds: 
$$
\begin{align}
\Large  \lim_{ m \to \infty }{\Big((1-{1\over{m}})^{m}\Big)^{nk \over m}}
\approx e^{-nk \over m} && {\dagger}

\end{align}
$$
So, the *approximate* probability that a particular bit *is unchanged* (0) after we process all the DB rows is:
$$
\Large q=e^{-nk \over m}
$$
Therefore, the probability that a bit *is changed* (1) is (approximately):
$$
\Large 1-e^{-nk \over m}
$$
But we have $k$ hash functions. So the probability that $k$ elements in the bit array are 1 is:
$$
\Large p \approx (1-e^{-nk \over m})^k
$$




[^1]: Note: We can't really have an array with an infinite size because of memory constrictions. If we did, the limit above would be 1, which makes sense: in an infinite-sized array, the chances of a particular bit not changing is 100%. However, we don't need to go far to reach $1 \over e$ in the limit above. $(1-{1 \over m})^m$ is already equal to $1 \over e$ by two decimal places. That's why we say the limit is approximately equals to $e^{-nk \over m}$. The real question is, what values of $k$ and $m$ work best to keep the probability of a false positive as small as *possible*? Possible is a keyword here.
