
```embed
title: "Database Indexing for Dumb Developers"
image: "https://i.ytimg.com/vi/lYh6LrSIDvY/maxresdefault.jpg"
description: "This video explains what happens under the hood when indexing a database and explains why it can lead to performance benefits."
url: "https://www.youtube.com/watch?v=lYh6LrSIDvY"
favicon: ""
aspectRatio: "56.25"
```

# How A [[B-Tree]] is used for Indexing Databases

Essentially you have a B-tree that has two things in each element: a key (from the column we created the index by) and a value (the location of data on disk—a tuple containing the page id and an offset value telling us where the is on the block).

### Rules for picking a column for indexing 
A column that we frequently use in the queries

