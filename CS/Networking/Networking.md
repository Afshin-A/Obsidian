The internet is the network of networks. It's a collection of all 
# IP Addresses
## IPv4 
This is a 32 bit number unique to each device that can access the internet (run the internet protocol). This number is divided into 4 octets (groups of 8 bits). Each octet can have a decimal value from 0 to 255 (because 8 bits can at most represent is 255). There can be $255^4\approx4.2\times10^9$ unique IP addresses, which isn't enough to account for all devices. That's why **IPv6** was introduced.

The format of an IP address depends on [[Networking#What is Subnet Mask?|subnet mask]] (click to view more info on IP addresses). For example, $255.255.255.0$ means that the last block of the IP address is used for internal networking, while the first 3 blocks are used for public internet.
## IPv6
Enter **IPv6**. It uses 128 bits, 4 parts with 32 bits each. The numbers are hexadecimal (in base 16). IPv4 offers $2^{128} \approx 3.40 \times 10^{38}$ unique  addresses.


### Dynamic IP Addresses
The fact that IPv4 addresses are limited means that it is more cost effective for internet service providers to give their users temporary IPs from a pool of available IP addresses. This means that the average home user's public IP address is constantly changing. This is one of the reasons [[Networking#MAC Addresses|MAC addresses]] exist. It's possible to pay extra to obtain a **static IP address** from your ISP, one that does not change. Static addresses must be manually assigned to each computer, which will be difficult for a large network (because there are simply many computers to configure). Therefore, dynamic IP addresses are automatically assigned by a [[Networking#DHCP|DHCP]] server. 
### MAC Addresses
Every network device (like network or Bluetooth cards) has a unique, 6 byte (32 bit) **MAC** (Media Access Control) address, aka **physical** or **hardware address**. It follows a format like
$$
\#\#-\#\#-\#\#-\#\#-\#\#-\#\#
$$
on Windows, where each number is in base 16 (hexadecimal).
The first half of the number represents the manufacturer of the network interface card (**NIC**).
Devices in a network use MAC and IP addresses in combination to communicate with each other. 
- IP address is used to locate a device in a network ~ Mailing address of a house
- MAC address is used to identify a device in a network ~ Name of the owner of the house
For TCP/IP to work, we really need the MAC address of the device (server) we're trying to connect to. So computer A sends an **ARP** (**Address Resolution Protoco**l) broadcast to get the MAC address of computer B. This signal is routed to the correct server using its IP address. Once we locate it, the server will send back its MAC address and communication can start.

### DHCP (Dynamic Host Configuration Protocol)
It's a protocol (hosted on a ISP server or routers) that automatically *leases* IP addresses from its pool of available addresses. By lease, we mean that IP addresses are assigned temporarily for a limited amount of time. This way, when a computer goes out of commission, its IP address becomes available again.
DHCP also sets up subnet mask, default gateway, and DNS server to computers.
The DHCP has a scope: the range of IP addresses it can assign.


#### How does the internet work?
Suppose you want to connect to the Google server. You need to traverse the internet to get a MAC address. First, you open your browser and type in google.com, which gets converted to an IP address thanks to a DNS server. In order to establish TCP/IP, your computer will broadcast an ARP signal. Using the network part of your IP address, your computer will know that the Google server is not in your local network. So it sends the ARP signal to the router (default gateway). The default gateway needs the MAC address of the next router in the path. So it sends ARP of its own. Once the connection is established, it passes the MAC address of your computer over. This process continues for as many routers as there are in the best possible path (determined by graph theory algorithms) to the Google server. Each router determines what router it will connect to next using [[Graph Theory|graph theory algorithms]]. Finally, we reach our destination and the MAC address is send back to our computer, after which the TCP/IP protocol can begin. 

# Managing Computer Networks
## Subnet
A **subnet** (sub-network) is created by a router. The router physically divides a network into smaller sub-networks for enhanced security and performance.
We have a few computers connected together via a network switch. When computers within the network want to communicate with each other, they broadcast a signal. The broadcast domain consists of all computers connected to the router. If there are many computers in the network, the data traffic causes a slow down. So we create smaller networks (computers connected together by a switch) and place routers that connect these subnetworks. Broadcasts do not go past routers. 
In addition, this adds modularity to the network: because the computers in one subnet do not have access to the data flow of the other subnets. 

## VLAN 
**VLAN** Does the same thing as subnet. But it divides the networks virtually. We replace the central switch with a VLAN-enabled switch. This eliminates the need for routers or physically moving computers around.
But how does it work? 

# What is Subnet Mask?
In a network, each device must have an IP address. IPv4 addresses can be divided into two parts. These are the **network address** and the **host address**
- Network address: unique to each network
- Host address: unique to every member of the network (like computers, servers, tablets, etc.)
Subnet masks resembles an IP address. It represents how many bits in an IP address represent the network address. They "mask" the network portion of the IP address. An example is $255.255.255.0$. You may be interested in why the number 255 is used here. That's because in binary form, an octet of 1s equals the decimal value 255. The subsequent bits of 1 in the subnet determine the network address portion of the IP address.

We can change the subnet mask to create more sub networks. 
$$\begin{align}
& 11111111.11111111.11111111.00000000 \\
& 255.255.255.0
\end{align}$$
This subnet mask allows us to have 256 hosts within our network (this number is technically 254 because the host addresses with all 0s and 1s are reserved). 
Suppose we wanted to add sub-networks in the system. We can do so by borrowing bits from the host address and adding them to the network address:
$$\begin{align}
& 11111111.11111111.11111111.11000000 \\
& 255.255.255.192
\end{align}$$
In this example, we have the ability to add 4 subnets to our network. However, now we can construct host addresses using 6 bits instead 8, effectively reducing the possible number of hosts by a factor of 4. With borrowing each bit, we increase the number of subnetworks by 2 while lowering the hosts by 2.

# LAN (Local Area Network)
Like your home network. It was limited range
- **Switch** routes signals (i.e. requests) to the right host using IPs. Only works with cables.
- WiFi access point. Allows devices to connect to a wired network wirelessly.
- **Router** is a device that sits between LAN and [[#WAN (Wide Area Network)|WAN]]. It's a "gateway" device.
- Two hosts would know they're part of the same network by comparing their network addresses, which is defined by the subnet mask.
- The term **gateway** typically refers to the IP address of the router. If you enter this address into a browser, you can access the router settings to view the port forwarding configuration.
	- **NAT** (Network Address Translation) is the process the router uses to translate the IP addresses in the local network for the purpose of communication with the outside.
	- **Firewall** is a security layer associated with the router. It's a set of rules that specify how a LAN device can communicate with a device outside of the network, and wise versa. For example, a connection can form only through a certain port would be one such rule.
		- **DMZ** (DeMilitarized zone) is a zone within the local network, such that the firewall allows external connections through to any devices in that zone. 
		- **Port Forwarding**. Applications on a host in a network can communicate through ports. Each port is associated with a port, which is set up in the port forwarding configuration of your router (accessed by entering the IP address of the router in a browser). This is how the router knows where to forward certain requests. For example, the default port for connecting to a webserver via HTTP and HTTPS is 80 and 443 respectively.
A **port** is a logical connection used by programs to exchange information.

A modem is responsible for modulating and demodulating signals. Computers only understand digital signals (1s and 0s). Demodulating is converting analog signals to digital signals. Modulating is the opposite process.
## Default Gateway
A device that routes data from one network to another. Every network has one, and it's usually a router.

# WAN (Wide Area Network)
It's when you connect multiple LANs to create a larger network.

## Private WAN
The nodes in such a WAN are privately owned. So the data doesn't cross the public internet and doesn't risk getting stolen or manipulated. These can be costly.

# Other Stuff
## TCP/IP (Transmission Control Protocol)
So far, I was under the impression that the HTTP protocol was responsible for transferring data over the internet. But it turns out, HTTP (among other protocols like SMTP) is only the first layer of TCP/IP. *The tip of the iceberg!*
These layers are as follows:
- Application layer. Applications, such as a web browser or a server, send data (an HTTP request, for example) to the transport layer to be *transported*.
- Transport (TCP) layer. TCP quantizes data into **packets** of manageable size to be sent by the next layer. It also ensures that all data is received and is in order to be assembled back. Otherwise, it restarts sending the data. TCP is a [[Networking#Connection Oriented Vs. Connectionless Oriented Protocols|connection oriented protocol]].
- Internet (IP) layer. 
- Network interface. 


HTTP is a protocol for preparing a request to be sent, and interpreting it when a response is received. Like a chef that preps a meal in the kitchen of a restaurant, ready to be taken out by un camarero/a waiter (deliberately not using the word server to avoid confusion). How that request is sent across the internet is handled by another protocol.

## Connection Oriented Vs. Connectionless Oriented Protocols
TCP is a **connection oriented protocol**, meaning that a session is created and in effect until the transport is complete. On the other hand, UDP is a **connectionless oriented protocol**. It doesn't establish a constant connection and does not care if data is sent orderly or even received... UDP is sometimes called the "fire and forget" protocol because it doesn't check data and is therefore faster than TCP.


### UDP
UDP (User Datagram Protocol) has a similar purpose to TCP. But it's a [[Networking#Connection Oriented Vs. Connectionless Oriented Protocols|connectionless oriented protocol]].

## DNS (Domain Name System)
DNS is the internet address book. Responsible for converting human readable names (like google.com) to IP addresses. The DNS system can be thought of as a query pipeline, with several servers that form a hierarchical relationship.
```tikz
\begin{document}
\begin{tikzpicture}[node distance={50mm}, very thick, main/.style={draw, rectangle}, every node/.style={fill=white, scale=1}] 

\node[main] (0) {Client};
\node[main] [right of=0] (1) {Resolver};
\node[main] [above right of=1] (2) {Root server};
\node[main] [right of=1] (3) {TLD server};
\node[main] [below right of=1] (4) {Name server};
\node[main] [left of=0] (5) {Target server};


\draw[->, bend left=10] (0) edge node {1} (1) ;
\draw[->, bend left=10] (1) edge node {8} (0);

\draw[->, bend left=10] (1) edge node {2} (2);
\draw[->, bend left=10] (2) edge node {3} (1);

\draw[->, bend left=10] (1) edge node {4} (3);
\draw[->, bend left=10] (3) edge node {5} (1);

\draw[->, bend left=10] (1) edge node {6} (4);
\draw[->, bend left=10] (4) edge node {7} (1);

\draw[->, bend left=10] (0) edge node {9} (5);
\draw[->, bend left=10] (5) edge node {10} (0);

\end{tikzpicture}
\end{document}
```
- **DNS Resolver**. In most cases, this is your ISP. If the web browser doesn't have the IP address for the website we'd like to visit, it will send a request to the DNS resolver. If the IP is still not found, the resolver will send a request to the root server.
- **Root server** is responsible for directing the resolver to the correct TLD server. In other words, it will return the IP address of the TLD server to the resolver.
- **TLD** **server**. There are different servers for each **Top Level Domain**, like `.com, .net, .io, etc.`. The TLD server will redirect the resolver to the correct name server.
- **Authoritative name server**. This is where IP addresses of, along side other information, the domain we'd like to reach are actually stored.

There are only 13 root servers, and they're owned by 12 different organizations and distributed worldwide. Why 13? To make the request as fast as possible, ideally we want to transfer the IP address of those 13 servers in one packet. Each IPv4 is 32 bits, and a packet can hold on to 512 bits. $13 \times 32=416$ bits, which leaves $96$ bits for other meta data for the packet. 


## OWASP
	Open Worldwide Application Security Project is "an online community that produces freely available articles, methodologies, documentation, tools, and technologies in the fields of IoT, system software and web application security.
OWASP offers a dependency check tool that's compatible for various programming languages like Java (through maven) and Python (through pip). It goes through your project and its dependencies, and checks for known vulnerabilities.
## SMTP (Simple Mail Transfer Protocol)


## Server 
A server is just a big computer that responds to (serves) user (or client) requests. To be more technical, a server is a role in a network. Any computer can play that role. But because it receives so many requests, it's typically a powerful machine, with specially designed processor, RAM, storage, operating system. In short, it has a different system architecture than a normal computer.
### Edge Server
Type of edge device that provides an entry point into a network. Other edges devices include routers and routing switches.
## WSGI 
A WSGI (Web Server Gateway Interface) compatible server is one that knows how to convert HTTP requests into key-value objects so that Flask and other Python web frameworks (like Django) can work with it.

## SSL/TSL 
Secure Sockets Layer is the predecessor to TLS (Transport Layer Security). SSL has long been deprecated and isn't supported by modern browsers. However the name is interchangeably used with TLS, which is basically a new version of SSL. Because the technology was acquired by a new business, the name was changed to TLS. Think of SSL as a packet that contains the identity of the owners of a website and, most importantly, the public key that's used for the end-to-end encryption in the [[HTTP|HTTPS]] protocol (HTTP with encryption). These certificates are issued by a certificate authority. [More information](https://www.cloudflare.com/learning/ssl/what-is-an-ssl-certificate/) from the Cloudflare website.
SSL/TSL belongs in the application layer of [[Networking#TCP/IP (Transmission Control Protocol)|TCP/IP protocol]].

## Checksums
Hashing algorithms take in the content of a file being sent over the internet and generate a string, which is sent along the file in the transport layer of [[Networking#TCP/IP (Transmission Control Protocol)|TCP/IP protocol]]. The receiver will use the same algorithm and file to generate its own checksum value. If the two values match, it is unlikely that the data was manipulated while in transport. But it's still not guaranteed.

## Forward and Backward Proxies
The definition of Proxy is a person that does something on behalf of someone else:
	The authority to represent someone else, especially in voting.

A **forward proxy** is a server that sits between your LAN and the internet, and it retrieves data on your behalf. It has its own IP address and masks the identity of the hosts in the network. In addition, it can act as a protection layer against malware. It logs user activity, like the websites visited. It can cache frequently used websites. In short, it regulates traffic going out of a network.

A **reverse proxy** is just like a forward proxy, but it regulates traffic coming into a network. It bottlenecks and regulates incoming traffic for servers. It's effective against DDOS attacks. It also does **load balancing**, evenly distributing incoming traffic to multiple servers to avoid latency.

### NGINX
	Nginx is a web server that can also be used as a reverse proxy, load balancer, mail proxy and HTTP cache.
It's also free and opensource.

## Vulnerabilities
### CSRF
Cross site request forgery
In this type of attack, attackers take advantage of the fact that a client (browser) is authenticated. Therefore, the backend server would consider any request sent as authenticated. 
This is countered by using anti-CSRF tokens and a strict content security policy (CSP)

### Injection Attacks
#### SSRF
Server-side request forgery (SSRF) is a type of an injection attack that gets a server, one that is typically authenticated in a network of backend servers, to reveal sensitive data or services .
For example, suppose that, instead of a username, an attacker inputs the server IP address server adjoined by port number of a service running that server (for reference, a Flask web app running locally can be accessed by `http://127.0.0.1:5000`), there's a chance that service could be accessible in a poorly designed system. Attackers could try different port numbers to find which services are accessible. They can even insert file paths to reveal files!
#### XSS
Cross-site scripting 
It has to do with submitting JavaScript code for user input which then gets executed. It is an injection attack, similar to SQL injection, but with JavaScript. 
The fact is, that an HTML page can have a `<script>` tag anywhere in its body, and browsers will run it. Attackers can inject malicious script to achieve many things, like:
- accessing cookies and session information
- adding html elements like a form with an action of sending info to other servers
- adding key loggers 
- 
Encoding is an effective method to combat this attack. We must make sure that tags like `<` and `>` are properly escaped, so that no one could send something like `<script> javascript code </script>`. Input validation is another effective method.


### VPN vs. Proxy
A VPN (virtual private network) is a service that encrypts your data going from you to the VPN provider servers. Just like a proxy, it sits between you and the endpoint you're trying to reach. But it is NOT a proxy in a sense that it doesn't do any caching, monitoring users (although who knows what free VPNs do with your data), load balancing, etc.. VPNs are only for data encryption.

## Virtualization
### Hypervisor
Hypervisor is what we call the software that handles virtualization, allocating resources for each virtual machine. There are two types:
- Bare-metal hypervisor: This software sits directly on hardware. In a way, it *is* the operating system. Example are VMware ESXi and Microsoft Hyper-V.
- Hosted hypervisor: This software usually sits on an operating system. One example is the Oracle Virtualbox.
Servers are powerful computers that are usually not used up to their maximum capabilities. Instead of having separate servers for different tasks like email, webserver, or database (because one OS may not be compatible with running all these), we run several virtual environments for each task in one server, saving on power and physical space.

## Containers
Because each VM (virtual machine) runs its own OS, they occupy lots of disk space and RAM. Enter **containers**. They're similar to VMs in the fact that they're distinct, "sandbox" units. They have their own network interface and IP addresses, can run commands as root and mount file systems.
A container is a portable and lightweight package that contains the "user space" (i.e. the space to hold bins, libraries (libs), static content, dependencies, etc.) a program needs to run on any machine/environment (but the OS needs to be the same, so a container made by Docker on Windows will only run on Windows machines). There's such a thing as container engine that runs on top of the OS.
Docker is to create, manage, and run containers, and is available for Windows and Linux.

## CDN (Content Delivery Network)
**CDN** speeds up delivery of static content (which do not change), like HTML and images to users. CDN provides numerous servers (also known as **PoP** or Point of Presence) across the world, the closest of which to the user delivers the cached content. The different types of CDN are:
- DNS-based routing - each PoP has a unique IP address, and the address of the closest server is returned to the user.
- Anycast - All PoPs form a network with the same IP address. The request is sent to the closest PoP to the user.
A PoP is essentially a reverse proxy. Users are most likely retrieving their content from cache than the actual server, reducing traffic and improving performance of the webserver, because it frees resources for other dynamic processes (as in processes that involve data to be created, updated, or deleted). Other benefits of CDN are:
- CDN will also optimize the data by compression or by converting image files to other types, for example.
- Using Anycast is an effective tactic against DDOS attacks because the attack would be diffused against many servers. There are ALOT of these servers world wide, more than an attacker probably has.
- We may also want to show our users different contents based on their geolocation. CDN can help with that.
CDN companies offer a UI for developers from the webserver in this example so they can configure things like which PoP holds what content and for how long before the static content receives updates from the actual webserver.
**Cloudfare** is an example of a CDN. Another example is the Amazon **CloudFront**.

## fault tolerant


## Scalability
### Horizontal
Adding more servers to the system. You have to design software with this architecture in mind, that supports multiple servers.
### Vertical
Adding more resources like processing power, memory RAM, and storage to the same server.

## Stateful Vs. Stateless Architecture
By state, we mean the data and configuration of a system at a particular point. As an analogy, state can be compared to the frames of a video. Frame after frame, the video changes. Similarly, the state of a system (including applications) constantly changes because the data keeps being worked on.

**Stateful** is a design architecture where the state of an application (for example, the data pertaining to web requests by one user) is stored in one web server. In such an architecture, user requests are handled by a [[Networking#Forward and Backward Proxies|reverse proxy]] and sticky sessions (which are responsible for remembering which server is handling a user's requests) to be sent to the same server throughout the entire session (of a customer is shopping on Walmart.com, for example). The problem with this architecture is that it's not **fault tolerant**, meaning that the server handling the client goes down and a new server has to take over, the state of that user will also be lost because no data is being shared between the servers. Another issue with the stateful architecture is that it's not [[Networking#Scalability|scalable]]: other servers cannot join in to process requests. So for example, a customer with a big order may experience delays.
In a **stateless** design, the data is stored separately from the servers and in databases (so the servers are stateless, not the system). **Redis**, the in-memory data store, is typically used to cache the state. It's fast because it uses RAM, not storage. ==This design solves the problems of scalability and fault tolerance of a stateful architecture.== Now, the state is not stored in just one server, and multiple servers can process requests, resulting in the load being more evenly distributed. 

Stateful and Stateless isn't exclusive to servers. It's also applicable to design patterns (RESTful services), programs (like firewalls), and functions. For example, the [[HTTP|HTTP]] protocol is stateless because each request is independent and has no knowledge of the previous requests. TCP, however, is stateful. It establishes and maintains a connection between client and server until that connection is ended.

	The key principle behind something that is stateful is that it has perfect memory or knowledge of previous calls or requests, while something that is stateless has no memory or knowledge of previous calls or requests.


## Single Point of Failure
In general, you don't want to design a system that bottlenecks at a point because if that fails, so will the system.

## Routing Table
How does the router determine the best route to the next router in the internet? Using graph theory algorithms
### Congestion control
Refers to the fact that routers won't send packets (data) over busy routes. 

## Streaming
A YouTube video doesn't have to load in its entirety for users to start watching. It loads bit by bit. As such, YouTube servers will send data packet by packet. This is called streaming.


## ISP
Internet service providers own a collection of routers, and they're connected to other ISPs, forming the global internet. There are different types of ISPs that operate at different scales. But it's important to note that ISPs are connected together. Hence the definition of the internet: the network of networks.
![[map of internet.png]]

## IXP


## RAID


## Three way handshake


## File Transfer Protocol (FTP)
This is a [[Networking#Connection Oriented Vs. Connectionless Oriented Protocols|connection oriented protocol]] like HTTP that runs in the application layer of TCP/IP. However, it's used to transfer files over the internet. A server must be designed to handle FTP requests. This would be called a FTP server. A client can send these requests via a browser, or special software (FTP client) designed to provide a user friendly UI. An example is **FileZilla**.
But, it is considered outdated and unsafe and files are transferred as plain text. Instead, Secure FTP (SFTP) should be used. It offers encryption and user authentication.
However, modern file storage systems like Google Drive use their own APIs that internally use HTTPS. That's right. ==HTTPS can be used to transfer any file, not just html.==
Trivial FTP or **TFTP** is a very simple protocol for transferring files within a local network. It's often used to transport config files. It uses [[Networking#UDP|UDP]], which is a connectionless oriented protocol.

## SSH
Secure Shell is a cryptographical protocol used to establish connections. 
SSH uses **symmetrical encryption** to encrypt the entire connection. That is, one secret key is used to encrypt and decrypt messages. An **asymmetrical encryption** scheme is used for authenticating users and passing the secret key used for the symmetrical encryption. Refer to the [[Dffie-Hellman Key Exchange]] algorithm.

### Key Exchange Algorithm


### Symmetrical Encryption Ciphers
- AES
- Blowfish
- 3DES
- CAST128
- Arcfour
