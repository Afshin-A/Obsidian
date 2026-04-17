
# Normalization
These are basically a series of rules that a database schema needs to follow in order to *avoid inconsistencies and redundancies within our data*. Otherwise, we may end up with data that is logically invalid, contradictory, or inconsistent. 

While normalization is good practice, it creates a lot of tables that force our queries to have to use lots of JOIN operations, which can sometimes be inefficient.

There are 5 normalization levels:

#### First normal form (1NF)
- Can't use rows ordering in a table to sort attributes because rows are not stored in order in a page.
- Can't mix in data types in a column. Attribute type is constant
- Every table must have a primary key
- Cannot have **repeating groups**, meaning you cannot store several relevant values (like a list, basically) in a cell together, and you cannot have multiple columns that are basically the same thing:

==The primary key columns are highlighted yellow in all examples==

| ==Player_ID== | Inventory                      |
| ------------- | ------------------------------ |
| 1             | "Sword, Shield, Potion, Armor" |
❌

| ==Player_ID== | Quantity_1 | Quantity_2 | Item_Type_2 | ... |
| ------------- | ---------- | ---------- | ----------- | --- |
| 1             | 5          | 1          | "Potion"    |     |
❌

Obviously you could end up with many rows. You will have inconsistencies. And, how are you going to query this table?

Instead, you would have:

| ==Player_ID== | ==Item_Type== | Quantity |
| --------- | --------- | -------- |
| 1         | "Sword"   | 5        |
| 1         | "Potion"  | 1        |
✅
But there is a problem here. **Primary keys must be unique for each row**. So for the table above, we use two columns as our primary key, in what's called a **composite key**. The combination of `player_id` and `item_type` for each row is unique.
#### 2NF
> Each non-key attribute must depend on the primary key. If it's a composite key, then it must depend on the entire key.

If our table has a composite primary key (i.e. the primary key is consisted of two or more attributes), then we can't how a row that depends only on a part of the primary key; no, it must depend on the entire primary key. Otherwise, that attribute doesn't belong on that table, and should be moved somewhere else. If not, we can end up with redundant and inconsistent data.

| ==Player_ID== | ==Item_Type== | Quantity | Player_Rating |
| ------------- | ------------- | -------- | ------------- |
| 1             | "Sword"       | 5        | Intermediate  |
| 1             | "Potion"      | 1        | Intermediate  |
❌

`Player_Rating` is being repeated twice. 
Suppose the rating changes from `Intermediate` to `Advanced`. Changing row 1 doesn't automatically change row 2. If we forget/fail to manually change the rating in every column, then we'll have inconsistent data.
Clearly, the `Player_Rating` column doesn't belong on this table.

| Player_ID | Player_Rating |
| --------- | ------------- |
| 1         | Intermediate  |
| 2         | Advanced      |
| ...       | ...           |
✅
#### 3NF
- Non-key attributes cannot depend on each other. Attributes can only depend on the primary key.
This is because if we update one column, the column it depends on must also be updated. If we forget or other wise the transaction fails, it would lead to inconsistencies. So it's best to move the related columns into their own table.  
#### 4NF
>Multi-value dependencies in a table can only depend on the key (the whole key)

Suppose we have a table like this. Suppose each model has a set of available colors. This is colored a **multi-valued dependency**:
$\text{\{Model\}}\twoheadrightarrow\text{\{Color\}}$

Another multi-valued dependency in this table exists between Model and Style. Each model has a set of styles:
$\text{\{Model\}}\twoheadrightarrow\text{\{Style\}}$

Now suppose all our models will be available in a new color. We would have to create num of models times num of styles new rows to accommodate for all combinations. And if we forget one, we make one combination unavailable. 

| ==Model== | ==Color== | ==Style== |
| --------- | --------- | --------- |
| Tweety    | Yellow    | Bungallow |
| Tweety    | Yellow    | Duplex    |
| Tweety    | Blue      | Bungallow |
| Tweety    | Blue      | Duplex    |
| Metro     | ...       | ...       |
❌

As before, the solution is to separate the tables

| ==Model== | ==Color== |
| --------- | --------- |
| Tweety    | Yellow    |
| Tweety    | Blue      |
| ...       | ...       |
✅

| ==Model==  | ==Style==     |
| ------ | --------- |
| Tweety | Bungallow |
| Tweety | Duplex    |
| ...    | ...       |
✅
And by the way, yes, you can have a table with only the primary key (composite, in this case).

#### 5NF
>A table (that is in 4NF) cannot be describable as the logical results of joining some other tables together.

If it can be divided, it should be divided. 

#### Summary
The first 3 forms can be summarized as follows:
**Every non-key attribute should depend on the key, the whole key, and nothing but the key.**
In most cases, this is enough to normalize the table.

##### Source
```embed
title: "Learn Database Normalization - 1NF, 2NF, 3NF, 4NF, 5NF"
image: "https://i.ytimg.com/vi/GFQaEYEc8_8/maxresdefault.jpg"
description: "An easy-to-follow database normalization tutorial, with lots of examples and a focus on the design process. Explains the \"why\" and \"how\" of normalization, an..."
url: "https://youtu.be/GFQaEYEc8_8"
favicon: ""
aspectRatio: "56.25"
```

# Denormalization
While normalization is good practice, it creates a lot of tables that force our queries to have to use lots of JOIN operations, which can  be inefficient. 
There are always tradeoffs. 
Sometimes, we may have to deliberately include redundant or precomputed data in our tables for faster queries. That's called denormalization. 