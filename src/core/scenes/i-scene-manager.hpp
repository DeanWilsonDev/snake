///
/// Created by Dean Wilson 29th May 2026
///

#pragma once
#include "core/debug/i-on-debugable.hpp"
#include "core/i-on-updatable.hpp"
#include "core/rendering/i-on-renderable.hpp"
#include "core/scenes/scene-lifetime.hpp"
#include "core/scenes/i-scene.hpp"
#include <string>
#include <functional>
#include <memory>

namespace Core {
namespace Scenes {

using SceneFactory = std::function<std::unique_ptr<IScene>()>;

class ISceneManager : public Debug::IOnDebugable, public IOnUpdatable, public Rendering::IOnRenderable {
 public:
  virtual ~ISceneManager() = default;

  virtual void Register(
      const std::string& name, SceneFactory factory,
      SceneLifetime lifetime = SceneLifetime::Persistent
  ) = 0;
  virtual void SwitchTo(const std::string& name) = 0;
  virtual void Push(const std::string& name) = 0;
  virtual void Pop() = 0;
};
}  // namespace Scenes
}  // namespace Core
