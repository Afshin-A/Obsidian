To show that a number $n$ is prime, we must show that it has no factors other than $1$ and $n$.
Thus, we start looking for factors ($a$ and $b$) starting at $2$. But when do we stop looking for factors?
The answer is $\sqrt{n}$ . This is because no number $n$ can have two factors greater than $\sqrt{n}$
If it did, then we would have a number greater than n: $a \cdot b > n$ 
Thus, if we search upto $\sqrt{n}$ and find no factors, we can be certain there are no factors greater than $\sqrt{n}$ , and that $n$ is prime.

This fact has many applications in number theory and computer science. One such application is the Sieve of Eratosthenes algorithm, used for finding primes upto a given integer, `max`.


```java
public static List<Integer> primes(int max) {  
        // LinkedList and ArrayList implement the List interface, which is why they share many methods such as add, get, iterator, etc.        
        List<Integer> numbers = new LinkedList<>();  
        List<Integer> primes = new LinkedList<>();  
  
        // Filling the numbers list with 2 and subsequent odd integers, because no even integer other than 2 can be prime  
        numbers.add(2);
        for (int i = 3; i <= max; i += 2) {
            numbers.add(i);
        }
  
        int primeNum;  
        int nextNum;  
        while (!numbers.isEmpty()) {  
            Iterator<Integer> itr = numbers.iterator();  
            // Get the next number
            primeNum = itr.next();  
  
            // Upon reaching sqrt(max) the remaining factors do not have a factor smaller or equal to sqrt(max) , and thus cannot have a factor greater or equal to sqrt(max) either (other than 1 or themselves). So they are all prime numbers. We can stop the algorithm earlier for more efficiency.
            if (primeNum >= Math.sqrt(max)) {  
                primes.addAll(numbers);  
                return primes;  
            }  
			// Add number to list of primes
            primes.add(primeNum);  
            // Remove number from the list of numbers
            itr.remove();  
  
  
            // Remove all remaining elements in numbers that are factor of primeNum  
            while (itr.hasNext()) {  
                nextNum = itr.next();  
                if (nextNum % primeNum == 0) {  
                    itr.remove();  
                }  
            }  
        }  
        return primes;  
    }
```


