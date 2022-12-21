Multiplying factors of a second degree polynomial derived by the quadratic equation doesn't always produce the original polynomail, especially if the coefficient of the $x^2$ term is not $1$.
Allow me to demonstrate:
$$ \begin{align}
f(x)=6x^2-x-1 \\
x={{-b \pm \sqrt{b^2-4ac}} \over 2a} \\
={{1 \pm \sqrt{1+(4)(1)(6)}} \over 12} \\
={{1 \pm 5} \over 12} \\
x={1 \over 2}, \quad x={-1 \over 3} \\
\text{Let } g(x)=(x-{1 \over 2})(x+{1 \over 3}) \\
g(x) \neq f(x)
\end{align}
$$
$f(x)$ and $g(x)$ both share the same zeros.
In general, $f(x) = a \cdot g(x)$
This is because in deriving the quadratic equation, the first step is to factor out the coefficient $a$:
$$
\begin{align}
f(x)=ax^2+bx+c=0 \\
({1 \over a})(x^2+{b\over a} x+{c \over a})=0 \\
x^2+{b\over a} x+{c \over a}=0 \\
x^2+{b\over a} x+({b \over 2a})^2-({b \over 2a})^2+{c \over a} \\
(x+{b \over 2a})^2={b^2-4ac \over 4a} \\
x={-b \over 2a}\pm\sqrt{{b^2-4ac \over 4a} \\} \\
x={-b \pm\sqrt{b^2-4ac} \over 2a} \\
\therefore \Big(x-({-b + \sqrt{b^2-4ac} \over 2a})\Big)\Big(x+({-b + \sqrt{b^2-4ac} \over 2a})\Big)=({1 \over a})(x^2+{b\over a} x+{c \over a}) = ({1 \over a})f(x)\\
\therefore a\Big(x-({-b + \sqrt{b^2-4ac} \over 2a})\Big)\Big(x-({-b - \sqrt{b^2-4ac} \over 2a})\Big) = f(x)
\end{align}
$$