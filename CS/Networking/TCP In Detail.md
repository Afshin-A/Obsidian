
<iframe width="560" height="315" src="https://www.youtube.com/embed/F27PLin3TV0?si=e2zbVcbj_Arni9pf&amp;controls=0" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

TCP is a two way connection. That means the sender and receiver can communicate Simultaneously. 

TCP ensures data integrity by using Checksums
It divides up data into segment. Each segment is consisted of a header. 
The header has source and destination IP addresses and ports, header flags (which are used to signify the start (SYN, short for synchronize) and end (FIN) of the connection), Each segment has a number. This means data does not necessarily have to be sent in order. The receiver will use segment numbers to put the data back in order. The size of each segment is communicated as MSS in the packet headers. 

The connection starts with a 3-way handshake. The sender will generate and send a random sequence number for the first sequence. The receiver will generate and send back its own sequence number, as well as an acknowledgement number. This is the next sequence number the receiver is expecting from the sender. Finally, the sender will send a response: a sequence number, and an acknowledgement number.   


Here's an article that also explains the sequence numbers 
https://www.geeksforgeeks.org/computer-networks/wrap-around-concept-and-tcp-sequence-number/



To end the connection, the sender and receiver perform a 4-way handshake. Basically 4 signals are sent. At the center of these is the FIN flag in the header that is now set to 1. The server/receiver sends a segment with this flag set to 1. The client/original sender acknowledges this with a message. The client then sends a message with its FIN set to 1. And the server acknowledges it. The end.
