//
// Created by Dean Wilson on 31/5/2025.
//

#pragma once
#include "igame-ui.hpp"
#include "../../core/iuser-interface.hpp"

namespace Game {
class GameOverUI final : public Core::IUserInterface{
 public:
  GameOverUI();
  ~GameOverUI() override = default;
  void Render() override;
};
}  // namespace Game
