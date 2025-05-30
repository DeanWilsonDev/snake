//
// Created by Dean Wilson on 29/5/2025.
//

#ifndef RENDERERMANAGER_H
#define RENDERERMANAGER_H
#include <vector>

namespace Component {
class IRenderComponent2D;
}

class IRenderer;
class IRenderable;

namespace Render2D {
class RenderManager {
 public:
  explicit RenderManager(IRenderer& renderer);
  void Register(Component::IRenderComponent2D* component);
  void Unregister(Component::IRenderComponent2D* component);
  void RenderAll() const;

 private:
  std::vector<Component::IRenderComponent2D*> renderComponents;
  IRenderer& renderer;
};
}  // namespace Render2D
#endif  // RENDERERMANAGER_H
