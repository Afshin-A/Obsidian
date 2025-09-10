These notes are based on *[Select One Star](https://selectstarsql.com/)* book, which uses a database that keeps track of 

SQL is a specification. Every DBMS (database management system) that adopts SQL works differently under the hood and may use different names for functions and keywords. One such example is `PostgreSQL`, a relational DBMS that builds more features on top of SQL. In addition, we use a tool named `PgAdmin` that provides us with a GUI to interact with our databases.

These are three different ways of how many inmates had a last statement
```sql
SELECT COUNT(CASE WHEN last_statement IS NULL THEN 1 
			ELSE NULL END)
FROM executions

-- worst time complexity 
-- because it goes through the table twice
SELECT COUNT(ex_number) - COUNT(last_statement) 
FROM executions

-- best time complexity
-- it first narrows down the query, then applies the aggregate function COUNT
SELECT COUNT(ex_number) 
FROM executions 
WHERE last_statement IS NULL
```

```SQL
-- average length of text
SELECT AVG(length(last_statement)) from executions
```

The `count` function does not *count* `null` values. It only counts non-null values.  So in the following, instead of 1, we could have any non-null value and it will be counted once:
```sql
SELECT COUNT(CASE WHEN last_statement IS NULL THEN 1 ELSE NULL END)
```
We could also achieve the same results if we rewrite this query using the `sum` aggregate function as follows:
```sql
SELECT SUM(CASE WHEN last_statement IS NULL THEN 1 ELSE 0 END)
```

Aggregate functions are called last
 



The DISTINCT keyword only returns unique results
```SQL
SELECT DISTINCT county from executions 
```


Here we find the ratio of the number of times the word (or variation of) 'innocent' is used in the last_statement column to all entries of the executions table
```SQL
SELECT 100. * COUNT(CASE WHEN
			 last_statement LIKE '%innocent%'
			 THEN 1 ELSE NULL END) / COUNT(*) 
			 AS 'Percentage of Claimed Innocence'
FROM executions
```

# GROUP BY \<column\>, \<column\> ...


This keyword creates buckets for each distinct value found in the given column. It creates a sub table for each value. We can run aggregate functions for these tables.

Suppose we are grouping by two columns. First, SQL will create groups based on the values of the first group. Then, within each of these groups, SQL will create groups based on the secondary values. 
### Buckets created:

- **Harris**
    - [Row 1] John Smith, 2020-01-01
    - [Row 2] Maria Lopez, 2021-05-10
- **Dallas**
    - [Row 3] James Taylor, 2019-07-12
    - [Row 5] Alice Green, 2018-12-05
- **Travis**
    - [Row 4] Susan Brown, 2022-03-22

```SQL
SELECT county, COUNT(*) AS total
FROM executions
GROUP BY county;
```

Results:

| county   | total |
| -------- | ----- |
| Anderson | 4     |
| Aransas  | 1     |
| Atascosa | 1     |
| ...      | ...   |

We can even group by conditions
```SQL
SELECT
  last_statement IS NOT NULL AS has_last_statement,
  COUNT(*)
FROM executions
GROUP BY has_last_statement
```



# Order of operation

`FROM < WHERE < GROUP BY < aggregation functions < HAVING`

return the number of executed prisoners 50 or above for each county
```SQL
SELECT county, COUNT(*)
FROM executions
WHERE ex_age >= 50
GROUP BY county
```


# Order of writing
SELECT
AGGREGATION FUNCTIONS
FROM 
WHERE 
GROUP BY
HAIVNG
ORDER BY (DESC)

`WHERE` cannot be used with aggregate functions because it is performed before. If we want to impose conditions based on the results of aggregate functions, we use the `HAVING` clause.

Suppose we want to return the number of executed prisoners who were 50 or older for each county, but only if the count was more than 1.
This can't be done with `WHERE` because it's executed before the aggregate function `COUNT(*)` is. 

```SQL
SELECT county, COUNT(*)
FROM executions
WHERE ex_age >= 50
GROUP BY county
HAVING COUNT(*) >= 2
```


# Multiple Queries in 1

This approach is efficient when the inner query is independent of the outer query because the SQL engine caches the static results.
But when the two are correlated, then the inner query gets called for every group. 


```SQL
SELECT first_name, last_name
FROM executions
WHERE LENGTH(last_statement) =
    (SELECT MAX(LENGTH(last_statement))
     FROM executions)
```

The inner query `SELECT MAX(LENGTH(last_statement)) FROM executions` just returns the length of the longest last inmate statement. The condition 

Another example:
Here we find the percentage of the executed inmates by county 
```SQL
SELECT
  county,
  100.0 * COUNT(*) / (SELECT COUNT(*) FROM executions)
    AS percentage
FROM executions
GROUP BY county
ORDER BY percentage DESC
```

# `ORDER BY`
When given no arguments, it orders the queries in an ascending order. However, we can say `ORDER BY <column> DESC` to make the query results in a descending order.


# JOIN 

## `INNER JOIN`
Joins two tables to create a new table. Rows from each table are joined to form a new row when there's a match between two values in those columns. We typically match a primary key from one table with a foreign key in another.

```SQL
SELECT *
FROM customer
JOIN event
ON customer.customer_id = event.customer_id
```

```
customer
 customer_id | name   | address 
-------------+--------+---------
           1 | Afshin | 5914 Br 
           2 | Sepide | 3108 Cr
           3 | Armin  | 5914 Br

event
 event_id | customer_id | action 
----------+-------------+----------
      101 | 1           | LOGIN 
      102 | 1           | LOGOUT
      103 | 2           | VIEW PAGE

query table
 customer_id | name   | address | event_id | customer_id | action
-------------+--------+---------+----------+-------------+-----------
           1 | Afshin | 5915 Br | 101      | 1           | LOGIN
           1 | Afshin | 5915 Br | 102      | 1           | LOGOUT
           2 | Sepide | 2108 Cr | 103      | 2           | VIEW PAGE
```
`customer_id` is a primary key in the table `customer` and a foreign key in the table `event`.

Can create multiple rows if there are duplicate data

## `LEFT JOIN`
In this joining method, all rows form the left table are matched with rows from the right table. If a row doesn't match anything from the right table, then the right portion of the table becomes `NULL`
```
query table
 customer_id | name   | address | event_id | customer_id | action
-------------+--------+---------+----------+-------------+-----------
           1 | Afshin | 5915 Br | 101      | 1           | LOGIN
           1 | Afshin | 5915 Br | 102      | 1           | LOGOUT
           2 | Sepide | 2108 Cr | 103      | 2           | VIEW PAGE
           3 | Armin  | 5914 Br | NULL     | 3           | NULL
```

## `RIGHT JOIN`
This is just the opposite of `LEFT JOIN.` But it is rare because any `RIGHT JOIN` can be rewritten as a `LEFT JOIN`.

## `FULL JOIN

A combination of `LEFT JOIN` and `RIGHT JOIN`
First it performs a LEFT JOIN. Then it performs a RIGHT JOIN
![[Pasted image 20250603194954.png]]
https://youtu.be/Yh4CrPHVBdE

## `UNION` and `UNION ALL`

```SQL
SELECT age 
FROM teacher
UNION
SELECT age
FROM student
```


# Postgress
## Types
### `VARCHAR`
Defines a string with varying length. You can define the max length. Ideal for usernames, passwords, etc..
```SQL
email VARCHAR(255) UNIQUE NOT NULL
```

### `ENUM`

```sql
CREATE TYPE roles AS ENUM('employee', 'admin', 'owner');
role roles NOT NULL DEFAULT 'employee'; 
```

```sql
CREATE TABLE users (
	role ENUM('employee', 'manager', 'admin') NOT NULL DEFAULT 'employee'
);
```

### `TEXT`
Variable length character string (no limit?)
```sql

```