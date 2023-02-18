Makes list initialization very quick.

```python
my_inefficient_list = []  
for i in range(10):  
    my_inefficient_list.append(i)  

my_efficient_list = [i for i in range(10)]  
```

# Nested List Comprehension
```python
nested_list_1 = [[i for i in range(10)] for j in range(10)]

nested_list_2 = []

for (i in range(10)):
	nested_list_2.append([])
	for (j in range(10)):
		nested_list_2[i].append(j)
```


```python
range(10) # 0, 1, 2 ... 9
range(2, 10) # 2, 3, ... 9
range(2, 10, 3) # 2, 5, 8  goes up in increments of 3
```