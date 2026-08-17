Q: Suppose there are multiple web apps on a server. How does data sent by the TCP protocol find its way to the right application?
A reverse proxy (like Nginx) acts as a traffic cop at port 80. It reads the incoming HTTP data and uses specific routing rules to direct the request to the correct application socket or internal port. The reverse proxy maintains its own listening TCP socket on port 80 to accept incoming client connections.  It then opens a separate, distinct backend socket to forward that data to the target application.


Applications can have zero to many networking sockets
Each network socket is associated with a networking port
A port is a 16 bit number. A TCP endpoint is a tuple of `(IP, port)`, which exists in the header for each TCP/IP packet
The OS uses this to decide which socket receives the incoming data stream
An **ephemeral port** is a temporary port number the OS dynamically assigns to an application for the duration of a specific network communication session. ==where is it used?==
The OS identifies TCP socket by using a unique 4-tuple of `(source IP, source port, destination IP, destination port)`
Each connection has its own socket on both ends.

# Multiplexing I/O
