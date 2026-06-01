#pragma once
#include "core/color/color-rgba.hpp"

namespace Core {

namespace Rendering {
class IRenderer {
 public:
  virtual ~IRenderer() = default;

  void virtual BeginDrawing() const = 0;
  void virtual EndDrawing() const = 0;
  void virtual ClearBackground(Color::ColorRGBA color) const = 0;

  // SIDE QUEST: Not sure if this one should be in here, we can come back to this
  void virtual DrawRectangle(float x, float y, float width, float height, Color::ColorRGBA) const = 0;
};
}  // namespace Rendering
}  // namespace Core
