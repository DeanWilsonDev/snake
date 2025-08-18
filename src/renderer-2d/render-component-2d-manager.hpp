//
// Created by Dean Wilson on 29/5/2025.
//

#pragma once

#include <vector>

namespace Renderer2D {

class IRenderable;
class IRenderer;

namespace Component {

class IRenderComponent2D;
}

class RenderComponent2DManager {
 public:
  explicit RenderComponent2DManager(const std::shared_ptr<IRenderer>& renderer);
  ~RenderComponent2DManager() = default;
  void Register(Component::IRenderComponent2D* component);
  void Unregister(Component::IRenderComponent2D* component);
  void RenderAll() const;

 private:
  std::vector<Component::IRenderComponent2D*> renderComponents;
  std::shared_ptr<IRenderer> renderer;
};
}  // namespace Renderer2D