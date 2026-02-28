//
// Created by Dean Wilson on 25/8/2025.
//

#pragma once
#include "core/i-debugable.hpp"
#include "core/i-updatable.hpp"
#include "renderer-2d/render-component-2d-manager.hpp"
#include "core/entity/entity.hpp"

#include <vector>

namespace Renderer2D {
class IRenderable;
}
namespace Core {

class GameEntityManager : public IUpdatable, IDebugable {
 public:
  GameEntityManager(const Renderer2D::RenderComponent2DManager& renderManager);
  void AddEntity(Entity::Entity* entity);
  void Update(float deltaTime) override;
  void DebugUpdate() override;
  void Render() const;

 private:
  std::vector<Entity::Entity*> entities;
  Renderer2D::RenderComponent2DManager renderManager;
};

}  // namespace Core
