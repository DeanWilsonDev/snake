#pragma once
#include "core/i-state-machine.hpp"
#include "core/i-game-state.h"

namespace Platform::Input {
class IInput;
}
namespace Game {
struct GameSettings;
}
namespace Renderer2D {
class IRenderer;
class RenderComponent2DManager;  // Side Quest: This should probably be an interface
}  // namespace Renderer2D

namespace Core {
class IGameState;
}  // namespace Core

namespace UserInterface {
class IGameUI;
class IUserInterface;
}  // namespace UserInterface

namespace Game {

class Apple;
class Snake;

class GameplayStateMachine final : public Core::IStateMachine {
 public:
  explicit GameplayStateMachine(Core::IGameState* currentState = nullptr);
  ~GameplayStateMachine() override;
  void Update(float deltaTime) override;
  void IncreaseScore();
  void Next() override;

  // Initializers
  void InitializeSnake() const;
  void InitializeApple() const;

  // Getters
  Core::IGameState* GetCurrentState() override { return this->currentState; };

  [[nodiscard]] UserInterface::IUserInterface* GetUserInterface() const
  {
    return this->userInterface;
  };
  [[nodiscard]] Platform::Input::IInput* GetInput() const { return this->input; };
  [[nodiscard]] UserInterface::IGameUI* GetGameUI() const { return this->gameUI; };
  [[nodiscard]] int& GetScore() { return this->score; };
  [[nodiscard]] int GetScore() const { return this->score; };
  [[nodiscard]] Snake* GetSnake() const { return this->snake; }
  [[nodiscard]] Apple* GetApple() const { return this->apple; }
  [[nodiscard]] GameSettings* GetGameSettings() const { return this->settings; }
  [[nodiscard]] Renderer2D::IRenderer* GetRenderer() const { return this->renderer; }
  [[nodiscard]] Renderer2D::RenderComponent2DManager* GetRenderManager() const
  {
    return this->renderManager;
  }

  // Setters
  void SetSnake(Snake& snake);
  void SetApple(Apple& apple);
  void SetUserInterface(UserInterface::IUserInterface& ui);
  void SetInput(Platform::Input::IInput& input) { this->input = &input; }
  void SetGameUI(UserInterface::IGameUI& gameUI);
  void SetGameSettings(GameSettings& settings) { this->settings = &settings; }
  void SetRenderer(Renderer2D::IRenderer& renderer) { this->renderer = &renderer; }
  void SetRenderManager(Renderer2D::RenderComponent2DManager& renderManager)
  {
    this->renderManager = &renderManager;
  }

  void ClearUI() { this->gameUI = nullptr; }
  void ChangeState(Core::IGameState* newState) override;

 private:
  Core::IGameState* DetermineNextState() override;

  Core::IGameState* currentState = nullptr;
  UserInterface::IUserInterface* userInterface = nullptr;
  UserInterface::IGameUI* gameUI = nullptr;
  Renderer2D::RenderComponent2DManager* renderManager = nullptr;
  Renderer2D::IRenderer* renderer = nullptr;
  Platform::Input::IInput* input = nullptr;
  GameSettings* settings = nullptr;
  Snake* snake = nullptr;
  Apple* apple = nullptr;
  int score = {0};
};
}  // namespace Game
