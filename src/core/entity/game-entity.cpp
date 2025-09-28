//
// Created by Dean Wilson on 25/8/2025.
//

#include "core/entity/game-entity.hpp"
#include "core/components/transform-component-2d.hpp"

namespace Core::Entity {

GameEntity::GameEntity(const GameEntityParams& params) : Entity(params)
{
  this->transform = params.transform;

  if (this->transform == nullptr) {
    this->transform = new Components::TransformComponent2D(
        Math::Vector2D::Zero(), 0.0f, Core::Math::Size2D::Zero()
    );
  }
}

GameEntity::~GameEntity()
{
  if (this->transform != nullptr) {
    delete this->transform;
    this->transform = nullptr;
  }
}

void GameEntity::Update(const float deltaTime)
{
  Entity::Update(deltaTime);
}
void GameEntity::Initialize()
{
  Entity::Initialize();
}

}  // namespace Core::Entity