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