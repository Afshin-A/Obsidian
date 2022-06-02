$$ \begin{align}
\text{Consider} \ P(x)=a_nx^n+a_{n-1}x^{n-1}+ \dots + a_1x+a_0= \\
\text{where} \ a_n, a_{n-1}, a_{n-2}, \dots a_1, a_0 \in z \ \text{and} \ a_n \neq 0 \\ \\
\text{suppose } {p\over q} \ \text{is rational and irreducible} \implies (p, q \in z)\\
P({p\over q})=a_n({p\over q})^n+a_{n-1}({p\over q})^{n-1}+ \dots + a_1({p\over q})+a_0=0 \\
a_n({p\over q})^n+a_{n-1}({p\over q})^{n-1}+ \dots + a_1({p\over q})=-a_0 \\
q^n\Big(a_n({p\over q})^n+a_{n-1}({p\over q})^{n-1}+ \dots + a_1({p\over q})=-a_0\Big) \\
a_np^n+a_{n-1}p^{n-1}q+\dots + a_1pq^{n-1}=-a_0q^n \\
p\Big(a_np^{n-1}+a_{n-1}p^{n-2}q+\dots +a_1q^{n-1} \Big)=-a_0q^n
\end{align}
$$
Since $p$ is a factor of the left hand side, it must also be a factor of the right hand side. $p$ is not a factor of $q^n$ because, per conditions stated above, ${p \over q}$ is irreducible, meaning $p$ and $q$ have no factors in common. Thus, $p$ must be a factor of $a_0$

Next, we will show that $q$ is a factor of $a_n$
$$
\begin{align}
q^n\Big(a_n({p\over q})^n+a_{n-1}({p\over q})^{n-1}+ \dots + a_1({p\over q})+a_0=0\Big) \\
a_{n-1}p^{n-1}q+\dots + a_1pq^{n-1}+a_0q^n=-a_np^n \\
q\Big(a_{n-1}p^{n-1}+\dots + a_1pq^{n-2}+a_0q^{n-1}\Big)=-a_np^n \\
\end{align}
$$
Since $q$ is not a factor of $p^n$, it must be a factor of $a_n$.

$\therefore$ Any ***rational*** zero of a polynomial will be of the form ${p \over q}$ where $p$ is a factor of $a_0$ and $q$ a factor of $a_n$

If a polynomial has no zeros of such, it will still have either ***irrational*** or imaginary zeros.

Example:
$P(x)=x^4-3x^3+x^2-3x+3$ has 2 irrational and 2 imaginary zeros. Neither of $(x\pm1), (x\pm3)$ factor $P(x)$ but its graph shows it has 2 positive zeros.