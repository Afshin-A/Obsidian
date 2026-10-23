# What is JSON-RPC?
A stateless protocol that uses the JSON format. RPC stands for remote procedure call, and as the name suggests, it is used to send a message to a server and request it to execute a specific function, and return the results.
It works independently of the underlying communication medium (i.e. the below layers in the networking model). This quality is also called **transport-agnostic**. In other words, JSON-RPC payloads can be sent with HTTP or WebSockets, or locally via stdio [^1][^2]
The request body looks something like this:
```json
{
  "jsonrpc": "2.0",
  "method": "subtract",
  "params": [42, 23],
  "id": 1
}
```
`jsonrpc` is the protocol version and *must be included*.
`params` is optional.
`id`: Since it may take some time for the server to prepare the result (process the request, run the function). Therefore, the client may not receive results in the same order as the requests. The  server includes the same `id` in the response so the client knows which request it corresponds to.
`id` is optional. If a request doesn't have it, the server treats it as receiving a notification. Fire and forget.
To reduce network traffic, clients can send an array of requests instead of one by one. Similarly, the server can send back an array of responses.



https://modelcontextprotocol.io/docs/2026-07-28/learn/architecture


[^1]: I just wanted to define the term "**transport-agnostic**" since it sounds fancy for an interview
[^2]: Agnostic means existing without knowledge of, or indifference to, a specific entity