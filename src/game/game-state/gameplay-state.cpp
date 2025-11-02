
#include "gameplay-state.hpp"
#include "game/settings/game-settings.h"
#include <umbra/log.h>
#include "gameplay-state-machine.hpp"
#include "game/game-objects/snake.hpp"
#include "game/game-objects/apple.hpp"
#include "physics/components/collider-component-2d.hpp"
#include "game/game-objects/snake-segment.hpp"
#include "game/ui/gameplay-ui.hpp"
#include "renderer-2d/render-component-2d-manager.hpp"

#include <cassert>

namespace Renderer2D {
class IRenderer;
}

namespace Game {

GameplayState::GameplayState(GameplayStateMachine& stateMachine)
    : gameplayStateMachine(stateMachine)
{
  LOG_TRACE("[GameplayState] Entering State");

  LOG_TRACE("[GameplayState] Setting up Input");
  this->input = this->gameplayStateMachine.GetInput();
  assert(input);

  LOG_TRACE("[GameplayState] Initializing Gameplay UI");
  const auto gameSettings = this->gameplayStateMachine.GetGameSettings();
  const auto userInterface = this->gameplayStateMachine.GetUserInterface();
  int& score = this->gameplayStateMachine.GetScore();
  LOG_TRACE("[GameplayState] Validating Game Settings");
  assert(gameSettings);
  LOG_TRACE("[GameplayState] Validating User Interface");
  assert(userInterface);
  LOG_TRACE("[GameplayState] Setting Gameplay UI");
  this->gameplayUI = new GameplayUI(*userInterface, *gameSettings, score);
}

void GameplayState::Enter()
{
  LOG_TRACE("[GameplayState] Beginning New Game");
  // this->gameplayStateMachine.InitializeSnake();
  // this->gameplayStateMachine.InitializeApple();
  LOG_DEBUG("[GameplayState] Logging GameUI: {}", static_cast<void*>(this->gameplayUI));

  if (auto renderManager = this->gameplayStateMachine.GetRenderManager()) {
    LOG_DEBUG("[GameplayState] RenderManager set to [{}]", static_cast<void*>(&renderManager));

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
  }

  this->gameplayStateMachine.SetGameUI(*this->gameplayUI);
}

void GameplayState::Update(float deltaTime)
{
  Snake* snake = this->gameplayStateMachine.GetSnake();
  Apple* apple = this->gameplayStateMachine.GetApple();
  LOG_TRACE("[GameplayState] Asserting Snake is Initialized");
  assert(snake);
  LOG_TRACE("[GameplayState] Snake Initialization Verified: [{}]", static_cast<void*>(&snake));
  LOG_TRACE("[GameplayState] Asserting Apple is Initialized");
  assert(apple);
  LOG_TRACE("[GameplayState] Apple Initialization Verified: [{}]", static_cast<void*>(&apple));

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

    LOG_DEBUG("[GameplayState] Body[{}]", static_cast<void*>(snake->body[i]));

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

  if (auto renderManager = this->gameplayStateMachine.GetRenderManager()) {
    LOG_DEBUG("[GameplayState] RenderManager set to [{}]", static_cast<void*>(&renderManager));
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
}

}  // namespace Game
