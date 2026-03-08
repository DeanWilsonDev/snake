#pragma once
#include "core/color.hpp"

namespace Core {

class IRenderer {
 public:
  virtual ~IRenderer() = default;

  void virtual BeginDrawing() = 0;
  void virtual EndDrawing() = 0;
  void virtual ClearBackground(Color color) = 0;


  // SIDE QUEST: Not sure if this one should be in here, we can come back to this
  void virtual DrawRectangle(float x, float y, float width, float height, Color) = 0;
};
}  // namespace Core
