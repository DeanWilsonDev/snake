//
// Created by Dean Wilson on 29/5/2025.
//

#pragma once

namespace Renderer2D::Component {
class IRenderComponent2D;
}

class IRenderer;

namespace Renderer2D {

class IRenderable {
 public:
  virtual ~IRenderable() = 0;
  virtual void Render(IRenderer& renderer) const = 0;
  virtual void SetPosition(float x, float y) = 0;
  [[nodiscard]] virtual float GetX() const = 0;
  [[nodiscard]] virtual float GetY() const = 0;
  [[nodiscard]] virtual float GetWidth() const = 0;
  [[nodiscard]] virtual float GetHeight() const = 0;
  [[nodiscard]] virtual Component::IRenderComponent2D* GetRenderComponent2D() const = 0;
};
}  // namespace Component
