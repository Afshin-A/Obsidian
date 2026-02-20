
The system is consisted of individual and/or independent components (or *nodes*) that work together over a network.

This includes databases, ...


# CAP
All distributed systems are subjected to the cap theorem. It explains the trade-off between the following 3 features of a distributed system: 
 - **C**onsistent. All or none of the nodes in the system can access the same, most up-to-date data. Otherwise the system throws an error. No *stale* data. *All nodes have a consistent view of the data.* When an outside source connects to the system, it will always get a consistent response.
- **A**vailable. The ability of the system to always be available to respond to the users, even if the data might be *stale*. A system that is up all the time and has a low response time is said to be available.
- **P**artition tolerance. The system will continue responding to users even if the graph gets disconnected into multiple sub-graphs. A system with  resilience to end up with isolated components by avoiding bottle necks and weak links. For example, if a node becomes unreachable such that the rest of the system is unable to communicate with it (due to a network error, or if a bridge node crashes and goes down), can the system still continue to respond to its users?

Depending on the nature of the system, if a network partition occurs, we must choose between either consistency or availability
Consider an ATM. If an outage occurs and this machine cannot connect to the bank system, it can either:
```
A - Become unavailable for deposit or withdraw, or
B - Accept deposits and withdraws but become inconsistent
```
But not both. Simply put, ==In the event of a network partition, a system cannot be both available and consistent. We must choose 1 or the other.==



<iframe width="560" height="315" src="https://www.youtube.com/embed/BHqjEjzAicA?si=Td9LASwBgxkHs8IM" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
