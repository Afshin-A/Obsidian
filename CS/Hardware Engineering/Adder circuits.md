


<center>
<iframe width="560" height="315" src="https://www.youtube.com/embed/LheGDXfUrwc?si=KidsYw673f5SmWqB" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
</center>



| $A$ | $B$ | $C_{in}$ | $S$ | $C_{out}$ |
| --- | --- | -------- | --- | --------- |
| 0   | 0   | 0        | 0   | 0         |
| 1   | 0   | 0        | 1   | 0         |
| 1   | 1   | 0        | 0   | 1         |
| 1   | 0   | 1        | 0   | 1         |
| 1   | 1   | 1        | 1   | 1         |

$$
\begin{align}
S=A \oplus B \oplus C_{in} \\
C_{out}=C_{in} \ \& \ (A \oplus B) \ | \ (A \ \& \ B)
\end{align}
$$
If A and B are both 1, C_out is 1
If only A or B is 1, but C_in is 1, then C_out is 1