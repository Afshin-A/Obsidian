
client receive automatic events from a server over a long lasting, unidirectional HTTP connection

Just like [[Web Sockets]], SSE is used in real-time applications. But Web Sockets are used for bidirectional use cases where the client is sending data back to the server just as frequently as it receives it.

It starts with the TCP handshake
Then the TLS handshake
The server keeps the connection open
In modern networks (HTTP/1.1 with Keep-Alive, HTTP/2, and HTTP/3) the HTTP  connection is kept open and reused for the next request to avoid having to perform the handshake again. 

Servers can attach an `id` to messages so that if the connection drops, the client automatically sends a `Last-Event-ID` header upon reconnecting, allowing the server to send only the data the client missed.