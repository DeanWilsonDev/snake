//
// Created by Dean Wilson on 30/5/2025.
//

#pragma once

#include "core/components/i-component.hpp"

namespace Core {
class IRenderer;

namespace Components {

class IRenderComponent2D : public Core::Components::IComponent {
 public:
  virtual ~IRenderComponent2D() = default;
  virtual void Render(Core::IRenderer& renderer) const = 0;
  [[nodiscard]] virtual float GetX() const = 0;
  [[nodiscard]] virtual float GetY() const = 0;
  [[nodiscard]] virtual float GetWidth() const = 0;
  [[nodiscard]] virtual float GetHeight() const = 0;
  [[nodiscard]] virtual bool GetActive() const = 0;
};
}  // namespace Components
}  // namespace Core
