#pragma once
#include "core/istate-machine.hpp"
#include "core/igame-state.h"

namespace Renderer2D {
class IRenderer;
class RenderComponent2DManager; // Side Quest: This should probably be an interface
}  // namespace Renderer2D

namespace Core {
class IGameState;
}  // namespace Core

namespace UserInterface {
class IUserInterface;
}  // namespace UserInterface

namespace Game {

class Apple;
class Snake;

class GameplayStateMachine final : public Core::IStateMachine {
 public:
  explicit GameplayStateMachine(Core::IGameState* currentState);
  ~GameplayStateMachine() override;
  void Update(float deltaTime) override;
  void IncreaseScore();
  void Next() override;

  // Initializers
  void InitializeSnake() const;
  void InitializeApple() const;

  // Getters
  Core::IGameState* GetCurrentState() override { return this->currentState; };

  [[nodiscard]] UserInterface::IUserInterface* GetUI() const { return this->ui; };
  [[nodiscard]] int GetScore() const { return this->score; };
  [[nodiscard]] Snake* GetSnake() const { return this->snake; }
  [[nodiscard]] Apple* GetApple() const { return this->apple; }
  [[nodiscard]] Renderer2D::IRenderer* GetRenderer() const { return this->renderer; }
  [[nodiscard]] Renderer2D::RenderComponent2DManager* GetRenderManager() const { return this->renderManager; }

  // Setters
  void SetSnake(Snake& snake);
  void SetApple(Apple& apple);
  void SetUI(UserInterface::IUserInterface& ui) { this->ui = &ui; }
  void SetRenderer(Renderer2D::IRenderer& renderer) { this->renderer = &renderer; }
  void SetRenderManager(Renderer2D::RenderComponent2DManager& renderManager)
  {
    this->renderManager = &renderManager;
  }

  void ClearUI() { this->ui = nullptr; }

 private:
  Core::IGameState* DetermineNextState() override;
  void ChangeState(Core::IGameState* newState) override;

  Core::IGameState* currentState = nullptr;
  UserInterface::IUserInterface* ui = nullptr;
  Renderer2D::RenderComponent2DManager* renderManager = nullptr;
  Renderer2D::IRenderer* renderer = nullptr;
  Snake* snake = nullptr;
  Apple* apple = nullptr;
  int score = {0};
};
}  // namespace Game
