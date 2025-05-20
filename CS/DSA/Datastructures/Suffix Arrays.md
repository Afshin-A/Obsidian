`text='AZAZA`

List all prefixes and the index at which they start

| Index | Prefix |
| ----- | ------ |
| 4     | A      |
| 3     | ZA     |
| 2     | AZA    |
| 1     | ZAZA   |
| 0     | AZAZA  |
Sort them lexicographically 

| Sorted Index | Prefix |
| ------------ | ------ |
| 4            | A      |
| 2            | AZA    |
| 0            | AZAZA  |
| 3            | ZA     |
| 1            | ZAZA   |
The list of sorted indices is referred to as the **suffix array**. 

| Sorted Index |
| ------------ |
| 4            |
| 2            |
| 0            |
| 3            |
| 1            |

# Longest Common Prefix, LCP

| Sorted Index | LCP | Prefix |
| ------------ | --- | ------ |
| 4            | 0   | A      |
| 2            | 1   | AZA    |
| 0            | 3   | AZAZA  |
| 3            | 0   | ZA     |
| 1            | 2   | ZAZA   |
It is the number of prefix characters that each element in the prefix array shares with the element before. LCP for the first element is always undefined (represented as 0) 


| LCP |
| --- |
| 0   |
| 1   |
| 3   |
| 0   |
| 2   |

# Number of Unique Substrings 

How many substrings are there in a string of length `n`?


```
  z
 /
y
 \
  x
    z
   /
  x
 /
y
```