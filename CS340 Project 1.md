## About the Project/Project Title
CRUD summarizes the 4 most basic and important functions of a web application, such as a database. Using CRUD, we can create, read, update, and delete data in a database. This repository offers a python module that allows users to easily manage their NoSQL databases in MongoD_B._


## Motivation
There are many different ways to interact a database in MongoDB: Atlas (cloud-based), mongosh (command-line/shell), MongoDB Compass (graphical user interface), as well as drivers for numerous programming languages, including Python. However, each of these methods require some knowledge of syntax, platform, or the programming language used, which can be overwhelming at first. In this project, the CRUD module offers a simple way to communicate with a MongoDB database; users can perform a CRUD operation with only a few lines of code!


## Getting Started
- To get started, first ensure all the requirements from [[CS340 Project 1#Installation (Ubuntu 22.04)|Installation]] are met.
- Download the _CRUD_ module (_CRUD.py)_ from this repository and place it in your python project.
- Start and run the MongoDB service by running the following command in your terminal window:
```shell
sudo systemctl start mongod
```
Note: There should be no response to this command in the terminal.

You are now ready to use the CRUD module in your project.


## Installation (Ubuntu 22.04)
Before using the CRUD python module, you must first install the following software on your system.
  
##### Requirements
- [_MongoDB_ and _Mongosh_](https://www.mongodb.com/docs/manual/tutorial/install-mongodb-on-ubuntu) - NoSQL DBMS (database management system) along with its shell
- [_Python_ (version 3)](https://www.python.org/downloads/source) - Python programming language
- [_Pymongo_](https://pymongo.readthedocs.io/en/stable/installation.html) _-_ MongoDB for Python

##### Recommended
The following is recommended (but optional) to help you visualize your database.
- _[MongoDB Compass](https://www.mongodb.com/try/download/compass) –_ Graphical user interface software that can manage your mongo databases


## Usage
To begin usage, 
- First import the AnimalShelter data class from the CRUD
```python
from CRUD import AnimalShelter
```

Next, we’re going to instantiate the AnimalShelter class call CRUD functions on the resulting object.

To instantiate AnimalShelter, we need to provide the following arguments in order:
- MongoDB username
- MongoDB password
- database name
- collection name
- MongoDB server port (This is optional and can be omitted to use the default value)

Example: 
```python
animal_shelter = AnimalShelter("aacuser", "password1", "AAC", "animals")
```

**Important:** If you receive an error message while instantiating, make sure an instance of MongoDB is running.
![[Screenshot from 2023-02-01 20-52-29.png]]

##### Create
To insert a document (as python dictionary) into the database, use the `create` function.

Example:
```python
animal_shelter.create(
	{
		"age_upon_outcome": "200 years",
		"animal_id": "WHALE!",
		"breed": "Sperm Whale",
		"color": "Grey"
	}
)
```
  
##### Read
To read from the database, first use the `read` function with a query argument (as python dictionary), then iterate over the resulting cursor object.

Example:
```python
query_results = animal_shelter.read({"breed": "Sperm Whale"})

for document in query_results:
	print(document)  
```



## Inserting Files into MongoDB
First, we use the following command to import the data-sheet into MongoDB. 
```shell
mongoimport --db=AAC --collection=animals --type=csv --file=aac_shelter_outcomes.csv --headerline --authenticationDatabase=admin --username=afshin --password
```

Since MongoDB is already protected, this command requires authentication.

![[mongoimport.png]]

  
## User Authentication
Here, we sign into MongoDB shell as a different user, “aacuser”. This user only has access to the “AAC” database:

![[authentication.png]]

## Testing with Jupyter Notebook
This section includes a few tests for the `CRUD` module. The following show the tests and their results.

- Creating an `AnimalShelter` instance and inserting data into the database.
![[project 1 instantiate and create.png]]

- Reading, updating, and removing data from the database.
![[project 1 read update and remove.png]]


## Contact
Questions, comments, or feedback? Contact the author, Afshin Ahvazi, at [afshin.ebadehahvazi@snhu.edu](mailto:afshin.ebadehahvazi@snhu.edu)