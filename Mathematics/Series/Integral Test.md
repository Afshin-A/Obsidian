A infinite sum can be used to approximate an integral. 
$$\begin{align}
&\int_{n}^{\infty}{f(x)dx} \ \approx\ \sum_{k=n}^{\infty}{f(k)}\\
& \\
\end{align}
$$
So, if the integral diverges, the sum also diverges.
If the integral converges, the sum also converges.


# p-Series
##  $p > 1$
$$\begin{align}
\sum_{x=1}^{\infty}{\frac{1}{x^p}} \ \approx\  &\int_{1}^{\infty}{\frac{1}{x^p}dx} = \lim_{a\to\infty}{\Big(\frac{a^{1-p}}{1-p}-{\frac{1^{1-p}}{1-p}}\Big)}=-{\frac{1}{1-p}}={\frac{1}{p-1}}\\
\end{align}
$$
$\boxed{ \therefore \text{ The series \textbf{converges} for } p > 1}$

## The Harmonic Series, $p=1$
$$\begin{align}
\sum_{x=1}^{\infty}{\frac{1}{x}} \ \approx\  &\int_{1}^{\infty}{\frac{1}{x}dx} = \lim_{a\to\infty}{\Big(\ln(a)-ln(1)\Big)}=\infty\\
\end{align}
$$
$\boxed{ \therefore \text{ The series \textbf{diverges} for } p=1}$

## $0<p<1$
$$\begin{align}
\sum_{x=1}^{\infty}{\frac{1}{x^p}} \ \approx\  &\int_{1}^{\infty}{\frac{1}{x^p}dx} = \lim_{a\to\infty}{\Big(\frac{a^{1-p}}{1-p}-{\frac{1^{1-p}}{1-p}}\Big)}=\lim_{a\to\infty}\Big(\frac{a^{1-p}}{1-p}\Big)=\infty\\
\end{align}
$$
$\boxed{ \therefore \text{ The series \textbf{diverges} for } 0<p<1}$

## $p\leq 0$
Let $p=-k$, such that $k>0$
$$\begin{align}
\sum_{x=1}^{\infty}{\frac{1}{x^{p}}}=\sum_{x=1}^{\infty}{\frac{1}{x^{-k}}}=\sum_{x=1}^{\infty}{x^k}=\infty
\end{align}
$$
$\boxed{ \therefore \text{ The series \textbf{diverges} for } p\leq 0}$
