Event sourcing is used to asynchronous 

The **CQS principle**—Command Query Separation—states that a method should not both read from, and write to a database, at the same time. Instead, the *commands* (write) and *queries* (read) should be separated.

Separation of concerns make the code more maintainable, and the bugs easier to detect. If your method is doing multiple things that cause various unrelated effects, it would become much harder to detect which part of the code is causing bugs later. 

In a more general sense, a function should only do one thing. This is called the *single response principle*, and it makes code readable, maintainable, and testable.

**CQRS** design patten—Command Query Responsibility Segregation
It separates commands and queries into their own independent subsystems, each with their own *controllers*, *services*, and *models*. You can even use two different databases. We write to the command database(s) and eventually move the data into the read database(s) via asynchronous events and message brokers like [[Apache Kafka]]. 
This separation of concerns allows us to design and grow our subsystems independently of each other. Loose coupling, baby! Maybe our application has a lot more reads than writes. Then we could introduce a cache between the app and the database, or add multiple duplicates of the database to reduce the traffic pressure. Similarly, writing to a database comes with its own problems, such as conflict of access/modifying the same data; we can use things like *domain driven design* and asynchronous message queues to resolve them. And there you have it. Two entirely different subsystems in our application. 
However, as incredible the CQRS sounds, it adds complexity to the application. In this design, reading and writing become independent of each other. But it goes back to the nature of the application:  sometimes it doesn't make sense to have reads and writes separate; other times not only does it make sense, but it also significantly speeds up the system. As such, CQRS is usually used for big systems with heavy load and complex logic. 
Another downside is temporary inconsistencies in the system. When the write to the command database, we create an event and send it to a message broker like Apache Kafka. The read subsystem responds by updating the query database(s). The tradeoff for this is that it adds temporary inconsistency between the read and write subsystems. This is referred to as *Eventual consistency*.

**Model**—a way to represent *something* in the system
	- *data model* is just just the structure of the data, e.g. a type in typescript
	- *domain model* contains both structure and rules for how data should be processed (behavior).
**Service** - a collection of common operations used by the different controllers
**Controllers** - methods called in response to an HTTP request

In CQRS, the commands are typically corresponds to a domain model, and the queries to a data model. 



Okay, but how does CQRS actually help speed things up? So what if we have two different databases?
Well, a database can be optimized for reads or writes, but usually not both. There are always tradeoffs. 
You can design a normalized schema, which is good for writes, but it becomes complex for reads because there joins everywhere.
Similarly, you can add indexing for easy reads, but then writes become complicated.
The bigger the database becomes, the more apparent this becomes.


```cardlink
url: https://newsletter.scalablethread.com/p/what-is-event-sourcing
title: "What is Event Sourcing?"
description: "Understanding Event Sourcing, How it works, and How to Rebuild State"
host: newsletter.scalablethread.com
favicon: https://substackcdn.com/image/fetch/$s_!K0LE!,f_auto,q_auto:good,fl_progressive:steep/https%3A%2F%2Fsubstack-post-media.s3.amazonaws.com%2Fpublic%2Fimages%2F6472bae5-c4cb-4aef-9649-27b7a42823cd%2Ffavicon-16x16.png
image: https://substackcdn.com/image/fetch/$s_!5lzi!,w_1200,h_675,c_fill,f_jpg,q_auto:good,fl_progressive:steep,g_auto/https%3A%2F%2Fsubstack-post-media.s3.amazonaws.com%2Fpublic%2Fimages%2F12fe063e-5703-4a3d-bc05-5df768f5aea2_1456x1048.png
```


**Domain Driven Design (DDD)**
Instead of having business rules scattered all over the place (in controllers, services, databases,), which will eventually become chaotic for large scale applications over time, we're going to centralize the logic into classes, and import and use them where they are needed. 
we create a *domain layer* and keep all the logic there.

It is also a mental model that keeps the application rules unified. Everything else is built around the rules. The rules aren't built into separate layers (e.g. backend controllers and services, database, frontend). 
That's because overtime, the services and controllers and even developers will multiply.
Keep in mind Domain Driven Design is to address chaos and entropy in huge, rapidly expanding systems that live for years, not for start ups. 
We can create a `domain/` folder at the root of the project and place 

domain means - The problem space, The business logic, The real-world rules
an *aggregate* is data that is grouped together. We can sometimes logically infer from the business rules that certain data are tightly connected and must be kept together. rule $\to$ aggregate
that way, it won't be possible for different parts of the system to modify the data independently, and we minimize the risk of ending up with inconsistent data. No, instead we special classes that follow OOP principles. These classes also contain the methods necessary to interact with the data. This is referred to as the *aggregate root*. It's technical definition is that it's the only entry point to the aggregate. So our controllers/services aren't going to add or remove data from our database. Instead, we would do calls like: 
```
backgroundCheck.submit() 
backgroundCheck.approve(adminId)  
backgroundCheck.addDocument(doc)
```


for example, information from different sources is processed and filtered and altered into a record. That record is an aggregate.

Each aggregate gets a *repository*, which is responsible for saving into and retrieving aggregates from the database. Once again, we create another layer and abstract all the database logic in it. 
All we have to do is, for example, define a `BackgroundCheckRepsitory` interface and implement a class that knows how to communicate to a database. The aggregate will then use that class to save changes to the database. If we wanted to switch to using a different database later (let's say Mongo instead of Postgress), all we have to do is create another class that knows how to connect to Mongo, and it implements the repository interface. This way, we won't have to change any code in the aggregate. We use dependency injection, and inject different classes into the aggregate.
```typescript
class BackgroundCheckAggregate {
	constructor(rep: RepositoryInterface) {
		this.rep = rep;
	}
	
	public save(data: AggregateType): void {
		this.rep.save();
	}
}

// calling code:
const backgroundCheckAggregate = new BackgroundCheckAggregate(new MongoDBRepository());
backgroundCheckAggregate.save( ... ); // exact implementation is not important for this example
```
