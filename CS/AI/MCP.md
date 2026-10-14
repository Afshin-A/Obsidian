![[MCP diagram.png]]

MCP host: An AI application that needs context
MCP client: Created by the host as an intermediary between the host and an MCP server to maintain the connection
MCP server: Provides the context

VS Code is an MCP Host
It creates an MCP client object, which maintains a connection to the Claude MCP server. If it also wants to connect to another server (perhaps a local server that gives it context from the system's files), it would create another MCP client.

https://modelcontextprotocol.io/docs/2026-07-28/learn/architecture
