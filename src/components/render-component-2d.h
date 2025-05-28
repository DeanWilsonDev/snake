//
//

#pragma once

#ifndef RENDERER_H
#define RENDERER_H
#include "../core/types.h"

class IRenderer;
class IStateMachine;

namespace Component {

class RenderComponent2D {
 public:
  RenderComponent2D(float size, float positionX, float positionY, Core::Color color);
  void Render(IRenderer& renderer) const;
  void SetPosition(float x, float y);

 private:
  float size;
  float positionX;
  float positionY;
  Core::Color color;
};
}  // namespace Component

#endif  // RENDERER_H
