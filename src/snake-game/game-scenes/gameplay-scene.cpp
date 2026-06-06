#include "snake-game/game-scenes/gameplay-scene.hpp"
#include "snake-game/game-entities/apple.hpp"
#include "snake-game/game-entities/snake.hpp"
#include "snake-game/settings/snake-game-settings.hpp"
#include "snake-game/game-entities/snake-segment.hpp"
#include "snake-game/game-entities/apple.hpp"
#include "core/math/transform-2d.hpp"
#include "engine/entities/entity-manager.hpp"

namespace SnakeGame {

GameplayScene::GameplayScene(const GameplaySceneParams& params)
    : renderComponentManager(params.renderComponentManager)
    , entityManager(&this->renderComponentManager)
    , eventBus(params.eventBus)
    , gameSettings(params.gameSettings)
    , screenWidth(params.screenWidth)
    , screenHeight(params.screenHeight)
{
}

GameplayScene::~GameplayScene() = default;

void GameplayScene::OnEnter(Core::Scenes::SceneTransitionContext ctx)
{
  this->transition = ctx;

  // Register Snake:
  SnakeParams snakeParams = {
      .settings = this->gameSettings,
      .screenWidth = this->screenWidth,
      .screenHeight = this->screenHeight
  };

  auto snake = new Snake(snakeParams);
  snake->Initialize();

  for (auto& segment : snake->body) {
    this->entityManager.AddEntity(segment.get());
  }

  // Register Apple

  auto appleTransform =
      new Core::Math::Transform2D(Core::Math::Vector2D::Zero(), 0, Core::Math::Size2D::Zero());

  AppleParams appleParams = AppleParams(appleTransform);

  auto apple = new Apple(appleParams);
  this->entityManager.AddEntity(apple);
}

void GameplayScene::Update(float deltaTime)
{
  // SIDE QUEST: This should probably just be handled in application.
  // I'm going to need to find an itelligent way to handle update priority
  // and decide what should update in what order
  this->stateMachine.Update(deltaTime);
  this->entityManager.OnUpdate(deltaTime);

  // if (stateMachine.IsGameOver()) transition.SwitchTo("mainMenu");
}

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

void GameplayScene::OnExit() {}
void GameplayScene::OnRender(const Core::Rendering::IRenderer&) const {}

void GameplayScene::DebugUpdate() const {}
void GameplayScene::DebugRender() const {}

}  // namespace SnakeGame
