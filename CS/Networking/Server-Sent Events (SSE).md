
Enables client to receive events from a server automatically. It establishes a long lasting, unidirectional HTTP connection.

HTTP is ordinarily bidirectional; it runs on top of bidirectional internet protocols like TCP or UDP—yes, HTTP can run over UDP as well.

The request and response are two halves of the same transaction. Both happen over the same connection. 

Just like [[Web Sockets]], SSE is used in real-time applications. But Web Sockets are used for bidirectional use cases where the client is sending data back to the server just as frequently as it receives it.

It starts with the TCP handshake
Then the TLS handshake
The server keeps the connection open
In modern networks (HTTP/1.1 with Keep-Alive, HTTP/2, and HTTP/3) the HTTP  connection is kept open and reused for the next request to avoid having to perform the handshake again. 

The HTTP request has a special header: `Accept: text/event-stream`, signaling to the server to keep the connection open. The response has the `Content-Type: text/event-stream` header. It will also intentionally omit the `Content-Length` header, which leaves the connection open.


Servers can attach an `id` to messages so that if the connection drops, the client automatically sends a `Last-Event-ID` header upon reconnecting, allowing the server to send only the data the client missed.

Browsers have native support for SSE via the JavaScript **`EventSource`** API. Using this API, SSE is initiated using a HTTP GET request. 