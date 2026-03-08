#pragma once
#include "core/entity/game-entity-manager.hpp"
#include "core/state-machine.hpp"
#include "core/i-game-state.hpp"
#include "engine/input/input-system.hpp"
#include "game/settings/game-settings.hpp"
#include "core/i-game-ui.hpp"

#include <memory>

namespace Core {
class IRenderer;
class RenderComponent2DManager;
}  // namespace Core

namespace Game {

class Apple;
class Snake;

struct GameContext {
  int score = {0};
  std::unique_ptr<GameSettings> settings = {nullptr};
  std::unique_ptr<Engine::Input::InputSystem> input = {nullptr};
  std::unique_ptr<Core::IGameUI> gameUI = {nullptr};
};

class GameplayStateMachine final : public Core::StateMachine {
 public:
  explicit GameplayStateMachine(std::unique_ptr<Core::IGameState> currentState = nullptr);
  ~GameplayStateMachine() override;
  void Update(float deltaTime) override;
  void DebugUpdate() override;

  [[nodiscard]] Core::IRenderer* GetRenderer() const { return this->renderer; }
  [[nodiscard]] Core::RenderComponent2DManager* GetRenderManager() const
  {
    return this->renderManager;
  }

  // Setters
  void SetSnake(Snake& snake);
  void SetApple(Apple& apple);
  void SetGameEntityManager(std::shared_ptr<Core::GameEntityManager> gameEntityManager);
  void SetRenderer(Core::IRenderer& renderer) { this->renderer = &renderer; }
  void SetRenderManager(Core::RenderComponent2DManager& renderManager)
  {
    this->renderManager = &renderManager;
  }
  GameContext& GetGameContext() { return this->gameContext; }

 private:
  GameContext gameContext;
  Core::RenderComponent2DManager* renderManager = nullptr;
  std::shared_ptr<Core::GameEntityManager> gameEntityManager = nullptr;
  Core::IRenderer* renderer = nullptr;
};
}  // namespace Game
