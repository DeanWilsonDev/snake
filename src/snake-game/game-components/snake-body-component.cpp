#include "snake-body-component.hpp"
#include <deque>
#include "snake-game/game-entities/snake-segment.hpp"

namespace SnakeGame {

SnakeBodyComponent::SnakeBodyComponent(SnakeBodyComponentParams& params) : head(params.head) {}

void SnakeBodyComponent::AddBodyPart(SnakeSegment* bodyPart)
{
  this->segments.push_back(bodyPart);
}

const std::deque<SnakeSegment*>& SnakeBodyComponent::GetSegments() const
{
  return this->segments;
}

void SnakeBodyComponent::Clear()
{
  this->segments.clear();
}

}  // namespace SnakeGame
