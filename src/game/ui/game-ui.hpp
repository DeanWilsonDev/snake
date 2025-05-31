//
// Created by Dean Wilson on 30/5/2025.
//
#pragma once

#include "../../raylib/user-interface/raylib-ui.h"

namespace Game {

// TODO: This class doesn't properly abstract Raylib away from the implementation
class GameUI : public RaylibAdapter::UserInterface::RaylibUI {
 public:
  GameUI(const Platform::Config::Window::WindowConfig& windowConfig);
  void Render() override;

 protected:
};

}  // namespace Game
