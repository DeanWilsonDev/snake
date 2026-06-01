//
// Created by Dean Wilson on 6/7/2025.
//
#pragma once

#include "core/rendering/i-render-component-manager.hpp"
#include "core/user-interface/i-game-ui.hpp"
#include "core/rendering/i-render-manager.hpp"

#include <string>
#include <memory>
#include <vector>

namespace Core {

namespace Math {
struct Vector2D;
}

namespace Rendering {
class IRenderer;
}

namespace UserInterface {
class IGameUI;

class UserInterfaceManager final : Core::Rendering::IRenderManager {
 public:
  explicit UserInterfaceManager();
  ~UserInterfaceManager();

  [[nodiscard]] UserInterface::IGameUI* GetGameUIByName(std::string name) const;
  void AddGameUI(std::unique_ptr<UserInterface::IGameUI> gameUI);
  void DrawUI() const;
  void DebugDrawUI() const;

  void OnRender(const Rendering::IRenderer& renderer) const override;

  // void OnUpdate(float deltaTime) override;
  //
  // void OnDebugUpdate() const override;
  // void OnDebugRender() const override;

 private:
  std::vector<std::unique_ptr<UserInterface::IGameUI>> gameUIs;
};
}  // namespace UserInterface
}  // namespace Core
