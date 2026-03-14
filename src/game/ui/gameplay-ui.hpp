//
// Created by Dean Wilson on 26/7/2025.
//

#pragma once
#include "game/game-state/gameplay-state-machine.hpp"
#include "core/user-interface/i-game-ui.hpp"
#include <memory>

namespace UserInterface {
class IUserInterface;
}

namespace Game {
struct GameSettings;

class GameplayUI final : public Core::UserInterface::IGameUI {
 public:
  explicit GameplayUI(GameContext& gameContext);
  virtual void OnDrawUI() override;

  [[nodiscard]] virtual Core::Rendering::Components::IRenderComponentUI&
  GetRenderComponentUI() const override
  {
    return *this->renderComponent;
  };

 private:
  std::unique_ptr<Core::Rendering::Components::IRenderComponentUI> renderComponent;
  char scoreBuffer[100] = {0};
  GameContext& gameContext;
};
}  // namespace Game
