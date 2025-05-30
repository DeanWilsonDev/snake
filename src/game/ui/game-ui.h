//
// Created by Dean Wilson on 30/5/2025.
//
#pragma once

#ifndef GAMEUI_H
#define GAMEUI_H

#include "../../raylib/user-interface/raylib-ui.h"

namespace Game::UI {

class GameUI : public  Raylib::UserInterface::RaylibUI {
  GameUI();
  void Render() override;
};

}  // namespace Game::UI
#endif  // GAMEUI_H
