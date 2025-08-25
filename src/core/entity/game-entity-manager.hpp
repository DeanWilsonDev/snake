//
// Created by Dean Wilson on 25/8/2025.
//

#pragma once
#include "game-entity.hpp"
#include "renderer-2d/i-renderable.h"
#include "renderer-2d/render-component-2d-manager.hpp"
#include "renderer-2d/components/i-render-component-2d.h"

#include <vector>

namespace Renderer2D {
class IRenderable;
}
namespace Core {

class GameEntityManager {
 public:

  GameEntityManager(
      const std::vector<Entity::GameEntity*>& entities,
      const Renderer2D::RenderComponent2DManager& renderManager
  );
  void AddEntity(Entity::GameEntity* entity);
  void Update(float deltaTime) const;
  void Render() const;

 private:
  std::vector<Entity::GameEntity*> entities;
  Renderer2D::RenderComponent2DManager renderManager;
};

}  // namespace Core
