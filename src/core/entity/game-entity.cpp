//
// Created by Dean Wilson on 25/8/2025.
//

#include "core/entity/game-entity.hpp"
#include <memory>
#include "core/components/transform-component-2d.hpp"
#include "core/entity/entity.h"
#include "core/math/vector-2d.hpp"
#include "core/math/size-2d.hpp"
#include "umbra/log.h"

namespace Core::Entity {

GameEntity::GameEntity(const GameEntityParams& params) : Entity(params)
{
  LOG_TRACE("[GameEntity] Setting up new GameEntity");

  if(params.transform){
    this->transformComponent = std::make_unique<Components::TransformComponent2D>(params.transform);
  }

  LOG_TRACE(
      "[GameEntity] Checking TransformComponent2D is Initialized: [{}]",
      static_cast<void*>(&this->transformComponent)
  );

  if (this->transformComponent == nullptr) {
    this->transformComponent = make_unique<Components::TransformComponent2D>(
        Math::Vector2D::Zero(), 0.0f, Core::Math::Size2D::Zero()
    );
  }
}

GameEntity::~GameEntity() {}

void GameEntity::Update(const float deltaTime)
{
  Entity::Update(deltaTime);
}
void GameEntity::Initialize()
{
  Entity::Initialize();
}

}  // namespace Core::Entity
