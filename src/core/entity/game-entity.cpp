//
// Created by Dean Wilson on 25/8/2025.
//

#include "core/entity/game-entity.hpp"
#include "core/components/transform-component-2d.hpp"
#include "core/math/i-transform-2d.hpp"

namespace Core::Entity {

GameEntity::GameEntity(Math::ITransform2D& transform)
{
  this->transform = new Components::TransformComponent2D(&transform);
}

void GameEntity::Update(const float deltaTime)
{
  Entity::Update(deltaTime);
}
void GameEntity::Initialize()
{
  Entity::Initialize();
}

}  // namespace Core