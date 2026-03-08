//
// Created by Dean Wilson on 29/5/2025.
//

#pragma once

#include <vector>
#include <memory>
#include "core/components/i-render-component-2d.hpp"

namespace Core {

class IRenderable;
class IRenderer;

namespace Components {
class IRenderComponent2D;
}

class RenderComponent2DManager {
 public:
  explicit RenderComponent2DManager(const std::shared_ptr<IRenderer>& renderer);
  ~RenderComponent2DManager() = default;
  void Register(Components::IRenderComponent2D* component);
  void Unregister(Components::IRenderComponent2D* component);
  void RenderAll() const;

 private:
  std::vector<Components::IRenderComponent2D*> renderComponents;
  std::shared_ptr<IRenderer> renderer;
};
}  // namespace Core
