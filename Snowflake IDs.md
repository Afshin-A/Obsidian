Originally create by Twitter, Snowflake IDs allow large backend distributed systems with massive user activity to create and manage millions of IDs per second.

An app like discord manages millions of user messages every second. If we were to look up each message using a UUID in the database, we would hit a massive network bottleneck, causing delays and crashes. 
We need a *stateless solution* so when the load balancer receives a request, it can just use the message ID to instantly know which backend server/node it should forward the request to. 

UUIDs are random, so using them as a database index creates fragments in the underlying B-tree structure, destroying read/write performance. We also can't sort such a table with UUID as primary key using time



challenges my manhood
undermines my authority
does not listen to me - from simple things  to more grave matters
disrespects me
does whatever she wants
calls me a pussy
touches my butt
does not give me peace - freaks out about the simplest things, overthinks the most insignificant things