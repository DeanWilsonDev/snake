//
// Created by Dean Wilson on 22 March 2026
//

#pragma once

#include "core/debug/i-debugable.hpp"
#include "core/i-updatable.hpp"
#include "core/rendering/i-render-manager.hpp"
#include "core/rendering/i-renderable.hpp"
#include <string>
#include <functional>

namespace Core {

struct SceneTransitionContext {
  std::function<void(const std::string&)> SwitchTo;
  std::function<void(const std::string&)> Push;
  std::function<void()> Pop;
};

class IGameScene : public IUpdatable, Debug::IDebugable, Rendering::IRenderManager {
 public:
  virtual ~IGameScene() = default;

  virtual void Initialize() = 0;

  virtual void OnEnter(SceneTransitionContext context) = 0;
  virtual void OnExit() = 0;

  virtual void Update(float deltaTime) override = 0;
  virtual void DebugUpdate() override = 0;

  virtual void OnRender(const Rendering::IRenderer& renderer) const override = 0;
  virtual void DebugRender() override = 0;
};

}  // namespace Core
