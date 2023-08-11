```c++
int a = 20;
int b = 30;
a = a + b;
b = a - b; // b now equals a;
a = a - b;
```

You can visualize this process by using shapes/objects, like an apple and an orange.
They say you can't add apples and oranges. Well, guess what! You can in programming--As long as they're of the same **type** (fruit) and have an `operator+` overloaded.