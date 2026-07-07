This is a protocol just like HTTP in the application layer of the TCP/IP model. It establishes a consistent, asynchronous, two-way connection between a client and a server. unlike HTTP, ==it's a stateful protocol.== So we need to be careful when scaling our application to a multi-server architecture. 

Just like HTTP, web sockets use TCP to ensure data is securely and orderly transported throughout the internet. 


The ==difference between HTTP and TCP is that they operate at different layers of the TCP/IP model== and do entirely different things,. TCP is responsible for establishing a connection, quantizing data into packets, sending them across the internet to the destination, and validating the data received (retry sending lost packets).
HTTP *uses* TCP. HTTP is a layer on top that defines the requests and responses that applications make and send. 



# How Web Sockets Work
The WebSocket protocol starts as a standard HTTP request from the client to the server. 
The client sends a special HTTP GET request, initiating an upgrade from HTTP to the WebSocket. It's also to ensure both ends support the WebSocket protocol. This request has a header like the following:
```http
GET /chat HTTP/1.1
Host: server.example.com
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==
Sec-WebSocket-Version: 13
```
`Sec-WebSocket-Key` is a 16-byte random number that gets encoded in base64 by the client and is sent to the receiver (usually the server). 
The server needs to let the client know it supports the protocol. So it prepends a *universally recognizable prefix*[^1] to the WebSocket key, hashes it using SHA-1, and sends it back to the client in an HTTP response like the following:
```HTTP
HTTP/1.1 101 Switching Protocols
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Accept: s3pPLMBiTxaQ9kYGzzhZRbK+xOo=
```
The HTTP 101 response code means the server is ready for the upgrade, and unlike 200 OK, it does not terminate the connection. 
Another important function of the WebSocket key is to ensure the request gets to the destination in the first place. Our request will travel through many proxies and caching servers and load balancers, etc.. These are highly optimized by caching responses to the same HTTP requests and returning responses on the spot. So the upgrade request might not even make it to the server. To combat this, the request header includes a nonce to guarantee we're reaching a server, then checking the server supports the protocol.
If we get a false 101 response, then all the packets will silently get dropped. <u>We will eventually find out when no acknowledgments come back</u> (**need to fact-check this**) , but we would have just wasted time and became inefficient.

The moment the client receives that `101 Switching Protocols` response and verifies the hash, the HTTP parser gets torn down and both endpoints hand the data in the underlying TCP socket over to their respective WebSocket handlers. 

WebSocket data is sent as *frames*:

|                |                                                          |
| -------------- | -------------------------------------------------------- |
| Opcode         | 4 bits used to tell the receiver what the frame contains |
| Payload length |                                                          |
| Masking key    |                                                          |
| Payload data   |                                                          |


| Opcode (hexadecimal) |                    |
| -------------------- | ------------------ |
| 0x0                  | Continuation frame |
| 0x1                  | Text frame         |
| 0x2                  | Binary frame       |
| 0x8                  | Close connection   |
| 0x9                  | Ping               |
| 0xA                  | Pong               |

#### The Ping-Pong/Heartbeat mechanism
##### The problem:
TCP is inherently a *silent* protocol. Theocratically, two endpoints can remain connected for weeks, even if there is no data exchange. However, requests travel through many nodes (routers, load balancers, firewalls, etc...) in the internet, many of which will drop TCP connections if they see it's idle for 30 to 60 seconds. These devices have limited ram, so they track stateful TCP connections using a **[[Networking#Routing Table|routing table]]**.
In addition, TCP does not constantly verify the connection is alive . There is no way to know the connection has been dropped unless one peer tries to send data. If it receives no acknowledgements, it tries resenting the data. However, after a timer expires and no acknowledgments are received, the OS will eventually close the connection. This is why the OS will keep an entry for all connections unless it knows they're disconnected, either gracefully or if they drop. An open connection that's actually disconnected is called a **zombie connection**. Zombie connections are *terrible for performance* because the OS keeps retrying and sending packets until it gets a timeout error. This can sometimes up to 15 minutes! All the while, system memory is in use (File descriptor slot is taken, TCP socket is open in memory) and CPU cycles are being wasted. Now imagine if you have thousands of these zombie connections. The heartbeat mechanism will show if the connection is dead in seconds. 
##### Solution:
To solve this problem, the WebSocket protocol adopts a **ping pong**, also known as **heartbeat**, mechanism. WebSocket needs a stable TCP connection. So, to keep the connection active, the server periodically sends a ping (an empty) frame, and the client responds with a pong, back and forth to keep the connection from timing out. 

#### WebSocket is a Stateful protocol
##### The problem:
With HTTP, when a user request is received by the load balancer, it can be sent to any of the backend servers for processing. These servers don't store user data themselves. They have to either retrieve it from the database or from an external cache.
But with WebSocket, the TCP socket exists only in the memory of one server. The connection is made to one server, which has a memory buffer for the TCP packets. This is called **stateful**. So requests from the same user have to be directed to the same server. This is referred to as **north-south traffic**. 
This makes it difficult to scale such applications. 
By default, there is no **east-west traffic** in the backend, i.e. servers don't know of each other's state. If our application wants to send a response packet to a client, it needs to know which server is hosting the WebSocket connection (the TCP socket) for that client. The fact is, ==WebSocket servers cannot operate in isolation==. 
##### The solution:
The solution to this problem is pub/sub backplane, an implementation of the **[[Events in CSharp|observer pattern]]** using a message broker like Redis or Kafka. Suggested further reading: 
[[Apache Kafka]]
[[CQRS and Event Sourcing]]

The backend servers are isolated and we need a way to connect them together. When the load balancer 


```cardlink
url: https://youtu.be/wb4qcdb0XWw
title: "What is a PubSub Architecture?"
description: "Pub/Sub is a backend architectural pattern, often put into practice with message broker technologies like RabbitMQ, Apache Kafka, Google PubSub, etc.Learn ba..."
host: youtu.be
favicon: https://www.youtube.com/s/desktop/0ecb6dad/img/favicon_32x32.png
image: https://i.ytimg.com/vi/wb4qcdb0XWw/maxresdefault.jpg
```

#### WebSocket (and TCP) connection cannot be directly established to a backend server
It must be to a load balancer, the entry point to the private backend infrastructure. In most cases, the public IP in the DNS will point to the load balancer. You don't want to expose 50 backend servers to the public internet because it's not safe. Another reason this is not possible is because the load balancer (AKA reverse proxy) is used for **TLS/SSL offloading**: to intelligently route traffic, the load balancer needs to decrypt HTTP requests and read their headers and cookies. 
When the initial HTTP upgrade comes, the load balancer will see which server is the least occupied. Then it maps a `(sender ip, port)` tuple to backend server, and uses it to forward future incoming TCP packets to that server.

**TLS/SSL offloading**
The industry standard is to end the TLS/SSL connection at the load balancer. It decrypts then forwards the plain-text date to the backend servers. This relieves the decrypting load off of the backend servers. While it boosts efficiency, this approach opens room for man-in-middle attacks because data is now in plain text in the internals of the system. So in applications that require a strict zero-trust policy (like banks, HIPPA compliant apps, etc..), it's best to preserve the end-to-end (that is, client to specific backend server that stores application sate) encryption. In this case, we use adopt **TLS Bridging** (or the more simpler name, re-encryption). As we mentioned, the load balancer needs to access HTTP headers and sender IP and port to forward requests to the right server. In TLS bridging, the load balancer decrypts the data and chooses a server to forward, but decrypts the data again (likely using a different algorithm than TLS). The end point server will then decrypt the data and use it.

*But if decrypting is such a heavy task, then why delegate it to the load balancer and create a single point of failure?*
Load balancers are hosted on specialized hardware (called **ASICs**, or Application-Specific Integrated Circuits) that's heavily optimized for mathematical computations used in cryptography, while general backend servers that run applications like python and node.js run on general-purpose CPUs.

In addition,
> To decrypt TLS, a server must possess your company's highly sensitive Private SSL Key.
> 
> If you pass encrypted traffic all the way to your backend servers, every single one of those servers needs a copy of that private key. If you are automatically scaling up and down—spinning up 50 new servers during peak hours and destroying them at night—you have to constantly distribute, rotate, and secure SSL certificates across hundreds of ephemeral, moving targets.
> 
> By terminating TLS at the load balancer, your SSL certificates live in one highly secure, centralized location.

## What are Network Sockets?
### File Descriptors
"Everything is a file", is the famous design philosophy implemented by Unix and Unix-like systems. It means system resources and devices are treated as files by the OS. This includes data streams, including files and data transmitted over a network. So file descriptors are used to also access devices...

In a literal sense, a file descriptor is a unique, non-negative *integer* an application (process) uses to request access to I/O resources from the OS.
It's an abstraction layer that sits between applications and OS resources, like data buffers that store unpacked data from a TCP connection (a TCP socket). Applications don't need to concern themselves with how the OS kernel handles data writes and reads. 
Every process has a descriptor table that automatically includes 3 file descriptors:
- 0—STDIN is the standard input (keyboard)
- 1—STDOUT is the standard output (terminal)
- 2—STDERR is the standard error (also terminal)
- Other data sources (like a network socket) will be added incrementally
When we use pipes (`|`) in the terminal commands, we're essentially changing where the output descriptor point to. 

Read more about the hierarchy of file descriptors in Unix systems [[Unix File Tables|here]]
### WebSocket Handlers
So we know applications get access to the TCP socket. But the TCP socket doesn't know what HTTP is. It doesn't know what a WebSocket is. It only knows a continuous, unbroken stream of raw bytes. It is the job of the applications to translate this data to the application layer protocols. Every programming languages or frameworks offers its own WebSocket handler, which is responsible for reading the data bytes from the TCP socket, applying the WebSocket protocol rules, decoding the data, extracting the request payload, then calling some callback function from the business logic layer of the application.

#### Why handlers operate in the application layer 
It may be surprising the application is responsible for converting TCP packets into protocol data. If it's all the same protocol rules, ==why isn't it done by a centralized system in the OS kernel?== 
This would actually be a very bad system design for several reasons. The kernel is the most privileged, sensitive area of the machine. If it was responsible for parsing application layer protocols like HTTP or WebSocket, then *any bugs or overflows would crash the entire system*. More damaging, it would *enable attackers to inject malicious code into the heart of the machine* and hijacking it. So delegating this task to applications also confines issues like this to an isolated (application) space. This way, *if there is an error, only the application goes down, not the entire system*. 
The fact is, TCP has been standardized since 1981 and rarely changed since. While HTTP and WebSocket versions rapidly change, making them naturally belong in the application layer. So if there are bugs, it's more than likely going to be found in the rapidly changing protocols like HTTP than something as stable as TCP.  

Also, the OS's only job is to move raw bytes from the physical Network Interface Card (NIC) into RAM as efficiently as possible, ensuring they arrive in order (TCP). This puts it in the layers 3-4 of the OSI model. It doesn't care if those bytes are an HTTP webpage or a multiplayer game state because those are in the application layer. If the OS had to inspect and understand the meaning of the bytes, the *network throughput would severely slow down*. This the basis of the **End-to-End Principle**, which states the network should be as simple and fast as possible, and the intelligence (application-specific features like security, error recovery, or data validation) should live at the endpoints.






# Polling
The client regularly sends HTTP requests to the server to check if there's new data available. The server then sends a response accordingly, even if there's no new information.
Most AJAX applications use this technique

# Long Polling
Long polling is very similar to polling, but the difference is the server holds on to the request and responds only when there is new data to send back.
HTTP requests have a timeout, however. So the client must have another request.
It's important to note that ==each request has to establish a new connection==, which is resource intensive and inefficient

[^1]: `258EAFA5-E914-47DA-95CA-C5AB0DC85B11`, a GUID that's defined in the official **WebSocket Protocol specification** (RFC 6455).  ==It's essentially a made up string==
