$$\begin{align}
S_0&=1^0+2^0+3^0+\dots+(N-1)^0+N^0 \\
&= 1 + 1 + 1 + \dots+1 + 1 = N
\end{align}
$$
$$\begin{align}
S_1&=1^1+2^2 \  \qquad + 3^1 \qquad \ \ +\dots+(N-1)^1+N^1 \\
S_1&=N+(N-1)+(N-2)+\dots+2 \qquad \quad \ +1 \\ \\
2S_1&=(N+1)+(N+1)+(N+1)+\dots+(N+1)+(N+1) \\
&=N(N+1) \\
\therefore S_1&={{N(N+1)}\over{2}}
\end{align}
$$
$$\begin{align}
S_2=\sum_{n=1}^{N}{n^2}=1^2+2^2+3^2+ \dots + (N-1)^2 + N^2 \\
\end{align}
$$
We begin by considering the following [[telescoping series]]:
$$
\begin{align}
\sum_{n=1}^{N}{(n^3+1)-n^3}&=
\underbrace{\cancel{(2)^3}-(1)^3}_{n=1} + \underbrace{(3)^3-\cancel{(2)^3}}_{n=2}+\underbrace{(4)^3-(3)^3}_{n=3}+\dots+\underbrace{(N-1)^3-(N)^3}_{n=N-1}+\underbrace{(N+1)^3-(N)^3}_{n=N} \\
&=-1+(N+1)^3
\end{align}
$$

$$\begin{align}
\sum_{n=1}^{N}{(n^3+1)-n^3}&=\sum_{n=1}^{N}{(n^3+3n^2+3n+1-n^3)}\\
&=\sum_{n=1}^{N}{(3n^2+3n+1)}\\
&=\Big(3\sum_{n=1}^{N}{n^2}\Big) + \Big(3\sum_{n=1}^{N}{n}\Big)+\Big(\sum_{n=1}^{N}{1}\Big)
\end{align}
$$
$$\begin{align}
&-1+(N+1)^3=\Big(3\sum_{n=1}^{N}{n^2}\Big) + \Big(3\sum_{n=1}^{N}{n}\Big)+\Big(\sum_{n=1}^{N}{1}\Big) \\
\Big(3\sum_{n=1}^{N}{n^2}\Big)&=N^3+3N^2+3N-\Big(3\sum_{n=1}^{N}{n}\Big)-\Big(\sum_{n=1}^{N}{1}\Big) \\
&=N^3+3N^2+3N-3{{N(N+1)\over{2}}}-N \\
&=N^3+3N^2+3N-{{3N^2+3N}\over{2}}-{2N\over{2}} \\
&={2N^3+6N^2+6N+{-3N^2-5N}\over{2}} \\
&={2N^3+3N^2+N\over{2}}={N(2N^2+3N+1)\over{2}}={N(2N+1)(N+1)\over{2}} \\

\end{align}
$$

$$
\begin{align}
3\sum_{n=1}^{N}{n^2}={N(2N+1)(N+1)\over{2}} \\
\sum_{n=1}^{N}{n^2}={N(2N+1)(N+1)\over{6}}
\end{align}
$$