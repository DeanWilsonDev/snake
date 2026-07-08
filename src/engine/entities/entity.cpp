//
// Created by Dean Wilson on 29/5/2025.
//

#include "engine/entities/entity.hpp"
#include "core/logging/log.hpp"
#include "engine/spatial/components/transform-component-2d.hpp"
#include "engine/spatial/size-2d.hpp"

#include <functional>
#include <memory>

namespace Engine::Entities {

Entity::Entity(const EntityParams& params) : active(params.active)
{
  LOG_TRACE("[GameEntity] Setting up new GameEntity");

  if (params.transform) {
    this->transformComponent =
        std::make_unique<Engine::Spatial::Components::TransformComponent2D>(params.transform);
  }

  LOG_TRACE(
      "[GameEntity] Checking TransformComponent2D is Initialized: [{}]",
      static_cast<void*>(&this->transformComponent)
  );

  if (this->transformComponent == nullptr) {
    this->transformComponent = make_unique<Engine::Spatial::Components::TransformComponent2D>(
        Core::Math::Vector2D::Zero(), 0.0f, Engine::Spatial::Size2D::Zero()
    );
  }
};

Entity::~Entity() = default;

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

Core::Components::IComponent* Entity::GetComponentByType(std::type_index type) const
{
  if (const auto it = components.find(type); it != components.end()) {
    return it->second.get();
  }
  return nullptr;
}

void Entity::ForEachComponent(
    std::function<bool(const Core::Components::IComponent*)> visitor
) const
{
  for (auto& [type, component] : this->components) {
    if (!visitor(component.get())) {
      return;
    }
  }
}

Core::Spatial::Components::ITransformComponent2D& Entity::GetTransformComponent()
{
  return *this->transformComponent;
};

const Core::Spatial::Components::ITransformComponent2D& Entity::GetTransformComponent() const
{
  return *this->transformComponent;
};

void Entity::BeginPlay() {}
void Entity::OnRegistration() {}
void Entity::OnActivate() {}
void Entity::Update(float) {}
void Entity::DebugUpdate() const {}
void Entity::DebugRender() const {}

}  // namespace Engine::Entities
