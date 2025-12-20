# Permutations
$$
P(n,r)=\frac{n!}{(n-r)!}
$$
Suppose we have 3 seats available and there are 6 people.
For seat 1, there are 6 possible choices. 
For seat 2, we have to make a choice out of the remaining 5 people. Thus, there are 5 choices.
Similarly, for seat 3, there are 4 possible choices. 
The total number of possibilities is:
$$
6 \times 5 \times 4
$$
This can be written as a quotient of factorials:
$$\begin{align}
\frac{6 \times 5 \times 4 \cancel{\times 3 \times 2 \times 1}}{\cancel{\times 3 \times 2 \times 1}} \\
\frac{6!}{(6-3)!}
\end{align}
$$

# Combinations
Order matters in permutations. 

What if we didn't care about the order? 
In that case, 3 people sitting in any order would count as 1 

$A, B, C$ is the same as $B, C, A$, $A, C, B$, and so on
How many ways can we arrange 3 people? That would be $3!$
So we need to shrink down the total number of permutations by a factor of $3!$

$$
C(n,r)=\frac{n!}{(n-r)! \ r!}
$$
