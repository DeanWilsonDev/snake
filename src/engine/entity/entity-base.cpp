//
// Created by Dean Wilson on 29/5/2025.
//

#include "entity-base.hpp"

namespace Engine::Entity {

EntityBase::EntityBase(const EntityBaseParams& params) : active(params.active) {};

EntityBase::~EntityBase() = default;

void EntityBase::Initialize() {}

void EntityBase::Update([[maybe_unused]] float deltaTime) {}

void EntityBase::DebugUpdate() const {}

void EntityBase::DebugRender() const {}

int EntityBase::GetID() const
{
  return this->id;
}
bool EntityBase::IsActive() const
{
  return this->active;
}

void EntityBase::SetActive(const bool active)
{
  this->active = active;
}

const bool& EntityBase::GetActive()
{
  return this->active;
}

int EntityBase::GenerateId()
{
  static int nextId = 0;
  return nextId++;
};

Core::Components::IComponent* EntityBase::GetComponentByType(std::type_index type)
{
  if (const auto it = components.find(type); it != components.end()) {
    return it->second.get();
  }
  return nullptr;
}

}  // namespace Engine::Entity
