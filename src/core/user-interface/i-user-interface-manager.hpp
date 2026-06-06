//
// Created by Dean Wilson on 15th March 2026
//

#pragma once

namespace Core {
namespace UserInterface {
class IGameUI;
class IUserInterface;

class IUserInterfaceManager {
 public:
  virtual ~IUserInterfaceManager() = default;

  virtual void Register(Core::UserInterface::IGameUI* gameUI) = 0;
  virtual void Unregister(Core::UserInterface::IGameUI* gameUI) = 0;

  // virtual IGameUI* GetGameUIByName(std::string name) const = 0;

  virtual void DrawUI(const IUserInterface& ui) const = 0;
};
}  // namespace UserInterface
}  // namespace Core
