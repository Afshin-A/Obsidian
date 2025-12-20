We cannot use the ternary operator as that is just synthetic sugar for an if-else statement.
No built in functions allowed
We cannot use absolute values, as that also uses if-else internally. Otherwise, we could use something like:
$$
\max(a,b)=\frac{a+b+|a-b|}{2}
$$



We need to find out the sign of $a - b$
The sign of a number is represented by the left most bit in two's complement method of representing binary numbers
Depending on the system (32 bit or 64 bit) and depending on the type used to store the variable, as defined by the programing language and compiler, we need to shift $a-b$ by M to find the left most bit. M is typically either 31 or 63, but it can be dynamically determined. 
Some programming languages don't even have a type limit for as long as the memory allows.
```
max(a, b) = a - ((a-b) AND ((a-b) >> 31))
```

if $a > b$,  then `(a-b) >> 31` would be 0, which would simplify the expression to $a-0=a$
If $b>a$, then `(a-b) >> 31` would be 1. We would then have:
$$
a - ((a-b) \ \text{and} \ 1) = a-(a-b)=b
$$
