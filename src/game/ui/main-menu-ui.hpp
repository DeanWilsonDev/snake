//
// Created by Dean Wilson on 30/5/2025.
//

#pragma once
#include "../../core/iuser-interface.hpp"

namespace Game {

class IGameUI;

class MainMenuUI final : public Core::IUserInterface {
 public:
  explicit MainMenuUI();
  void Render() override;
};

}  // namespace Game
