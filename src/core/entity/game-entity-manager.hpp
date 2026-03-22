//
// Created by Dean Wilson on 25/8/2025.
//

#pragma once
#include "core/debug/i-on-debugable.hpp"
#include "core/i-on-updatable.hpp"
#include "core/rendering/i-render-manager.hpp"
#include "core/entity/entity.hpp"
#include "core/rendering/i-on-renderable.hpp"
#include "core/rendering/render-component-2d-manager.hpp"

#include <vector>

namespace Core {

namespace Rendering {
class IRenderer;
}

class GameEntityManager : public IOnUpdatable, Debug::IOnDebugable, Rendering::IOnRenderable {
 public:
  GameEntityManager(Rendering::RenderComponent2DManager* renderManager);
  void AddEntity(Entity::Entity* entity);
  void OnUpdate(float deltaTime) override;
  void OnDebugUpdate() override;
  void OnRender(const Rendering::IRenderer& renderer) override;

 private:
  std::vector<Entity::Entity*> entities;
  Rendering::RenderComponent2DManager* renderManager;
};

}  // namespace Core
