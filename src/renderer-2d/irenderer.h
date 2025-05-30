#pragma once
#include "../core/types.h"
class Color;

namespace Renderer2D {

class IRenderer {
 public:
  virtual ~IRenderer() = default;

  void virtual Render() = 0;
  void virtual Draw() = 0;
  void virtual GetGameplayState() = 0;

  void virtual DrawRectangle(float x, float y, float width, float height, Core::Color) = 0;
};
}  // namespace Render2D
