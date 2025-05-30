//
// Created by Dean Wilson on 29/5/2025.
//

#ifndef RENDERERMANAGER_H
#define RENDERERMANAGER_H

#pragma once

#include <vector>

namespace Renderer2D {

class IRenderable;
class IRenderer;

namespace Component {
class IRenderComponent2D;
}

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
}  // namespace Renderer2D
#endif  // RENDERERMANAGER_H
