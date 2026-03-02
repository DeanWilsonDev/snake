#pragma once
#include <memory>
#include "core/entity/game-entity-manager.hpp"
#include "core/state-machine.hpp"
#include "core/i-game-state.hpp"
#include "engine/input/input-system.hpp"

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

struct GameContext {
  int score = {0};
  std::unique_ptr<GameSettings> settings = {nullptr};
  std::unique_ptr<Engine::Input::InputSystem> input = {nullptr};
};

class GameplayStateMachine final : public Core::StateMachine {
 public:
  explicit GameplayStateMachine(std::unique_ptr<Core::IGameState> currentState = nullptr);
  ~GameplayStateMachine() override;
  void Update(float deltaTime) override;
  void DebugUpdate() override;
  void Next() override;

  [[nodiscard]] UserInterface::IUserInterface* GetUserInterface() const
  {
    return this->userInterface;
  };
  [[nodiscard]] Platform::Input::IInput* GetInput() const { return this->input; };
  [[nodiscard]] UserInterface::IGameUI* GetGameUI() const { return this->gameUI; };
  [[nodiscard]] GameSettings* GetGameSettings() const { return this->settings; }
  [[nodiscard]] Renderer2D::IRenderer* GetRenderer() const { return this->renderer; }
  [[nodiscard]] Renderer2D::RenderComponent2DManager* GetRenderManager() const
  {
    return this->renderManager;
  }

  // Setters
  void SetSnake(Snake& snake);
  void SetApple(Apple& apple);
  void SetGameEntityManager(std::shared_ptr<Core::GameEntityManager> gameEntityManager);
  void SetUserInterface(UserInterface::IUserInterface& ui);
  void SetInput(Platform::Input::IInput& input) { this->input = &input; }
  void SetGameUI(UserInterface::IGameUI& gameUI);
  void SetGameSettings(GameSettings& settings) { this->settings = &settings; }
  void SetRenderer(Renderer2D::IRenderer& renderer) { this->renderer = &renderer; }
  void SetRenderManager(Renderer2D::RenderComponent2DManager& renderManager)
  {
    this->renderManager = &renderManager;
  }
  GameContext& GetGameContext() { return this->gameContext; }

  void ClearUI() { this->gameUI = nullptr; }

 private:
  // REAPER: Clean up these pointers to use modern C++ varients

  GameContext gameContext;
  UserInterface::IUserInterface* userInterface = nullptr;
  UserInterface::IGameUI* gameUI = nullptr;
  Renderer2D::RenderComponent2DManager* renderManager = nullptr;
  std::shared_ptr<Core::GameEntityManager> gameEntityManager = nullptr;
  Renderer2D::IRenderer* renderer = nullptr;
  Platform::Input::IInput* input = nullptr;
  GameSettings* settings = nullptr;
};
}  // namespace Game
