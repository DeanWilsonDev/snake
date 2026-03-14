//
// Created by Dean Wilson on 30/5/2025.
//

#pragma once

#include "core/rendering/components/i-render-component.hpp"

namespace Core {

namespace Rendering {

class IRenderer;

namespace Components {

class IRenderComponentUI : public Core::Rendering::Components::IRenderComponent {
 public:
  virtual ~IRenderComponentUI() = default;
};
}  // namespace Components
}  // namespace Rendering
}  // namespace Core
