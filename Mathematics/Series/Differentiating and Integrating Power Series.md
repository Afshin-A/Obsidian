Supposes two power series have an integrand and anti-derivative relationship (or if one is a derivative of the other). If we know the function form of one, then we can find the other function as well. For example:
$$
\begin{align}
f(x)=-2-4x-8x^2-16x^3-\dots= \\
f(x)=-2\sum_{n=0}^{\infty}{(2x)^n}=\frac{-2}{1-2x} \\
f(x) \ \text{converges if} \ 1<\left|2x\right| \implies x \in (\frac{-1}{2}, \ \frac{1}{2})
\end{align}
$$
$$\begin{align}
g(x)=-2x-2x^2-\frac{8}{3}x^3-4x^4-\dots \\
\int{f(x) \ dx}=\int{\big(-2-4x-8x^2-16x^3-\dots\big)\ dx} \\
=C-2x-2x^2-\frac{8}{3}x^3-4x^4-\dots \\
g(x)+C \\\\
g(0)=0 \implies C=0\\
g(x)=\int{f(x)\ dx}=\int{\frac{-2}{1-2x}dx}=\int{\frac{du}{u}}=\ln(|u|)=\ln(|1-2x|) \\
\boxed{g(x)=\ln(|1-2x|)}
\end{align}
$$
