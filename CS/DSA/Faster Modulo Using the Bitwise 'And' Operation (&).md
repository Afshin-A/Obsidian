$$
x \mod{y} = x \ \& \ (y-1)
$$

**This is usually used in hash tables for a quick way to map something to an index. All we have to do is make sure the size of the table is a power of 2.** #fasthash

**This is only possible when the divisor is a power of 2**.
$x \mod{y}$ can be found faster if y is a power of 2
The problem turns into a simple bitwise & operation, which is extremely fast



Quick recap.

In binary, dividing a number by 2 is the same as shifting its bits to the left by 1

Modulo is the remainder after division. 

example
```

```

$$
\begin{align}
15 = 1111_{2} \\
15&=1 \times 2^3 + 1 \times 2^2+ 1 \times 2^1+ 1 \times 2^0 \\
\frac{15}{2} &= \frac{1 \times 2^3 + 1 \times 2^2+ 1 \times 2^1+ 1 \times 2^0}{2} \\
&= 1 \times 2^2 + 1 \times 2^1+ 1 \times 2^0+ 1 \times 2^{(-1)} \\
&=7.5 \\
\end{align}
$$
In the example above, the last bit gets dropped because $2^{-1}$ can't be represented in binary. That is why quotients are always rounded down to the nearest digit.

Let's divide 15 by 4. This is the same as `15 >> 2`, 
$$
\begin{align}
\frac{15}{4} = 3+\cancel{\frac{3}{4}} \text{this part gets lost} \\
1111 \gg 2 = 11 \\
11 \ll 2 = 1100
\end{align}
$$

If we're dividing by 4 ($2^2$), then the last 2 binary digits are the remainder. These get lost. We need to recover them
We can recover those by using a bit mask. $2^2$-1 creates a number of all 1s. We take the & of the dividend and divisor-1, and we get those lost bits.


