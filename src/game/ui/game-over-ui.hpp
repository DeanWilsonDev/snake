//
// Created by Dean Wilson on 31/5/2025.
//

#pragma once
#include "core/i-game-ui.hpp"

namespace UserInterface {
class IUserInterface;
}
namespace Game {
struct GameSettings;
class GameOverUI final : public Core::IGameUI {
 public:
  explicit GameOverUI(UserInterface::IUserInterface& ui, GameSettings& settings, int& score);
  ~GameOverUI() override = default;
  void Render() override;

 private:
  UserInterface::IUserInterface& ui;
  GameSettings& settings;
  int& score;
  char scoreBuffer[100] = {0};
};
}  // namespace Game
