//
// Created by Dean Wilson on 6/6/2026.
//

#include "debug-user-interface-manager.hpp"
#include "core/debug/i-debug-game-ui.hpp"
#include "core/debug/i-debug-user-interface.hpp"
#include "core/logging/log.hpp"

using namespace Core::Debug;

namespace Debug::UserInterface {

DebugUserInterfaceManager::DebugUserInterfaceManager() {}

DebugUserInterfaceManager::~DebugUserInterfaceManager() = default;

void DebugUserInterfaceManager::Register(IDebugGameUI* debugUI)
{
  LOG_CORE_INFO("[DebugUserInterfaceManager] Registering Debug UI: {}", debugUI->GetName());
  if (auto ui = dynamic_cast<IDebugGameUI*>(debugUI)) {
    this->debugGameUIs.push_back(ui);
  }
}

void DebugUserInterfaceManager::Unregister(IDebugGameUI* debugGameUI)
{
  if (auto ui = dynamic_cast<IDebugGameUI*>(debugGameUI)) {
    std::erase(this->debugGameUIs, ui);
    return;
  }
  LOG_CORE_ERROR("[DebugUserInterfaceManager] Component set to nullptr, cannot Unregister");
}

void DebugUserInterfaceManager::DebugDrawUI(const Core::Debug::IDebugUserInterface& debugUI) const
{
  for (const IDebugGameUI* debugGameUI : this->debugGameUIs) {
    if (!debugGameUI) {
      continue;
    }
    debugGameUI->OnDebugDrawUI(debugUI);
  }
}

}  // namespace Debug::UserInterface
