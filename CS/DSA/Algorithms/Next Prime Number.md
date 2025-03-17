When studying the double hashing probing method in the hash table data structure, I found myself to be in need of a way of finding the next prime number. In this probing method, the table size must be a prime number or else we could get stuck in an infinite cycle of repeat values, never finding an empty spot on the table.

We could always brute force our way through. However, there are two ways of effectively finding the next prime number.

# Sieve of Eratosthenes

This is a super efficient way of finding all pre-computing all prime numbers smaller than $10^6$ ($10^7$ at most). 