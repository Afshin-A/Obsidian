# Finite Geometric Sum
$$\begin{align}
S_n&=\sum_{k=0}^{n}{ar^k}=ar^0+ar^1+ar^2+\dots+ar^n \\
rS_n&=ar^1+ar^2+\dots+ar^n+ar^{n+1} \\\\
rS_n-S_n&=ar^{n+1}-ar^0 \\ \\
S_n&=\frac{ar^{n+1}-a}{r-1} \\
&= \frac{a-ar^{n+1}}{1-r} \\\\
&\boxed{S_n=\frac{a-ar^{n+1}}{1-r}}
\end{align}
$$
# Infinite Geometric Sum
Assuming $\lvert r \rvert < 1$, the following limit converges.

$$\begin{align}
\lim_{n \to \infty}{S_n}=\lim_{n \to \infty}{\frac{a-ar^{n+1}}{1-r}}=\frac{a}{1-r}
\end{align}
$$
Else if $\lvert r \rvert \geq 1$ the limit will diverge.


# Arithmetic geometric series
$$
\begin{align}
S(r)=\sum^{m}_{h=0}r^h =\frac{r^{m+1}-1}{r-1}\\
\frac{d}{dr}\left[S(r)\right]
=\frac{d}{dr}\left[\sum^{m}_{h=0}r^h \right] = \frac{d}{dr} \left[ \frac{r^{m+1}-1}{r-1} \right]\\

rS'(r)=\sum^{m}_{h=0}{hr^{h}}=r\frac{(r-1)(m+1)r^m-(r^{m+1}-1)}{(r-1)^2} \\ \\
=r(mr^{m+1}+\cancel{r^{m+1}}-mr^m-r^m\cancel{-r^{m+1}}+1) \\ 
=r(mr^{m+1}-(m+1)r^m+1) \\ \\

\boxed{\sum^{m}_{h=0}{hr^{h}}=r(mr^{m+1}-(m+1)r^m+1)}
\end{align}
$$

## Example used in time complexity of building max heap

$$
\begin{align}
\sum^{\log_{2}n}_{h=0}{h2^{h}}&=2\Big((\log_{2}n)(2^{\log_{2}n+1})-(\log_{2}n+1)(2^{\log_{2}n})+1\Big) \\
&=4n\log_{2}n-2n\log_{2}n-2n+2 \\
&=2n\log_{2}n-2n+2
\end{align}
$$