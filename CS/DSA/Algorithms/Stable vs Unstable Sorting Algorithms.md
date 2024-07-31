A stable sorting algorithm is one that keeps the __relative order__ of equal elements in the collection we are sorting. What do we mean by relative order? For instance, if we have:
$$
A=\{5,8_1,9,8_2,3\}
$$
then the first 8 must appear before the second 8. 
$$
A_\text{sorted} = {3,5,8_1,8_2,9}
$$
For many applications, equal elements are considered equal. End of story. For others, not so much.

```
Input:

how much wood would woodchuck chuck if woodchuck could chuck wood

Output:

how       1
much      1
wood      2
would     1
woodchuck 2
chuck     2
if        1
could     1
```
___
```
First pass, sorted lexicographically:

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