//
// Created by Dean Wilson on 14th March 2026
//

#pragma once

namespace Core {
namespace Rendering {
namespace Components {
class IRenderComponent;
}

class IRenderer;

class IRenderManager {
 public:
  virtual ~IRenderManager() = 0;
  virtual void OnRender(const IRenderer& renderer) const = 0;
};
}  // namespace Rendering
};  // namespace Core
