//
// Created by Dean Wilson on 29/5/2025.
//

#include "engine/entities/entity.hpp"
#include "core/logging/log.hpp"
#include "core/components/transform-component-2d.hpp"
#include <memory>

namespace Engine::Entities {

Entity::Entity(const EntityParams& params) : active(params.active)
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
};

Entity::~Entity() = default;

void Entity::Initialize() {}

void Entity::Update([[maybe_unused]] float deltaTime) {}

void Entity::DebugUpdate() const {}

void Entity::DebugRender() const {}

int Entity::GetID() const
{
  return this->id;
}
bool Entity::IsActive() const
{
  return this->active;
}

void Entity::SetActive(const bool active)
{
  this->active = active;
}

const bool& Entity::GetActive() const
{
  return this->active;
}

int Entity::GenerateId()
{
  static int nextId = 0;
  return nextId++;
};

Core::Components::IComponent* Entity::GetComponentByType(std::type_index type)
{
  if (const auto it = components.find(type); it != components.end()) {
    return it->second.get();
  }
  return nullptr;
}

}  // namespace Engine::Entities
