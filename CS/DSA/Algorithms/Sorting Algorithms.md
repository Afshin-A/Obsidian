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

The time complexity of the bubble sort algorithm, at the worst case, is $O(n^2)$.
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
