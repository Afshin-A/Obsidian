```
\usepackage{circuitikz}
\begin{document}

\begin{circuitikz}[american, voltage shift=0.5]
\draw (0,0)
    % 9V Battery
    to[battery, l=$9V$] (0,4)
    % First resistor
    to[short, -*] (2,4)
    to[R=$R_1$, i>_=$I_1$] (2,0)
    -- (0,0);
\draw (2,4) -- (4,4)
    % Second resistor
    to[R=$R_2$, i>_=$I_2$] (4,0)
    to[short, -*] (2,0);
\draw (4,4) -- (6,4)
    % Third resistor
    to[R=$R_3$, i>_=$I_3$] (6,0)
    to[short, -*] (4,0);
\draw (6,4) -- (8,4)
    % Circuit breaker
    to[cspst, l=$Breaker$] (8,0)
    -- (6,0);
\end{circuitikz}

\end{document}
```

```tikz
\usepackage{circuitikz}
\begin{document}

\begin{circuitikz}[american, voltage shift=0.5]
\draw (0,0)
    % 9V Battery
    to[battery, l=$9V$] (0,4)
    % First resistor
    to[short, -*] (2,4)
    to[R=$R_1$, i>_=$I_1$] (2,0)
    -- (0,0);
\draw (2,4) -- (4,4)
    % Second resistor
    to[R=$R_2$, i>_=$I_2$] (4,0)
    to[short, -*] (2,0);
\draw (4,4) -- (6,4)
    % Third resistor
    to[R=$R_3$, i>_=$I_3$] (6,0)
    to[short, -*] (4,0);
\draw (6,4) -- (8,4)
    % Circuit breaker
    to[cspst, l=$Breaker$] (8,0)
    -- (6,0);
\end{circuitikz}

\end{document}

```

```
\usepackage{circuitikz}
\begin{document}

\begin{circuitikz}[american, voltage shift=0.5]
\draw (0,0)
    % 9V Battery
    to[battery, l=$9V$] (0,4)
    % First resistor
    to[R=$R_1$] (4,4)
    % Second resistor
    to[R=$R_2$] (6,4)
    % Third resistor
    to[R=$R_3$] (8,4)
    % Circuit breaker
    -- (10,4)
    -- (10,0)
    -- (0,0);

\end{circuitikz}
\end{document}
```
```tikz

\usepackage{circuitikz}
\begin{document}

\begin{circuitikz}[american, voltage shift=0.5]
\draw (0,0)
    % 9V Battery
    to[battery, l=$9V$] (0,4)
    % First resistor
    to[R=$R_1$] (4,4)
    % Second resistor
    to[R=$R_2$] (6,4)
    % Third resistor
    to[R=$R_3$] (8,4)
    % Circuit breaker
    -- (10,4)
    -- (10,0)
    -- (0,0);
\end{circuitikz}

\end{document}

```


```tikz
\usepackage{circuitikz}
\begin{document}

\begin{circuitikz}[american, voltage shift=0.5]
\draw (0,0)
    % 9V Battery
    to[battery, l=$9V$] (0,4)
    % First resistor
    to[R=$R_1$] (4,4)
    % Second resistor
    to[R=$R_2$] (8,4)
    % Third resistor
    to[R=$R_3$] (12,4)
    % Completing the circuit back to the battery
    -- (14,4) -- (14,0)
    to[cspst, l=$Breaker$] (0,0);

\end{circuitikz}

\end{document}

```
```
\usepackage{circuitikz}
\begin{document}

\begin{circuitikz}[american, voltage shift=0.5]
\draw (0,0)
    % 9V Battery
    to[battery, l=$9V$] (0,4)
    % First resistor
    to[R=$R_1$] (4,4)
    % Second resistor
    to[R=$R_2$] (8,4)
    % Third resistor
    to[R=$R_3$] (12,4)
    % Completing the circuit back to the battery
    -- (14,4) -- (14,0)
    to[cspst, l=$Breaker$] (0,0);

% Adding a voltmeter across the first resistor
\draw (0,4) 
    to[short, -*] (1,4)
    -- (1,4) -- (1,6)  
    to[voltmeter, l=$V_{R1}$] (3,6)
    to[short, -*] (3,4);

\end{circuitikz}
\end{document}
```

```tikz
\usepackage{circuitikz}
\begin{document}

\begin{circuitikz}[american, voltage shift=0.5]
    % Define spacing and coordinates using variables
    \def\compDist{4} % spacing between components
    \def\height{4} % vertical position for components
    \def\vHeight{\height * 1.5} % vertical position for voltmeter
    \def\vStart{\compDist/4}
    \def\vEnd{\vStart + \compDist/2}

    % Draw the main circuit
    \draw (0,0)
        % 9V Battery
        to[battery, l=$9V$] (0,\height)
        % First resistor
        \foreach \i in {1,...,3} {
            to[R=$R_\i$] (\i*\compDist,\height)
        }
        % Completing the circuit back to the battery
        -- (3*\compDist,\height) -- (3*\compDist,0)
        to[cspst, l=$Breaker$] (0,0);

    % Adding a voltmeter across the first resistor
    \foreach \i in {1,...,3} {
	    \draw (\i-1*\compDist,\height) 
		    to[short, -*] (\i*\vStart,\height)
	        -- (\i*\vStart,\height) -- (\i*\vStart,\vHeight)
	        to[voltmeter, l=$V_{R\i}$] (\i*\vEnd,\vHeight)
	        to[short, -*] (\i*\vEnd,\height);
    }

\end{circuitikz}
\end{document}
```
    to[short, -*] (1,4)
    -- (1,4) -- (1,6)  
    to[voltmeter, l=$V_{R1}$] (3,6)
    to[short, -*] (3,4);

```
\usepackage{circuitikz}
\begin{document}

\begin{circuitikz}[american, voltage shift=0.5]
    \def\x{4} % spacing between components
    \def\y{4} % vertical position for components
    \def\d{1.5 * \y} % vertical position for voltmeter


    % Draw the main circuit
    \draw (0,0)
        % 9V Battery
        to[battery, l=$9V$] (0,\y)
        % First resistor
        \foreach \i in {1,...,3} {
            to[R=$R_\i$] (\i*\x,\y)
        }
        % Completing the circuit back to the battery
        -- (3*\x,\y) -- (3*\x,0)
        to[cspst, l=$Breaker$] (0,0);

    % Adding a voltmeter across the first resistor
    \foreach \i in {1,...,3} {
		\def\a{\i-1*\x}
		\def\b{\a + \x/4}
		\def\c{\a + 3*\x/4}
		\draw (\a,\y) 
			to[short, -*] (\b,\y)
		    -- (\b,\y) -- (\b,\d)
		    to[voltmeter, l=$V_{R\i}$] (\c,\d)
		    to[short, -*] (\c,\y);
    }

\end{circuitikz}
\end{document}
```

```tikz
\usepackage{circuitikz}
\usepackage{pgfmath}
\begin{document}

\begin{circuitikz}[american, voltage shift=0.5]
    \def\x{4} % spacing between components
    \def\y{4} % vertical position for components
    \def\d{1.5 * \y} % vertical position for voltmeter

    % Draw the main circuit
    \draw (0,0)
        % 9V Battery
        to[battery, l=$9V$] (0,\y)
        % First resistor
        \foreach \i in {1,...,3} {
            to[R=$R_\i$] (\i*\x,\y)
        }
        % Completing the circuit back to the battery
        -- (3*\x,\y) -- (3*\x,0)
        to[cspst, l=$Breaker$] (0,0);

    % Adding voltmeters across each resistor
    \foreach \i in {1,...,3} {
		\pgfmathsetmacro{\a}{(\i-1) * \x} 
		\pgfmathsetmacro{\b}{\a + \x / 4}
		\pgfmathsetmacro{\c}{\a + 3 * \x / 4}
		\draw (\a,\y) 
			to[short, -*] (\b,\y)
		    -- (\b,\y) -- (\b,\d)
		    to[voltmeter, l=$V_\i$] (\c,\d)
		    to[short, -*] (\c,\y);
    }

\end{circuitikz}
\end{document}
```


