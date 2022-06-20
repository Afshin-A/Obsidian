Let $P(x)$ be a polynomial of degree $n$ with a complex zero $Z$.
$\therefore P(Z)=0$
We will show that the conjugate of $Z$, $\overline{Z,}$ is also a zero of $P(x)$

###### The conjugate of the sum of any number of complex numbers (with arbitrary, real components) equals the conjugates of those numbers added together.

Suppose $A, B, C \ \dots \ D$ are complex numbers of the form $a+bi \text{ where } a,b \in R$.
$$
\begin{align}
A+B+C+ \dots +D &=(a+a_{i}i)+(b+b_{i}i)+(c+c_{i}i)+\dots+(d+d_{i}i)\\
&=(a+b+c+\dots+d)+(a_{i}+b_{i}+c_{i}+\dots+d_{i})i \\\\
\overline{(A+B+C+\dots+D)}&=(a+b+c+\dots+d)-(a_{i}+b_{i}+c_{i}+\dots+d_{i})i \\\\
\overline{A} + \overline{B} + \overline{C} + \dots \overline{D} &= (a-a_{i})+(b-b_{i})+(c-c_{i})+\dots(d-d_{i})\\
&= (a+b+c+\dots+d)-(a_i+b_i+c_i+\dots+d_i)i \\\\
\therefore \overline{(A+B+C+\dots+D)}&=\overline{A} + \overline{B} + \overline{C} + \dots \overline{D}
\end{align}
$$


###### The conjugate of the product of two complex numbers (with any arbitrary, real components) equals the conjugates of those two numbers multiplied together.
$$
\begin{align}
A\cdot B=(a+a_ii)(b+b_ii)&=ab+ab_ii+ba_ii+a_ib_ii^2 \\
&=ab+ab_ii+ba_ii-a_ib_i \\
&=(ab-a_ib_i)+(ab_i+ba_i)i \\
\end{align}
$$
Let $p=ab-a_ib_i$ and $q=ab_i+ba_i$. $p \text{ and } q$ are real numbers because their components are all real numbers. Therefore, $A\cdot B=p+qi$ is a complex number in the standard form. This will come handy as we extend this idea to more than 2 numbers.
$$
\begin{align}

\overline{(A\cdot B)} &= p-qi \\\\
\overline{A} \cdot \overline{B} = (a-a_ii)(b-b_ii)&=ab-ab_ii-ba_ii+a_ib_ii^2\\
&=ab-ab_ii-ba_ii-a_ib_i\\
&=(ab-a_ib_i)-(ab_i+ba_i)i\\
&=p-qi \\\\
\therefore \overline{(A\cdot B)} &= \overline{A} \cdot \overline{B}

\end{align}
$$
Now consider $\overline{(A\cdot B\cdot C)}$. Since we know $A\cdot B$ is another complex number, we let $D=A\cdot B$ and get $\overline{(D\cdot C)}$. As shown above, [[The conjugate of product of two complex numbers with any arbitrary real components equals the conjugates of those two numbers multiplied together]]. Thus, the proof stands for 3 complex numbers. We can repeat this reasoning for any number of complex numbers.

###### [[Conjugate of a Complex Zero is also a Zero in Polynomials]]
Proof:
$$\begin{align}
P(x)&=a_nx^n+a_{n-1}n^{n-1}+\dots+a_1x+a_0 \\
P\Big(\overline{Z}\Big)&=a_n\Big(\overline{Z}\Big)^n+a_{n-1}\Big(\overline{Z}\Big)^{n-1}+\dots+a_1\Big(\overline{Z}\Big)+a_0\\
&=a_n\overline{\Big({Z^n}\Big)}+a_{n-1}\overline{\Big(Z^{n-1}\Big)}+\dots+a_1\overline{\Big(Z\Big)}+a_0\\
&=\overline{\Big({a_nZ^n}\Big)}+\overline{\Big(a_{n-1}Z^{n-1}\Big)}+\dots+\overline{\Big(a_1Z\Big)}+a_0\\
&=\overline{\Big(
a_nZ^n+a_{n-1}Z^{n-1}+\dots+a_1Z+a_0\Big)}\\
&=\overline{P(Z)}=\overline{0}=0
\end{align}
$$

<center><b>Sources</b></center>
Stewart, J., Redlin, L., Watson, S., & Panman, P. (2017). _Precalculus: Mathematics for calculus_. Cengage Learning.