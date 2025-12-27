//
// Created by Dean Wilson on 29/5/2025.
//
#include "core/entity/entity.h"

namespace Core::Entity {
Entity::Entity(const EntityParams& params) : active(params.active){};
Entity::~Entity() = default;
void Entity::Initialize() {}
void Entity::Update([[maybe_unused]] float deltaTime) {}
void Entity::DebugUpdate() {}
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
bool& Entity::GetActive()
{
  return this->active;
}

int Entity::GenerateId()
{
  static int nextId = 0;
  return nextId++;
};

}  // namespace Core::Entity
