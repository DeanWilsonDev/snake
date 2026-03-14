//
// Created by Dean Wilson on 6/7/2025.
//

#include "user-interface-manager.hpp"
#include "core/user-interface/i-game-ui.hpp"
#include "core/rendering/i-renderer.hpp"

#include <memory>
#include <utility>

namespace Core {

UserInterfaceManager::UserInterfaceManager() {}

UserInterfaceManager::~UserInterfaceManager() = default;

void UserInterfaceManager::AddGameUI(std::unique_ptr<UserInterface::IGameUI> gameUI)
{
  if (!gameUI) {
    return;
  }
  this->gameUIs.push_back(std::move(gameUI));
}
void UserInterfaceManager::Update(float deltaTime)
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

void UserInterfaceManager::Render(const Rendering::IRenderer& renderer) const
{
  for (const std::unique_ptr<UserInterface::IGameUI>& gameUI : this->gameUIs) {
    if (!gameUI) {
      continue;
    }
    gameUI->GetRenderComponentUI().Render(renderer);
  }
}
void UserInterfaceManager::DebugUpdate()
{
  for (const std::unique_ptr<UserInterface::IGameUI>& gameUI : this->gameUIs) {
    if (!gameUI) {
      continue;
    }
    gameUI->DebugUpdate();
  }
}
void UserInterfaceManager::DebugRender()
{
  for (const std::unique_ptr<UserInterface::IGameUI>& gameUI : this->gameUIs) {
    if (!gameUI) {
      continue;
    }
    gameUI->DebugRender();
  }
}

}  // namespace Core
