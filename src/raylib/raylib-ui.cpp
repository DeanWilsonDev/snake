#include "../raylib-ui.h"
#include "raylib.h"

void RaylibUI::drawTextCentered(const char* text, Vector2 position, float fontSize)
{
  const Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 1);
  position.x -= textSize.x / 2.0f;
  DrawText(text, position.x, position.y, fontSize, {255, 255, 255, 255});
}
