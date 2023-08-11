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
    
    for i in range(len(unsorted_list)):
        smallest_index = i
        for j in range(i+1, len(unsorted_list)):
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
def swap_list_elements(ls: list, index_a: int, index_b: int):
    ls[index_a], ls[index_b] = ls[index_b], ls[index_a]


def bubble_sort(unsorted_list: list):
    for i in range(len(unsorted_list)):
        for j in range(len(unsorted_list)-i-1):
            if unsorted_list[j] > unsorted_list[j+1]:
                swap_list_elements(unsorted_list, j, j+1)
    return unsorted_list
```


# Insertion Sorting
Insertion sorting, in a way, works the opposite of bubble sort: for each iteration, it goes through the list and moves elements to the left if they're smaller than the previous elements.

```python
def insertion_sort(unsorted_list: list):
	# start at second element
    for i in range(1, len(unsorted_list)):
        j = i
        while j > 0 and unsorted_list[j] < unsorted_list[j-1]:
            swap_list_elements(unsorted_list, j, j-1)
            j -= 1
    return unsorted_list
```


# Merge Sorting


# Quick Sorting
