# A Short Summary of TCP
TCP stands for **Transmission Control Protocol**

<iframe width="560" height="315" src="https://www.youtube.com/embed/F27PLin3TV0?si=e2zbVcbj_Arni9pf&amp;controls=0" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

*TCP is a two-way connection*, meaning the sender and receiver can communicate simultaneously. For example, HTTP request and response occur over the same TCP session. *WebSocket* connections can stay open for a very long time. Both of these protocols on top of the TCP layer in the *[[OSI and TCP IP Models|OSI model]]*.

TCP ensures data integrity by using checksums.

TCP divides data into segments. Each segment has a header and the payload. 
The header includes a few important things:
- IP address and *network port* for both the sender and the receiver. A 4-tuple of these numbers is used by the server and client's operating systems to identify and manage the associated *network sockets* on each machine. 
- *Header flags* are used to signify the start (SYN, short for synchronize) and end (FIN) of the connection.
- Segment number. Data does not necessarily have to be sent in order over the network. The receiver will use segment numbers to put the data back in order. In addition, the size of each segment is communicated as MSS in the packet headers. 

The connection starts with a **3-way handshake**. 
1. The sender will generate a random number and send it to the receiver. This is called the **sequence number**.
2. The receiver will generate its own sequence number and sends it back to the sender. It also sends an **acknowledgement number**. This mechanism is used to communicate with the sender the bytes received or needs to be retransmitted. 
- Which data needs retransmission?
- Whether the receiver even received anything.
1. Finally, the sender will send its next sequence number, and an acknowledgement number.
In the end, both the sender and the receiver 


Here's an article that also explains the sequence numbers 
https://www.geeksforgeeks.org/computer-networks/wrap-around-concept-and-tcp-sequence-number/



To end the connection, the sender and receiver perform a **4-way handshake**. Four signals are exchanged in total. The FIN flag in the header is now set to 1. The server/receiver sends a segment with this flag set to 1. The client/original sender acknowledges this with a message. The client then sends a message with its FIN set to 1. And the server acknowledges it. The end.


# A more detailed explanation of TCP
At the TCP layer, the packet is consisted of two things: the *header* and the *payload*. 
Some packets only contain a header, such as those sent during the handshake and the one sent for connection termination.
In addition, the *header size is not constant*. At minimum it's 20 bytes and can go up to 60 bytes.
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




The first sequence numbers (by sender and receiver) are random. Subsequent numbers are the "cumulative byte stream location of the packet's first payload byte". *Sequence number is a byte counter for the data being sent.* This allows TCP segments to be of varying sizes.

*Data offset* is a the field in the header that indicates its size (of the header), but it only has 4 bits. The maximum number we can represent is 15, but the largest the header can be 60 bytes. To overcome this limitation, the receiver multiplies the offset by 4 (because $4*15=60$ bytes, the maximum header size). 

There's technically no senders and receivers in TCP. But we use this terminology for simplicity and clarity in our discussions.

Why are there two sequence numbers? Because once the TCP handshake is complete, **there is no dedicated "sender" and "receiver."** There are only two **Peers**. And both peers are actively sending data. Both peers are actively receiving data. It is a two-way highway. Each side is independent of the other. So each side needs its own sequence number. The acknowledgement number is related to the sequence number of the other peer:
- **Sequence Number:** "This is the byte-counter for the data **I am sending to you**."
- **Acknowledgment Number:** "I have perfectly received every single contiguous byte up to this specific byte offset."
The receiver periodically sends acknowledgement packets to the sender. This way, the sender knows that, hey, it's been a while and the rest of the data hasn't been received, so it assumes the data bytes after the acknowledgement number were lost and re-sends them
The receiver adds an artificial delay between each acknowledgement packet. This way, it can send more data it wants to send piggybacking along the acknowledgment packet. This is because the receiver doesn't just send acknowledgment packets: it also sends **HTTP control frames**, used to manage connection state, flow control, etc.. For example, the client can signal to the server to send data faster or slow down; it can stop the stream if the user clicks away, for example; it sends periodic health checks to the server to make sure the connection is still active.


==Think of TCP has a highway.== There is no relationship between the data moving in different sides of the highway. This is not the application layer of the network model. 

The TCP layer is under the Application layer. Multiple applications could be sending data back and forth simultaneously. So how does the TCP layer know which goes to where? Well, that's not right...A TCP connection is *not a generic, shared highway for the entire machine*. It is a strictly bound, private tunnel between exactly _two_ specific application processes. Different applications absolutely cannot "share" the same TCP connection to send data.
A connection is established between two peers for two specific apps on each side, which communicate through the specified ports.

The OS sits between the TCP and the application layers. 
Each connection has a unique combination of *source IP, destination IP, source port, destination port*. The OS creates a 4-tuple of these numbers. Two applications communicating on two machines will always map to the same tuple. 
The OS creates a map of this tuple to a memory buffer. After assembling data, it puts it in the right memory buffer, which the correct application can access. That memory buffer is called a [[More notes on TCP Sockets and Ports|TCP Socket]]. Applications access it via a *[[File Tables in Unix|file descriptor]]*.
The OS handles all the routing, sequencing, and acknowledging under the hood. At the application layer, we can just call a read function and read a pristine, ordered stream of bytes.

HTTP is based on TCP/IP
[[Web Sockets]] are based on HTTP.

*TCP is an idle connection*


## acknowledgment numbers

The sender fires packets. 
The receiver keeps track of two things: the next expected byte, AKA the acknowledgment number, and a data structure that stores the out-of-order received segments in the receiver's buffer.
Both the sender and receiver have a fixed-size memory buffer. 
Adjacent bytes get merged together. 
The data structure stores a range of bytes.
When a new segment arrives, we want to look up its closest neighbors and merge them together.
The acknowledgment number goes up.
TCP has different implementations, but they commonly use balanced search trees such as a red-black tree where the key is the segment number
