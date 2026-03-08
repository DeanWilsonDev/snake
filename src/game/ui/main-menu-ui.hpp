//
// Created by Dean Wilson on 30/5/2025.
//

#pragma once
#include "core/i-game-ui.hpp"

namespace UserInterface {
class IUserInterface;
}

namespace Game {
struct GameSettings;

class MainMenuUI final : public Core::IGameUI {
 public:
  explicit MainMenuUI(UserInterface::IUserInterface& ui, GameSettings& settings);
  ~MainMenuUI() override;
  void Render() override;

 private:
  char scoreBuffer[100] = {0};
  GameSettings& settings;
  UserInterface::IUserInterface& ui;
};

}  // namespace Game
