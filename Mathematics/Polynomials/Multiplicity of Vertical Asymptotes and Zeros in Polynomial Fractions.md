Multiplicity helps us determine if graph of $f(x)$ changes sign at a zero, or around a vertical asymptote.
Consider
$$
f(x)={x^3-x^2 \over x^3-3x-2} = {x^2(x-1) \over x^3-3x-2}
$$
##### Factoring $x^3-3x-2$:
Possible zeros: $\pm1, \pm2$
$1$ sign variation in $f(x) \implies 1$ positive zero
$f(-x)=-x^3+3x-2 \implies 2$ or $0$ negative zeros
$$
\begin{array}{c|rrr}&1&0&-3&-2\\x-1 &1&-1&-1&2\\\hline\\&1&1&-2&\neq0\\
\end{array}
$$
$$
\begin{array}{c|rrr}&1&0&-3&-2\\x-2 &1&-2&-4&-2\\\hline\\&1&2&1&0\\
\end{array}
$$
$x^3-3x-2=(x-2)(x^2+2x+1)=(x-2)(x+1)^2$

$$
f(x)={x^2(x-1) \over (x-2)(x+1)^2}
$$
##### Characteristics of $f(x)$:
x-intercepts: $x=0$ even multiplicity; $x=1$ odd multiplicity
y-intercept: $f(0)=0$
Vertical asymptote: $x=2$ odd multiplicity; $x=-1$ even multiplicity
Horizontal asymptote: $\lim\limits_{x \to \infty}f(x)=\lim\limits_{x \to -\infty}f(x)=1$

![[Pasted image 20220519190256.png]]

##### Graphing $f(x)$ with ease
We start graphing by following the horizontal asymptote from right to left. 
You can easily tell $\lim\limits_{x \to 2^{-}}f(x)=\infty$ because there are only 3 zeros at $x=1$ (with multiplicity = 2) and $x=0$. If the limit was $-\infty,\ f(x)$ would have to pass the $x-$axis; that would mean there is an additional zeros.
The rest of the puzzle just falls into place after that.
$\lim\limits_{x \to 2^{+}}f(x)=-\infty$ because the multiplicity of $(x-2)$
in the denominator of $f(x)$ is odd: if $(x-2)$ is positive on the right side of $2$, then $(x-2)$ must be negative on the left side of $2$. A negative number raised to an odd power is negative.
Next we get to the zero at $x=1$. Since its multiplicity is odd, it passes the x-axis. 
The next zero is at $x=0$ with an even multiplicity, so $f(x)$ doesn't pass the x-axis. Next we reach the other vertical asymptote at $x=-1$. There are no more zeros, so $f(x)$ has no place but to go up. The multiplicity of $(x+2)$ in the denominator of $f(x)$ is even, so the $f(x)$ must also go up on the left of the asymptote. 
Finally, we follow the horizontal asymptote as found in [[Multiplicity of Vertical Asymptotes and Zeros in Polynomial Fractions#Characteristics of f x]]