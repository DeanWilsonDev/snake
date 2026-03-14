//
// Created by Dean Wilson on 14th March 2026
//

#pragma once

#include "core/components/i-component.hpp"
#include "core/rendering/i-renderable.hpp"

namespace Core {

namespace Rendering {

class IRenderer;

namespace Components {

class IRenderComponent : public Core::Components::IComponent, IRenderable {
 public:
  virtual ~IRenderComponent() = default;
  virtual void Render(const IRenderer& renderer) const = 0;
  [[nodiscard]] virtual float GetX() const = 0;
  [[nodiscard]] virtual float GetY() const = 0;
  [[nodiscard]] virtual float GetWidth() const = 0;
  [[nodiscard]] virtual float GetHeight() const = 0;
  [[nodiscard]] virtual bool GetActive() const = 0;
};
}  // namespace Components
}  // namespace Rendering
}  // namespace Core
