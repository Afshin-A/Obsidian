A stable sorting algorithm is one that keeps the __relative order__ of equal elements in the collection we are sorting. What do we mean by relative order? For instance, if we have:
$$
A=\{5,8_1,9,8_2,3\}
$$
then the first 8 must appear before the second 8. 
$$
A_\text{sorted} = {3,5,8_1,8_2,9}
$$
For many applications, equal elements are considered equal. For example, a 1 is a 1. End of story. 
But for other scenarios, the order matters. This is especially true for more complex objects like tuples. It's also true if the position in the array has implicit properties. For example, let's say our array stores customer order objects. Objects added last show later orders. Say we sort the array based on last name, "Alan Smith" comes after "Joe Smith". A stable algorithm ensures that after sorting, Alan will always come after Joe. 

Here's another example. Given our input:
```
how much wood would woodchuck chuck if woodchuck could chuck wood
```
the output is a counter for the words in the input:
```
how       1
much      1
wood      2
would     1
woodchuck 2
chuck     2
if        1
could     1
```
We then sort the tuples lexicographically:
```
(chuck, 2)
(could, 1)
(how, 1)
(if, 1)
(much, 1)
(wood, 2)
(woodchuck, 2)
(would, 1)
```

**Note: Order from previous output is not preserved.**
`chuck` was before `wood` above, but the ordering has changed.
```
Second pass, sorted by count using an unstable sort:

(wood, 2)
(chuck, 2)
(woodchuck, 2)
(could, 1)
(how, 1)
(if, 1)
(would, 1)
(much, 1)
```
___
If we instead use a stable sorting algorithm, we get:
```
Second pass, sorted by count using a stable sort:

(chuck, 2)
(wood, 2)
(woodchuck, 2)
(could, 1)
(how, 1)
(if, 1)
(much, 1)
(would, 1)
```

## Examples of Sorting Algorithms
### Stable
- Merge Sort
- Timsort
- Counting Sort
- Insertion Sort
- Bubble Sort
### Unstable
- Quicksort
- Heapsort
- Selection