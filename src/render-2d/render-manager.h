//
// Created by Dean Wilson on 29/5/2025.
//

#ifndef RENDERERMANAGER_H
#define RENDERERMANAGER_H
#include <vector>

class IRenderer;
class IRenderable;
namespace Render2D {
class RenderManager {
 public:
  explicit RenderManager(IRenderer& renderer);
  void Register(IRenderable* component);
  void Unregister(IRenderable* component);
  void RenderAll() const;

 private:
  std::vector<IRenderable*> renderComponents;
  IRenderer& renderer;
};
}  // namespace Render2D
#endif  // RENDERERMANAGER_H
