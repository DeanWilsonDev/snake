#pragma once
#include "types.h"
class Color;

class IRenderer {
 public:
  virtual ~IRenderer() = default;

  void virtual Render() = 0;
  void virtual Draw() = 0;
  void virtual GetGameplayState() = 0;

  void virtual DrawRectangle(float x, float y, float width, float height, Core::Color) = 0;
};
