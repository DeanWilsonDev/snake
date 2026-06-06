//
// Created by Dean Wilson on 6th June 2026
//

#pragma once

namespace Core {
namespace Debug {
class IDebugGameUI;
class IDebugUserInterface;

class IDebugUserInterfaceManager {
 public:
  virtual ~IDebugUserInterfaceManager() = default;

  virtual void Register(Core::Debug::IDebugGameUI* debugUI) = 0;
  virtual void Unregister(Core::Debug::IDebugGameUI* debugUI) = 0;

  // virtual IDebugGameUI* GetDebugGameUIByName(std::string name) const = 0;

  virtual void DebugDrawUI(const IDebugUserInterface& debugUI) const = 0;
};
}  // namespace Debug
}  // namespace Core
