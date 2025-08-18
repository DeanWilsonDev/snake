
#include "gameplay-state.hpp"
#include "game/settings/game-settings.h"
#include "log.h"
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

  LOG_TRACE("[GameplayState] Initializing Main Menu UI");
  const auto gameSettings = this->gameplayStateMachine.GetGameSettings();
  const auto userInterface = this->gameplayStateMachine.GetUserInterface();
  int& score = this->gameplayStateMachine.GetScore();
  LOG_TRACE("[GameplayState] Validating Game Settings");
  assert(gameSettings);
  LOG_TRACE("[GameplayState] Validating User Interface");
  assert(userInterface);
  LOG_TRACE("[GameplayState] Setting Main Menu UI");
  this->gameplayUI = new GameplayUI(*userInterface, *gameSettings, score);
}

void GameplayState::Enter()
{
  LOG_TRACE("[GameplayState] Beginning New Game");
  this->gameplayStateMachine.InitializeSnake();
  this->gameplayStateMachine.InitializeApple();

  if (auto renderManager = this->gameplayStateMachine.GetRenderManager()) {
    LOG_DEBUG("[GameplayState] RenderManager set to [{}]", static_cast<void*>(&renderManager));

    const Snake* snake = this->gameplayStateMachine.GetSnake();
    const Apple* apple = this->gameplayStateMachine.GetApple();

    if (!snake) {
      LOG_FATAL("[GameplayState] Snake is not initialized");
      return;
    }

    if (!apple) {
      LOG_FATAL("[GameplayState] Snake is not initialized");
      return;
    }

    renderManager->Register(&snake->GetRendererComponent2D());
    renderManager->Register(&apple->GetRendererComponent2D());
  }
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

  if (snake->GetColliderComponent().Intersects(apple->GetColliderComponent())) {
    apple->transform.position = apple->GetNewPosition();
    this->gameplayStateMachine.IncreaseScore();
    snake->SetGrow(true);
  }

  for (int i = 0; i < snake->body.size(); i++) {
    if (snake->body[i] == nullptr) {
      break;
    }

    LOG_DEBUG("Body[{}]", static_cast<void*>(snake->body[i]));

    if (snake->head != nullptr && snake->body[i] != snake->head) {
      // Side Quest: [Debug] Create a Debug module to allow for Debug drawing
      // if (this->debugEnabled) {
      //   DrawRectangleRec(snake->body[i]->GetBounds(), RED);
      // }

      if (snake->head->GetColliderComponent()->Intersects(*snake->body[i]->GetColliderComponent()
          )) {
        LOG_INFO("Head hit body part with index: {}", i);
        this->gameplayStateMachine.Next();
      }
    }
  }
}

void GameplayState::Exit()
{
  if (gameplayUI) {
    delete gameplayUI;
    gameplayUI = nullptr;
  }
  this->gameplayStateMachine.ClearUI();

  if (auto renderManager = this->gameplayStateMachine.GetRenderManager()) {
    LOG_DEBUG("[GameplayState] RenderManager set to [{}]", static_cast<void*>(&renderManager));
    const Snake* snake = this->gameplayStateMachine.GetSnake();
    const Apple* apple = this->gameplayStateMachine.GetApple();

    if (!snake) {
      LOG_FATAL("[GameplayState] Snake is not initialized");
      return;
    }

    if (!apple) {
      LOG_FATAL("[GameplayState] Snake is not initialized");
      return;
    }

    renderManager->Unregister(&snake->GetRendererComponent2D());
    renderManager->Unregister(&apple->GetRendererComponent2D());
  }
}

}  // namespace Game
