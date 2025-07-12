//
// Created by Dean Wilson on 31/5/2025.
//

#pragma once
#include "user-interface/iuser-interface.hpp"

namespace Game {
class GameOverUI final : public UserInterface::IUserInterface{
 public:
  explicit GameOverUI(int score);
  ~GameOverUI() override = default;
  void Render() override;
private:
  int score = {0};
  char scoreBuffer[100] = {0};
};
}  // namespace Game
