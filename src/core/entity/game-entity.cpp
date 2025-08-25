//
// Created by Dean Wilson on 25/8/2025.
//

#include "core/entity/game-entity.hpp"

namespace Core::Entity {

GameEntity::GameEntity(int id, Math::Transform2D& transform) : Entity(), transform(transform) {}

void GameEntity::Update(const float deltaTime)
{
  Entity::Update(deltaTime);
}
void GameEntity::Initialize()
{
  Entity::Initialize();
}

}  // namespace Core