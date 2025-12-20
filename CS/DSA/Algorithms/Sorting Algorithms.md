# Selection Sorting
This sorting algorithm loops through the list, finds the smallest element, and brings it forward to the front of the list. It repeats this for as many times as there are elements in the list until the list is sorted.

```
for each element in the list
	for every other element after the current element
		set smallest to current element
		if this element is smaller than smallest
			mark that element as smallest
		swap current element with smallest
			
```

Here's an implementation of selection sort using Python. See [[Tuple Assignments]] for how element swapping works.
```python
def selection_sort(unsorted_list: list):
    list_size = len(unsorted_list)
    for i in range(list_size):
	    smallest_index = i
        for j in range(i+1, list_size):
            if unsorted_list[j] < unsorted_list[smallest_index]:
                smallest_index = j
        if smallest_index is not i:
            # swaping list elements via tuple-assignment
            unsorted_list[i], unsorted_list[smallest_index] = unsorted_list[smallest_index], unsorted_list[i]
    
    return unsorted_list
```


# Bubble Sorting
Bubble sort is pretty much **the simplest and slowest**  sorting algorithm, as the time complexity is always  $O(n^2)$. 

Starting at index 0, this algorithm works by comparing two adjacent elements. If the first element is larger than the second, then they are swapped. Then, the second and third element are compared. If the second element (which was the first element in the previous iteration) is larger than the third, then they're swapped. As you can see, at each step, largest element is moved to the right. This process continues for every element in the list with the exception of the last (because the last element has no element to its right).

```
[4, 3, 8, 5, 2] comparing 4 and 3. 4 > 3 so swap
[3, 4, 8, 5, 2] comparing 4 and 8. 4 < 8 so no swap
[3, 4, 8, 5, 2] comparing 8 and 5. 8 > 5 so swap
[3, 4, 5, 8, 2] comparing 8 and 2. 8 > 2 so swap
[3, 4, 5, 2, 8]

Now the largest element is at the end of the list.

Repeat this process starting from start of the list. But do not include the final element.
```

```python
def bubble_sort(unsorted_list: list):
	list_size = len(unsorted_list)
    for i in range(list_size):
        for j in range(list_size-i-1):
            if unsorted_list[j] > unsorted_list[j+1]:
                unsorted_list[j], unsorted_list[j+1] = unsorted_list[j+1], unsorted_list[j]
    return unsorted_list
```


# Insertion 
As we work our way from left to right, there will be two partitions formed: one on the left, and one on the right. During each iteration, an element from the right partition is *inserted* in the sorted, left partition. Therefore, The left partition keeps growing while the right partition shrinks.
Specifically, 
```python
def insertion_sort(unsorted_list: list):
	# start at second element
    for i in range(1, len(unsorted_list)):
        j = i
        while j > 0 and unsorted_list[j] < unsorted_list[j-1]:
            unsorted_list[j], unsorted_list[j+1] = unsorted_list[j+1], unsorted_list[j]
            j -= 1
    return unsorted_list
```

Similar to bubble sorting, the time complexity of the insertion sorting algorithm, at the worst case, is $O(n^2)$

# Comparing Selection, Bubble, and Insertion Sorting Algorithms 
The time complexity of all these algorithms is $O(n^2)$ at the worst case. So neither is appropriate for large lists. However, for small lists, lists that are nearly sorted should be sorted with insertion sort because it will take the least number of swaps. 
```
|1 | 2 3 5 4 6 |
| 1 2 3 5 | 4 6 |
| 1 2 3 4 5| 6 |
```
In the example above, once we have 1 sorted partition, there are no more comparisons. Whereas in bubble sort, we would loop back from the start and compare adjacent elements again. There would be so many unnecessary comparisons.

Selection sort works the same way regardless of how organized the list already is.
# Merge Sorting


# Quick Sorting



# Counting Sort
```
[5, 1, 2, 1, 1, 4, 0] elements array, define k as the range of elements: k=max-min+1=5-0+1=6
[1, 3, 1, 0, 1, 1] counts of elements
[0, 1, 2, 3, 4, 5] indices represent elements len(indices)=k=6
[1, 4, 5, 5, 6, 7] prefix sums array
```
The counts array tells us so much: we have one 0, three 1s, and so on.
But using the prefix sums array, we can use a technique that keeps the relative order of the elements, making this a [[Stable vs Unstable Sorting Algorithms|stable]] algorithm. 
When you add up the counts of the elements, you're really saying how many elements come before the current element. For example, you have one 0 and three 1s, giving you 4. In the final array, the last place 1 will be, is going to be the 4th position (which is at index 3 because arrays start at index 0).
We loop through our elements array from right to left. For each element, we see the last position it goes to, insert it in the final array, then we decrement the prefix sum so we know where the next repeat of the current element goes. 
```
             ↓      ↓               ↓
[5,1,2,1,1,4,0]    [1,4,5,5,6,7]    [0,0,0,0,0,0,0]
input              prefix sums      results
```
Last place 0 goes into is 0

```
           ↓                ↓                  ↓
[5,1,2,1,1,4,0]    [0,4,5,5,6,7]    [0,0,0,0,0,4,0]
```
Last place 4 goes into is index 5

```
         ↓            ↓                    ↓
[5,1,2,1,1,4,0]    [0,4,5,5,6,7]    [0,0,0,1,0,4,0]
```
Last place 1 goes into is index 3

```
       ↓              ↓                  ↓  
[5,1,2,1,1,4,0]    [0,3,5,5,6,7]    [0,0,1,1,0,4,0]
```
We see another 1. The last place this goes into is 2

The pattern continues until we get the sorted array:
```
[0, 1, 1, 1, 2, 4, 5]
```

**Time complexity is $O(n+k)$** because we traverse through the input and counter arrays linearly. 
The smaller the k, the better the algorithm will perform. Keep in mind we need a counter array the size of K. It wouldn't be efficient if we only had 10 elements with a gap of 10 million. That would make n=10 and k=10_000_000. So we'd have about 9_999_990 slots filled with 0, used for nothing. ==So the closer n is to k, the better.==

The algorithm can be modified to support negative numbers as well. We need to align the smallest number (for example, -5) with 0. So we add 5 to all the elements, which is the same thing as subtracting -5
Notice that the algorithm depends on k, not the smallest value. So if the smallest number in the input array is 1000, we can shift everything by subtracting all numbers by 1000.
In other words, the algorithm can be made more efficient by subtracting then adding back the smallest value to all numbers.
```c#
        var input = new int[] { 100, 102, 100, 103 }; // k=largest-smallest+1=103-100+1=4
        var largest = input[0];
        var smallest = input[0];
        // step 1: find largest and smallest
        foreach (var current in input)
        {
            if (current > largest)
            {
                largest = current;
            }
            else if (current < smallest)
            {
                smallest = current;
            }
        }
        // Find k
        var k = largest - smallest + 1;
        var counts = new int[k];
        var prefixSums = new int[k];
        // find counts
        foreach (var current in input)
        {
            counts[current - smallest]++;
        }
        // [100, 102, 100, 103];
        // [2, 0, 1, 1] counts
        // [2, 0, 3, 4] prefixsums
        // Find prefix sums
        prefixSums[0] = counts[0];
        for (int i = 1; i < counts.Length; i++)
        {
            prefixSums[i] = prefixSums[i - 1] + counts[i];
        }
        // Populate output
        var output = new int[input.Length];
        for (int i = output.Length - 1; i >= 0; i--)
        {
            var current = input[i];
            var index = --prefixSums[current - smallest]; // first decrement the prefix sum by 1 then assing to index
            output[index] = current;
        }
        Console.WriteLine(string.Join(", ", output));
```


Counting sort is not exclusive to integers. It can be applied to any hashable object. Counting sort requires an input of integers. We can map our array of objects to integers. ==but how exactly?==

## TLDR
**Use counting sort when we want to sort integers that are close to each other in range**

# Radix Sort
This sorting algorithm is used to sort integers *very efficiently* under the right conditions. 
It's really a wrapper, meaning it uses a stable sorting algorithm (typically [[Sorting Algorithms#Counting Sort|counting sort]]) at its core.

**Radix** means **base**. We sort the array based on the base 10 digits: the 1s, 10s, 100s... positions.
It is possible to sort numbers in other bases. But of course the smaller the radix, the more digits there will be. For example, you need 7 digits to represent $99_{10}$ in base 2, since $\lceil\log_{2}99\rceil=7$), so this algorithm becomes inefficient.

The right most digit of a number $n$ is $n \mod{10}$. 
To get the next digit, we first divide n by 10, then take the modulus.
In general, all digits can be found like this:
```python
n = 1234
digits = []
while n > 0:
	digits.append(n % 10)
	n =/ 10
```

Back to radix sorting, our input is:
```
53 89 150 36 231 234
```

Step 1: we sort the numbers based their 1s--AKA their right-most--digits. 
```
150 231 53 234 36 89
```

Step 2: we sort based on the 10s positions:
```
231 234 36 150 53 89
```
**Why radix sort *must* use a stable sorting algorithm**—
Note that 231 was before 233 in step 1. This placement lingers in step 2 since both have 3 as their second digit (so they're considered equal in this step). This is the defining property of a stable sorting algorithm, and it is crucial here because it saves the work we're doing from one step to the next. For example, in the next step, 231 will stay before 234 since again they have the same 3rd digit. But if the algorithm wasn't stable and the order of (equal) array elements could randomly change, then we'd end up with the wrong answer. 

In step 2, if you look at the 2 right-most digits, you see they're actually sorted:
```
31 34 36 50 53 89
```

Step 3: 
We use 0 to represent missing digits. For example, in this round, 89 becomes 089 (for comparison purposes). This works out mathematically since $0 \mod{10}=0$
```
36 53 89 150 231 234
```

And we're done. We know to stop here because ...

**Time complexity is $O(d(n+k))$** where d is the most digits any element in the input array has. 
This is logical since we have d steps (as many as there are digits), and for each step we do a counting sort, which has a time complexity of $O(n+k)$. Recall that $k$ is the range of integers we're sorting, and in each step of radix sort, there are only 10 possible values: 0-9. So $k=10$
