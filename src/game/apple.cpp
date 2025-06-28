#include "apple.h"
#include "snake.hpp"
#include "../game-session.h"
#include "raylib.h"

namespace Game {

Apple::Apple(const AppleParams& params) :
     settings(params.settings)
, snake(params.snake)
{
  LOG_TRACE("[Apple] Initializing");
  this->transform.position = this->GetNewPosition();
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
  DrawRectangleRec(
      {
          positionX,
          positionY,
        scaleX,
        scaleY
      },
      RED
  );

  // Side Quest: Create functions for these
  Vector2 snakeHeadCenter = {
      this->snake->head->position.x + boxSize / 2.0f,
      this->snake->head->position.y + boxSize / 2.0f,
  };

  Vector2 appleCenter = {
      this->position.x + (boxSize - boxSize / 2.0f) / 2.0f,
      this->position.y + (boxSize - boxSize / 2.0f) / 2.0f,
  };

  if (CheckCollisionCircles(
          snakeHeadCenter, this->snake->size / 2.0f - 2.0f, appleCenter, size - 2.0f
      )) {
    this->position = this->GetNewPosition();

    this->state->increaseScore();

    // TODO make set function
    this->snake->grow = true;
  }
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

}  // namespace Game
