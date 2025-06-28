#include "raylib-user-interface-facade.hpp"
#include "raylib.h"
#include "log.h"

namespace RaylibFacade::UserInterface {

RaylibUserInterfaceFacade::RaylibUserInterfaceFacade()
{
  LOG_TRACE("Initializing Raylib User Interface");
}
void RaylibUserInterfaceFacade::DrawTextCentered(const char* text, Vector2 position, float fontSize)
{
  const Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 1);
  position.x -= textSize.x / 2.0f;
  DrawText(text, position.x, position.y, fontSize, {255, 255, 255, 255});
}

}  // namespace RaylibAdapter::UserInterface
