//
// Created by Dean Wilson on 30/5/2025.
//

#pragma once
#include "user-interface/iuser-interface.hpp"

namespace Game {

class IGameUI;

class MainMenuUI final : public UserInterface::IUserInterface {
 public:
  explicit MainMenuUI();
  void Render() override;
private:
  char scoreBuffer[100] = {0};
};

}  // namespace Game
