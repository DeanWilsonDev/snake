//
// Created by Dean Wilson on 31/5/2025.
//

#pragma once
#include "game-ui.hpp"

namespace Game {
class GameOverUI : public GameUI {
 public:
  GameOverUI(const Platform::Config::Window::WindowConfig& windowConfig);
  ~GameOverUI() override = default;
  void Render() override;
};
}  // namespace Game
