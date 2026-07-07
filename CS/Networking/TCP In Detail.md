I
TCP stands for **Transmission Control Protocol**

<iframe width="560" height="315" src="https://www.youtube.com/embed/F27PLin3TV0?si=e2zbVcbj_Arni9pf&amp;controls=0" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

TCP is a two way connection. That means the sender and receiver can communicate Simultaneously. 

TCP ensures data integrity by using Checksums
It divides up data into segment. Each segment is consisted of a header. 
The header has source and destination IP addresses and ports, header flags (which are used to signify the start (SYN, short for synchronize) and end (FIN) of the connection), Each segment has a number. This means data does not necessarily have to be sent in order. The receiver will use segment numbers to put the data back in order. The size of each segment is communicated as MSS in the packet headers. 

The connection starts with a *3-way handshake*. The sender will generate and send a random sequence number for the first sequence. The receiver will generate and send back its own sequence number, as well as an *acknowledgement number*. This is the next sequence number the receiver is expecting from the sender. Finally, the sender will send a response: a sequence number, and an acknowledgement number.   


Here's an article that also explains the sequence numbers 
https://www.geeksforgeeks.org/computer-networks/wrap-around-concept-and-tcp-sequence-number/



To end the connection, the sender and receiver perform a 4-way handshake. Basically 4 signals are sent. At the center of these is the FIN flag in the header that is now set to 1. The server/receiver sends a segment with this flag set to 1. The client/original sender acknowledges this with a message. The client then sends a message with its FIN set to 1. And the server acknowledges it. The end.


# New
At the TCP layer, the packet is consisted of two things: the header and the payload. 
Some packets only contain a header. Example are the packets sent during the handshake and the one sent during connection termination.
The header size is not constant. At minimum it's 20 bytes, and at most it's 60 bytes.
Every header must have the core, consisting of 20 mandatory bytes. 


| Element                | Size        | Purpose |
| ---------------------- | ----------- | ------- |
| Source port            | 2 bytes     |         |
| Destination port       | 2 bytes     |         |
| Sequence number        | 4 bytes     |         |
| Acknowledgement number | 4 bytes     |         |
| Data offset            | 4 bits      |         |
| Reserved               | 3 bits      |         |
| Flags                  | 9 bits      |         |
| Window                 | 2 bytes     |         |
| Urgent pointer         | 2 bytes     |         |
| Checksum               | 2 bytes     |         |
| Extra options          | 0-40 bytes  |         |
| **Total**              | 20-60 bytes |         |

The "flag" bits, when they're on (i.e. set to 1), identify the nature of the packet. For example, when the `SYN` flag is on, it means this is the first packet sent by the sender to Initiates a connection with the receiver. **The purpose is to *synchronize* with the receiver.**  ==The first packet does not contain any data.== 
The receiver sends an acknowledgement-synchronize (`SYN-ACK`) response. Both the `SYN` and `ACK` flags are on.
So the server sends its sequence number. And the receive sends its own sequence number back.

```tx
| TCP Handshake  |||
| Handshake step | Sender                  | Receiver               | 
| :------------: | :---------------------- | ---------------------- |
| 1              | Sends its sequence number, $X$               |                        |
| 2              |                         | 1. Acknowledges $X$    |\
|                |                         | 2. Sends its own sequence number, $Y$           |\
|                |                         | 3. Expects $X+1$       |
| 3              |  1. Acknowledges $Y$    |                        |\
|                |  2. Expects $Y+1$ next  |                        |
```




The first sequence numbers (by sender and receiver) are random. Subsequent numbers are the "cumulative byte stream location of the packet's first payload byte" (???)

*Data offset* is the size of the header, but it only has 4 bits. The maximum number we can represent is 15, but the largest the header can be 60 bytes. To overcome this limitation, the receiver multiplies the offset by 4 (because $4*15=60$ bytes, the maximum header size). 


Why are there two sequence numbers? Because once the TCP handshake is complete, **there is no dedicated "sender" and "receiver."** There are only two **Peers**. And both peers are actively sending data. Both peers are actively receiving data. It is a two-way highway. Each side is independent of the other. So each side needs its own sequence number. The acknowledgement number is related to the sequence number of the other peer:
- **Sequence Number:** "This is the byte-counter for the data **I am sending to you**."
- **Acknowledgment Number:** "I have perfectly received every single contiguous byte up to this specific byte offset."
The receiver periodically sends acknowledgement packets to the sender. This way, the sender knows that, hey, it's been a while and the rest of the data hasn't been received, so it assumes the data bytes after the acknowledgement number were lost and re-sends them
The receiver adds an artificial delay between each acknowledgement packet. This way, it can send more data it wants to send piggybacking along the acknowledgment packet. This is because the receiver doesn't just send acknowledgment packets: it also sends **HTTP control frames**, used to manage connection state, flow control, etc.. For example, the client can signal to the server to send data faster or slow down; it can stop the stream if the user clicks away, for example; it sends periodic health checks to the server to make sure the connection is still active.


==Think of TCP has a highway.== There is no relationship between the data moving in different sides of the highway. This is not the application layer of the network model. 

The TCP layer is under the Application layer. Multiple applications could be sending data back and forth simultaneously. So how does the TCP layer know which goes to where? Well, that's not right...A TCP connection is *not a generic, shared highway for the entire machine*. It is a strictly bound, private tunnel between exactly _two_ specific application processes. Different applications absolutely cannot "share" the same TCP connection to send data.
A connection is established between two peers for two specific apps on each side, which communicate through the specified ports.

The OS sits between the TCP and the application layers. 
Each connection has a unique combination of source IP, destination IP, source port, destination port. The OS creates a 4-tuple of these numbers. Two applications communicating on two machines will always map to the same tuple. 
The OS creates a map of this tuple to a memory buffer. After assembling data, it puts it in the right memory buffer, which the correct application can access. That memory buffer is called a **TCP socket.** Applications access it via a *[[Unix File Tables|file descriptor]]*.
The OS handles all the routing, sequencing, and acknowledging under the hood. At the application layer, we can just call a read function and read a pristine, ordered stream of bytes.

HTTP is based on TCP/IP
[[Web Sockets]] are based on HTTP.

*TCP is an idle connection*