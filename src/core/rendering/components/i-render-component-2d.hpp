//
// Created by Dean Wilson on 30/5/2025.
//

#pragma once

#include "core/rendering/components/i-render-component.hpp"

namespace Core {

namespace Rendering {

class IRenderer;

namespace Components {

class IRenderComponent2D : public Core::Rendering::Components::IRenderComponent {
 public:
  virtual ~IRenderComponent2D() = default;
};
}  // namespace Components
}  // namespace Rendering
}  // namespace Core
