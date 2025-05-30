#pragma once

#include "irender-component-2d.h"

class IStateMachine;

namespace Core {
class Color;
}

class IRenderer;

namespace Renderer2D::Component {

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
}  // namespace Renderer2D::Component