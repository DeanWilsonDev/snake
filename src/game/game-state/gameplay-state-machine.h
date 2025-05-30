#pragma once
#include "../../core/istate-machine.h"
#include "../../core/igame-state.h"

namespace Renderer2D {
class IRenderer;
class RenderManager;
}  // namespace Renderer2D

class Apple;
class Snake;
namespace Core {
class IGameState;
class IUserInterface;
}  // namespace Core

namespace Game {

enum State {
  STATE_MAIN_MENU,
  STATE_GAMEPLAY,
  STATE_GAME_OVER,
};

class GameplayStateMachine final : public Core::IStateMachine {
 public:
  explicit GameplayStateMachine(Core::IGameState* currentState);
  ~GameplayStateMachine() override;
  void ChangeState(Core::IGameState* newState) override;
  void Update(float deltaTime) override;
  void IncreaseScore();

  // Getters
  Core::IGameState* GetCurrentState() override { return this->currentState; };

  [[nodiscard]] Core::IUserInterface* GetUI() { return this->ui; };
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

 private:
  Core::IGameState* currentState = nullptr;
  Core::IUserInterface* ui;
  Renderer2D::RenderManager* renderManager;
  Renderer2D::IRenderer* renderer;
  Snake* snake;
  Apple* apple;
  int score;
};
}  // namespace Game
