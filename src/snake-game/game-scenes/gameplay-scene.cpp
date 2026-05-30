#include "snake-game/game-scenes/gameplay-scene.hpp"
#include "engine/entities/entity-manager.hpp"
#include "renderer-2d/render-component-2d-manager.hpp"

namespace SnakeGame {

GameplayScene::GameplayScene(const GameplaySceneParams& params)
    : renderComponentManager()
    , entityManager(&this->renderComponentManager)
    , eventBus(*params.eventBus)
{
}

void GameplayScene::Initialize() {}

// GameplayScene.cpp
void GameplayScene::OnEnter(Core::Scenes::SceneTransitionContext ctx)
{
  this->transition = ctx;
  // initialise entities, reset state etc.
}

void GameplayScene::Update(float deltaTime)
{
  stateMachine.Update(deltaTime);
  entityManager.OnUpdate(deltaTime);

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

void GameplayScene::DebugUpdate() const {}
void GameplayScene::DebugRender() const {}

}  // namespace SnakeGame
