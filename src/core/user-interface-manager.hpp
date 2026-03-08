//
// Created by Dean Wilson on 6/7/2025.
//
#pragma once

#include "core/i-game-ui.hpp"
#include "core/render-component-2d-manager.hpp"
#include "core/i-debugable.hpp"
#include "core/i-updatable.hpp"

#include <string>
#include <memory>
#include <vector>

namespace Core {
class IGameUI;

namespace Math {
struct Vector2D;
}

class UserInterfaceManager final : public Core::IUpdatable, Core::IDebugable {
 public:
  explicit UserInterfaceManager(const RenderComponent2DManager& renderManager);
  [[nodiscard]] IGameUI* GetGameUIByName(std::string name) const;
  void AddGameUI(IGameUI* gameUI);
  void Update(float deltaTime) override;
  void Render() const;
  void DebugUpdate() override;
  void DebugRender() override;

 private:
  std::vector<std::unique_ptr<IGameUI>> gameUIs;
  RenderComponent2DManager renderManager;
};
}  // namespace Core
