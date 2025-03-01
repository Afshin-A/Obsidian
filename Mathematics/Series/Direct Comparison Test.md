Suppose:
- We have two series $S_n$ and $T_n$ such that all terms are larger than 0 (in other words, terms do not oscillate with respect to the x-axis). Note that, if necessary, we can customize the lower limit so that this condition becomes true.
- $S_n > T_n$ for all $n$
- $S_n$ and $T_n$ follow a similar pattern
Then,
If $S_n$ converges, $T_n$ also converges
If $T_n$ diverges, $S_n$ also diverges


Example:
$$\begin{align}
S_n&=\sum^{\infty}_{n=1}{\frac{1}{2^n+n}} \\
T_n&=\sum^{\infty}_{n=1}{\frac{1}{2^n}}=\sum^{\infty}_{n=1}{(\frac{1}{2})^n} \implies \text{geometric series converges} \\ \\
&T_n, \ S_n > 0 \ \wedge \ T_n > S_n \ \text{for all } n \\ \\
&\therefore \ S_n \ \text{converges}
\end{align}
$$

**Note:** Just because a series is larger and it converges, it doesn't mean any series that's smaller will also converge. No, the two series must follow a similar pattern. 
