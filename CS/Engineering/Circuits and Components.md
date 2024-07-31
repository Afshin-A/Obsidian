# Voltage
Electrical potential energy difference in a battery (for example) that drives electrons to flow in a conductor. Measured in volts (V). 
Technically, voltage is a standardized unit. It's the work done per unit of charge.
$$
P \propto V
$$
The more the change in potential energy, the more work is done: the steeper the hill, the more work you have to do to reach the top.
Voltage is a way to measure **how much work is needed per unit of charge**. Think of it like saying, "How much effort do I need to push each pebble up the hill?"
# Current
Flow of electrons, measured in amps (A), which is the equivalent of 1 **coulomb** (C) per second. 
# Energy
Energy is the capacity to do work
# Work
Energy transferred to an object to make it move.
# Power
Rate at which work is done, measured in Watts (W)
$$
P={\text{Work} \over t}
$$
$$\begin{align}
V={W\over Q} \\
W=E=QV\\
P={W \over t} = {QV \over t} = {IV} \\
P&=IV=({V \over R})V={V^2\over R}\\
P&=IV=I(IR)=I^2R\\
\end{align}
$$
$$
\begin{align}
P&=IV\\
&={V^2 \over R}\\
&=I^2R
\end{align}
$$
# Direct Current (DC)
The current that flows in a linear fashion through a circuit
# Alternating Current
A different type of electricity. Electrons go back and forth, like a stationary sine wave that goes up and down. It has a frequency, and it is efficient being moved through wires at long distances.

Most appliances use a combination of alternating (for a motor) and direct currents (for circuits). 
# Resistor
Special material that drops voltage. It slows the flow of electrons. As electrons flow through the resistor, they collide with the atoms in the resistor and their kinetic energy is converted to and released as heat. Resistors consume power, equivalent of the heat that dissipates off the surface of the resistor.
This is how a circuit is said to do work.

When we go across a resistor, the voltage drops. We can use ohm's law to find out how much.
# Lightbulb
The lightbulb is consisted of a filament. It is a resistor that radiates lots of heat and therefore light (as a result of black body radiation).

# Fuse
A thin line inside a capsule. If the current goes above the rate the fuse is designed to handle, the line breaks and opens the circuit, protecting expensive hardware from being damaged.
# Ohm's Law
$$
\begin{align}
V&=IR \\
\text{Volate} &= \text{Current} \times \text{Resistance} \\ \\
&\Rightarrow I = {{V} \over {R}}

\end{align}
$$
More voltage, more current. More resistance, less current.
$$\begin{align}
I \propto V \\
I \propto {1 \over R}
\end{align}
$$
# Variable Voltage and Resistance, Constant Current
In a series circuit, __the current is the same everywhere__. But the voltage can vary because of different resistance values.

If there are multiple resistors in the circuit, the voltage across each resistor will be different. But, if you put the multimeter before the first resistor and after the last resistor, the voltage will be the same as the battery. This is because resistors added in a series will have their resistances added together. The first resistor will lower the current by some amount. Now, that current will enter the second resister, adding its effect to the current. And so on. The overall effect is as if there is just one big resistor. 

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
\coordinate (A) at (-5,1);
\coordinate (B) at (-5,0.5);
\coordinate (C) at (-5,0);

\node[] (1) at (-5,2) {Legend};
\node[] (2) at (-5,1) {Voltmeter};
\draw (-4,1)
	to[voltmeter] (-2,1);
\node[] (3) at (-5,0) {Resistor};
\draw (-4,0)
	to[resistor] (-2,0);



\end{circuitikz}
\end{document}
```



# Series 
If we place two batteries in series, the voltage of the circuit is the sum of the individual batteries. Think of each battery like a water pump. Each pump increases the water pressure cumulatively (they add up together).

# Parallel
Two batteries with parallel relative positions do not boost each other. Instead, they last for longer. In a parallel series, the voltage is the same everywhere because all the components are connected to the positive terminal on one side, and the negative on the other side. So that means it's the voltage that varies.

```tikz
\usepackage{circuitikz}
\usepackage{pgfmath}
\begin{document}

\begin{circuitikz}[american, voltage shift=0.5]
    % Define coordinates for better readability
    \coordinate (A) at (0,0);
    \coordinate (B) at (0,4);
    \coordinate (C) at (4,4);
    \coordinate (D) at (4,0);

    % Draw the main circuit
    \draw (A)
        to[battery, l=$9V$] (B)
        to[short,l=$I_t \rightarrow$] (1, 4)
        to[short] (C)
        to[short] (D)
        to[short] (1, 0)
        to[short,l=$I_t \leftarrow$] (A);
    % Adding three resistors in parallel
    \foreach \i in {1,...,3}
	    \draw (B) 
	        to[short, -] (\i,4)
	        to[short, -, l=$I_\i \downarrow$] (\i,3)
	        to[R=$R_\i$] (\i,0)
	        to[short, -] (A);




\end{circuitikz}

\end{document}

```


Think of it like water. The current will weaken as it splits to each branch and the value will depend on the resistance in that branch. The current that goes into the branches equals the current that comes out. 
$$
I_t=I_1 + I_2 + \dots + I_n
$$

The total resistance of the parallel circuit can be calculated such as:
$$
R_t = {1 \over {{1\over R_1}+{1 \over R_2}+{1 \over R_3} + \dots + {1 \over R_n}}}
$$
# Complex Circuits
We work our way outwards from within. 
<iframe width="560" height="315" src="https://www.youtube.com/embed/-PiB2Xd3P94?si=KgPDPn0DOJx1IVyW" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>


# Multiple Batteries


Whenever charge moves through a resistor, it loses energy that is converted to heat and light. Voltage is potential energy. In other words, voltage always drops through resistors and other similar components.





[[Electric field, potential energy, and potential (khan academy)]]



# Resistivity of resistors

Resistivity $\rho$ depends on the material from which the resistor is made of.
$$\begin{align}
\text{Resistance} &\propto L \\
\text{Resistance} &\propto {1 \over A} \\
R&=\rho {L \over A} \\
\end{align}
$$
$$\begin{align}
Conductivity &= {1 \over Reistivity} \\
\sigma &= {1 \over \rho} 
\end{align}
$$
# Voltmeters and ammeters
Yes, it's ammeter, not ampmeter.
**Never connect an ammeter in parallel to a circle.** Ammeters have very little resistance so they don't interfere with the current. When connected in parallel, all the current would flow through the ammeter and blow it up. More current goes through the branch with less resistance. 
In contrast, voltmeters should be connected in parallel, because we are trying to measure the difference in electric potential across a component, like a resistor. If you connect a voltmeter to a wire, it will read a voltage of 0 because there is no change in the electric potential. Remember that 
$$
\text{Voltage} = \Delta U_e
$$
Voltmeters have a very large resistance so no current diverts from the component that we want to measure the voltage for. Remember that $V=IR$. $R$ is constant, so a change in current would change the voltage as well.


# Capacitors
```tikz

\usepackage{tikz}
\usepackage{circuitikz}
\begin{document}
\begin{tikzpicture}[invisible/.style={draw=none, fill=none}]

% capacitor
\draw 
	(2,1) -- node[left] {$-$} (2,3)
	(3,1) -- node[right] {$+$} (3,3);

% Capacitor
\draw (2,1.9)
	to[short] (0,1.9)
	to[short, l=$- \uparrow$] (0,-1)
	to[battery, l=$-V+$] (5,-1)
	to[short, l=$- \downarrow$] (5,1.9)
	to[short] (3,1.9);

\node[invisible] (1) at (2.5,3.) {$\leftarrow V \rightarrow$};

\end{tikzpicture}
\end{document}
```
A capacitor stores charge. It consists of two conductor sheets placed close to each other, but not touching. We connect a battery to a capacitor, positive head to one sheet, and negative to the another. The voltage in the battery draws electrons from one sheet to another. So, one sheet becomes positively charged, and the other stores the charge and becomes negative. As we leave the battery on, charge continues to build up and a voltage (change in electric potential) is created between the sheets. This continues until the voltage in the capacitor matches the voltage in the battery.

Once we reach this stage, we have an equilibrium state in the system. Charge no longer flows. 
~~One way to think about it is the potential field of the capacitor cancels the potential field of the battery~~
~~Or can we say the electric field created by the battery cancels the electric field created by the capacitor? Electric field goes from positive to negative. In the battery, it foes from right to left.~~

It's interesting that anything the battery is connected to in series gets the voltage of the battery. A resistor has the same electric potential difference across than the battery. If it didn't, then potential energy would keep building up in the battery. But that's not the case. the potential energy is constant until the battery wears out. So all the energy that goes around is converted to another form like heat. 

You could say that charge only moves as long as it's in a more stable energy level. 
Would a ball drop if it had the same energy at a height and ground level? No. Similarly, charge would not move if the voltage at the battery equals the voltage of the capacitor. But whilst the energy of the capacitor is less (more stable), charge will flow there and electric potential continues to build up.

## Capacitance
A capacitor is rated by its **capacitance.** 

The net charge of the capacitor is 0. $Q$ above refers to the magnitude of charge on one sheet.
To standardize capacitors and be able to compare them, we need to find out how much charge they can store under the same voltage.
$$\begin{align}
&C={Q \over V} \\
&\text{Farad} = {\text{Coulomb} \over \text{Volts}}
\end{align}
$$
### Capacitance derived using electric flux (wtf is electric flux?)
Capacitance is a property of the capacitor. It doesn't depend on the amount of charge it can store. This is because the more charge it stores, the higher the voltage goes. So the ratio stays the same.
We can increase the capacitance by increasing the size of the sheets or using different materials, that way more charge is stored. The charge can spread through out a large sheet easier, so less electric potential is built. 

```tikz

\usepackage{tikz}
\usepackage{circuitikz}
\begin{document}
\begin{tikzpicture}[invisible/.style={draw=none, fill=white}]

% Back sheet coordinates
\coordinate (A) at (2,0);
\coordinate (B) at (0,1);
\coordinate (C) at (0,4);
\coordinate (D) at (2,3);
% Front sheet coordinates
\coordinate (E) at (1,-1);
\coordinate (F) at (-1,0);
\coordinate (G) at (-1,3);
\coordinate (H) at (1,2);
% Area label
\coordinate (area) at ($(E)!0.5!(G)$);
\coordinate (dist) at ($(A)!0.5!(E)$);

\filldraw[fill=blue!20, draw=black] (A) -- (B) -- (C) -- (D) -- cycle;
\filldraw[fill=red!20] (E) -- (F) -- (G) -- (H) -- cycle;

\node at (area) {$A$};


\draw[dotted] (A) -- (E);
\node[invisible] at (dist) {$d$};

\end{tikzpicture}
\end{document}
```

==Apparently to understand this we need to understand electric flux and Gauss's law==
$$
C=\epsilon_0 {A \over d}
$$
## Dielectrics
Dielectrics always increase the capacitance of a capacitor. They're made from non-conductor materials and placed between the sheets to prevent them from touching, keeping the charges separated and the voltage up.
When we place the non-conductor in the electric field, its atoms become polarized. Partially positive close to the negative sheet, and partially negative close to the positive sheet. This overall alleviates the electric potential energy in the system. It reduces the voltage (the difference in electric potential) between the sheets. Therefore, it will take longer before the voltage between the sheets builds up, so more charge is moved.
Dielectric constant $\Large \kappa$ (Greek kappa) is unique to the materials we use in between the sheets.
$$
\Large C_{\text{dielectric}} = \kappa C \ \ \ \ \ \ \ \kappa>1
$$
## Energy of a capacitor
```tikz
\usepackage{circuitikz}
\usepackage{pgfmath}
\begin{document}
\begin{circuitikz}[american, voltage shift=0.5]

\draw (0,0)
to[short] (0,2)
to[capacitor, l=$V$] (3,2)
to[short] (3,0)
to[bulb, l=light bulb] (0,0);

\end{circuitikz}
\end{document}
```

How much energy is stored in a capacitor? How much energy can it release? These two questions are equivalent (because there's no where else for the energy to go, since we assume no resistance in the wires).
Suppose we charge the capacitor until it gains the same voltage as the battery, then disconnect it. 
Voltage (by definition) is energy divided by charge. So,
$$\begin{align}
E=QV
\end{align}
$$
We also know that,
$$
C=\frac{Q}{V} \to V=\frac{Q}{C}
$$
But, as the charge of the capacitor reduces, so does its voltage. So now charge flows with a lower voltage, so less energy is being supplied to the light bulb. 
To find the total energy of the system, we need to find the sum of all the energies. When charge moves, some electric potential energy is converted to other forms of energy. At every instance, a little bit of charge moves due to a varying amount of electric potential energy. We need find the sum of all those energies to find how much energy the capacitor released overall.
$$\begin{align}
E_{total}&=\int_0^{Q_{total}}{dE}\\
&=\int_{0}^{Q_{total}}{VdQ}\\
&=\int_0^{Q_{total}}{\frac{Q}{C}}dQ &&\text{Writing $V$ in terms of $Q$}\\
&=\frac{1}{C}\int_0^{Q_{total}}{QdQ}=\boxed{\frac{Q^2}{2C}} \\
E_{total}&=\frac{1}{2C}Q^2=\frac{1}{2}\frac{Q}{C}Q=\boxed{\frac{1}{2}VQ} &&\text{Substitute $\frac{Q}{C}$ for $V$}\\
E_{total}&=\frac{1}{2}VQ=\frac{1}{2}V(CV)=\boxed{\frac{1}{2}CV^2} &&\text{Substitute $CV$ for $Q$}\\
\end{align}
$$
```tikz
\usepackage{tikz}

\begin{document}    
\begin{tikzpicture}
  \draw[->] (0, 0) -- (5, 0) node[right] {$Q$};
  \draw[->] (0, 0) -- (0, 5) node[above] {$V$};
  \draw[scale=1, domain=0:4, smooth, variable=\x, blue] plot ({\x}, {-1*\x+4});
  \filldraw[fill=blue!20, draw=none] (0,0) -- (0,4) -- (4,0) -- cycle;
  \node at (1.5,1) {$U=\frac{1}{2}VQ$};
\end{tikzpicture}
\end{document}
```
Source:
<center><iframe width="560" height="315" src="https://www.youtube.com/embed/toycHgLOuUM?si=7DNmFYrR4u-n29Yc" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe></center>

## Relationship between Capacitance and Current
So we know that $C=\frac{Q}{V}$. Rearranging, we get
$$\begin{align}
Q&=CV \\
dQ&=CdV \\
\frac{dQ}{dt}&=C\frac{dV}{dt} \\
I &= C\frac{dV}{dt} \\
\end{align}
$$
**Need to rework this. $C=\frac{Q}{V}$ is true for when the capacitor is fully charged. What about for while it is charging?**
## Capacitors in series

```tikz
\usepackage{circuitikz}
\usepackage{pgfmath}
\begin{document}
\begin{circuitikz}[american, voltage shift=0.5]

\draw (0,0)
to[short] (0,2)
to[capacitor, l=$C_1$] (2,2)
to[capacitor, l=$C_2$] (4,2)
to[capacitor, l=$C_3$] (6,2)
to[capacitor, l=$C_4$] (6,0)
to[battery, l=$V$] (0,0);

\end{circuitikz}
\end{document}
```



==In a series circuit, the sum of individual voltages of all components equals the voltage of the battery. This is universally true because energy of the battery must be consumed by/transferred to the components, and there are no leftovers (else the battery would keep building energy).==

In a series circuit, all capacitors will have the same charge.
$$\begin{align}
V=V_1+V_2+V_3+V_4 \\
Q_1 = Q_2=Q_3=Q_4
\end{align}
$$

Now suppose we replace all the capacitors with an equivalent capacitor, like we did with resistors. We want to find the capacitance of the equivalent capacitor using the capacitances of the individual series capacitors in the circuit.
```tikz
\usepackage{circuitikz}
\usepackage{pgfmath}
\begin{document}
\begin{circuitikz}[american, voltage shift=0.5]

\draw (0,0)
to[short] (0,2)
to[capacitor, l=$C_{eq}$] (6,2)
to[short] (6,0)
to[battery, l=$V$] (0,0);

\end{circuitikz}
\end{document}
```
This equivalent capacitor will the the voltage of the battery.
$$\begin{align}
V={Q \over C_{eq}} = {Q \over C_1} + {Q \over C_2} + {Q \over C_3} + {Q \over C_4} \\
\boxed{{1 \over C_{eq}} = {1 \over C_1} + {1 \over C_2} + {1 \over C_3} + {1 \over C_4}} 
\end{align}
$$
## Capacitors in parallel
```tikz
\usepackage{circuitikz}
\usepackage{pgfmath}
\begin{document}
\begin{circuitikz}[american, voltage shift=0.5]

\draw (0,0)
to[short] (0,2)
to[capacitor, l=$C_{1}$] (4,2)
to[short] (4,0)
to[battery, l=$V$] (0,0);

\draw (0,2)
to[short] (0,4.5)
to[capacitor, l=$C_2$] (4,4.5)
to[short] (4,0);

\end{circuitikz}
\end{document}
```

The capacitors above are connected in parallel. They have the same voltage because both of them connect to the same end of the battery on each side.
$$
V_1 = V_2
$$
Remember that capacitance $C$ is the charge a capacitor can hold per unit of voltage, i.e. $C=\frac{Q}{V}$. So, if the voltage for parallel capacitors is the same, that means that if, for example, $C_1 = 2 C_2$, capacitor 1 holds twice the charge of capacitor 2.

The total charge comes from both capacitors. 
$$
Q = Q_1 + Q_2
$$
Now suppose we want to find the capacitance of the equivalent capacitor.
$$\begin{align}
C_{eq}&={Q_{total} \over V_{eq}} \\
C_{eq}&={{Q_1 + Q_2} \over V_{eq}} = {Q_1 \over V_{eq}} + {Q_2 \over V_{eq}} \\
&= {Q_1 \over V_1} + {Q_2 \over V2}\\
&= C_1 + C_2 &V_{eq}=V_1=V_2\\
\end{align}
$$
$$
\therefore \boxed{C_{e} = C_1 + C_2}
$$
