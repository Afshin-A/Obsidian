This is a way of representing negative numbers in binary.



The first method is that we simply use the left most bit to represent the sing of the integer. 0 for positive, and 1 for negative. However, this leads to problems such as having negative 0. Also, adding positive and negatives does not work.
```
-7	1111
-6	1110
-5	1101
-4	1100
-3	1011
-2	1010
-1	1001
-0  1000
0	0000
1	0001
2	0010
3	0011
4	0100
5	0101
6	0110
7	0111
```

Next, we have one's complement. The idea is that if we add a positive number with its equivalent, we should get 0. So we flip all the bits in a number to get its negative equivalent:

```
-7	1000
-6	1001
-5	1010
-4	1011
-3	1100
-2	1101
-1	1110
-0  1111
0	0000
1	0001
2	0010
3	0011
4	0100
5	0101
6	0110
7	0111
```

Now that we add numbers, we see that the numbers are off by 1. 
```
5	0101
+
-5	1010
--------
-0	1111

6	0110
+
-2	1101
--------
3	0011
```

We need to add 1 to get the right answer. This is two's complement: to get the negative of a positive number, flip all its bits and add 1. In our chart, we remove -0 and shift everything down by 1 row. This has the same effect as adding 1 to everything.

```
-8	1000
-7	1001
-6	1010
-5	1011
-4	1100
-3	1101
-2	1110
-1  1111
0	0000
1	0001
2	0010
3	0011
4	0100
5	0101
6	0110
7	0111
```

The left most bit in `1111` (which is $-1$) for example represents $-8$. So we would have $-8+4+2+1=1$.   