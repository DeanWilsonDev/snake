//
// Created by Dean Wilson on 26/7/2025.
//

#pragma once
#include "game/game-state/gameplay-state-machine.hpp"
#include "core/i-game-ui.hpp"

namespace UserInterface {
class IUserInterface;
}

namespace Game {
struct GameSettings;

class GameplayUI final : public Core::IGameUI {
 public:
  explicit GameplayUI(GameContext& gameContext);
  void Render() override;

 private:
  char scoreBuffer[100] = {0};
  GameContext& gameContext;
};
}  // namespace Game
