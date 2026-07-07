**awk** is a scripting language based on C, created in 1977. Today, it's used as a tool to efficiently search text files by treating them as tables. A ==popular use is for searching through application logs== since most backends define a data type for logs. Therefore, all log entries would follow the same format and related fields fall on the same column.
The #awk command follows a format:

```bash
awk 
'
	BEGIN { action }
	condition { action }
	END { action } 
'
filename.extension
```
*Condition* defines the rule for whether a row should be included. It can be regex or conditional statements. More in the examples below.
`BEGIN` and `END` (must be capitalized) signify codes that execute before and after reading the file respectively.

##### Example 1: Counting the total number of HTTP 500 errors
```bash
awk '
BEGIN { error_count = 0 }
$5 == 500 { error_count++ }
END { print "Total Server Errors:", error_count }
' api_logs.log
```
**Note**: ==awk automatically initializes variables to default values==, so we don't need to initialize them in `BEGIN`
##### Example 2: Counting the total response time for all successful (200) requests
```bash
awk '
$5 == 200 { 
	total_time += $6
	count++ 
}
END { 
	if (count > 0) {
		print "Average 200 OK response time:", total_time / count, "ms"
    } else {
      print "No 200 OK requests found."
    }
}
' api_logs.log
```
##### Example 3: Counting how many times each endpoint was called
```bash
awk '
{ 
  counter[$4]++
}
END {
  for (endpoint in counter) {
    print endpoint, counter[endpoint]
  }
}
' api_logs.log
```

  
While awk has built in functions for sorting and filtering, ==it is significantly more efficient== to use specialized UNIX tools like *grep* and *sort*. The larger the files, the more apparent this becomes. The work flow is searching through directories for files with `grep`, searching in the files with `awk`, then sorting the results using the `sort` utility. 

##### Example 4: Calculating the total response time for all requests made by the IP address 192.168.1.101 across several log files
```bash
grep "192.168.1.101" | # pipe results to awk
awk '
$1 == 192.168.1.101 { total_time += $6 } # Assume first column is IP address. Double check IP address matches for added security
END { print "Total response time:", total_time }
'
```



Example 5: Deeper data analysis using multi-dimensional arrays in gawk (GNU awk)