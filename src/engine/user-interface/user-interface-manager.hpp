//
// Created by Dean Wilson on 6/7/2025.
//
#pragma once

#include "core/user-interface/i-game-ui.hpp"
#include "core/user-interface/i-user-interface-manager.hpp"
#include "core/user-interface/i-user-interface.hpp"

#include <memory>
#include <vector>

using namespace Core::UserInterface;

namespace Core {
class IGameUI;
}

namespace Engine {

namespace Math {
struct Vector2D;
}

namespace Rendering {
class IRenderer;
}

namespace UserInterface {

class UserInterfaceManager final : public IUserInterfaceManager {
 public:
  explicit UserInterfaceManager();
  ~UserInterfaceManager();

  // [[nodiscard]] IGameUI* GetGameUIByName(std::string name) const override;

  void AddGameUI(std::unique_ptr<IGameUI> gameUI);

  void Register(Core::UserInterface::IGameUI* gameUI) override;
  void Unregister(Core::UserInterface::IGameUI* gameUI) override;

  void DrawUI(const IUserInterface& ui) const override;

 private:
  std::vector<IGameUI*> gameUIs;
};
}  // namespace UserInterface
}  // namespace Engine
