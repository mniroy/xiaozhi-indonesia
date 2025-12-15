# MCP Protocol IoT Control Usage Instructions

> This document introduces how to implement IoT control for ESP32 devices based on the MCP protocol. For detailed protocol flow, please refer to [`mcp-protocol.md`](./mcp-protocol.md).

## Introduction

MCP (Model Context Protocol) is the next-generation protocol recommended for IoT control. It uses standard JSON-RPC 2.0 format to discover and call "Tools" between the backend and the device, enabling flexible device control.

## Typical Usage Flow

1. Device establishes a connection with the backend via a base protocol (e.g., WebSocket/MQTT) after startup.
2. The backend initializes the session via the MCP protocol's `initialize` method.
3. The backend retrieves all tools (functions) supported by the device and their parameter descriptions via `tools/list`.
4. The backend calls specific tools via `tools/call` to control the device.

For detailed protocol formats and interactions, please see [`mcp-protocol.md`](./mcp-protocol.md).

## Device-Side Tool Registration Method

The device uses the `McpServer::AddTool` method to register "Tools" that can be called by the backend. Its common function signature is as follows:

```cpp
void AddTool(
    const std::string& name,           // Tool name, recommended to be unique and hierarchical, e.g., self.dog.forward
    const std::string& description,    // Tool description, concise explanation for LLM understanding
    const PropertyList& properties,    // Input parameter list (can be empty), supports types: boolean, integer, string
    std::function<ReturnValue(const PropertyList&)> callback // Callback implementation when tool is called
);
```
- `name`: Unique identifier for the tool, recommended to use "module.function" naming style.
- `description`: Natural language description to facilitate AI/user understanding.
- `properties`: Parameter list, supporting boolean, integer, string types, with range and default value specification.
- `callback`: Actual execution logic when a call request is received; return value can be bool/int/string.

## Typical Registration Example (Taking ESP-Hi as an example)

```cpp
void InitializeTools() {
    auto& mcp_server = McpServer::GetInstance();
    // Example 1: No parameters, control robot forward
    mcp_server.AddTool("self.dog.forward", "Move robot forward", PropertyList(), [this](const PropertyList&) -> ReturnValue {
        servo_dog_ctrl_send(DOG_STATE_FORWARD, NULL);
        return true;
    });
    // Example 2: With parameters, set RGB light color
    mcp_server.AddTool("self.light.set_rgb", "Set RGB color", PropertyList({
        Property("r", kPropertyTypeInteger, 0, 255),
        Property("g", kPropertyTypeInteger, 0, 255),
        Property("b", kPropertyTypeInteger, 0, 255)
    }), [this](const PropertyList& properties) -> ReturnValue {
        int r = properties["r"].value<int>();
        int g = properties["g"].value<int>();
        int b = properties["b"].value<int>();
        led_on_ = true;
        SetLedColor(r, g, b);
        return true;
    });
}
```

## Common Tool Call JSON-RPC Examples

### 1. Get Tool List
```json
{
  "jsonrpc": "2.0",
  "method": "tools/list",
  "params": { "cursor": "" },
  "id": 1
}
```

### 2. Control Chassis Forward
```json
{
  "jsonrpc": "2.0",
  "method": "tools/call",
  "params": {
    "name": "self.chassis.go_forward",
    "arguments": {}
  },
  "id": 2
}
```

### 3. Switch Light Mode
```json
{
  "jsonrpc": "2.0",
  "method": "tools/call",
  "params": {
    "name": "self.chassis.switch_light_mode",
    "arguments": { "light_mode": 3 }
  },
  "id": 3
}
```

### 4. Camera Flip
```json
{
  "jsonrpc": "2.0",
  "method": "tools/call",
  "params": {
    "name": "self.camera.set_camera_flipped",
    "arguments": {}
  },
  "id": 4
}
```

## Notes
- Tool names, parameters, and return values are subject to device-side `AddTool` registration.
- It is recommended that all new projects use the MCP protocol for IoT control.
- For detailed protocol and advanced usage, please consult [`mcp-protocol.md`](./mcp-protocol.md).