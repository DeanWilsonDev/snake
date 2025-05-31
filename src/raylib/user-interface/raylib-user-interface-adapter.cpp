#include "raylib-user-interface-adapter.hpp"
#include "raylib.h"

namespace RaylibAdapter::UserInterface {

RaylibUserInterfaceAdapter::RaylibUserInterfaceAdapter()
{
  LOG_TRACE("Initializing Raylib User Interface");
}
void RaylibUserInterfaceAdapter::DrawTextCentered(const char* text, Vector2 position, float fontSize)
{
  const Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 1);
  position.x -= textSize.x / 2.0f;
  DrawText(text, position.x, position.y, fontSize, {255, 255, 255, 255});
}

}  // namespace RaylibAdapter::UserInterface
