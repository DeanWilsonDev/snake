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

class IOnRenderable {
 public:
  virtual ~IOnRenderable() = 0;
  virtual void OnRender(const IRenderer& renderer) const = 0;
};
}  // namespace Rendering
};  // namespace Core
