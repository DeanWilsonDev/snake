//
// Created by Dean Wilson on 30/5/2025.
//

#pragma once
#include "core/user-interface/i-game-ui.hpp"
#include "core/user-interface/i-user-interface.hpp"
// #include <memory>

namespace UserInterface {
class IUserInterface;
}

namespace SnakeGame {
struct GameSettings;

class MainMenuUI final : public Core::UserInterface::IGameUI {
 public:
  explicit MainMenuUI(int screenWidth, int screenHeight);
  ~MainMenuUI() override;

  void OnDrawUI(const Core::UserInterface::IUserInterface& ui) const override;

  // [[nodiscard]] virtual Core::Rendering::Components::IRenderComponentUI&
  // GetRenderComponentUI() const override;

 private:
  // std::unique_ptr<Core::Rendering::Components::IRenderComponentUI> renderComponent;
  int screenWidth;
  int screenHeight;
};

}  // namespace SnakeGame
