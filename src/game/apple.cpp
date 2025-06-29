#include "apple.hpp"
#include "snake.hpp"
#include "../game-session.h"
#include "raylib.h"

namespace Game {

Apple::Apple(const AppleParams& params) :
     settings(params.settings)
{
  this->Initialize();
}

void Apple::Update(float deltaTime)
{
  const int boxSize = this->settings.GetBoxSize();
  const float positionX = this->transform.position.x;
  const float positionY = this->transform.position.y;
  const float scaleX = this->transform.scale.x;
  const float scaleY = this->transform.scale.y;
  const float size = boxSize / 2.0f;

  // TODO: Move this to the renderer
  DrawRectangleRec({positionX, positionY, scaleX, scaleY}, RED);

  if (CheckCollisionCircles(
          this.snake->GetCenter(), this->snake->size / 2.0f - 2.0f, this->GetCenter(), size - 2.0f
      )) {
    this->transform.position = this->GetNewPosition();

    this->state->increaseScore();

    // TODO make set function
    this->snake->grow = true;
  }
}
void Apple::Initialize()
{
  LOG_TRACE("[Apple] Initializing");
  this->transform.position = this->GetNewPosition();
  LOG_TRACE("[Apple] Finished Initializing");
};

Core::Math::Vector2D Apple::GetNewPosition() const
{
  const int boxSize = this->settings.GetBoxSize();
  const int screenWidth = this->settings.GetScreenWidth();
  const int screenHeight = this->settings.GetScreenHeight();
  return {
      GetRandomValue(0, (screenWidth / boxSize) - 1) * boxSize + (boxSize - boxSize / 2.0f) / 2.0f,
      GetRandomValue(0, (screenHeight / boxSize) - 1) * boxSize + (boxSize - boxSize / 2.0f) / 2.0f
  };
}
Core::Math::Vector2D Apple::GetCenter() const
{
  const int boxSize = this->settings.GetBoxSize();
  return {
    this->transform.position.x + (boxSize - boxSize / 2.0f) / 2.0f,
    this->transform.position.y + (boxSize - boxSize / 2.0f) / 2.0f,
};
}

}  // namespace Game
