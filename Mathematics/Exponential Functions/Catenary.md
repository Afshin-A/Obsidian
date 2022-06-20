The shape of a rope or string when you hold on to it by each end. It is the most stable and "optimal \[shape\] for distributing the internal structural forces of the
arch" (p338).

The catenary is not a prabola:
$$
y=a(e^{bx}+e^{-bx})
$$

$e$ is a rational number and is defined as follows:
$$
\lim_\limits{n \to \infty}(1+{1 \over n})^n=e \approx 2.718
$$

#### Making Sense of the Compount Interest Formula
$$
P(1+r) \to [P(1+r)](1+r) \to \dots \to P(1+r)^t
$$
We start with an initial amount $P$. After each time cycle we are awarded $r\%$ of the total amount.
After 1 cycle, we have $P+Pr=P(1+r)$. After 2 cycles, we have $[P(1+r)](1+r)=P(1+r)^2$. Thus, after $t$ cycles, our total amount is $P(1+r)^t$.

#### Continous Interest
Let $m={n \over r}$. As $n \to \infty, m \to \infty$
$$
\begin{align}
\lim_\limits{n \to \infty} P(1+{r \over n})^{nt}&=\lim_\limits{n \to \infty} P\Big(\big((1+ {1 \over m}\big)^{n \over r}\Big)^{rt} \\ 
&=\lim_\limits{m \to \infty}P\Big(\big((1+ {1 \over m}\big)^{m}\Big)^{rt} \\
&=Pe^{rt}
\end{align}
$$
Continous Interest can also be used to model continous population growth. Continous interest says that if you start with $P$ dollars and continously let it grow by $r\%$, then we get $Pe^{rt}$ dollars at time $t$. The same analogy can be applied to population: if you start with population $P$ and continously let it grow by $r\%$, then we get $Pe^{rt}$ pop at time $t$.


##### How do we compare the graphs of $y=ln(x)$ and $y=\sqrt{x}$ ?
We can graph and compare their inverses: $e^x$ and $x^2$. $e^x$ raises much more quickly than $x^2$. When we rotate both functions across the line $y=x$ (because [[Inverse Functions of a Function is its Reflection Over y=x]]) we'll see that $ln(x)$ raises rapidly, but with respect to the x-axis, not y-axis. 

##### Estimating a solution
Find two integers in between which the solution to $9^x=100$  exists.
$9^2<100$ and $9^3 > 100$ so $2<x<3$. Easy peasy.

##### Continous decay formula
Suppose a population $P$ is reduced by a certain percentage  $r$ each year.

Initially, $P=P_0$
After 1 year, $P_1=P_0-P_0r=P_0(1-r)$
After 2 years, $P_2=P_1-P_1r=P_1(1-r)=P_0(1-r)(1-r)=P_0(1-r)^2$
After 3 years, $P_3=P_2-P_2r=P_2(1-r)=P_0(1-r)^2(1-r)=P_0(1-r)^3$
After t years, $P_t=P_0(1-r)^t$

Let's assume that in each year, pop is reduced n times.
$P_t=P_0(1-{r \over n})^{nt}$
What happens if $n \to \infty$ and we do $\infty$ iterations each year?
$$ 
\begin{align}
\lim_\limits{n \to \infty} \Big(P_0(1-{r \over n})^{nt}\Big) =\\
P_0\lim_\limits{n \to \infty} \Big((1-{1 \over m})^{{n \over r}rt}\Big) =\\
P_0\lim_\limits{n \to \infty} \Big((1-{1 \over m})^{m \ rt}\Big) =\\
P_0\lim_\limits{m \to \infty} \Big((1-{1 \over m})^{m}\Big)^{rt}\Big) =\\
P_0\lim_\limits{m \to \infty} \Big(e^{-1}\Big)^{rt} =
P_0e^{-rt}
\end{align}
$$

Let $y={1 \over n}$. As $n \to \infty, \ y \to 0$: 
$$
\begin{align}
\lim_\limits{n \to \infty} (1+{1 \over n})^n &= 
\lim_\limits{y \to 0} (1+y)^{1 \over y} = e && \text{}\\
\lim_\limits{n \to 0} (1+n)^{1 \over n} &= e && \text{Because y is a dummy variable}
\end{align}
$$

Next we evaluate the following:

$$
\begin{align}
\lim_\limits{n \to \infty}(1-{1 \over n})^n & = \lim_\limits{n \to \infty}\Big(1+({-1 \over n})\Big)^n && \text{Let $y={-1 \over n}$} \\
& = \lim_\limits{y \to 0}(1+y)^{-1/y} \\
& = \lim_\limits{y \to 0}\Big((1+y)^{1/y}\Big)^{-1} \\
& = \Big(\lim_\limits{y \to 0}(1+y)^{1/y} \Big)^{-1} && \text{Proof (sorta) below}\\
& = e^{-1}
\end{align}
$$

$$
\lim_\limits{x \to a} {f(x)}^b=\big(f(a)\big)^b=\big(\lim_\limits{x \to a} {f(x)}\big)^b
$$