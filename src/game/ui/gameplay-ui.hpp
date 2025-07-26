//
// Created by Dean Wilson on 26/7/2025.
//

#pragma once
#include "user-interface/i-game-ui.hpp"

namespace UserInterface {
class IUserInterface;
}

namespace Game {
struct GameSettings;

class GameplayUI final : public UserInterface::IGameUI {
 public:
  explicit GameplayUI(UserInterface::IUserInterface& ui, GameSettings& settings, int& score);
  void Render() override;

 private:
  UserInterface::IUserInterface& ui;
  GameSettings& settings;
  char scoreBuffer[100] = {0};
  int& score;
};
}  // namespace Game
