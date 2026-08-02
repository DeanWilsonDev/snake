#include "snake-game/game-scenes/gameplay-scene.hpp"
#include <memory>
#include "core/logging/log.hpp"
#include "snake-game/game-entities/snake.hpp"
#include "snake-game/game-events/game-started-event.hpp"
#include "snake-game/game-systems/apple-spawn-system.hpp"
#include "snake-game/game-systems/snake-growth-system.hpp"
#include "snake-game/game-systems/snake-spawn-system.hpp"
#include "engine/scenes/scene.hpp"

namespace SnakeGame {

GameplayScene::GameplayScene(const GameplaySceneParams& params)
    : Engine::Scenes::Scene(params)
    , gameSettings(params.gameSettings)
    , screenWidth(params.screenWidth)
    , screenHeight(params.screenHeight)
{
}

GameplayScene::~GameplayScene() = default;

void GameplayScene::OnEnter(Core::Scenes::SceneTransitionContext ctx)
{
  LOG_DEBUG("RUNNING GAMEPLAY SCENE ON ENTER");
  this->transition = ctx;

  // Add Game Systems

  auto appleSpawnParams = AppleSpawnSystemParams{
      .settings = this->gameSettings,
      .screenWidth = this->screenWidth,
      .screenHeight = this->screenHeight
  };

  this->CreateGameSystem<AppleSpawnSystem>(appleSpawnParams);

  auto snakeSpawnParams = SnakeSpawnSystemParams{
      .settings = this->gameSettings,
      .screenWidth = this->screenWidth,
      .screenHeight = this->screenHeight,
  };
  this->CreateGameSystem<SnakeSpawnSystem>(snakeSpawnParams);

  auto snakeGrowParams = SnakeGrowSystemParams{
      .settings = this->gameSettings,
  };

  this->CreateGameSystem<SnakeGrowSystem>(snakeGrowParams);
  // Tigger OnGameStart Event

  this->GetEventBus().Publish(GameStartedEvent{});
}

void GameplayScene::Update(float deltaTime)
{
  // SIDE QUEST: This should probably just be handled in application.
  // I'm going to need to find an itelligent way to handle update priority
  // and decide what should update in what order
  this->stateMachine.Update(deltaTime);

  // if (stateMachine.IsGameOver()) transition.SwitchTo("mainMenu");
}

void GameplayScene::Render(const Core::Rendering::IRenderer&) const {}

// // PauseScene — example of push/pop overlay
// void GameplayScene::Update(float deltaTime)
// {
//     if (Input::IsPressed(Key::Escape))
//         transition.Push("pause");
//     // ...
// }
//
// void PauseScene::Update(float deltaTime)
// {
//     if (Input::IsPressed(Key::Escape))
//         transition.Pop();   // returns to gameplay, same instance
// }

void GameplayScene::OnSceneExit() {}

void GameplayScene::DebugUpdate() const {}

void GameplayScene::DebugRender() const {}

}  // namespace SnakeGame
