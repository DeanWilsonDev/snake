//
// Created by Dean Wilson on 30/5/2025.
//

#ifndef IRENDER_COMPONENT_H
#define IRENDER_COMPONENT_H
#include "core/components/i-component.hpp"

namespace Renderer2D {
class IRenderer;
namespace Component {
class IRenderComponent2D: public Core::Components::IComponent {
 public:
  virtual ~IRenderComponent2D() = default;
  virtual void Render(IRenderer& renderer) const = 0;
  virtual void SetEnabled(bool enabled) = 0;
  [[nodiscard]] virtual float GetX() const = 0;
  [[nodiscard]] virtual float GetY() const = 0;
  [[nodiscard]] virtual float GetWidth() const = 0;
  [[nodiscard]] virtual float GetHeight() const = 0;
  [[nodiscard]] virtual bool GetEnabled() const = 0;
};
}  // namespace Component
}  // namespace Renderer2D
#endif  // IRENDER_COMPONENT_H
