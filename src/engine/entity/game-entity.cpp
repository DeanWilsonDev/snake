//
// Created by Dean Wilson on 25/8/2025.
//

#include "game-entity.hpp"
#include <memory>
#include "core/components/transform-component-2d.hpp"
#include "entity-base.hpp"
#include "core/math/vector-2d.hpp"
#include "core/math/size-2d.hpp"
#include "core/logging/log.hpp"

namespace Engine::Entity {

GameEntity::GameEntity(const GameEntityParams& params) : EntityBase(params)
{
  LOG_TRACE("[GameEntity] Setting up new GameEntity");

  if (params.transform) {
    this->transformComponent =
        std::make_unique<Core::Components::TransformComponent2D>(params.transform);
  }

  LOG_TRACE(
      "[GameEntity] Checking TransformComponent2D is Initialized: [{}]",
      static_cast<void*>(&this->transformComponent)
  );

  if (this->transformComponent == nullptr) {
    this->transformComponent = make_unique<Core::Components::TransformComponent2D>(
        Core::Math::Vector2D::Zero(), 0.0f, Core::Math::Size2D::Zero()
    );
  }
}

GameEntity::~GameEntity() {}

void GameEntity::DebugUpdate()
{
  EntityBase::DebugUpdate();
}

void GameEntity::Update(const float deltaTime)
{
  EntityBase::Update(deltaTime);
}
void GameEntity::Initialize()
{
  EntityBase::Initialize();
}

Core::Components::TransformComponent2D& GameEntity::GetTransformComponent()
{
  return *this->transformComponent;
}

}  // namespace Engine::Entity
