//
// Created by Dean Wilson 22 March 2026
//

#pragma once

#include "core/scenes/i-scene.hpp"
#include "core/scenes/scene-lifetime.hpp"
#include "core/scenes/i-scene-manager.hpp"
#include "core/rendering/i-renderer.hpp"
#include "core/scenes/scene-transition-context.hpp"

#include <vector>
#include <memory>
#include <unordered_map>

using namespace Core::Scenes;

namespace Core {
namespace Rendering {
class IRenderer;

}

}  // namespace Core

namespace Engine {

namespace Scenes {

class SceneManager : public ISceneManager {
 public:
  SceneManager();
  ~SceneManager() = default;

  void Register(
      const std::string& name, SceneFactory factory,
      SceneLifetime lifetime = SceneLifetime::Persistent
  ) override;
  void SwitchTo(const std::string& name) override;
  void Push(const std::string& name) override;
  void Pop() override;

  virtual void OnUpdate(float deltaTime) override;
  virtual void OnDebugUpdate() const override;
  virtual void OnDebugRender() const override;
  virtual void OnRender(const Core::Rendering::IRenderer& renderer) const override;


 private:
  struct SceneEntry {
    SceneFactory factory;
    std::unique_ptr<IScene> instance;
    SceneLifetime lifetime;
  };

  IScene* ResolveScene(const std::string& name);
  SceneTransitionContext MakeContext();

  std::unordered_map<std::string, SceneEntry> registry;
  IScene* activeScene = nullptr;
  std::vector<IScene*> overlayStack;
};

}  // namespace Scenes
}  // namespace Engine
