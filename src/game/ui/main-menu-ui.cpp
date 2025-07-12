//
// Created by Dean Wilson on 30/5/2025.
//

#include "main-menu-ui.hpp"

#include "core/math/vector-2d.hpp"
#include "platform/window/window-manager.hpp"
#include "user-interface/user-interface-manager.hpp"

namespace Game {

MainMenuUI::MainMenuUI() = default;

void MainMenuUI::Render()
{
  const auto screenWidth = static_cast<float>(Platform::Window::WindowManager::GetScreenWidth());

  UserInterface::UserInterfaceManager::DrawTextCentered(
      "Snake", (Core::Math::Vector2D){screenWidth / 2.0f, 40.0f}, 80
  );
  UserInterface::UserInterfaceManager::DrawTextCentered(
      "Press 'Enter' to start", (Core::Math::Vector2D){screenWidth / 2.0f, 200.0f}, 20
  );
}

}  // namespace Game