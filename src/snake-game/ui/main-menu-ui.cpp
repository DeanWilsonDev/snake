//
// Created by Dean Wilson on 30/5/2025.
//

#include "main-menu-ui.hpp"

#include "core/math/vector-2d.hpp"
#include "user-interface/i-user-interface.hpp"

namespace SnakeGame {

MainMenuUI::MainMenuUI(UserInterface::IUserInterface& ui, int screenWidth, int screenHeight)
    : ui(ui), screenWidth(screenWidth), screenHeight(screenHeight)
{
}

MainMenuUI::~MainMenuUI() = default;

void MainMenuUI::OnDebugDrawUI() {}

void MainMenuUI::OnDrawUI()
{
  this->ui.DrawTextCentered("Snake", Core::Math::Vector2D{screenWidth / 2.0f, 40.0f}, 80);
  this->ui.DrawTextCentered(
      "Press 'Enter' to start", Core::Math::Vector2D{screenWidth / 2.0f, 200.0f}, 20
  );
}

Core::Rendering::Components::IRenderComponentUI& MainMenuUI::GetRenderComponentUI() const
{
  return *this->renderComponent;
}

}  // namespace SnakeGame
