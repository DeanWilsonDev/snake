
#include "gameplay-state.hpp"
#include "gameplay-state-machine.hpp"
#include "game/game-objects/snake.hpp"
#include "game/game-objects/apple.hpp"
#include "physics/components/collider-component-2d.hpp"
#include "game/game-objects/snake-segment.hpp"
#include "game/ui/gameplay-ui.hpp"
#include "umbra/log.h"

#include <cstddef>
#include <cassert>

namespace Renderer2D {
class IRenderer;
}

namespace Game {

GameplayState::GameplayState(GameplayStateMachine& stateMachine)
    : gameplayStateMachine(stateMachine)
{
  this->input = this->gameplayStateMachine.GetInput();
  assert(input);

  const auto gameSettings = this->gameplayStateMachine.GetGameSettings();
  const auto userInterface = this->gameplayStateMachine.GetUserInterface();
  int& score = this->gameplayStateMachine.GetScore();
  assert(gameSettings);
  assert(userInterface);
  this->gameplayUI = new GameplayUI(*userInterface, *gameSettings, score);
}

void GameplayState::Enter()
{
  Snake* snake = this->gameplayStateMachine.GetSnake();
  Apple* apple = this->gameplayStateMachine.GetApple();

  if (!snake) {
    LOG_FATAL("[GameplayState] Snake is not initialized");
    return;
  }

  if (!apple) {
    LOG_FATAL("[GameplayState] Snake is not initialized");
    return;
  }

  snake->SetActive(true);
  apple->SetActive(true);

  this->gameplayStateMachine.SetGameUI(*this->gameplayUI);
}

void GameplayState::Update(float deltaTime)
{
  Snake* snake = this->gameplayStateMachine.GetSnake();
  Apple* apple = this->gameplayStateMachine.GetApple();
  assert(snake);
  assert(apple);

  snake->Update(deltaTime);
  apple->Update(deltaTime);

  if (snake->head->GetColliderComponent()->Intersects(*apple->GetColliderComponent())) {
    apple->transform->position = apple->GetNewPosition();
    this->gameplayStateMachine.IncreaseScore();
    snake->SetGrow(true);
  }

  for (size_t i = 0; i < snake->body.size(); i++) {
    if (snake->body[i] == nullptr) {
      break;
    }

    if (snake->head != nullptr && snake->body[i] != snake->head) {
      // Side Quest: [Debug] Create a Debug module to allow for Debug drawing
      // if (this->debugEnabled) {
      //   DrawRectangleRec(snake->body[i]->GetBounds(), RED);
      // }

      // if (snake->head->GetColliderComponent()->Intersects(*snake->body[i]->GetColliderComponent()
      //     )) {
      //   LOG_INFO("[GameplayState] Head hit body part with index: {}", i);
      //   this->gameplayStateMachine.Next();
      // }
    }
  }
}

void GameplayState::Exit()
{
  if (gameplayUI != nullptr) {
    delete gameplayUI;
    gameplayUI = nullptr;
  }

  this->gameplayStateMachine.ClearUI();

  Snake* snake = this->gameplayStateMachine.GetSnake();
  Apple* apple = this->gameplayStateMachine.GetApple();

  if (!snake) {
    LOG_FATAL("[GameplayState] Snake is not initialized");
    return;
  }

  if (!apple) {
    LOG_FATAL("[GameplayState] Snake is not initialized");
    return;
  }

  snake->SetActive(false);
  apple->SetActive(false);
  snake->Destroy();
}

}  // namespace Game
