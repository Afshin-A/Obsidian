#API

API stands for [[Application Programming Interface]]. As the name suggests, it is an interface that allows computer applications and servers to communicate with each other. Think about how you use your smart phone. The phone provides an interface that allows you, the consumer, to access the services that the phone, the service provider, offers. An API is a window between service providers and consumers. Both sides need to follow a contract--a set of rules--that define how they can interact with each other; this is where the API comes into play. (In comparison, in OOP, we can define how others can use a class using encapsulation, accessor and mutator methods.) If the service provider changes, the consumer should not have any difficulty to access the same service offered by a different provider.

Another real life example of an API is the electric wall socket. All electronic devices (consumers) have power cords that are designed to connect to the socket. On the other side, electricity provided by the socket can have many sources: it could be from a nuclear powerplant or a hydroelectric dam. Thanks to the wall socket (the API), the consumers need not be concerned with the source of the electricity, i.e. 
 the service provider, or details of how things work. (**Abstraction**)
 
API also play an important role in application design. Instead of creating a big  application with intertwined parts, so that changing one part would likely break other parts of the program and require more changes (such a design is called a **Monolithic Architecture**) we could break it up into distinct and discrete parts. Each part would become a service that is provided to the rest of the program through an API. This is called a **Microservices Architecture**; creating changes in a service or replacing the service provider should not break the program. This is starting to sound like **Object Oriented Programming**.

Many providers offer their services (through API's) consumers over the web--sometimes for free, and sometimes paid. Some services are interconnected via API's. In the big picture, there are millions (even billions) more of these services and API's. Together, this network of services, API's, and consumers is referred to as the **API economy**:
<p align="center"><img src="C:\Users\scand\Documents\GitHub\Obsidian\.resources\API Economy.png" height="300" width="450"/></p>

[Programmableweb](https://www.programmableweb.com/) website is a tool for studying/tracking the API economy; it includes a glossary of different API's, software developlemt kits (SDK), source code, and more.
SDK, also known as helper libraries, are offered by service providers. These libraries enable developers to use API with a programming language.

REpresentational State Rransfer (REST) is a standard that many remote API's over the web follow. An API is Restful if it follows a criteria:

stateless
should support chaching

CRUD->Create, Read, Update, Delete

[[HTTP]] 