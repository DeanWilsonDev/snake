//
// Created by Dean Wilson on 6/7/2025.
//

#include "user-interface-manager.hpp"
#include "core/user-interface/i-game-ui.hpp"
#include "core/user-interface/i-user-interface.hpp"
#include "core/logging/log.hpp"

using namespace Core::UserInterface;

namespace Engine::UserInterface {

UserInterfaceManager::UserInterfaceManager() {}

UserInterfaceManager::~UserInterfaceManager() = default;

void UserInterfaceManager::Register(IGameUI* gameUI)
{
  if (auto ui = dynamic_cast<IGameUI*>(gameUI)) {
    this->gameUIs.push_back(ui);
  }
}

void UserInterfaceManager::Unregister(IGameUI* gameUI)
{
  if (auto ui = dynamic_cast<IGameUI*>(gameUI)) {
    std::erase(this->gameUIs, ui);
    return;
  }
  LOG_CORE_ERROR("[DebugUserInterfaceManager] Component set to nullptr, cannot Unregister");
}

void UserInterfaceManager::DrawUI(const IUserInterface& ui) const
{
  for (const IGameUI* gameUI : this->gameUIs) {
    if (!gameUI) {
      continue;
    }
    gameUI->OnDrawUI(ui);
  }
}

}  // namespace Engine::UserInterface
