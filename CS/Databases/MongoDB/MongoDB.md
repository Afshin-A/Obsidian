## Notes on Databases
DBMS – Databse Management System, is a program used to interact with the database. Examples include PostgreSQL.

### Relational Databases (SQL)
This database architecture uses **relations** (tables) to store data in an organized manner.
The rows of such a table are refered to as **tuples**, and can be thought of as object. Every tuple must have a unique primary key (in this case, `ID`). 
The columns represent **attributes** of the objects.

ID | Name | Academic_Program | Credits_Earned | Credits_Needed 
--- | --- | :---: | --- | --- 
1 | Afshin | CS | 80 | 40 
2 | Ram | Phys | 112 | 8

We can retrieve or manipulate data in a relational database via a **query** (a request). SQL (Structured Query Language) is the most common language for these tasks. Popular open-source DBMS applications are MySQL, PostgreSQL, and SQLite.

### Non-Relational Databases
Not structured. There is no rigid structure that dictates what type the type must be or how it should be stored. For example, in SQL, all entries in a column must be the same type, as you can see from the `Name` entry from the table above. In NoSQL, the data can be of any type. You can have a strnig in one row and an ineger in the next. Thus, no rigid structure.

NoSQL includes and is not only limited to SQL, so they're called **Not Only SQL** (NoSQL).
NoSQL stands for **not only SQL**. NoSQL also includes SQL because of how useful they are. 
SQL is a query language: relational (tables), rigid, structured.
NoSQL is consisted of different types of flexible, expandable, distributed (servers holding data can be all around the world, clusters, instead of just one machine) DBMSs
#### Key-Value Databases
Also called **key-value stores**
Basically a java map or a python dictionary
####  Column-based
What is the average number of credits earned by all students? Going by the relational database above, we would have to go through each row and extract the value for Credits_Earned. That means unnecessarily reading names, degrees, and other unrelated fields. 
What if, instead, we only consider the Credits_Earned column?
Column-based databases shine when answering questions like this. They use columns that are stored in separate files. Apache Cassandra is a popular example.
CQL - Cassandra Query Language
keyspace - a logical grouping of tables
`describe keyspaces;`

#### Document-Oriented Databses
Also called **document stores**. **MongoDB** is a popular DBMS for document stores.
These are a type of key-value databses. but the values are documents. the documents have metadata that define how data can be retrieved.
These documents are stored as JSON objects and can contain complex data, including other documents.


### JSON
Javascript object notation is a light way of storing and transfering data over the web. Every major programming language has modules for parsing JSON.
Example of JSON:
```json
{  
  "title": "Gattaca",  
  "release_year": 1997,  
  "is_awesome": true,  
  "won_oscar": false,  
  "flopped": null,  
  "actors": ["Ethan Hawke", "Uma Thurman", "Alan Arkin", "Loren Dean"],  
  "budget": 3.6e7,  
  "credits": {  
    "director": "Andrew Niccol",  
    "writer": "Andrew Niccol",  
    "composer": "Michael Nyman",  
    "cinematographer": "Sławomir Idziak"  
  }  
}
```
It is similar to a python dictionary or a java map. All the keys are strings. Values can be strings, numbers, booleans, null, lists, and other json objects.

### BSON
Stands for Binary JSON, and is used in the MongoDB DBSM.
MongoDB encrypts JSON into BSON, so it is not human readable.

### Schema 
Schema is the organization and structure of a database as whole. For example, in a SQL database, it could be the organization of different tables.

MongoDB documents can be 16 MB at most to prevent cluttering memory. MongoDB stores BSON objects directly into memory for speed, but this imposes limitations like document size.
**PyMongo** - Python driver for MongoDB
We such drivers it to communicate with the database. So the system would be layered as application-driver-database.
__mongoengine__ is an ODM for MongoDB. The system is layered as application-odm-driver-database.
**ODM** - Object Document Mapper, is ORM for NoSQL databases.
**ORM**, Object Relational Mapping,  is a software that internally uses a driver, but builds more functionality for users in working with databases, and also introduces object oriented programming elements.

Robo 3T (formely named Robomongo) is a GUI tool to visually view MongoDB databases. 
It claims to be free and open source, but requires account registration and personal details. Would not allow download unless you accept their cookies. Two words: Shove off.


DataStax DB, an online service that allows you to create NoSQL databases. It is built on Apache Cassandra and uses the Cassandra Query Language (CQL) to interact with the database.
The use of DataStax DBMS is optional; however, it allows us to explore all major NoSQL databse types.



## Installing and Using MongoDB and MongoShell (Ubuntu)
First start a local mongodb server:
```shell
sudo systemctl start mongod
```
Then start the mongo shell:
```shell
mongosh
```

```
sudo systemctl start mongod
sudo systemctl stop mongod
sudo systemctl restart mongod
sudo systemctl status mongod
```
A note for [installing mongoDB on ubuntu](https://www.mongodb.com/docs/manual/tutorial/install-mongodb-on-ubuntu/): Follow these steps, when [creating the configuration file](https://www.mongodb.com/docs/manual/tutorial/install-mongodb-on-ubuntu/#create-a-list-file-for-mongodb): 
replace `focal` in `echo "deb [ arch=amd64,arm64 ] https://repo.mongodb.org/apt/ubuntu focal/mongodb-org/6.0 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-6.0.list` with `jammy`, the codename for ubuntu 22 LTS


## MongoDB Compass
This is a GUI for interacting with MongoDB databses. 
I've already installed it on this machine (laptop 14)


## MongoDB Shell (mongosh)
In MongoDB, A document is basically a JSON object.
```
{
	"_id: ObjectId('621ff30d2a3e781873fcb663'),
	"name": "Saturn",
	"orderFromSun": 6",
	"hasRings": true,
	"mainAtmosphere": ["H2","He","CH4"],
	"surfaceTemperatureC": {
		"min": null,
		"max": null,
		"mean": -139.15
	}
}
```
A collection is a group of documents.
A database is a group of collections.

Note: A document can also contain a document. A access a sub-document field, we use the dot notation:
```
"surfaceTemperatureC.min"
```
**Note: the dot notation syntax requires to be surrounded by quotation mark**

### CRUD (Create, Read, Update, Delete) in MongoDB

#### Create
```
db.collection_name.insertOne(<document>)
db.collection_name.insertMany([<document>, <document>, ...])
```

#### Read
```
# Returns a list of all documents that have the given key and value
db.collection_name.find({key: value})
db.collection_name.find({key: {$eq: value}})

# Returns a list of all documents that have the given key with a value that is among the given list
db.collection_name.find({key: {$in: [value1, value2, ...]}})


# Returns a list of all documents that have the given key with a value that is greater than 10
db.collection_name.find({key: {$gt: 10}})

```
The comparison operators are:
```
$gt    # Greather than
$lt    # Less than
$gte   # Greater than or equal
$lte   # Less than or equal
```

Querying array elements
```
# If key is associated with an array or string value, then this command returns a list of all documents that have the given key and value. value can be standalone, or could be part of an array.
db.collection_name.find({key: value})

# We can ensure the query only checks for values inside arrays with combining the $elemMatch and $eq operators:
# In other words, this ensures key is an array
db.collection_name.find({key: {$elemMatch: {$eq: value}}})
```

```
 db.accounts.find({completed_transfers: {elemMatch: {$eq: 'TR617907396'}})
```

More examples:
Given the document,
```
{
_id: 1
items: [
	{
		name: "laptop"
		tags: ["stationary", "office", "general"],
		price: 828.99,
		quantity: 3
	}
],
customer: {
	gender: "M", 
	age: 65, 
	email:"kurt@gmail.com", 
	rating: 5
	}
}
```
the command, 
```
db.collection_name.find(
{
items:
	{
	$elemMatch:
		{
			name: "laptop",
			price: {$gt: 500},
			quantity: {$gte: 1}
		}
	}
})
```
translates to:
Inside the collection `collection_name`, finds all documents that have an array field named items, whose elements match the following specification:
```
name: "laptop",     # field name has value "laptop" 
price: {$gt: 500},  # field price has value > 500
quantity: {$gte: 1} # field quantity has value >= 1
```



console commands:
```
cls # clear console
db.getCollectionNames()   # lists the collections in the database
<query command>.limit(5) # limits a query result to 5 documents, for example
<query command>.pretty() # formats the query result

```

Logical operators
In a query, the `$and` operator means that a document must match all the given requirements to be returned
```
db.collection_name.find({$and: [{<expression>}, {<expression>}, ...])

# shorthand way of writing the command above:
db.collection_name.find({<expression1>, <expression2>, ...})
```

The `$or` operator has a similar syntax as above.

#### Update
```
# Find a document and replaces its content
db.collection_name.replaceOne(query, <document>, <options>)
```
`query` refers to how we find the document we wish to replace
`<document>` is what we're going to replace the existing document with. It will override all contents of the document except for `_id`

```
db.collection_name.updateOne(filter, <document>, <options>)
# update requires either of the following two operators:
$set   this operator adds a field and value to a document if the field doesn't already exist. Otherwise, it replaces the value of the field.
$push  this operator adds allows for adding elements to an array
```

`$push` and `$set` have a similar syntax:
```
db.collection_name.updateOne(
	{field1: {$eq: value1}},
	{$set: {field2: value2}}
)
db.collection_name.updateOne(
	{field1: {$eq: value1}},
	{$push: {field2: value2},
	{upsert: true}} # upsert is explained below
)
```

How to update an array field by appending multiple values. We use the `$each` operator. 
```
db.collection_name.updateOne(
	{field1: value1},
	{$push: {field2: {$each: [value2, value3 ...]}}}
)
```
The `$each` operator is followed by an array. It's like, for each value in the given array, do something.

How to update a particular value inside an array. We're not appending to an array.
```
db.collection_name.updateOne(
	{field1: value1}, # find the document
	{$set: {field2.1: value2}}
	# field2 is an array. field2.1 refers to the element at index 1, and we're setting the value of that element to value2
)
```


How to increment values with the `$inc` operator
```
db.birds.updateOne(
	{ common_name: 'Robin redbreast' }, 
	{ $set: { 
		$inc: {sightings: 1},
		last_updated: new Date()
		}
	}, 
	{ upsert: true })
```
Explanation of command: 
First find a document that has a field `common_name` and value `Robin redbreast`. Then update the following fields if they exist, or add if they do not:
* Increment the value of `sightnings` by 1
* set `last_updated` to current time as returned by `new Date()` function
Finally, if no such document (with a field `"common_name": "Robin Breast"` exists, then add the argument document to the collection.

Both `replaceOne()` and `updateOne()` methods can have an optional, third parameter `<options>` in a form of a document. 
**upsert** - if no documents match the filter, then enabling upsert allows the `updateOne()` method to insert the `<document>` argument into the collection.
```
# Enabling upsert via options
db.collection_name.updateOne(filter, <document>, {upsert: true})
```

`findAndModify()`
This method works just like the `updateOne()` method. But it can also returns the modified document. But the syntax is different
Advantages of `findAndModify()` are:
- We can do `findOne()` and `updateOne()` in one go around the collection
- Multithreading applications will not interfere with each other. Suppose inbetween the time we run `updateOne()` and `findOne()` methods, another thread runs its own `updateOne()` method. Then, when we call `findOne()`, we're viewing the result of someone else's work, not our own.
```
db.collection_name.findAndModify(
	{
		query: <query>,
		update: <document>,
		new: true  # if set to true, the new modified document is returned. else, the original document is returned.
	}
)
```
Example:
```
db.birds.findAndModify(
	{ 
		query: {common_name: 'Blue Jay' },
		update: {$inc: { sightings_count: 1 }},
		new: true,
		upsert: true
	}
)
```
Note: `findAndModify()` can also use `upsert`.


`updateMany()`
This method both works and has a similar syntax to the `updateOne()` method. However, as `updateOne()` updates only 1 document, `updateMany()` updates all documents that match its query argument.
`updateMany()` is not an all-or-nothing operation. Even if it fails, some documents may still be updated.

#### Delete
```
db.collection_name.deleteOne(<querry document>)
db.collection_name.deleteMany(<querry document>)
```


### Modifying Queries
The `db.collection_name.find()` method returns a cursor, which is a pointer to the collection returned by the query. Cursor objects have several important methods:
#### `.sort()`
We can sort query results either by a field in ascending or desending order as follows:
```
db.collection_name.find(<query filter>).sort({field1: 1, field2: 1}) # where the fields are from the documents in the collection on which the find() method is called.
# use 1 for ascending order and -1 for descending order
```

##### It is possible to sort based on multiple fields at the same time. 
The function first sorts by `field`,  then by `field2`, and so on. The subsequent sorts only make a difference if fields have the same value. For example,  suppose we have the following `scores` collection.
```

db.scores.find({}).sort({score: -1, num: 1})

// returns:
  {
    _id: ObjectId("63cd94ead686ab9305b943d8"),
    name: 'Jack',
    num: 10,
    score: 65
  },
  {
    _id: ObjectId("63cd940ed686ab9305b943d6"),
    name: 'Isabella',
    num: 11,
    score: 65
  },
  {
    _id: ObjectId("63cd940ed686ab9305b943d3"),
    name: 'Harry',
    num: 3,
    score: 62
  }


// The results are first sorted by score in an descending order. Isabella and Jack are placed on top next to each other and Harry comes next. Then, the results are sorted by num in an ascending order. Jack goes above Isabella because his num is smaller. The rest of the document is untouched.
In other words, the subsequent sorts only matter if some fields have the same value.
```


In this example, we are working we a collection named `sales` within our database. Our objective is to find all sale documents where a coupon was used online, and sort them by date from newest to oldest (i.e. in an descending order)
```
db.sales.find(
	{couponUsed: true, purchaseMethod: 'Online'},
	{_id: 1, saleDate: 1, couponUsed: 1, purchaseMethod: 1} # This is a projection. To avoid clutter, what fields from the queried documents are displayed. More examples ahead.
	).sort({saleDate: -1})
```

#### `.limit()`
This method limits the number of documents returned in a query. It can enhance performance.
```
db.collection_name.find(<query filter>).sort({field1: 1, field2: 1}).limit(3)
```

Sample document from a collection named `sales`:
```
{
  _id: ObjectId("5bd761dcae323e45a93ccfe8"),
  saleDate: ISODate("2015-03-23T21:06:49.506Z"),
  items: [
    {
      name: 'printer paper',
      tags: [ 'office', 'stationary' ],
      price: Decimal128("40.01"),
      quantity: 2
    },
    {
      name: 'notepad',
      tags: [ 'office', 'writing', 'school' ],
      price: Decimal128("35.29"),
      quantity: 2
    },
    {
      name: 'pens',
      tags: [ 'writing', 'office', 'school', 'stationary' ],
      price: Decimal128("56.12"),
      quantity: 5
    }
  ],
  storeLocation: 'Denver',
  customer: { gender: 'M', age: 42, email: 'cauho@witwuta.sv', satisfaction: 4 },
  couponUsed: true,
  purchaseMethod: 'Online'
}
```
Objective: Return the data on the three most recent sales made from the London store that included one or more of the following items: a laptop, a backpack or printer paper.
```
db.sales.find(
	{
	storeLocation: 'London', 
	'items.name': {$in: ['laptop', 'backpack', 'printer paper']}
	}
).sort({saleDate: -1}).limit(3)

```

#### Projections
Query methods like `find()` return all fields from the documents that match the query filter. But these methods can take a second argument, a projection document, that would limit which document fields are returned.
```
db.collection_name.find(<query filter>, {field1: 1, field2: 1, _id: 0}) # 1 is for inclusion, meaning, only return the values for field1 and field2

db.collection_name.find(<query filter>, {field1: 0, field2: 0}) # 0 is for exclusion, meaning return all field-value pairs except for field1 and field2 and their values.

# Note that inclusion and exclusion cannot be used together, except for _id. This is because, by default, mongoDB will always return the _id field, even if we do not explicitly include it. But we can excluse it from the query results 
```

Example: Given the `sales` collection above,
Find the data on sales to customers less than 30 years old in which the customer satisfaction rating was greater than three. Return only the customer's age and satisfaction rating, the sale date and store location. Do not include the `_id` field.
```
db.sales.find(
	{"customer.age": {$lt: 30}, "customer.satisfaction": {$gt: 3}},
	{
		"customer.age": 1,
		"customer.satisfaction: 1",
		saleDate: 1,
		storeLocation: 1, 
		_id: 0
	}
)
```

#### `.countDocuments()`

```
db.collection_name.countDocuments() // Returns the count of all documents in the collection

db.collection_name.countDocuments(<query filter>) // Returns the count of all documents that match the given query filters.
```


### Aggregation Pipeline
Terminology:
- Aggregation: An analysis/summary on data. Does not alter the data
- Stage: A single aggregation operation done on data. There are several stages as described below. Each stage has its own syntax.
- Aggregation "pipeline": An array of stages completed one at a time. The results from one stage become input for the next. This is similar to chaining method calls (like in Java, for example).

General syntax:
```
db.collection_name.aggregate([
	{$stage_name : {<expression>}},
	{$stage_name : {<expression>}},
	...
])
```

Field paths
`$field1` is called a field path, and refers to the value 

#### Aggregation Stages
##### `$match`
```
db.collection_name.aggregate([
	{$match: {field: value}}
])
```
This stage works just like the `.find()` operation (the read from CRUD)

##### `$group`
This stage is given a group of documents. It will groups those documents based on a given key, called the "group key". Then, for each unique value for the group key, it will produce a document. What these documents contain, is determined by an "accumulator" expression

Example: 
Suppose we're working with a collection `zips` that holds info on all cities in the US, such as:
```
{
	_id: 
	city: 'San Diego',
	zip: 92121
	loc: {y: 32.8, x: 117.2},
	pop: 2286,
	state: 'CA'
}
```

```
db.zips.aggregate([
	{$match: {state: 'CA'}}, // Stage 1. Retrieve all cities in California
	{ // Stage 2
		$group: {
		// Group key. Group documents based on the unique values for they field city
			_id: "$city", 
			totalZips: {$count: {}} // accumulator. $count returns the number of documents in a group. Which means, it returns the number of zip codes (or loc, or pop) in each city group.
		}
	}
])
```

Another example:
Working with a collection `sightings` which records where and when a bird was sighted.
```
{
  _id: ObjectId("62cf8eb2bb9cdbee29caab03"),
  species_common: 'Eastern Bluebird',
  species_scientific: 'Sialia sialis',
  date: ISODate("2022-01-18T23:55:40.000Z"),
  location: { type: 'Point', coordinates: [ 40, -74 ] }
}
```

We wish to find where we have the best chances of seeing the Eastern Bluebird:

```
db.sightings.aggregate([
	{ $match: { species_common: 'Eastern Bluebird' } }, 
	{ $group: 
		{
			_id: "$location.coordinates", 
			number_of_sightings: { $count: {} } 
		} 
	}
])
```
which returns
```
[
  { _id: [ 40, -74 ], number_of_sightings: 3 },
  { _id: [ 40, -73 ], number_of_sightings: 1 },
  { _id: [ 41, -74 ], number_of_sightings: 1 }
]
```

In stage 1, we get a list of all documents where `species_common: 'Eastern Bird'`
In stage 2, we group the documents given by the previous stage by the value of their `location.coordinates`, i.e. the group key. For each group, we create a document that contains the group key and how many duplicates it had.

Which means, the coordinate `[ 40, -74 ]` was repeated 3 times: there were 3 instances where this coordinate was repeated

##### `$sort`
Works just like the [[MongoDB#`.sort()`|.sort()]] with minor difference in syntax:
```
{
	$sort: {
		"field_name": 1 // 1 for ascending order, and -1 for descending
	}
}
```


##### `$limit`
Works just like the `.limit()` function 
```
{
	$limit: x // where x is a natural number
}
```

For this example, consider the `sightings` collection from earlier.
Find 4 sightings that are most towards north. In other words, sort the documents by location coordinate, from most northern location to south, and limit the results to 4. 
```
db.sightings.aggregate([
	{$sort: {"location.coordinates.1": -1}},
	{$limit: 4}
])
```

##### `$project`
The concept is similar to [[MongoDB#Projections|projections]]
Determines what fields should be included or excluded, usually in the final stage of the pipeline.
```
$project: {
	<field1>: 1, // 1 to include
	<field2>: 0,  // 0 to exclude. can we combine 1 and 0, unlike in .find() projections?
	<field3>: 'new value'
}
```

We can also add new fields or update values of existing fields to the pipeline (output). Note that these stage operations do not alter the contents of the database.

##### `$set`
Used add to or modify fields in the pipeline. The [[MongoDB#`$project`|$project]] stage can also add or modify fields in the pipeline. But it cannot exclude fields. In other words, with `$set` you can only add to or modify the existing fields in the documents in the pipeline.
Suppose you needed to add an extra field to the pipeline. With the `$project` method, you would have to include all other fields, and then add the new field. But with `$set`, we can, plain and simple, just add a new field.
Example:
```
db.zips.aggregate([
	{
		$set: {population_2022: {$round: {$multiply: [1.0031, "$pop"]}}}
	} // multiply the value of the field pop with 1.0031,  round the results, save it to a field named population_2022 and add it to the pipeline. That is, add it to all documents in the pipeline.
])
```

##### `$count`
How many documents are there in the pipeline?
```
{
	$count: "total"
}
```
The number of documents is saved into a field `total`. The result is an array that includes a single document like `[{total: num}]` where `num` is the number of documents.

##### `$out`
Convert a pipeline to a new collection!
This should be the last stage in a pipeline.
**Causion: If the collection already exists, `$out` scraps all its documents**
```
{
	$out:
	{
		db: "database name", // This can be ignored. If so, the new collection is created in the database on which we are operating.
		coll: "collection name"
	}
}
```


### Indexes
Query for data faster. Normally, a read operation (like `.find()`) would go through an entire collection, checking every single document. But with indexes, we can create an internal, sorted data structure (a B tree (not a binary tree)) that points a key to a value (using pointers).
MongoDB creates an index table using the `_id` field by default. So if we search for a document using its `_id`, MongoDB wouldn't search through the entire collection. It would nearly instantly find the document. 
We should create indexes on data that is used most commonly

<iframe width="560" height="315" src="https://www.youtube.com/embed/D14wWW9EEx8" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>
Cons of indexes, is that because they are sorted, adding or updating documents means the indexes should also be updated.

There are 3 types of indexes: single-field, multi-key, and compund. All share the same syntax.

#### Single-Field Indexes
```
db.collection_name.createIndex(
	{
		field: sort_order // Create index based on this field. sort_order (1 for ascending or -1 for descending) indicates how the documents are sorted in the index.
	}, 
	{
		unique: true // Optional. Enforces uniqueness for the specified index field. Then, we cannot insert or update the collection with a duplicate value for the field.
	}
)
```


```
db.collection_name.getIndexes() // Returns an array that holds information for every indexes showed for this collection. It looks something like,

[
  { v: 2, key: { _id: 1 }, name: '_id' },
  { v: 2, key: { account_id: 1 }, name: 'account_id_1', unique: true }
]

MongoDB creates an index based on the _id field by default
```

Additionally, when performing a query, we can view how (or verify that) mongodb performed the reading operation using indexes with the `.explain()` function:
```
db.collection_name()
	.explain()
	.find({ field: value })
	.sort({ field: 1 })
```



#### Multi-Key Indexes
Suppose we wish to create an index based on a field that is an array (or a sub-document, or even a sub-array).
Only one array (or other similar types) may be used to create an index.

The syntax for creating a multikey index is the same as creating a singlekey index.
```
db.accounts.findOne()
db.accounts.getIndexes()
db.accounts.createIndexe({transfers_complete: 1})
```


In this example, we are working with a collection named `accounts`. `db.accounts.findOne()` returns the following:
```
{
  _id: ObjectId("62d6e04ecab6d8e130497482"),
  account_id: 'MDB333829449',
  account_holder: 'Kate Stone',
  account_type: 'checking',
  balance: Decimal128("4688"),
  transfers_complete: [
    'TR854412948',
    'TR413308451',
    'TR328708274',
    'TR192714918',
    'TR263422717'
  ]
}
```


```
db.accounts.createIndex({transfers_complete: 1})
db.accounts.getIndexes()

// Both of these searches yield the same result. $elemMatch is used to only search in array fields. 
db.accounts.find({transfers_complete: {$elemMatch: {$eq: 'TR617907396'}}})
// Searches for all field types, including inside arrays 
db.accounts.find({transfers_complete: 'TR617907396'})

// The .explain() method for both queries shows they both use the created multi-key index to search.
```


#### Compound Indexes
```
db.collection_name.createIndex({field1: 1, field2: -1, field3: 1})
```
Only queries that contnain or sort by the the prefix in the index can use the index. By prefix, I mean the first argument in the `.createIndex()` method.

Argument positions matter. Place fields tested for equality first. Less processing time as fewer documents are returned 

https://learn.mongodb.com/learn/course/mongodb-indexes/lesson-4-working-with-compound-indexes-in-mongodb/learn?client=customer&page=2

Explore: It is possible to make queries faster by using projections. Querying with a projection means only certain fields from the documents will be returned. If these fields are already in the index, then MongoDB will not have to read any data from the collection, only the index. Thus, the query will be faster. Thus, an index could be designed with that in mind.


## Importing a CSV file into MongoDB using mongoimport
```
mongoimport --file=aac_shelter_outcomes.csv --type=csv --db=AAC --collection=animals  --fieldFile=aac_shelter_outcomes_field_file.txt
```

With authentication, there are a few more options added to the command:
```
mongoimport --db=AAC --collection==animals --type=csv --file=aac_shelter_outcomes.csv --fieldFile=aac_shelter_outcomes_field_file.txt --authenticationDatabase=admin --username=afshin --password=""
```
Notes:
- `authenticationDatabase` is required and should be set to the db in which the user was created.
- `--password=""` will prompt the user to enter their password not in plain text. We can also exclude this option all together for the same result.
First we change directory (`cd`) to the directory of `aac_shelter_outcomes.csv`, from which we are importing data.

~~The `--fieldFile` specifies which columns (or fields) we import from the datasheet, and what data type they should be imported as. ~~
```
﻿age_upon_outcome:string
...
date_of_birth:date
```
Using the `--fieldFile` option **did not work**. `mongoimport` would use the whole line (such as `age_upon_outcome:string`) as the field name. In addition, simply not including a column name does not skip the column.
I tried using a different approach to specify type and skip columns:
```
$mongoimport --db=AAC --collection=animals --type csv --file=aac_shelter_outcomes.csv --fields age_upon_outcome,animal_id,animal_type,breed,color,date_of_birth:date,datetime:date,monthyear:date,name,outcome_subtype,outcome_type,sec_upon_outcome,location_lat,location_long,age_upon_outcome_in_weeks --authenticationDatabase=admin --username=afshin --password=""

```
**This also did not work.** In fact, it worked the same way as above and imported the whole `fieldName:type` as field name.


The file has 1001 rows. The first row has the column titles, and should be ignored. `mongoimport` has a `--headerline` option that ignores the first row and uses the column names as field names in the documents. Each row is considered a document.
However, `--headerline` is not compatible with `--fieldFile` and other similar options like `--fields`.
When I use the command above, the feedback says 1001 documents were imported. Does that mean the first document with the field names was also imported? Yes. `mongoimport` is also importing the column header row as a document.

**This is what finally worked:**
Ultimately, I had to just delete the column from the spreadsheet before importing. I ended up using a simple import command:
```
mongoimport --db=AAC --collection=animals --type csv --file=aac_shelter_outcomes.csv --headerline  --authenticationDatabase=admin --username=afshin --password=""
```
Then, after importing, I converted a the appropriate fields from string to date type using the `updateMany()` function (see [[#CRUD (Create, Read, Update, Delete) in MongoDB#Read]])
```
db.animals.updateMany({}, [
	{
	$set: 
		{"date_of_birth": {$dateFromString: {dateString: "$date_of_birth"}}}
	}]
)
```
Now, by using the `--headerline` option, we only import 1000 documents, excluding the first row.

## User Authentication in MongoDB Shell
So far, using mongodb has been as easy as starting a mongodb server instance and mongosh:
```
sudo systemctl start mongod
mongosh
```
But it is possible to set up authentication with username and password before loging into mongosh. 
Then, we can sign into `mongosh` with a modified command
```
mongosh --authenticationDatabase admin -u afshin -p password1

// This is more secure. Users won't have to enter their passwords in plain text, and password cannot be recovered in terminal history.
mongosh --authenticationDatabase admin -u afshin --password
```
But before that, we must enable this feature inside the `/etc/mongod.conf` file by adding the following:
```
security:
	authorization: enabled
```

Now to create accounts.
A user that is created in the `admin` database has access to all databases. However, to restrict user access to a database, that user can be created in that specific database.
The role `userAdminAnyDatabase` allows us to manage users. When this role is created inside the `admin` database, we can manage users in all databases.
However, to be able to read from and write to databases, we will also need the `readWriteAnyDatabase` role.

```
use admin
db.createUser(
	{
		user: "afshin", 
		pwd: "password1", 
		roles: 
			[
				{role: "userAdminAnyDatabase", db: "admin"}, 
				{role: "readWriteAnyDatabase", db: "admin" },
			]
	}
)

// update user roles
db.grandRolesToUser("afshin",
	[
		{role: "", db: "admin"}
	]	
)

// another method to update users. more details are needed
db.updateUser({})
```

All possible roles:
```
db.grantRolesToUser("afshin", 
	[
		{ role: "read", db: "mydb" },
		{ role: "readWrite", db: "mydb" },
		{ role: "dbAdmin", db: "mydb" },
		{ role: "dbOwner", db: "mydb" },
		{ role: "clusterAdmin", db: "admin" },
		{ role: "readAnyDatabase", db: "admin" },
		{ role: "readWriteAnyDatabase", db: "admin" },
		{ role: "userAdminAnyDatabase", db: "admin" },
		{ role: "dbAdminAnyDatabase", db: "admin" },
		{ role: "clusterMonitor", db: "admin" },
		{ role: "clusterManager", db: "admin" },
		{ role: "hostManager", db: "admin" },
		{ role: "backup", db: "admin" },
		{ role: "restore", db: "admin" },
		{ role: "root", db: "admin" },
	]
)
```

To create a user for a database:
```
// first switch to the database for which the user is being created
use mydb
// then create the user
db.createUser({
	user: "username",
	pwd: "myPassword",
	roles: [ { role: "readWrite", db: "mydb" } ]
})
```