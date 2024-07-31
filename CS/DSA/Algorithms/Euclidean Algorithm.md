Suppose there exist two integers $a, \ b$ where $a>b$ and  $a=bq+r \ (Equation \ 1)$. So dividing $a$ by $b$ gives a quotient $q$ and a remainder of $r$.
The greatest common divisor of $a$ and $b \quad gcd(a, \ b) \quad$ is the greatest integer that evenly divides both $a$ and $b$.
We are going to show that
$$
gcd(a, b)=gcd(b,r)
$$
Rearranging $Equation \ 1$ gives:
$$
a-bq=r
$$
Any integer $x$ that evenly divides both $a$ and $b$ will also evenly divide $r$.
So we can define $D$ to be the set of all $x's$ as follows:
$$
D=\{x \in Z | x\mid a, x\mid b\} \\

$$
$$
\set{x \in Z  }
$$
```java
public static int gcd(int a, int b) {   
    // In case user enters negative numbers  
    if (a < 0 || b < 0) {  
        return gcd(Math.abs(a), Math.abs(b));  
    }  
    else if (b == 0) {  
        return a;  
    }  
    else {  
        return gcd(b, a % b);  
    }  
}

```