#include "snake-game/game-entities/snake.hpp"
#include "snake-game/settings/snake-game-settings.hpp"
#include "snake-segment.hpp"
#include "core/math/vector-2d.hpp"
#include "core/entities/i-entity-manager.hpp"
#include "engine/spatial/transform-2d.hpp"
#include "snake-game/game-entities/snake-head.hpp"

#include <cmath>
#include <memory>

namespace SnakeGame {

Snake::~Snake() = default;

Snake::Snake(const SnakeParams& snakeParams)
    : entityManager(snakeParams.entityManager)
    , settings(snakeParams.settings)
    , screenWidth(snakeParams.screenWidth)
    , screenHeight(snakeParams.screenHeight)
{
  auto snakeSize = static_cast<float>(settings.boxSize);

  this->transform = Engine::Spatial::Transform2D({100.f, 100.0f}, 0, {snakeSize, snakeSize});
}

Snake* Snake::Initialize()
{
  this->size = static_cast<float>(this->settings.boxSize);
  this->speed = this->size * 5.0f;
  // this->length = this->settings.defaultSnakeLength;
  this->direction = {1.0f, 0.0f};
  this->grow = false;


  return this;
}

void Snake::Update(const float)
{
  // accumulatedDistance += this->speed * deltaTime;
  //
  // if (accumulatedDistance >= this->size) {
  //   if (this->head->direction.x != 0.0f || this->head->direction.y != 0.0f) {
  //     this->SetDirection(this->head->direction);
  //   }
  //   this->Move();
  //   this->CheckIfShouldGrow();
  //   accumulatedDistance -= this->size;
  //   this->Teleport();
  // }
}


// MAIN QUEST: Move this to a game system
void Snake::CheckIfShouldGrow()
{
  // if (this->grow) {
  //   const auto params = SnakeSegmentParams{this->length, &this->body.back()->transform};
  //
  //   this->CreateSegment(params);
  //
  //   this->length++;
  //   this->grow = false;
  // }
}

void Snake::Teleport() const
{
  // SIDE QUEST: BoundaryWrapSystem
  // Wrapping behaviour should be handled by a dedicated BoundaryWrapSystem in the
  // game-systems layer rather than the Snake querying screen dimensions directly.
  // Snake should have no knowledge of screen bounds — the system takes a list of
  // entities and wraps their positions if they exceed the boundary.

  // for (auto& segment : this->body) {
  //   auto& segmentPosition = segment->GetTransformComponent().GetPosition();
  //   if (segmentPosition.x > this->screenWidth) {
  //     segmentPosition.x = 0;
  //   }
  //   else if (segmentPosition.x < 0) {
  //     segmentPosition.x = this->screenWidth;
  //   }
  //   else if (segmentPosition.y > this->screenHeight) {
  //     segmentPosition.y = 0;
  //   }
  //   else if (segmentPosition.y < 0) {
  //     segmentPosition.y = this->screenHeight;
  //   }
  // }
}

Core::Math::Vector2D Snake::GetCenter() const
{
//   const auto boxSize = static_cast<float>(this->settings.boxSize);
//   return {
//       this->head->GetTransformComponent().GetPosition().x + boxSize / 2.0f,
//       this->head->GetTransformComponent().GetPosition().y + boxSize / 2.0f,
//   };
}

void Snake::Destroy()
{
  for (auto& segment : this->body) {
    this->entityManager.RemoveEntity(segment);
  }
  this->body.clear();
  this->head = nullptr;
}
}  // namespace SnakeGame
