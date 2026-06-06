//
// Created by Dean Wilson on 31/5/2025.
//

#pragma once
// #include <memory>
// #include "core/rendering/components/i-render-component-ui.hpp"
#include "core/user-interface/i-game-ui.hpp"

namespace Core {

namespace UserInterface {
class IUserInterface;
class IDebugUserInterface;
}  // namespace UserInterface
}  // namespace Core

namespace SnakeGame {
struct GameSettings;
class GameOverUI final : public Core::UserInterface::IGameUI {
 public:
  explicit GameOverUI(int screenWidth, int screenHeight, int& score);
  virtual ~GameOverUI() override {};
  virtual void OnDrawUI(const Core::UserInterface::IUserInterface& ui) const override;

  // MAIN QUEST: Set up UI Components
  // [[nodiscard]] virtual Core::Rendering::Components::IRenderComponentUI&
  // GetRenderComponentUI() const override
  // {
  //   return *this->renderComponent;
  // };

 private:
  // std::unique_ptr<Core::Rendering::Components::IRenderComponentUI> renderComponent;
  int screenWidth;
  int screenHeight;
  int& score;
  char scoreBuffer[100] = {0};
};
}  // namespace SnakeGame
