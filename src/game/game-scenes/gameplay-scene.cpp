#include "gameplay-scene.hpp"

namespace SnakeGame {

// GameplayScene.cpp
void GameplayScene::OnEnter(Engine::SceneTransitionContext ctx)
{
  this->transition = ctx;
  // initialise entities, reset state etc.
}

void GameplayScene::Update(float deltaTime)
{
  stateMachine.Update(deltaTime);
  entityManager.Update(deltaTime);

  if (stateMachine.IsGameOver()) transition.SwitchTo("mainMenu");
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

}  // namespace Game
