#pragma once

#include "Settings/game-settings.h"
#include "../game-session.h"
#include "../core/entity.h"

namespace Game {

struct AppleParams {
  GameSettings settings;
  Snake* snake;
};

class Apple final: public Core::Entity {
 public:
  explicit Apple(const AppleParams& params);
  void Update(float deltaTime) override;
  Core::Math::Vector2D GetNewPosition() const;
  Core::Math::Vector2D GetCenter() const;

  GameSettings settings;
  Snake* snake;
};
}  // namespace Game
