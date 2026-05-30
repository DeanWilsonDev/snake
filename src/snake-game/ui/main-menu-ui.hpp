//
// Created by Dean Wilson on 30/5/2025.
//

#pragma once
#include "core/user-interface/i-game-ui.hpp"

namespace UserInterface {
class IUserInterface;
}

namespace SnakeGame {
struct GameSettings;

class MainMenuUI final : public Core::UserInterface::IGameUI {
 public:
  explicit MainMenuUI(UserInterface::IUserInterface& ui, GameSettings& settings);
  ~MainMenuUI() override;

  void OnDrawUI() override;
  void OnDebugDrawUI() override;

  [[maybe_unused]] virtual void Update([[maybe_unused]] float deltaTime) override;
  [[maybe_unused]] virtual void DebugRender() const override;
  [[maybe_unused]] virtual void DebugUpdate() const override;
  [[nodiscard]] virtual Core::Rendering::Components::IRenderComponentUI&
  GetRenderComponentUI() const override;

 private:
  char scoreBuffer[100] = {0};
  GameSettings& settings;
  UserInterface::IUserInterface& ui;
};

}  // namespace SnakeGame
