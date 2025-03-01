Lets us approximate a function $P$ around $x=0$ by rewriting it as a polynomial.
$$\begin{align}
P_{n}(x)\approx f(0)+f^{'}(0)x+ \frac{1}{2}f^{''}(0)x^2+\frac{1}{6}f^{'''}(0)x^3+ \cdots + \frac{1}{n!}f^{n}(0)x^n \\
P(x)=\sum^{\infty}_{n=0}{\frac{f^n(0)x^n}{n!}}
\end{align}
$$
# Taylor Series
Approximating the function $P$ at an arbitrary $x=c$
$$\begin{align}
P(x)\approx f(c)+f^{'}(c)(x-c)+ \frac{1}{2}f^{''}(c)(x-c)^2+\frac{1}{6}f^{'''}(c)(x-c)^3+ \cdots \\
P(x)=\sum^{\infty}_{n=c}{\frac{f^n(c)(x-c)^n}{n!}}
\end{align}
$$
We replace $x$ with $x-c$ to account for the shift. It's like shifting your function $c$ units to the right. This way, when we plug in $c$ for $x$ in $P(x)$, we get the correct outcome.


# Taylor Polynomial Remainder
This helps determine how accurate our approximation of a polynomial using a Taylor series is.
At a point $x$, how accurate is our approximation? 
The remainder, or the error, of $n$th degree approximation of a polynomial at $x=a$ is defined as:
$$\begin{align}
R_{N,a}(x) = E_{N,a}(x)=\lvert f(x)-{P}_{N,a}(x)\rvert \\\\\\
E=f(a)-P(a)=0\\
E'=f'(a)-P'(a)=0\\
\dots \\
E^n=f^n(a)-P^n(a)=0
\end{align}
$$
This makes sense because it comes from the definition of the Taylor series. We're purposefully designing each term of the polynomial so when we take its derivative, the derivative equals that of the function we're approximating. ~~In fact, we're approximating the original function by ensuring that at $x=a$, the derivative coefficients in the polynomial are the same.~~ So if we take the first derivative of both $f(x)$ and $P(x)$, they'll be equal at $x=a$. If we take the second derivative, we get the same outcome. And so on for as many times as we can take the derivatives.

Note that $P(x)$ is a polynomial. Therefore, $P^{n+1}(x)$ is 0. Therefore,
$$
E^{n+1}(x)=f^{n+1}(x)
$$


Note
$$
\int_a^bf(x)\ dx\leq {\left|{\int_a^bf(x)\ dx}\right|} \leq \int_a^b\left| f(x) \right| \ dx
$$
If $f(x) \leq 0$ in $[a,b]$ then the area under the curve for both $f(x)$ and $|f(x)|$ is equal. But if $f(x) < 0$ for some regions, value of $\int_a^b{f(x)dx}$ also becomes negative in those regions, and subtracts from the areas where $f(x) > 0$, making the overall definite integral greater. 

Suppose there exists $M$ such that
$$\begin{align}
&\left|E^{n+1}(x)\right|=\left|f^{n+1}(x)\right| \leq M && x \in [a,\ b]\\
\end{align}
$$
This means $M$ is an upper bound to the margin of error. Then,
$$\begin{align}
\left|\int{E^{n+1}(x)\ dx}\right| \leq \int{\left|E^{n+1}(x)\right| \ dx} \leq \int{Mdx} \\
\left|\int{E^{n+1}(x)\ dx}\right| \leq \int{Mdx} \\
\left|E^{n}(x)\right| \leq Mx+C
\end{align}
$$
To minimize the margin of error, we want to minimize $C$. The smallest error is 0 at $x=a$
$$\begin{align}
\left|E^{n}(a)\right|=0 \leq Ma+C \\
-Ma \leq C
\end{align}
$$
So the smallest possible value for $C$ is $-Ma$

$$\begin{align}
\left|E^{n}(x)\right| \leq Mx-Ma = M(x-a)\\
\int{\left|E^{n}(x)\right|\ dx} \leq \int{M(x-a)}\ dx\\
\left|\int{E^{n}(x)\ dx}\right| \leq \int{M(x-a) \ dx} \\
\left|E^{n-1}(x)\right| \leq \frac{M(x-a)^2}{2}+C \\
\\
\left|E^{n-1}(a)\right|=0\leq \cancel{\frac{M(a-a)^2}{2}}+C=C \\
0 \leq C
\\ \\ 
\therefore \left|E^{n-1}(x)\right| &\leq \frac{M(x-a)^2}{2} \\
&\vdots \\
\left|E^{0}(x)\right|=\left|E(x)\right| &\leq \frac{M(x-a)^{n+1}}{(n+1)!} \\ \\ \\
\boxed{
\left|E(x)\right| \leq \frac{M(x-a)^{n+1}}{(n+1)!}
}
\end{align}
$$
Recall that $M$ is the upper bound to our margin of error. If we are given $M$, we can say with certainty that the error at some arbitrary point $b$ is 
$$
\begin{align}
\boxed{
\left|E(b)\right| \leq \frac{M(b-a)^{n+1}}{(n+1)!}
}
\end{align}
$$
We can also deduce $M$ if we can make sure $f(x)$ (the function we're approximating) is bound in some interval that includes $a$ and $b$.
With The Taylor remainder theorem, we are given a margin of error and produce a polynomial approximation. We can basically determine how many terms in our polynomial is enough.


# Power Series
The concept of a power series is similar to geometric series. In fact, geometric series is a special case of power series
$$
f(x)=\sum^{\infty}_{n=0}{a_n(x-c)^n}=a_0+a_1(x-c)+a_2(x-c)^2+\dots
$$

## Interval of Convergence
$$
g(x)=\sum_{n=0}^{\infty}{ax^n}=ax^0+ax^1+ax^2+\dots
$$
$g(x)$ converges to $\frac{a}{1-x}$ for $x \in [-1, \ 1]$. This is called the interval of convergence.


# Taylor Series and Power Series
A Taylor series representation of a function is basically a power series.
$$\begin{align}
&P_c(x)= f(c)+f^{'}(c)(x-c)+ \frac{1}{2}f^{''}(c)(x-c)^2+\frac{1}{6}f^{'''}(c)(x-c)^3+ \cdots \\
&P(x)=\sum_{n=0}^{\infty}{a_n(x-c)^n} \quad \text{where} \ a_n=f^n(c)
\end{align}
$$

### Example 1
Write $f(x)$ as a power series.
$$\begin{align}
f(x)=2-8x^2+32x^4-128x^6+\dots \\
f(x)=\sum_{n=0}^{\infty}{2(-4x^2)^n} = \frac{2}{1+4x^2}\\ \\
\text{common ratio, }r=-4x^2 \\
\left|-4x^2\right| < 1 \implies \text{converges} \\ \\
4x^2 < 1 \\
\text{radiance of convergence: }[\frac{-1}{2}, \ \frac{1}{2}]
\end{align}
$$

### Example 2
$$
f(x)=\frac{6}{1+x^3}=\sum_{n=0}^{\infty}{6(-x^3)^n}=6-6x^3+6x^6+\dots
$$

### Example 3
$$\begin{align}
f(x)=\arctan(2x) \\
\frac{df}{dx}=\frac{2}{1+4x^2} \\
g(x)=\frac{1}{1+x}=(1+x)^{-1}\\
g'(x)=-(1+x)^{-2}\\
g''(x)=2(1+x)^{-3} \\
g'''(x)=-6(1+x)^{-4} \\ \\
g(x) \approx g(0)+g'(0)x+\frac{g''(0)}{2}x^2+\frac{g''(0)}{6}x^3 + \dots \\
\approx 1-x+x^2-x^3+x^4 -\dots \\
\\
f'(x)=2g(4x^2) \approx 2\Big(1-(4x^2)+(4x^2)^2-(4x^2)^3+(4x^2)^4 -\dots \Big)\\
\approx 2-8x^2+32x^4-128x^6+ \dots \\
\arctan(2x) = \int{\big(2-8x^2+32x^4-128x^6+ \dots}\big)\ dx \\
=C+2x-\frac{8}{3}x^3+\frac{32}{5}x^5-\frac{128}{7}x^7 +\dots\\
\arctan(0)=0 \to C=0\\ 

\boxed{\arctan(2x) = 2x-\frac{8}{3}x^3+\frac{32}{5}x^5-\frac{128}{7}x^7+\dots}
\end{align}
$$


# Euler's Identity
## Power Series Representation of $\cos(x)$
| $f(x)$    | $\cos(x)$  | eval at $x=0 \to 1$ |
| --------- | ---------- | ------------------- |
| $f'(x)$   | $-\sin(x)$ | 0                   |
| $f''(x)$  | $-\cos(x)$ | -1                  |
| $f'''(x)$ | $\sin(x)$  | 0                   |
| $f^4(x)$  | $\cos(x)$  | 1                   |
$$
\cos(x) \approx 1 - \frac{x^2}{2!}+\frac{x^4}{4!}-\frac{x^6}{6!}+\dots
$$
## Power Series Representation of $\sin(x)$

| $f(x)$    | $\sin(x)$  | eval at $x=0 \to 0$ |
| --------- | ---------- | ------------------- |
| $f'(x)$   | $\cos(x)$  | 1                   |
| $f''(x)$  | $-\sin(x)$ | 0                   |
| $f'''(x)$ | $-\cos(x)$ | -1                  |
| $f^4(x)$  | $\sin(x)$  | 0                   |

$$
\sin(x) \approx x-\frac{x^3}{3!}+\frac{x^5}{5!}-\frac{x^7}{7!}\dots
$$
## Power Series Representation of $e^x$
| $f(x)$  | $e^x$ | eval at $x=0 \to 1$ |     |
| ------- | ----- | ------------------- | --- |
| $f'(x)$ | $e^x$ | 1                   |     |
$$
e^x\approx 1+x+\frac{x^2}{2!}+\frac{x^3}{3!}+\frac{x^4}{4!}+\dots
$$
# Euler's Identity
$$
\cos(x)+\sin(x)=1+x-\frac{x^2}{2!}-\frac{x^3}{3!}+\frac{x^4}{4!}+\frac{x^5}{5!}\dots
$$
$$
\begin{align}
i^1=i \\
i^2=-1 \\
i^3=-i \\
i^4=1 \\
i^5=i\\
i^6=-1\\
i^7=-i
\end{align}
$$
$$
e^{ix}\approx 1+ix-\frac{x^2}{2!}-i\frac{x^3}{3!}+\frac{x^4}{4!}+i\frac{x^5}{5!}-\frac{x^6}{6!}-i\frac{x^7}{7!}+\dots
$$
All odd powers of $x$ are now preceded by $i$. These are from the Maclaurin representation of $\sin(x)$. 

$$
\boxed{
e^{ix}=\cos(x)+i\sin(x)
}
$$
Let $x=\pi$
$$\begin{align}
e^{i\pi}=\cos(\pi)+i\sin(\pi) \\
e^{i\pi}=-1 \\
\boxed{e^{i\pi}+1=0}
\end{align}
$$
