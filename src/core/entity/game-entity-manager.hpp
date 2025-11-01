//
// Created by Dean Wilson on 25/8/2025.
//

#pragma once
#include "renderer-2d/render-component-2d-manager.hpp"
#include "core/entity/entity.h"

#include <vector>

namespace Renderer2D {
class IRenderable;
}
namespace Core {

class GameEntityManager {
 public:
  GameEntityManager(
      const std::vector<Entity::Entity*>& entities,
      const Renderer2D::RenderComponent2DManager& renderManager
  );
  void AddEntity(Entity::Entity* entity);
  void Update(float deltaTime) const;
  void Render() const;

 private:
  std::vector<Entity::Entity*> entities;
  Renderer2D::RenderComponent2DManager renderManager;
};

}  // namespace Core
