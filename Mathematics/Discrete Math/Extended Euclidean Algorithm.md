The extended Euclidean algorithm can be used to find the modular inverse of a number.
It works just like the Euclidean algorithm. However, each step is augmented with extra variables $x, \ y$ that allow us to find the integer linear combination of $a, \ b$, such that  $xa+yb=\gcd(a,b)$. This is called a linear Diophantine equation.

We want to add and subtract copies of a and b until we get to the gcd. That is exactly what we do in the Euclidean algorithm. So that's why we call this the extended Euclidean algorithm because with a little book keeping we can solve for those coefficients.