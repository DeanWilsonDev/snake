#include "gameplay-scene.hpp"
#include "core/entity/game-entity-manager.hpp"
#include "core/rendering/render-component-2d-manager.hpp"

namespace SnakeGame {

GameplayScene::GameplayScene(const GameplaySceneParams& params)
    : renderComponentManager()
    , entityManager(&this->renderComponentManager)
    , eventBus(*params.eventBus)
{
}

void GameplayScene::Initialize() {}

// GameplayScene.cpp
void GameplayScene::OnEnter(Core::SceneTransitionContext ctx)
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

void GameplayScene::DebugUpdate() {}
void GameplayScene::DebugRender() {}

}  // namespace SnakeGame
