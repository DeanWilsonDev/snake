#include "apple.hpp"
#include "snake.hpp"
#include "core/core.h"

namespace Game {

Apple::Apple(const AppleParams& params) : settings(params.settings), colliderComponent(params.colliderComponent)
{
  this->Initialize();
}

void Apple::Update(float deltaTime)
{

}

void Apple::Initialize()
{
  LOG_TRACE("[Apple] Initializing");
  this->transform.position = this->GetNewPosition();
  LOG_TRACE("[Apple] Finished Initializing");
};

Core::Math::Vector2D Apple::GetNewPosition() const
{
  const auto boxSize = static_cast<float>(this->settings.GetBoxSize());
  const auto screenWidth = static_cast<float>(GameSettings::GetScreenWidth());
  const auto screenHeight = static_cast<float>(GameSettings::GetScreenHeight());

  const auto maxWidth = static_cast<int>(screenWidth / boxSize - 1.f);
  const auto maxHeight = static_cast<int>(screenHeight / boxSize - 1.f);

  const auto posX =
      static_cast<float>(Core::GetRandomValue(0, maxWidth)) * boxSize + (boxSize - boxSize / 2.0f) / 2.0f;

  const auto posY = static_cast<float>(Core::GetRandomValue(0, maxHeight)) * boxSize +
                    (boxSize - boxSize / 2.0f) / 2.0f;

  return {.x = posX, .y = posY};
}

Core::Math::Vector2D Apple::GetCenter() const
{
  const auto boxSize = static_cast<float>(this->settings.GetBoxSize());
  return {
      this->transform.position.x + (boxSize - boxSize / 2.0f) / 2.0f,
      this->transform.position.y + (boxSize - boxSize / 2.0f) / 2.0f,
  };
}

}  // namespace Game
