#pragma once
#include "engine/entities/entity-manager.hpp"
#include "engine/state/state-machine.hpp"
#include "core/state/i-game-state.hpp"
#include "engine/input/input-system.hpp"
#include "snake-game/settings/snake-game-settings.hpp"

#include <memory>

namespace Core {
namespace Rendering {
class IRenderer;
class RenderComponent2DManager;
}  // namespace Rendering
}  // namespace Core

namespace SnakeGame {

class Apple;
class Snake;

struct GameContext {
  int score = {0};
  std::unique_ptr<SnakeGameSettings> settings = {nullptr};
  std::unique_ptr<Engine::Input::InputSystem> input = {nullptr};
};

class GameplayStateMachine final : public Engine::State::StateMachine {
 public:
  explicit GameplayStateMachine(std::unique_ptr<Core::State::IGameState> currentState = nullptr);
  ~GameplayStateMachine() override;
  void Update(float deltaTime) override;
  void DebugUpdate() const override;
  void DebugRender() const override;

  [[nodiscard]] Core::Rendering::IRenderer* GetRenderer() const { return this->renderer; }
  [[nodiscard]] Core::Rendering::RenderComponent2DManager* GetRenderManager() const
  {
    return this->renderManager;
  }

  // Setters
  void SetSnake(Snake& snake);
  void SetApple(Apple& apple);
  void SetGameEntityManager(std::shared_ptr<Engine::Entities::EntityManager> gameEntityManager);
  void SetRenderer(Core::Rendering::IRenderer& renderer) { this->renderer = &renderer; }
  void SetRenderManager(Core::Rendering::RenderComponent2DManager& renderManager)
  {
    this->renderManager = &renderManager;
  }
  GameContext& GetGameContext() { return this->gameContext; }

 private:
  GameContext gameContext;
  Core::Rendering::RenderComponent2DManager* renderManager = nullptr;
  std::shared_ptr<Engine::Entities::EntityManager> entityManager = nullptr;
  Core::Rendering::IRenderer* renderer = nullptr;
};
}  // namespace SnakeGame
