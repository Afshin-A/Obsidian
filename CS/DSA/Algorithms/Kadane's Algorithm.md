A dynamic programming algorithm used for solving the maximum subarray problem.

### The maximum subarray problem
Given an array, find the sum of the subarray with the largest sum. 

Example:
```ts
[-2, 1, -3, 4, -1, 2, 1, -5, 4]
```

We need two variables:
- `current_sum` keeps track of the sum of the current subarray
- `max_sum` keeps track of the greatest sum seen so far


If the current element is larger than the current element + `current_sum`, that means the preceding elements are actually holding back the sum, so we can lose them and start a new subarray. 


```ts
for(let i = 1; i < elements.length; i++) {
}
```







<center><iframe width="560" height="315" src="https://www.youtube.com/embed/lq8KOs1Ujas?si=cfNlNaqa2PwCJeEr" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe></center>
