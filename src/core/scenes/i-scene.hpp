//
// Created by Dean Wilson on 22 March 2026
//

#pragma once

#include "core/debug/i-debugable.hpp"
#include "core/life-cycle-hooks/i-on-registration.hpp"
#include "core/life-cycle-hooks/i-updatable.hpp"
#include "core/rendering/i-renderable.hpp"

namespace Core {
namespace Scenes {

struct SceneTransitionContext;

class IScene: public IUpdatable, public Debug::IDebugable, public Rendering::IRenderable, public IOnRegistration {
 public:
  virtual ~IScene() = default;

  virtual void OnEnter(SceneTransitionContext context) = 0;
  virtual void OnExit() = 0;
};

}  // namespace Scenes
}  // namespace Core
