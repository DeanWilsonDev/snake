//
// Created by Dean Wilson on 6/7/2025.
//

#include "user-interface-manager.hpp"
#include "core/user-interface/i-game-ui.hpp"
#include "core/rendering/i-renderer.hpp"

#include <memory>
#include <utility>

namespace Core::UserInterface {

UserInterfaceManager::UserInterfaceManager() {}

UserInterfaceManager::~UserInterfaceManager() = default;

void UserInterfaceManager::AddGameUI(std::unique_ptr<UserInterface::IGameUI> gameUI)
{
  if (!gameUI) {
    return;
  }
  this->gameUIs.push_back(std::move(gameUI));
}

void UserInterfaceManager::OnUpdate(float deltaTime)
{
  for (const std::unique_ptr<UserInterface::IGameUI>& gameUI : this->gameUIs) {
    if (!gameUI) {
      continue;
    }
    gameUI->Update(deltaTime);
  }
}

void UserInterfaceManager::DrawUI() const
{
  for (const std::unique_ptr<UserInterface::IGameUI>& gameUI : this->gameUIs) {
    if (!gameUI) {
      continue;
    }
    gameUI->OnDrawUI();
  }
}

void UserInterfaceManager::DebugDrawUI() const
{
  for (const std::unique_ptr<UserInterface::IGameUI>& gameUI : this->gameUIs) {
    if (!gameUI) {
      continue;
    }
    gameUI->OnDebugDrawUI();
  }
}

void UserInterfaceManager::OnRender(const Rendering::IRenderer& renderer) const
{
  for (const std::unique_ptr<UserInterface::IGameUI>& gameUI : this->gameUIs) {
    if (!gameUI) {
      continue;
    }
    gameUI->GetRenderComponentUI().Render(renderer);
  }
}
void UserInterfaceManager::OnDebugUpdate() const
{
  for (const std::unique_ptr<UserInterface::IGameUI>& gameUI : this->gameUIs) {
    if (!gameUI) {
      continue;
    }
    gameUI->DebugUpdate();
  }
}

void UserInterfaceManager::OnDebugRender() const
{
  for (const std::unique_ptr<UserInterface::IGameUI>& gameUI : this->gameUIs) {
    if (!gameUI) {
      continue;
    }
    gameUI->DebugRender();
  }
}

}  // namespace Core::UserInterface
