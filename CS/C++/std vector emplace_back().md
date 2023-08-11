```c++
std::vector::push_back() vs std::vector::emplace_back()
```

Capacity Vs. Size
Capacity is the maximum potential number of elements an array can hold
Size is the actual number of  elements currently in the array 

```c++
std::vector<int> vec; // 0 capacity and size
```


```c++
std::vector<int> vec(3) // size is 3, so the vector looks like: 0, 0, 0
// default constructor for int gets called 3 times
```


```c++
std::vector<int> vec; // 0 capacity
vec.reserve(3) // sets the capacity to 3, but size is 0
```

Vectors are dynamic, so each time the capacity is reached, the vector will internally reallocate all its elements to a new and larger array (since vectors use arrays internally). So in conclusion, if you know the capacity of the array from the start, it's a good idea to set it right after initialization to avoid unnecessary copying of elements.

`push_back`
This method adds a copy of the argument to the end of the array it is called upon. So, it calls the copy constructor, creates a temporary object, which is then removed when the vector is destroyed.\

`emplace_back` works similarly to `push_back`, but it doesn't copy. it can take the arguments for the constructor of the object and directly insert a new object into the back of the vector, without copying. 