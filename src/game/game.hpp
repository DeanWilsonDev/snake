//
// Created by Dean Wilson on 14/7/2025.
//

#pragma once
#include "../core/igame.hpp"
#include "raylib-facade/renderer/raylib-renderer-facade.hpp"

#include <memory>

namespace Game {
class GameplayStateMachine;
}
namespace Core {
class DependencyInjector;
}
namespace Renderer2D {
class RenderComponent2DManager;
}
namespace Engine::Config {
struct ProjectSettings;
}
namespace Game {

class Game final: public Core::IGame {
 public:

  explicit Game(
    Core::DependencyInjector& injector,
    Engine::Config::ProjectSettings& projectSettings,
    Renderer2D::RenderComponent2DManager& renderManager
    );

  void Initialize() override;
  void Update(float deltaTime) override;
  void Render() override;

private:
  Core::DependencyInjector& injector;
  Engine::Config::ProjectSettings& projectSettings;
  Renderer2D::RenderComponent2DManager& renderManager;
  std::shared_ptr<GameplayStateMachine> gameplayStateMachine;
};

} // Game
