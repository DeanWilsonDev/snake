//
// Created by Dean Wilson on 25/8/2025.
//

#pragma once
#include "core/i-debugable.hpp"
#include "core/i-updatable.hpp"
#include "core/render-component-2d-manager.hpp"
#include "core/entity/entity.hpp"

#include <vector>

namespace Core {
class GameEntityManager : public IUpdatable, IDebugable {
 public:
  GameEntityManager(const RenderComponent2DManager& renderManager);
  void AddEntity(Entity::Entity* entity);
  void Update(float deltaTime) override;
  void DebugUpdate() override;
  void Render() const;

 private:
  std::vector<Entity::Entity*> entities;
  RenderComponent2DManager renderManager;
};

}  // namespace Core
