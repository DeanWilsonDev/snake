//
// Created by Dean Wilson 22 March 2026
//

#pragma once

#include "core/debug/i-on-debugable.hpp"
#include "core/i-game-scene.hpp"
#include "core/i-on-updatable.hpp"
#include "core/rendering/i-on-renderable.hpp"
#include "core/rendering/i-renderer.hpp"
#include <functional>
#include <vector>
#include <memory>
#include <unordered_map>

namespace Core {
class IGameScene;
namespace Rendering {
class IRenderer;

}

}  // namespace Core

namespace Engine {

namespace Scenes {

enum class SceneLifetime {
  Persistent,  // Reuse same instance across visits
  Transient    // Recreate fresh on every visit
};

using SceneFactory = std::function<std::unique_ptr<Core::IGameScene>()>;

class SceneManager : public Core::Debug::IOnDebugable,
                     Core::IOnUpdatable,
                     Core::Rendering::IOnRenderable {
 public:
  SceneManager();
  ~SceneManager() = default;

  void Register(
      const std::string& name, SceneFactory factory,
      SceneLifetime lifetime = SceneLifetime::Persistent
  );
  void SwitchTo(const std::string& name);
  void Push(const std::string& name);
  void Pop();

  virtual void OnUpdate(float deltaTime) override;
  virtual void OnDebugUpdate() const override;
  virtual void OnDebugRender() const override;
  virtual void OnRender(const Core::Rendering::IRenderer& renderer) const override;

 private:
  struct SceneEntry {
    SceneFactory factory;
    std::unique_ptr<Core::IGameScene> instance;
    SceneLifetime lifetime;
  };

  Core::IGameScene* ResolveScene(const std::string& name);
  Core::SceneTransitionContext MakeContext();

  std::unordered_map<std::string, SceneEntry> registry;
  Core::IGameScene* activeScene = nullptr;
  std::vector<Core::IGameScene*> overlayStack;
};

}  // namespace Scenes
}  // namespace Engine
