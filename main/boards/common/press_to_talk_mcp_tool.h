#ifndef PRESS_TO_TALK_MCP_TOOL_H
#define PRESS_TO_TALK_MCP_TOOL_H

#include "mcp_server.h"
#include "settings.h"

// Reusable press-to-talk mode MCP tool class
class PressToTalkMcpTool {
private:
  bool press_to_talk_enabled_;

public:
  PressToTalkMcpTool();

  // Initialize tool, register to MCP server
  void Initialize();

  // Get current press-to-talk mode status
  bool IsPressToTalkEnabled() const;

private:
  // Callback function for MCP tool
  ReturnValue HandleSetPressToTalk(const PropertyList &properties);

  // Internal method: set press to talk status and save to settings
  void SetPressToTalkEnabled(bool enabled);
};

#endif // PRESS_TO_TALK_MCP_TOOL_H