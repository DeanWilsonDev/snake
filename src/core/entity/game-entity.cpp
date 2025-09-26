//
// Created by Dean Wilson on 25/8/2025.
//

#include "core/entity/game-entity.hpp"
#include "core/components/transform-component-2d.hpp"

namespace Core::Entity {

GameEntity::GameEntity(Components::TransformComponent2D& transform)
{
  this->transform = &transform;
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