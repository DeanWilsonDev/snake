//
// Created by Dean Wilson on 29/5/2025.
//

#pragma once

namespace Core {
namespace Rendering {
namespace Components {
class IRenderComponent;
}

class IRenderer;

class IRenderable {
 public:
  virtual ~IRenderable() = default;
  virtual void Render(const Rendering::IRenderer& renderer) const = 0;
};
}  // namespace Rendering
};  // namespace Core
