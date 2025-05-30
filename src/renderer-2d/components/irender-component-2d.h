//
// Created by Dean Wilson on 30/5/2025.
//

#ifndef IRENDER_COMPONENT_H
#define IRENDER_COMPONENT_H

class IRenderer;

namespace Renderer2D::Component {
class IRenderComponent2D {
public:
  virtual ~IRenderComponent2D() = 0;
  virtual void Render(IRenderer& renderer) const = 0;
  virtual void SetPosition(float x, float y) = 0;
  [[nodiscard]] virtual float GetX() const = 0;
  [[nodiscard]] virtual float GetY() const = 0;
  [[nodiscard]] virtual float GetWidth() const = 0;
  [[nodiscard]] virtual float GetHeight() const = 0;
};
}  // namespace Renderer2D::Component
#endif  // IRENDER_COMPONENT_H
