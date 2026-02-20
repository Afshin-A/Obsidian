Similar to binary search, this algorithm is used to search for a target in a sorted array in `O(log(n))` time complexity. However, instead of division, this algorithm uses addition and subtraction.

Binary addition/subtraction is a much more efficient operation than division. The difference is negligible in modern hardware, however.

Addition uses something called "Carry Look-Ahead" [[Adder circuits|adder]] to almost instantly add even large numbers with carryons, while division is an iterative operation involving subtractions and bit-shifting, and we can't predict the outcome without going each iteration in order.

Fibonacci search was important on older hardware, but it is still a neat algorithm to know. 

https://youtu.be/OLMA_MEqgEA
