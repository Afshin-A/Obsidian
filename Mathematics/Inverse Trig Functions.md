Trigonometric functions are periodic and not one-to-one over their entire domain. Thus, in order to define an inverse function, we must restrict the original graphs over a range in which they are one-to-one, and all y values are represented.

$f(a)=b$ and $f(a)=c \implies f$ is not a function. For a function $f(x)$ to have an inverse, it must be **one-to-one**: each $x$ value is mapped to a unique $y$ value. If a particular $y$ value was linked to multiple $x$ values, $f^{-1}(y)$ would have multiple $x$ values and $f^{-1}$ would not be a function.

#### $sin^{-1}(x)$

#### $cos^{-1}(x)$

#### $tan^{-1}(x)$

#### $cot^{-1}(x)$

#### $sec^{-1}(x)$

#### $csc^{-1}(x)$


#### Warning when evaluating functions like $sin\Big(sin^{-1}(x)\Big)$
$cos\Big(cos^{-1}(x)\Big)$ isn't always just equal to $x. \quad cos\Big(cos^{-1}(5)\Big)$ for example is not defined, because the domain of $f(x)=cos^{-1}(x)$ is $[-1, \ 1]$
Similarly, $sin^{-1}\Big(sin(\pi)\Big)$ cannot be equal to $\pi$ because the range of $g(x)=sin^{-1}(x)$ is $[- {\pi \over 2}, \ {\pi \over 2}]$. Instead, we have,
$$
sin^{-1}\Big(sin(\pi)\Big)=sin^{-1}(0)=0
$$
As another example, consider that $cos^{-1}\Big(cos({7\pi \over 6})\Big)$ cannot simply be equal to ${7\pi \over 6}$ because the range of $cos^{-1}(x)$ is $[0,\ \pi]$. Instead,
$$
cos^{-1}\Big(cos({7\pi \over 6})\Big) = cos^{-1}({- \sqrt{3} \over 2})={5 \pi \over 6}
$$
$tan^{-1}\Big(tan({2 \pi \over 3})\Big)$ is not ${2 \pi \over 3}$ because the range of $tan^{-1}(x)$ is $[- {\pi \over 2}, \ {\pi \over 2}]$. Therefore,
$$
\begin{align}
tan^{-1}\Big(tan({2 \pi \over 3})\Big)
&=tan^{-1}\Big({{\sqrt{3} \over 2} \over {-1 \over 2}}\Big) \\
&=tan^{-1}\Big(-{{\sqrt{3} \over 2} \over {1 \over 2}}\Big) \\
&=-tan^{-1}\Big({{\sqrt{3} \over 2} \over {1 \over 2}}\Big) &&\text{Because $arctan(x)$ is an odd function} \\
&=-{\pi \over 3}
\end{align}
$$