//
// Created by Dean Wilson on 31/5/2025.
//

#pragma once
#include <memory>
#include "core/rendering/components/i-render-component-ui.hpp"
#include "core/user-interface/i-game-ui.hpp"

namespace UserInterface {
class IUserInterface;
}
namespace SnakeGame {
struct GameSettings;
class GameOverUI final : public Core::UserInterface::IGameUI {
 public:
  explicit GameOverUI(
      UserInterface::IUserInterface& ui, int screenWidth, int screenHeight, int& score
  );
  virtual ~GameOverUI() override {};
  virtual void OnDrawUI() override;

  [[nodiscard]] virtual Core::Rendering::Components::IRenderComponentUI&
  GetRenderComponentUI() const override
  {
    return *this->renderComponent;
  };

 private:
  std::unique_ptr<Core::Rendering::Components::IRenderComponentUI> renderComponent;
  UserInterface::IUserInterface& ui;
  int screenWidth;
  int screenHeight;
  int& score;
  char scoreBuffer[100] = {0};
};
}  // namespace SnakeGame
