///
/// Created by Dean Wilson 29th May 2026
///

#pragma once
#include "core/debug/i-on-debugable.hpp"
#include "core/i-on-updatable.hpp"
#include "core/rendering/i-on-renderable.hpp"
#include "core/scenes/scene-lifetime.hpp"
#include "core/scenes/i-game-scene.hpp"
#include <string>
#include <functional>
#include <memory>

namespace Core {
namespace Scenes {

using SceneFactory = std::function<std::unique_ptr<IGameScene>()>;

class ISceneManager : public Debug::IOnDebugable, IOnUpdatable, Rendering::IOnRenderable {
 public:
  virtual ~ISceneManager() = 0;

  virtual void Register(
      const std::string& name, SceneFactory factory,
      SceneLifetime lifetime = SceneLifetime::Persistent
  ) = 0;
  virtual void SwitchTo(const std::string& name) = 0;
  virtual void Push(const std::string& name) = 0;
  virtual void Pop() = 0;

  virtual void OnUpdate(float deltaTime) = 0;
  virtual void OnDebugUpdate() const = 0;
  virtual void OnDebugRender() const = 0;
  virtual void OnRender(const Core::Rendering::IRenderer& renderer) const = 0;
};
}  // namespace Scenes
}  // namespace Core
