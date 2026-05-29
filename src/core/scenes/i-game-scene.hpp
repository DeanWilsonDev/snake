//
// Created by Dean Wilson on 22 March 2026
//

#pragma once

#include "core/debug/i-debugable.hpp"
#include "core/i-updatable.hpp"
#include "core/rendering/i-render-manager.hpp"
#include "core/rendering/i-renderable.hpp"

namespace Core {
namespace Scenes {

struct SceneTransitionContext;

class IGameScene : public IUpdatable, Debug::IDebugable, Rendering::IRenderManager {
 public:
  virtual ~IGameScene() = default;

  virtual void Initialize() = 0;

  virtual void OnEnter(SceneTransitionContext context) = 0;
  virtual void OnExit() = 0;

  virtual void Update(float deltaTime) override = 0;
  virtual void DebugUpdate() const override = 0;

  virtual void OnRender(const Rendering::IRenderer& renderer) const override = 0;
  virtual void DebugRender() const override = 0;
};

}  // namespace Scenes
}  // namespace Core
