#pragma once
#include "istate-machine.h"

namespace Render2D {
class IRenderer;
}
namespace Render2D {
class RenderManager;
}
namespace Component {
class IRenderable;
}
class Apple;
class Snake;
class IGameState;
struct GameSettings;
class GameSession;
class IUserInterface;
class RaylibUI;

class GameplayStateMachine final : public IStateMachine {
 public:

  GameplayStateMachine(IGameState* currentState, GameSettings& settings);
  ~GameplayStateMachine() override;
  void ChangeState(IGameState* newState) override;
  void Update(float deltaTime) override;
  void IncreaseScore();

  // Getters
  IGameState* GetCurrentState() override { return this->currentState; };
  GameSettings& GetSettings() override { return this->settings; };
  [[nodiscard]] IUserInterface* GetUI() override { return this->ui; };
  [[nodiscard]] IGameState* GetCurrentState() const { return this->currentState; };
  [[nodiscard]] int GetScore() const { return this->score; };
  [[nodiscard]] Snake* GetSnake() const { return this->snake; }
  [[nodiscard]] Apple* GetApple() const { return this->apple; }
  [[nodiscard]] Render2D::IRenderer* GetRenderer() const { return this->renderer; }
  [[nodiscard]] Render2D::RenderManager* GetRenderManager() const { return this->renderManager; }

  // Setters
  void SetSnake(Snake& snake) { this->snake = &snake; }
  void SetApple(Apple& apple) { this->apple = &apple; }
  void SetUI(IUserInterface& ui) { this->ui = &ui; }
  void SetRenderer(Render2D::IRenderer& renderer) { this->renderer = &renderer; }
  void SetRenderManager(Render2D::RenderManager& renderManager)
  {
    this->renderManager = &renderManager;
  }

 private:
  GameSettings& settings;
  IGameState* currentState = nullptr;
  IUserInterface* ui;
  Render2D::RenderManager* renderManager;
  Render2D::IRenderer* renderer;
  Snake* snake;
  Apple* apple;
  int score;
};
