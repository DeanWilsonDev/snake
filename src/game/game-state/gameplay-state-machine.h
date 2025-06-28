#pragma once
#include "../../core/istate-machine.hpp"
#include "../../core/igame-state.h"
#include "../snake.hpp"

namespace Renderer2D {
class IRenderer;
class RenderManager;
}  // namespace Renderer2D

namespace Core {
class IGameState;
class IUserInterface;
}  // namespace Core

namespace Game {

class Apple;
class Snake;

enum State {
  STATE_MAIN_MENU,
  STATE_GAMEPLAY,
  STATE_GAME_OVER,
  STATE_NONE
};

class GameplayStateMachine final : public Core::IStateMachine {
 public:
  explicit GameplayStateMachine(Core::IGameState* currentState);
  ~GameplayStateMachine() override;
  void ChangeState(Core::IGameState* newState) override;
  void Update(float deltaTime) override;
  void IncreaseScore();
  void Next() override;

  // Initializers
  [[nodiscard]] Snake* InitializeSnake() const { return this->snake->Initialize(); }

  // Getters
  Core::IGameState* GetCurrentState() override { return this->currentState; };

  [[nodiscard]] Core::IUserInterface* GetUI() const { return this->ui; };
  [[nodiscard]] int GetScore() const { return this->score; };
  [[nodiscard]] Snake* GetSnake() const { return this->snake; }
  [[nodiscard]] Apple* GetApple() const { return this->apple; }
  [[nodiscard]] Renderer2D::IRenderer* GetRenderer() const { return this->renderer; }
  [[nodiscard]] Renderer2D::RenderManager* GetRenderManager() const { return this->renderManager; }

  // Setters
  void SetSnake(Snake& snake);
  void SetApple(Apple& apple);
  void SetUI(Core::IUserInterface& ui) { this->ui = &ui; }
  void SetRenderer(Renderer2D::IRenderer& renderer) { this->renderer = &renderer; }
  void SetRenderManager(Renderer2D::RenderManager& renderManager)
  {
    this->renderManager = &renderManager;
  }


  void ClearUI() { this->ui = nullptr; }

protected:
  Core::IGameState* DetermineNextState() override;

 private:
  Core::IGameState* currentState = nullptr;
  Core::IUserInterface* ui;
  Renderer2D::RenderManager* renderManager;
  Renderer2D::IRenderer* renderer;
  Snake* snake;
  Apple* apple;
  int score = {0};
};
}  // namespace Game
