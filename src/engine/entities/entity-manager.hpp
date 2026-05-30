//
// Created by Dean Wilson on 25/8/2025.
//

#pragma once
#include "core/debug/i-on-debugable.hpp"
#include "core/i-on-updatable.hpp"
#include "core/rendering/i-on-renderable.hpp"

#include <vector>

namespace Core {
namespace Entities {
class IEntity;
}
namespace Rendering {
class IRenderer;
class IRenderComponentManager;
}  // namespace Rendering
}  // namespace Core

namespace Engine {

namespace Entities {

class EntityManager : public Core::IOnUpdatable,
                      Core::Debug::IOnDebugable,
                      Core::Rendering::IOnRenderable {
 public:
  EntityManager(Core::Rendering::IRenderComponentManager* renderManager);
  void AddEntity(Core::Entities::IEntity* entity);
  void OnUpdate(float deltaTime) override;
  void OnDebugUpdate() const override;
  void OnDebugRender() const override;
  void OnRender(const Core::Rendering::IRenderer& renderer) const override;

 private:
  std::vector<Core::Entities::IEntity*> entities;
  Core::Rendering::IRenderComponentManager* renderManager;
};

}  // namespace Entities
}  // namespace Engine
