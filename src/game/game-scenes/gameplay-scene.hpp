///
/// Created by Dean Wilson 22 March 2026
///

#pragma once

#include "core/i-game-scene.hpp"
#include "game/game-state/gameplay-state-machine.hpp"
#include "core/state/i-game-state.hpp"
#include "core/entity/game-entity-manager.hpp"



namespace Game {
class GameplayStateMachine;

class GameplayScene : public Core::IGameScene {
 public:
  void OnEnter(Core::SceneTransitionContext ctx) override;
  void OnExit() override;
  void Update(float deltaTime) override;
  void Render() const override;

 private:
  Core::SceneTransitionContext transition;
  Core::IGameState state;
  Core::Entity::GameEntityManager entityManager;
  GameplayStateMachine stateMachine;
};
}  // namespace Game
