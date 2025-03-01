$$\begin{align}
\text{Let} \ b_n=(-1)^n \ a_n \\
\sum_{n=k}^{\infty}{b_n}
\end{align}
$$
This test applies to series with alternating signs
If 
- $\lim_{n\to \infty}{b_n}=0$
- $b_n$ is non-increasing (monotonic)
Then the sum converges. If these criteria are not met, it does not mean divergence.


# Approximating Alternating Sums
Assuming an alternating sum converges using the test above, we can approximate the sum as follows:

$$
\begin{align}
S=\sum^{\infty}_{n=1}{\frac{(-1)^{n+1}}{n^2}}
=&\underbrace{
	1-\frac{1}{4}+\frac{1}{9}-\frac{1}{16}
}_{S_4}+
\underbrace{
	(\overbrace{\frac{1}{25}-\frac{1}{36}}^{+})+(\overbrace{\frac{1}{49}-\frac{1}{64}}^{+})\dots
}_{R_4} 
\\
R_4 &= \frac{1}{25}-\frac{1}{36}+\frac{1}{49}-\frac{1}{64}+\frac{1}{81}\dots \\
&=\frac{1}{25}-(\overbrace{\frac{1}{36}-\frac{1}{49}}^{+})-(\overbrace{\frac{1}{64}-\frac{1}{81}}^{+})\cdots
\\
\\
&(R_4 > 0) \ \wedge \ (R_4 < \frac{1}{25}) 
\\
\\
S &= S_4 + R_4 < S_4 + \frac{1}{25} \\
S &< S_4 + \frac{1}{25} \\
S &> S_4 \\
&\boxed{S_4 < S < S_4 + \frac{1}{25}} \\
\end{align}
$$

In general,
$$
S_k < S < S_k + S_{k+1} 
$$
where $S_k$ is the $k^{th}$ partial sum of S. As $k\to \infty$, the approximation becomes more and more accurate.

