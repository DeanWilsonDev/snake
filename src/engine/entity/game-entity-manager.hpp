//
// Created by Dean Wilson on 25/8/2025.
//

#pragma once
#include "core/debug/i-on-debugable.hpp"
#include "core/i-on-updatable.hpp"
#include "core/rendering/i-on-renderable.hpp"

#include <vector>

namespace Core {
namespace Entity {
class IEntity;
}
namespace Rendering {
class IRenderer;
class IRenderComponentManager;
}  // namespace Rendering
}  // namespace Core

namespace Engine {

namespace Entity {

class GameEntityManager : public Core::IOnUpdatable,
                          Core::Debug::IOnDebugable,
                          Core::Rendering::IOnRenderable {
 public:
  GameEntityManager(Core::Rendering::IRenderComponentManager* renderManager);
  void AddEntity(Core::Entity::IEntity* entity);
  void OnUpdate(float deltaTime) override;
  void OnDebugUpdate() const override;
  void OnDebugRender() const override;
  void OnRender(const Core::Rendering::IRenderer& renderer) const override;

 private:
  std::vector<Core::Entity::IEntity*> entities;
  Core::Rendering::IRenderComponentManager* renderManager;
};

}  // namespace Entity
}  // namespace Engine
