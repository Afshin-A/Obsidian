![[MCP diagram.png]]
 > **MCP** (Model Context Protocol) is an open-source standard for connecting AI applications to external systems.

There are 3 components in MCP:
1. **Host**: This is the AI application the user interacts with. It sends prompts to an underlying LLM and receives and processes the responses. It's the center of the application. It sits at the center and communicates with both the external LLM API provider and the MCP Server providing the tools.
2. **Client**: This is a software component that lives inside the host. It's responsible to maintain a connection between the host and an MCP server. A host can have multiple clients. Each client handles connection to a different external data source. 
3. **Server**: This is an isolated program that has the logic (data or functions) the host needs access to. It receives JSON-RPC requests from the Client, performs the requested action, and ==returns the context==? The server is unaware of the LLM. It simply exposes its functions and data schemas in a standardized format.
The server can be local or remote on a separate machine (like an AWS cloud instance). Consequently, there are two methods of communication supported in MCP:
- STDIO for local servers: Client spawns the Server as a child process on the exact same machine
- HTTP for remote servers: Client sends JSON payloads via POST requests to the, and the Server pushes real-time updates back via an open [[Server-Sent Events (SSE)|SSE]].



For example, VS Code is an MCP host. It creates an MCP client object, which maintains a connection to the Claude MCP server. If it also wants to connect to another server (perhaps a local server that gives it context from the system's files), it would create another MCP client.


The MCP client use **JSON-RPC** to request response from the MCP server. 
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
