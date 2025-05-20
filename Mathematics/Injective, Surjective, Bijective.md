Suppose we have a $f$ such that $f: \symbb{Z}/_{n\symbb{Z}} \to \symbb{Z}/_{n\symbb{Z}}$
The domain of this function is $\{ 0, 1, \dots n-1 \}$. The co-domain is the same as the domain. 
Co-domain is the set of all possible values that $f(x)$ can land on, while the range is the set of all actual values for $f(x)$. In other words, 
$$
\text{range} \in \text{co-domain}
$$

From Wikipedia, $f$ is injective if it:

> ...maps distinct elements of its domain to distinct elements of its codomain; that is, $x1 \neq x2$ implies $f(x_1) \neq f(x_2)$ (equivalently by contraposition, $f(x_1) \neq f(x_2)$ implies $x_{1}=x_{2}$). In other words, every element of the function's codomain is the image of at most one element of its domain. (There may some elements in the codomain that are not mapped from elements in the domain.)

A function $f$ is surjective if:
>  for every element $y$ of the function's codomain, there exists at least one element $x$ in the function's domain such that $f(x) = y$. The function $f$ may map one or more elements of $X$ (domain) to the same element of $Y$ ()

A bijective relationship falls in between injective and surjective. 
A **bijection** means that each letter maps to exactly one number in the map.


![[function-mapping.svg]]
<center><a href="https://www.mathsisfun.com/sets/injective-surjective-bijective.html">Image credit: Math is Fun</a></center>

$$
\begin{align}
\text{Let }f: \symbb{Z}/_{n\symbb{Z}} \to \symbb{Z}/_{n\symbb{Z}}
\end{align}
$$
Theorem:
**$f$ is a bijection if and only if its dynamical portrait consists of independent cycles.**

Proof:
The proof of this is pretty simple. The term "if and only if" means this is an equivalence statement is true going both ways. 
First, let's prove it going forward. We assume $f$ is a bijection. When going to the next node, we can only go to an unvisited node. If the next node has been visited before, then that means we would have two arrows going into that node, which means it's not a bijection. Eventually we will meet the first node because there are a finite number of nodes (think of each node as numbers going around a circle, like a clock.)


Now going backwards, suppose we have some independent cycles. By independent we mean the cycles do not share any nodes and are completely separated. If we zoom into the cycles, each node will have an edge going in and an edge going out. So it's a bijection relationship. You can draw some cycles for an easier grasp.

Theorem:
Given $f(x)=x+a$, where $a, n \in \symbb{Z}$, $n>0$, $f$ is bijective.
