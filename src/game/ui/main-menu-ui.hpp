//
// Created by Dean Wilson on 30/5/2025.
//

#pragma once

#ifndef MAIN_MENU_USER_INTERFACE_H
#define MAIN_MENU_USER_INTERFACE_H

#include "game-ui.hpp"

namespace Game {

class GameUI;

class MainMenuUI : public GameUI {
 public:
  explicit MainMenuUI(const Platform::Config::Window::WindowConfig& windowConfig);
  void Render() override;
};

}  // namespace Game
#endif  // MAIN_MENU_USER_INTERFACE_H
