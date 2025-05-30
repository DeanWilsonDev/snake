#pragma once
#include "istate-machine.h"

namespace Renderer2D {
class IRenderer;
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
  [[nodiscard]] Renderer2D::IRenderer* GetRenderer() const { return this->renderer; }
  [[nodiscard]] Renderer2D::RenderManager* GetRenderManager() const { return this->renderManager; }

  // Setters
  void SetSnake(Snake& snake) { this->snake = &snake; }
  void SetApple(Apple& apple) { this->apple = &apple; }
  void SetUI(IUserInterface& ui) { this->ui = &ui; }
  void SetRenderer(Renderer2D::IRenderer& renderer) { this->renderer = &renderer; }
  void SetRenderManager(Renderer2D::RenderManager& renderManager)
  {
    this->renderManager = &renderManager;
  }

 private:
  GameSettings& settings;
  IGameState* currentState = nullptr;
  IUserInterface* ui;
  Renderer2D::RenderManager* renderManager;
  Renderer2D::IRenderer* renderer;
  Snake* snake;
  Apple* apple;
  int score;
};
