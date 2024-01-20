# IP Addresses
## IPv4 
This is a 32 bit number unique to each device that can access the internet (run the internet protocol). This number is divided into 4 octets (groups of 8 bits). Each octet can have a decimal value from 0 to 255 (because 8 bits can at most represent is 255). There can be $255^4\approx4.2\times10^9$ unique IP addresses, which isn't enough to account for all devices. 

The format of an IP address depends on [[Computer Networking#What is Subnet Mask?|subnet mask]]. For example, $255.255.255.0$ means that the last block of the IP address is used for internal networking, while the first 3 blocks are used for public internet.
## IPv6
Enter **IPv6**. It uses 128 bits, 4 parts with 32 bits each. The numbers are hexadecimal (in base 16). IPv4 offers $2^{128} \approx 3.40 \times 10^{38}$ unique  addresses.


### Dynamic IP Addresses
The fact that IPv4 addresses are limited means that it is more cost effective for internet service providers to give their users temporary IPs from a pool of available IP addresses. This means that the average home user's public IP address is constantly changing. This is one of the reasons [[Computer Networking#MAC Addresses|MAC addresses]] exist. It's possible to pay extra to obtain a **static IP address** from your ISP, one that does not change. 


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
For TCP/IP to work, we really need the MAC address of the device (server) we're trying to connect to. So computer A sends an ARP (Address Resolution Protocol) broadcast to get the MAC address of computer B. This signal is routed to the correct server using its IP address. Once we locate it, the server will send back its MAC address and communication can start.

How does the internet work?
Suppose you want to connect to Google. You need to traverse the internet. First, you open your browser and type in google.com, which gets converted to an IP address thanks to DNS.
# Managing Computer Networks
## Subnet
A  **subnet** (sub-network) is created by a router. The router physically divide a network into smaller sub-networks for enhanced security and performance.
We have a few computers connected together via a network switch. When computers within the network want to communicate with each other, they broadcast a signal. The broadcast domain consists of all computers connected to the router. If there are many computers in the network, the data traffic causes a slow down. So we create smaller networks (computers connected together by a switch) and place routers that connect these subnetworks. Broadcasts do not go bast routers. 
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
- **Switch** routes signals (i.e. requests) to the right host using IPs
- **Router** is a device that sits between LAN and [[#WAN (Wide Area Network)|WAN]]. It's a "gateway" device.
- Two hosts would know they're part of the same network by comparing their network addresses, which is defined by the subnet mask.
- The term **gateway** typically refers to the IP address of the router. If you enter this address into a browser, you can access the router settings to view the port forwarding configuration.
	- **NAT** (Network Address Translation) is the process the router uses to translate the IP addresses in the local network for the purpose of communication with the outside.
	- **Firewall** is a security layer associated with the router. It's a set of rules that specify how a LAN device can communicate with a device outside of the network, and wise versa. For example, a connection can form only through a certain port would be one such rule.
		- **DMZ** (DeMilitarized zone) is a zone within the local network, such that the firewall allows external connections through to any devices in that zone. 
		- **Port Forwarding**. Applications on a host in a network can communicate through ports. The default port for connecting to a webserver via HTTP and HTTPS is 80 and 443 respectively.
A port is a logical connection used by programs to exchange information.

A modem is responsible for modulating and demodulating signals. Computers only understand digital signals (1s and 0s). Demodulating is converting analog signals to digital signals. Modulating is the opposite process.
# WAN (Wide Area Network)


# Other Stuff
## TCP/IP (Transmission Control Protocol)
So far, I was under the impression that the HTTP protocol was responsible for transferring data over the internet. But it turns out, HTTP (among other protocols like SMTP) is only the first layer of TCP/IP. *The tip of the iceberg!*
These layers are as follows:
- Application layer. Applications, such as a web browser or a server, send data (an HTTP request, for example) to the transport layer to be *transported*.
- Transport (TCP) layer. TCP quantizes data into packets of manageable size to be sent by the next layer. It also ensures that all data is received and is in order to be assembled back. Otherwise, it restarts sending the data. TCP is a **connection oriented protocol**, meaning that a session is created and in effect until the transport is complete.
- Internet (IP) layer. 
- Network interface. 

HTTP is a protocol for preparing a request to be sent, and interpreting it when a response is received. Like a chef that preps a meal in the kitchen of a restaurant, ready to be taken out by un camarero/a waiter (deliberately not using the word server to avoid confusion). How that request is sent across the internet is handled by another protocol.

### UDP
UDP (User Datagram Protocol) has a similar purpose to TCP. But it's a **connectionless oriented protocol**. It doesn't establish a constant connection and does not care if data is sent orderly or received.. UDP is sometimes called the "fire and forget" protocol because it doesn't check data and is therefore faster than TCP.

## DNS (Domain Name System)
Internet address book. Responsible for converting human readable names (like google.com) to IP addresses.

### DNS Resolver

IP (Internet Protocol)
OWASP
SMTP (Simple Mail Transfer Protocol)
## Server 
A server is just a big computer that responds to (serves) user (or client) requests. To be more technical, a server is a role in a network. Any computer can play that role. But because it receives so many requests, it's typically a powerful machine, with specially designed processor, RAM, storage, operating system. In short, it has a different system architecture than a normal computer.
### Edge Server
Type of edge device that provides an entry point into a network. Other edges devices include routers and routing switches.
## WSGI 
A WSGI (Web Server Gateway Interface) compatible server is one that knows how to convert HTTP requests into key-value objects so that Flask and other Python web frameworks (like Django) can work with it.

## SSL/TSL 
Secure Sockets Layer is the predecessor to TLS (Transport Layer Security). SSL has long been deprecated and isn't supported by modern browsers. However the name is interchangeably used with TLS, which is basically a new version of SSL. Because the technology was acquired by a new business, the name was changed to TLS. Think of SSL as a packet that contains the identity of the owners of a website and, most importantly, the public key that's used for the end-to-end encryption in the [[CS/HTTP|HTTPS]] protocol (HTTP with encryption). These certificates are issued by a certificate authority. [More information](https://www.cloudflare.com/learning/ssl/what-is-an-ssl-certificate/) from the Cloudflare website.

## Forward and Backward Proxies
The definition of Proxy is a person that does something on behalf of someone else:
	The authority to represent someone else, especially in voting.

A **forward proxy** is a server that sits between your LAN and the internet, and it retrieves data on your behalf. It has its own IP address and masks the identity of the hosts in the network. In addition, it can act as a protection layer against malware. It logs user activity, like the websites visited. It can cache frequently used websites. In short, it regulates traffic going out of a network.

A **reverse proxy** is just like a forward proxy, but it regulates traffic coming into a network. It bottlenecks and regulates incoming traffic for servers. It's effective against DDOS attacks. It also does **load balancing**, evenly distributing incoming traffic to multiple servers to avoid latency.

### NGINX
	Nginx is a web server that can also be used as a reverse proxy, load balancer, mail proxy and HTTP cache.
It's also free and opensource.
## SSRF
Server-side request forgery

## XSS
Cross-site scripting 

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

**Stateful** is a design architecture where the state of an application (for example, the data pertaining to web requests by one user) is stored in one web server. In such an architecture, user requests are handled by a [[Computer Networking#Forward and Backward Proxies|reverse proxy]] and sticky sessions (which are responsible for remembering which server is handling a user's requests) to be sent to the same server throughout the entire session (of a customer is shopping on Walmart.com, for example). The problem with this architecture is that it's not **fault tolerant**, meaning that the server handling the client goes down and a new server has to take over, the state of that user will also be lost because no data is being shared between the servers. Another issue with the stateful architecture is that it's not [[Computer Networking#Scalability|scalable]]: other servers cannot join in to process requests. So for example, a customer with a big order may experience delays.
In a **stateless** design, the data is stored separately from the servers in databases (so the servers are stateless, not the system). **Redis**, the in-memory data store, is typically used to cache the state. It's fast because it uses RAM, not storage. ==This design solves the problems of scalability and fault tolerance of a stateful architecture.== Now, the state is not stored in just one server, and multiple servers can process requests, resulting in the load being more evenly distributed. 

Stateful and Stateless isn't exclusive to servers. It's also applicable to design patterns (RESTful services), programs (like firewalls), and functions. For example, the [[CS/HTTP|HTTP]] protocol is stateless because each request is independent and has no knowledge of the previous requests. TCP, however, is stateful. It establishes and maintains a connection between client and server until that connection is ended.

	The key principle behind something that is stateful is that it has perfect memory or knowledge of previous calls or requests, while something that is stateless has no memory or knowledge of previous calls or requests.