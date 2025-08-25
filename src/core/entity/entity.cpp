//
// Created by Dean Wilson on 29/5/2025.
//
#include "core/entity/entity.h"

namespace Core::Entity {
Entity::Entity(const int id): id(id){}
Entity::~Entity() = default;
void Entity::Initialize() {}
void Entity::Update(float deltaTime) {}
int Entity::GetID() const
{
  return id;
};
}  // namespace Core::Entity
