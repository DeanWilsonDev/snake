//
// Created by Dean Wilson on 30/5/2025.
//

#pragma once

#ifndef MAIN_MENU_USER_INTERFACE_H
#define MAIN_MENU_USER_INTERFACE_H

#include "game-ui.h"

namespace Game::UI {

class GameUI;

class MainMenu : public GameUI {
  MainMenu();
  void Render() override;
};

}  // namespace Game::UI
#endif  // MAIN_MENU_USER_INTERFACE_H
