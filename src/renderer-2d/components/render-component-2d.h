#pragma once

#ifndef RENDERER_H
#define RENDERER_H
#include "irender-component-2d.h"

class IStateMachine;
namespace Core {
class Color;
}

namespace Renderer2D::Component {

class IRenderer;

class RenderComponent2D final : public IRenderComponent2D {
 public:
  RenderComponent2D(float width, float height, float positionX, float positionY, Core::Color color);
  ~RenderComponent2D() override;
  void Render(IRenderer& renderer) const override;
  void SetPosition(float x, float y) override;
  [[nodiscard]] float GetX() const override;
  [[nodiscard]] float GetY() const override;
  [[nodiscard]] float GetWidth() const override;
  [[nodiscard]] float GetHeight() const override;

 private:
  float width;
  float height;
  float positionX;
  float positionY;
  Core::Color color;
};
}  // namespace Render::Component

#endif  // RENDERER_H
