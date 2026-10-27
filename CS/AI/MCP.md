![[MCP diagram.png]]
 > **MCP** (Model Context Protocol) is an open-source standard for connecting AI applications to external systems.

There are 3 components in MCP:
1. **Host**: This is the AI application the user interacts with. It sends prompts to an underlying LLM and receives and processes the responses. It's the center of the application. It sits at the center and communicates with both the external LLM API provider and the MCP Server providing the tools.
2. **Client**: This is a software component that lives inside the host. It's responsible to maintain a connection between the host and an MCP server. A host can have multiple clients. Each client handles connection to a different external data source. 
3. **Server**: This is an isolated program that has the logic (data or functions) the host needs access to. It receives JSON-RPC requests from the Client, performs the requested action, and ==returns the context==? The server is unaware of the LLM. It simply exposes its functions and data schemas in a standardized format.

For example, VS Code is an MCP host. It creates an MCP client object, which maintains a connection to the Claude MCP server. If it also wants to connect to another server (perhaps a local server that gives it context from the system's files), it would create another MCP client.

The server can be local or remote on a separate machine (like an AWS cloud instance). Consequently, there are two methods of communication supported in MCP:
- STDIO for local servers: Client spawns the Server as a child process on the exact same machine
- HTTP for remote servers: Client sends JSON payloads via POST requests to the, and the Server pushes real-time updates back via an open [[Server-Sent Events (SSE)|SSE]].



The MCP client sends and receives **[[JSON-RPC]]** payloads to communicate with the MCP server. 


First, the client needs to know what the server is capable of using the `server/discover` method. So the server needs to have this method per the protocol. It's technically not required because the AI can guess the tool names and we can implement error handling if they don't exist.

*MCP is stateless*. Every request carries its own context.
Every request must contain a `_meta` object in its parameters so the server knows the identity of the client. 

```json
{
  "jsonrpc": "2.0",
  "id": "discover-1",
  "method": "server/discover",
  "params": {
    "_meta": {
      "io.modelcontextprotocol/protocolVersion": "2026-07-28",
      "io.modelcontextprotocol/clientInfo": {
        "name": "SocialMediaAgent",
        "version": "1.0.0"
      },
      "io.modelcontextprotocol/clientCapabilities": {}
    }
  }
}
```

The server responds with its own information and capabilities.
```json
{
  "jsonrpc": "2.0",
  "id": "discover-1",
  "result": {
    "resultType": "complete",
    "supportedVersions": ["2026-07-28"],
    "capabilities": {
      "tools": { "listChanged": true },
      "resources": {}
    },
    "_meta": {
      "io.modelcontextprotocol/serverInfo": {
        "name": "instagram-api-server",
        "version": "2.1.0"
      }
    }
  }
}
```
`id` in the response matches the request.

There are two types of errors that can happen:
1. Protocol errors may happen because of an issue in the protocol, like if the client sends an incorrect JSON-RPC request, if the connection drops, etc..
2. Tool errors happen if the actual tools the server is trying to use fails. The server will send a valid JSON-RPC response, and it also includes a field `"isError": true` followed by a string explaining the error, so the *AI can understand what went wrong and try again*. This is incredibly important for AI development.

Since MCP is stateless, does the host need to send its entire context/history with every request? But the host only needs the result of a function; why was MCP statefull before?

The host does not need to send the entire history to the server. It only extracts the parameters it needs for the function it needs to run. The server doesn't need to know why the AI chose to run the function. Whether the MCP protocol is stateless or not, it has to do with the protocol, not the contents of the payloads. 
The server stores client information and configuration, and routes the client to the same backend server every time. This is fine for local servers or even small applications. But AI applications are becoming more complexed, and it's challenging to scale in microservice-scale applications that scale vertically. 

The MCP capabilities break down to 3 different categories:
1. Tools—executable functions the AI can autonomously choose to run. Client sends `tools/list` request to discover the tools, and a `tools/call` request to call them.
2. Resources—read only sources that provide context to the AI. Examples are files, database records, API responses. These are application controlled; the host injects them into the LLM's prompt. Client sends `resources/list` request. Server responds with the *URI* of the resources.
3. prompts—instructions for the LLM in the form of reusable, dynamic templates that can take arguments 

Resources and prompts are not necessarily static. While a resource could be a file, it could also point to a dynamic list like `social://comments/latest` where they change every few seconds. Prompts can actually accept arguments from the client or it could contain query results from a database before it's returned to the client. 

https://share.google/aimode/DCATWJrDfoXgjoXlA
