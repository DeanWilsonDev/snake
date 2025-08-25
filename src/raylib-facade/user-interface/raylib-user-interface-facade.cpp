#include "raylib-user-interface-facade.hpp"
#include "raylib.h"
#include "log.h"
#include "../../core/entity/entity.h"

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

}  // namespace RaylibAdapter::UserInterface
