#include "raylib-debug-user-interface-facade.hpp"
#include "core/debug/i-debug-hud.hpp"
#include "core/debug/debug-node.hpp"
#include "raylib.h"
#include "core/logging/log.hpp"
#include <string>

namespace RaylibFacade::UserInterface {

RaylibDebugUserInterfaceFacade::RaylibDebugUserInterfaceFacade()
{
  LOG_TRACE("Initializing Raylib Debug User Interface");
}

void RaylibDebugUserInterfaceFacade::RenderDebugHUD(const Core::Debug::IDebugHUD& debugHUD)
{
  int y = 10;
  int lineCount = 0;
  debugHUD.Visit([&](const std::string&, const Core::Debug::DebugNode&, int) { lineCount++; });

  int lineHeight = 20;
  int bgX = 0;
  int bgY = 0;
  int bgWidth = 350;
  int bgHeight = lineCount * lineHeight + 20;

  Color bgColor = {0, 0, 0, 155};

  DrawRectangle(bgX, bgY, bgWidth, bgHeight, bgColor);

  debugHUD.Visit([&](const std::string& key, const Core::Debug::DebugNode& node, int depth) {
    int x = 10 + depth * 20;

    if (node.IsValue()) {
      DrawText(
          TextFormat("%s: %s", key.c_str(), node.AsValue()->ToString().c_str()), x, y, 16, WHITE
      );
    }
    else {
      DrawText(key.c_str(), x, y, 16, YELLOW);
    }
    y += 20;
  });
}

}  // namespace RaylibFacade::UserInterface
