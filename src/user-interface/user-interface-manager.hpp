//
// Created by Dean Wilson on 6/7/2025.
//
#pragma once

namespace Core::Math {
struct Vector2D;
}

namespace UserInterface {
class IGameUI;

class UserInterfaceManager final {
 public:
  explicit UserInterfaceManager(IGameUI* gameUI) : gameUI(gameUI) {}
  [[nodiscard]] IGameUI* GetGameUI() const { return this->gameUI; }

 private:
  IGameUI* gameUI;
};
}  // namespace UserInterface
