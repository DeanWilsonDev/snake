//
// Created by Dean Wilson on 25/8/2025.
//

#pragma once
#include "entity.h"

#include <cassert>
#include <typeindex>
#include <unordered_map>

namespace Core::Math {
struct Transform2D;
}
namespace Core::Entity {

class GameEntity : public Entity {
 public:
  explicit GameEntity(int id, Math::Transform2D& transform);
  void Update(float deltaTime) override;
  void Initialize() override;
  // Properties
  Math::Transform2D& transform;
  template <typename T, typename... Args>
  void AddComponent(Args&&... args);

  template <typename T>
  T* GetComponent();

  template <typename T>
  void RemoveComponent();

 private:
  std::unordered_map<std::type_index, std::unique_ptr<void>> components;
};

template <typename T, typename... Args>
void GameEntity::AddComponent(Args&&... args)
{
  // Ensure no duplicate components of the same type
  const auto type = std::type_index(typeid(T));
  assert(!components.contains(type) && "Component already added!");

  // Emplace a new instance of T using perfect forwarding of arguments
  components[type] = std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
T* GameEntity::GetComponent()
{
  const auto type = std::type_index(typeid(T));

  // Attempt to find the component
  if (const auto it = components.find(type); it != components.end()) {
    return static_cast<T*>(it->second.get());
  }
  return nullptr;
}

template <typename T>
void GameEntity::RemoveComponent()
{
  const auto type = std::type_index(typeid(T));
  this->components.erase(type);
}

}  // namespace Core::Entity
