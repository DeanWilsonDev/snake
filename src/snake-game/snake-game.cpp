
#include "snake-game/snake-game.hpp"
#include "engine/scenes/scene-manager.hpp"
#include "snake-game/game-scenes/gameplay-scene.hpp"
#include <functional>

namespace SnakeGame {

void SnakeGame::Initialize()
{
  auto sceneManager = this->GetSceneManager();
  sceneManager.Register(
      "mainMenu",
      []() { return std::make_unique<MainMenuScene>(); },
      Engine::Scenes::SceneLifetime::Persistent
  );

  sceneManager.Register(
      "gameplay",
      []() { return std::make_unique<GameplayScene>(); },
      Engine::Scenes::SceneLifetime::Transient
  );  // fresh game each visit

  sceneManager.Register(
      "pause",
      []() { return std::make_unique<PauseScene>(); },
      Engine::Scenes::SceneLifetime::Transient
  );

  sceneManager.SwitchTo("mainMenu");
}

}  // namespace SnakeGame
