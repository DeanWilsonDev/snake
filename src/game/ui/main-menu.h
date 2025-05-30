//
// Created by Dean Wilson on 30/5/2025.
//

#pragma once

#ifndef MAIN_MENU_USER_INTERFACE_H
#define MAIN_MENU_USER_INTERFACE_H

namespace Game::UI {

class GameUI;

class MainMenu : GameUI {
  MainMenu();
  void Render() override;
};

}  // namespace Game::UI
#endif  // MAIN_MENU_USER_INTERFACE_H
