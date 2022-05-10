#FactoringPolynomials 
 
### Remainder Theorem
Let $f(x)$ and $D(x)$ be polynomials where the degree of $f(x)$ > the degree of $g(x)$. $f(x)\over D(x)$ is found by long division to be $${f(x)\over D(x)} = Q(x) + {R(x) \over D(x)}$$
$F(x)$ is the dividend.
$D(x)$ is the divisor.
$Q(x)$ is the quotient.
$R(x)$ is the remaiander.

Alternately, $$f(x)=Q(x)D(x)+R(x)$$
Let $D(x)$ be a **1st degree** polynomial such that $D(x)= x-c \quad \text{where } c\in z$. Since the remainder will always be at ;east one degree less than the divisor, $R(x)$ must be a constant. Therefore, we denote $R(x)$ as $r$.
$$f(x)=Q(x)(x-c)+r$$
$$\begin{align} f(c) & = Q(c)(c-c)+r=r \\
f(c) & = r
\end{align}
$$

### Factor Theorem
$(x-c)$ is a factor of $f(x)$ $\iff$ $x=c$ is a zero of $f(x)$.

**Proof**
$(x-c)$ is a perfect factor of $f(x)$ if the remainder of $f(x)\over(x-c)$ is $0$. Therefore, $f(x)=(x-c)Q(x)+0 \to f(c)=(c-c)\cdot Q(x)=0$

#### Applications
![[Pasted image 20220502200832.png]]

A.
We use the #RemainderTheorem.
$f(x)=6x^{1000}-17x^{562}+12x+26=Q(x)(x+1)+r$
$$\begin{align}
f(-1) &= Q(x)(-1+1)+r \\ &=r \\
f(-1) & = 6(-1)^{1000}-17(-1)^{562}+12(-1)+26 \\ & = 6-17-12+26=3 \\
 &\therefore r = 3
\end{align}
$$
Notice how the quotient is not even needed to find the remainder.

B.
We use both the remainder and factor theorems. If $x-1$ is a factor of $g(x)=x^{567}-3x^{400}+x^9+2$, then the remainder of $g(x)\over {x-1}$ , $r$, is $0$.
$$\begin{align}
r=g(1)=1-3+1+2=0 \\
\therefore (x-1) \ \text{is a factor of} \ g(x)
\end{align}
$$
