#pragma once
#include "core/color.h"
class Color;

namespace Renderer2D {

class IRenderer {
 public:
  virtual ~IRenderer() = default;

  void virtual BeginDrawing() = 0;
  void virtual EndDrawing() = 0;
  void virtual ClearBackground(Core::Color color) = 0;

  void virtual DrawRectangle(float x, float y, float width, float height, Core::Color) = 0;
};
}  // namespace Render2D
