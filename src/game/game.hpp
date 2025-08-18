//
// Created by Dean Wilson on 14/7/2025.
//

#pragma once
#include "../core/i-game.hpp"

#include <memory>

namespace Game {
struct GameSettings;
}
namespace Game {
class Snake;
class Apple;
class GameplayStateMachine;
}  // namespace Game
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

class Game final : public Core::IGame {
 public:
  explicit Game(
      Core::DependencyInjector& injector, Engine::Config::ProjectSettings& projectSettings,
      Renderer2D::RenderComponent2DManager& renderManager
  );

  ~Game() override;

  void Initialize() override;
  void Update(float deltaTime) override;
  void Render() override;

 private:
  Core::DependencyInjector& injector;
  Engine::Config::ProjectSettings& projectSettings;
  Renderer2D::RenderComponent2DManager& renderManager;
  GameplayStateMachine* gameplayStateMachine{nullptr};
  GameSettings* settings{nullptr};
  Snake* snake{nullptr};
  Apple* apple{nullptr};
};

}  // namespace Game
