//
// Created by Dean Wilson on 14/7/2025.
//

#pragma once

#include "core/debug/i-on-debugable.hpp"
#include "core/i-on-updatable.hpp"
#include "core/rendering/i-on-renderable.hpp"

namespace Core {

namespace Rendering {
class IRenderer;
}

class IGame : public Debug::IOnDebugable, Rendering::IOnRenderable, IOnUpdatable {
 public:
  virtual ~IGame() = default;

  // Called once to initialize game-specific systems and resources
  virtual void Initialize() = 0;

  // Called every frame to handle game-specific logic
  virtual void OnUpdate([[maybe_unused]] float deltaTime) = 0;
  [[maybe_unused]] virtual void OnDebugUpdate() const = 0;

  // Called every frame to handle game-specific rendering
  virtual void OnRender(const Rendering::IRenderer& renderer) const = 0;
  [[maybe_unused]] virtual void OnDebugRender() const = 0;
};

}  // namespace Core
