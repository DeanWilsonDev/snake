//
// Created by Dean Wilson on 30/5/2025.
//
#pragma once

#include "../../raylib/user-interface/raylib-ui.h"

namespace Game::UI {

class GameUI : public  RaylibAdapter::UserInterface::RaylibUI {
  GameUI();
  void Render() override;
};

}  // namespace Game::UI
