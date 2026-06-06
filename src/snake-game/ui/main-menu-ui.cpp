//
// Created by Dean Wilson on 30/5/2025.
//

#include "main-menu-ui.hpp"

#include "core/math/vector-2d.hpp"
#include "core/user-interface/i-user-interface.hpp"

namespace SnakeGame {

MainMenuUI::MainMenuUI(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight)
{
}

MainMenuUI::~MainMenuUI() = default;

void MainMenuUI::OnDrawUI(const Core::UserInterface::IUserInterface& ui) const
{
  ui.DrawTextCentered("Snake", Core::Math::Vector2D{screenWidth / 2.0f, 40.0f}, 80);
  ui.DrawTextCentered(
      "Press 'Enter' to start", Core::Math::Vector2D{screenWidth / 2.0f, 200.0f}, 20
  );
}

// Core::Rendering::Components::IRenderComponentUI& MainMenuUI::GetRenderComponentUI() const
// {
//   return *this->renderComponent;
// }

}  // namespace SnakeGame
