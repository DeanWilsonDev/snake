#include "raylib-user-interface-facade.hpp"
#include "debug/i-debug-hud.hpp"
#include "debug/debug-node.hpp"
#include "raylib.h"
#include <umbra/log.h>
#include <memory>
#include <string>
#include "core/math/vector-2d.hpp"

namespace RaylibFacade::UserInterface {

RaylibUserInterfaceFacade::RaylibUserInterfaceFacade()
{
  LOG_TRACE("Initializing Raylib User Interface");
}
void RaylibUserInterfaceFacade::DrawTextCentered(
    const char* text, Core::Math::Vector2D position, const float fontSize
)
{
  const auto [x, y] = MeasureTextEx(GetFontDefault(), text, fontSize, 1);
  position.x -= x / 2.0f;
  DrawText(text, position.x, position.y, fontSize, {255, 255, 255, 255});
}

void RaylibUserInterfaceFacade::RenderDebugHUD(const Debug::IDebugHUD& debugHUD) 
{
  int y = 10;
  int lineCount = 0;
  debugHUD.Visit([&](const std::string&, const Debug::DebugNode&, int) { lineCount++; });

  int lineHeight = 20;
  int bgX = 0;
  int bgY = 0;
  int bgWidth = 350;
  int bgHeight = lineCount * lineHeight + 20;

  Color bgColor = {0, 0, 0, 155};

  DrawRectangle(bgX, bgY, bgWidth, bgHeight, bgColor);

  debugHUD.Visit([&](const std::string& key, const Debug::DebugNode& node, int depth) {
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
