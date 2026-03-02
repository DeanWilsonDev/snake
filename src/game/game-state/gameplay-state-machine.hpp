#pragma once
#include "core/entity/game-entity-manager.hpp"
#include "core/state-machine.hpp"
#include "core/i-game-state.hpp"
#include "engine/input/input-system.hpp"
#include "game/settings/game-settings.hpp"

#include <memory>

namespace Renderer2D {
class IRenderer;
class RenderComponent2DManager;
}  // namespace Renderer2D

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

  [[nodiscard]] Renderer2D::IRenderer* GetRenderer() const { return this->renderer; }
  [[nodiscard]] Renderer2D::RenderComponent2DManager* GetRenderManager() const
  {
    return this->renderManager;
  }

  // Setters
  void SetSnake(Snake& snake);
  void SetApple(Apple& apple);
  void SetGameEntityManager(std::shared_ptr<Core::GameEntityManager> gameEntityManager);
  void SetRenderer(Renderer2D::IRenderer& renderer) { this->renderer = &renderer; }
  void SetRenderManager(Renderer2D::RenderComponent2DManager& renderManager)
  {
    this->renderManager = &renderManager;
  }
  GameContext& GetGameContext() { return this->gameContext; }


 private:
  // REAPER: Clean up these pointers to use modern C++ varients

  GameContext gameContext;
  Renderer2D::RenderComponent2DManager* renderManager = nullptr;
  std::shared_ptr<Core::GameEntityManager> gameEntityManager = nullptr;
  Renderer2D::IRenderer* renderer = nullptr;
};
}  // namespace Game
