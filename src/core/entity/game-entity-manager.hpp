//
// Created by Dean Wilson on 25/8/2025.
//

#pragma once
#include "core/debug/i-debugable.hpp"
#include "core/i-updatable.hpp"
#include "core/rendering/i-render-manager.hpp"
#include "core/entity/entity.hpp"
#include "core/rendering/render-component-2d-manager.hpp"

#include <vector>

namespace Core {

namespace Rendering {
class IRenderer;
}

class GameEntityManager : public IUpdatable, Debug::IDebugable {
 public:
  GameEntityManager(Rendering::RenderComponent2DManager* renderManager);
  void AddEntity(Entity::Entity* entity);
  void Update(float deltaTime) override;
  void DebugUpdate() override;
  void Render(const Rendering::IRenderer& renderer) const;

 private:
  std::vector<Entity::Entity*> entities;
  Rendering::RenderComponent2DManager* renderManager;
};

}  // namespace Core
