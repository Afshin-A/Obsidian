These notes are based on *[Select One Star](https://selectstarsql.com/)* book, which uses a database that keeps track of 

SQL is a specification. Every DBMS (database management system) that adopts SQL works differently under the hood and may use different names for functions and keywords. One such example is `PostgreSQL`, a relational DBMS that builds more features on top of SQL. In addition, we use a tool named `PgAdmin` that provides us with a GUI to interact with our databases.

These are three different ways of how many inmates had a last statement
```sql
SELECT * FROM table_name LIMIT 3
SELECT column_name_1, column_name_2 FROM table_name LIMIT 3
SELECT 51.0/2 , 51%2, 51/2
select first_name, last_name, ex_age from executions where ex_age <= 25
```


### `LIKE` and wildcards
```sql
SELECT first_name, last_name, ex_number FROM executions WHERE first_name = 'Raymond' AND last_name LIKE '%Landry%'
```

### `Count` 
```sql
SELECT COUNT(*) FROM executions
SELECT COUNT(last_statement) FROM executions
```

### CASE WHEN
Run if-else statement on each row, then return a value for each row
```sql
select case when last_statement is null then 1 else 0 end 
from executions 
```
if `last_statement` is `null`, return 1 for that row, else return 0

We can then call an **aggregate** function on the resulting table.

## Aggregate and Scalar functions
**Aggregate functions** are executed over a range of columns, and return a single value. Ex. `avg`, `count`, `min`, `max`
Aggregate functions are called last

**Scalar functions** are executed for each row, and return a value for each row. Ex. `length`

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

The `count` function *does not count* `null` values. It only counts non-null values.  So in the following, instead of 1, we could have any non-null value and it will be counted once:
```sql
SELECT COUNT(CASE WHEN last_statement IS NULL THEN 1 ELSE NULL END)
```
We could also achieve the same results if we rewrite this query using the `sum` aggregate function as follows:
```sql
SELECT SUM(CASE WHEN last_statement IS NULL THEN 1 ELSE 0 END)
```


 


## The DISTINCT keyword
It's used along size a column name to return a sub-table that only contains unique results
```SQL
SELECT DISTINCT county from executions 
```

Average executions per county = total number of executions / number of distinct counties 
```sql
select count(ex_number) * 1.0 / count(distinct county) from executions
```


## Combining aggregate functions and case-when statement
Let's say we want to count all rows that have some sort of property. First, we need to build modify the table. We use the case-when statement to change the value of each row, then we can call the aggregate an aggregate function on the modified table.   
Here we find the ratio of the number of times the word (or variation of) 'innocent' is used in the `last_statement` column to all entries of the executions table
```SQL
SELECT 100. * COUNT(CASE WHEN
			 last_statement LIKE '%innocent%'
			 THEN 1 ELSE NULL END) / COUNT(*) 
			 AS 'Percentage of Claimed Innocence'
FROM executions
```

The following does not work because the `where last_statement like "%innocennt%"` trims the table, so when we call `count(*)`, we're counting the already trimmed table, not the whole table
```sql
select 1.0 * count(last_statements) / count(*) from executions where last_statement like "%innocent%"
```

**The where clause happens before grouping and aggregating**
# GROUP BY \<column\>, \<column\> ...
This keyword creates buckets for each distinct value found in the given column. It creates a sub table for each value. We can run aggregate functions for these tables.
```SQL
SELECT county, COUNT(*) AS total
FROM executions
GROUP BY county;
```
The result would look something like this:

| county   | total |
| -------- | ----- |
| Anderson | 4     |
| Aransas  | 1     |
| Atascosa | 1     |
| ...      | ...   |

**Suppose we are grouping by two columns.**
First, SQL will create groups based on the values of the first group. Then, within each of these groups, SQL will create groups based on the secondary values. 
### Buckets created:
- **Harris**
    - [Row 1] John Smith, 2020-01-01
    - [Row 2] Maria Lopez, 2021-05-10
- **Dallas**
    - [Row 3] James Taylor, 2019-07-12
    - [Row 5] Alice Green, 2018-12-05
- **Travis**
    - [Row 4] Susan Brown, 2022-03-22



We can even group by conditions
```SQL
SELECT
  last_statement IS NOT NULL AS has_last_statement,
  COUNT(*)
FROM executions
GROUP BY has_last_statement
```

More examples:
Return the number of executed prisoners 50 or above for each county:
```sql 
select county, sum(case when ex_age >= 50 then 1 else 0 end)
from executions 
group by county
```
First create the sub-tables, then for each sub-table, we run the aggregate function


```sql
select county, count(*)
from executions
where ex_age >= 50
group by county
```
First, the where clause creates a new table. Then, the group by divides it into sub-tables that share the same value for county. Then, we run the count aggregate function for each.
# Order of operation
` aliases < FROM < WHERE < GROUP BY < aggregation functions < HAVING < SELECT < ORDER BY < `

1. Evaluate aliases and expressions
2. Import the table
3. Narrow down the table to meet WHERE condition
4. Group table into sub-tables 
5. Run aggregate function for each group
6. Filter the results of aggregate function for each sub-group
7. Generate table
8. Sort the results
9. 

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

# Having
**`WHERE` cannot be used with aggregate functions because it is performed before**
So if we want to further filter the results of an aggregate function, we can use the *having clause*


Suppose we want to return the number of executed prisoners who were 50 or older for each county, but only if the count was more than 1.
This can't be done with `WHERE` because it's executed before the aggregate function `COUNT(*)` is. 

```SQL
SELECT county, COUNT(*) as "number of executions"
FROM executions
WHERE ex_age >= 50
GROUP BY county
HAVING COUNT(*) >= 2
```

1. The where clause creates a table where all ages are >= 50
2. We group the results by county 
3. We aggregate function `count` is called on each group. The result is stored in a variable for each sub-group.
4. The having clause filters the groups based on that variable. Any group with a count of less than 2 is eliminated.
5. Finally, the SELECT clause creates the columns for each group. 


```sql
select county from executions
group by county
```
This example has a group by, but there is no aggregate function. So instead, the SQL engine returns the unique county values.
# Nested Queries 
Clauses like Group by and where take in the database and change through a pipeline, until the final result is achieved. What if our query needs an aggregate value from the entire, ungrouped, unfiltered table? Well, we could run two separate queries. 
We can also nest queries within each other. 
```SQL
SELECT first_name, last_name
FROM executions
WHERE LENGTH(last_statement) =
    (SELECT MAX(LENGTH(last_statement))
     FROM executions)
```
The inner query `SELECT MAX(LENGTH(last_statement)) FROM executions` just returns the length of the longest last inmate statement.

*This approach is efficient when the inner query is independent of the outer query because the SQL engine caches the static results.*
*But when the two are correlated, then the inner query gets called for every group.* 

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

# `ORDER BY <column>` 
We can sort the final results in a descending or ascending order. The default is ascending, which can be omitted: `... order by percentage`
 However, if we want the results in a descending order, we would have to say: `... order by desc`
 
 
# JOIN 
It's often faster and safer to perform a join operation on two tables and then do the query as normal, than performing two separate queries and then combining the results.

There are different types of join, and they all differ in how the handle mismatched rows. 
- Suppose there that a row from table1 does not match any rows from table2. **Then inner** join will drop that row from the final table. 
- If we use **left join**, the row will be stayed in and the missing columns from table 2 will have null value
- A row from table2 might not match with any rows from table 1. **Right join** will keep that row in and fill the columns from table 1 with null.
- **Outer join** is the combination of left join and right join. Any rows that do not have a matching row will stay in the table, but missing columns are instead null.
The syntax is as follows:
```sql
SELECT *
FROM customer
JOIN event
ON customer.customer_id = event.customer_id
```
Think of `FROM customer JOIN event ON customer.customer_id = event.customer_id` as one operation. This is the line that creates a new table. The remaining operations may continue as normal:
```sql
SELECT count(*) as "total events"
FROM customer
JOIN event
ON customer.customer_id = event.customer_id
where ... 
```
## `INNER JOIN`
This is the default join operation.
Joins two tables to create a new table. Rows from each table are joined to form a new row when there's a match between two values in those columns. We typically match a primary key from one table with a foreign key in another.
Let's say we want to join the customer table with the events table based on the customer_id. 
If there is no matching event for the customer, then no data shows in the table. Neither from the customer, nor the event.
The c
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
           2 | Sepid  | 3108 Cr
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
           2 | Sepid  | 2108 Cr | 103      | 2           | VIEW PAGE
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

`RIGHT JOIN`  is just the opposite of `LEFT JOIN.` But it is rare because any `RIGHT JOIN` can be rewritten as a `LEFT JOIN` (?)
## `FULL JOIN
A combination of `LEFT JOIN` and `RIGHT JOIN`. 
First it performs a LEFT JOIN. Then it performs a RIGHT JOIN
![[Pasted image 20250603194954.png]]
https://youtu.be/Yh4CrPHVBdE

## Natural join
A NATURAL JOIN in SQL is a type of join that automatically combines tables based on columns that share the same name and compatible data types in both tables. Unlike other join types like INNER JOIN, you do not explicitly specify the join condition using an `ON` clause. Instead, SQL implicitly identifies and uses all common columns for the join.
# Self Joins
Join requires two tables. Sometimes, the second table is a modified version of the first table. In a sense, we're merging a table with itself. This is called a self join.

For example, suppose we have a table that lists all the executions in the state of Texas. We want to find out the top 5 longest delays between two executions. 
We need to relate an execution with its preceding execution in a new column named `last_ex`. Take a look at the table:
```
| ex_number | ex_date | 
| 1         | date1   |
| 2         | date2   | 
| 3         | date3   | 
| 4         | date4   | 
```
In order to match 1 with `date2` we need to either move 1 down by 1 row, or move `date2` up by 1 row. 
The first option is pretty easy to do:
```sql
select ex_number+1 as ex_number, ex_date from executions
```
This creates a new table that we are now ready to merge with the original table as follows:
```sql
select executions.ex_number, executions.ex_date, julianday(executions.ex_date) - julianday(last_executions.last_ex_date) as delay
from executions join (select ex_number+1 as ex_number, ex_date as last_ex_date from executions) last_executions
on executions.ex_number = last_executions.ex_number
order by delay desc
limit 5
```
Dates in SQL can be represented in many different formats. In this case, they're represented by a simple string (e.g. `yyyy-mm-dd`) The `julainday` is a function in SQLite that takes in a date and returns a number of days that are past some historical event. It doesn't really matter because we're interested in the difference between two dates, which remains the same (since we convert the dates the same way).

- We can give the newly created table an alias: `(select ex_number+1 as ex_number, ex_date as last_ex_date from executions) last_executions`
- We need to give `ex_number+1` an alias: `ex_number+1 as ex_number`. That's because we need to refer to the column `ex_number+1` later, and we can't use `ex_number+1` is not a valid name in programming languages, and SQL is no exception.
- When two tables have the same variable names, we need to use the table name to refer to the variables to avoid ambiguity and compiler errors. That's why you see things like `select executions.ex_number, executions.ex_date` ...

Here's a shorter way to write the same query as above:
```sql
select executions.ex_number, executions.ex_date, julianday(executions.ex_date) - julianday(last_executions.ex_date) as delay
from executions join executions last_executions on executions.ex_date = last_executions.ex_date+1
order by delay desc
limit 5
```
In this approach, we copy the executions table and under a name name: `from executions join executions last_executions`.
But then, on the condition, we connect/merge ex_date with the next row: `executions.ex_date = last_executions.ex_date+1`
![[PXL_20250919_044955247~2.jpg|400]]



## `UNION` and `UNION ALL`

```SQL
SELECT age 
FROM teacher
UNION
SELECT age
FROM student
```


# PostgreSQL
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

# Offset - Limit Pagination
```sql
select * from people
order by id
limit 10
offset 280
```
This query will construct a table. Then, it will skip 280 rows and return the next 10 rows after that.

This method is sometimes used for pagination in APIs. Suppose a user wants to view the data in their client as a table. Instead of returning and displaying a huge table, we can lazy load each page. If each page fits only 10 rows, then we return 10 rows at a time with each request. Going to the next page sends out a request for the next 10 pages.
The more general query would look like this:
```sql
select * from table 
order by id
limit page_size
offset (page_number)*page_size
```
The column we order by needs to be *deterministic*. That means that two queries must return the exact same results. Suppose we order a query by name. If 10 people have the same name, there is no guarantee in what order the people will be displayed. Instead we must order by something unique like their id in addition to their name.
But **offset pagination is not efficient** because we would have to calculate the next page--construct a table, start at row 1 and go down by the offset, and return that sub-set--EVERY TIME a request comes in.

# Cursor based pagination
The server sends back the last id, and the client sends it back so the server may resume searching from there 

Let's say we want to order by `first_name` and by `id`. In case there are duplicates, we would sort duplicate names by `id`, which is unique. 
```
id   first_name
1    Aaron
5    Aaron
```
We send to the server  `{first_name=name,id=x`. The database checks for `where first_name = name and id > x`
If there there are no more entries for the given `name`, then we need to move on  
```sql
select * from people 
where (first_name = name and id > x) or (first_name > name)
limit 10
```


# **ACID** compliance
PostgreSQL is ACID compliant:
- **A**: Atomicity. All or nothing. An operation either succeeds or fails as a unit. If one part of an operation fails, the entire thing fails.
- **C**: Consistency. The database is always brought to a valid state. DBSM has strict data validation and integrity rules.
- **I**: Isolation. Concurrent transactions do not interfere with each other.
- **D**: Durability. Once an operation is successfully complete, changes are permanent.

# SQL Order of execution

1. From
2. Join 
3. On
4. Where
5. Group by
6. Aggregate Functions
7. Having
8. Order By
9. Limit
10. Select

<iframe width="560" height="315" src="https://www.youtube.com/embed/BHwzDmr6d7s?si=zgjkIWSOXHh8SZqA" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
