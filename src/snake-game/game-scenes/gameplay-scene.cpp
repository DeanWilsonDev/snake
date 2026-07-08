#include "snake-game/game-scenes/gameplay-scene.hpp"
#include <memory>
#include "engine/entities/entity-manager.hpp"
#include "snake-game/game-entities/apple.hpp"
#include "snake-game/game-entities/snake.hpp"
#include "snake-game/game-entities/apple.hpp"
#include "engine/spatial/transform-2d.hpp"
#include "core/entities/i-entity-manager.hpp"

namespace SnakeGame {

GameplayScene::GameplayScene(const GameplaySceneParams& params)
    : renderComponentManager(params.renderComponentManager)
    , eventBus(params.eventBus)
    , gameSettings(params.gameSettings)
    , screenWidth(params.screenWidth)
    , screenHeight(params.screenHeight)
{
  this->entityManager = make_unique<Engine::Entities::EntityManager>(&this->renderComponentManager);
}

GameplayScene::~GameplayScene() = default;

void GameplayScene::OnEnter(Core::Scenes::SceneTransitionContext ctx)
{
  this->transition = ctx;

  // Register Snake:
  SnakeParams snakeParams = {
      .entityManager = *this->entityManager,
      .settings = this->gameSettings,
      .screenWidth = this->screenWidth,
      .screenHeight = this->screenHeight
  };

  this->snake = std::make_unique<Snake>(snakeParams);
  this->snake->Initialize();

  // Register Apple

  // MAIN QUEST: Swap this out after the apple spawner exists
  Engine::Spatial::Transform2D localTransform = Engine::Spatial::Transform2D::Empty();
  AppleParams appleParams = AppleParams(&localTransform);

  auto apple = make_unique<Apple>(appleParams);
  this->entityManager->AddEntity(std::move(apple));
}

void GameplayScene::Update(float deltaTime)
{
  // SIDE QUEST: This should probably just be handled in application.
  // I'm going to need to find an itelligent way to handle update priority
  // and decide what should update in what order
  this->stateMachine.Update(deltaTime);
  this->entityManager->OnUpdate(deltaTime);

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
