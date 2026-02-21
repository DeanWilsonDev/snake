//
// Created by Dean Wilson on 29/5/2025.
//
#pragma once

#include "core/components/i-component.hpp"
#include <cassert>
#include <typeindex>
#include <unordered_map>
#include <memory>

namespace Core::Entity {

struct EntityParams {
  bool active = true;

  EntityParams(bool active = true) : active(active) {}
};

class Entity {
 public:
  explicit Entity(const EntityParams& params);
  virtual ~Entity() = 0;

  virtual void Initialize();
  virtual void Update(float deltaTime);
  virtual void DebugUpdate();
  [[nodiscard]] int GetID() const;
  [[nodiscard]] bool IsActive() const;
  virtual void SetActive(bool active);
  virtual bool& GetActive();

  template <typename T, typename... Args>
  void AddComponent(Args&&... args);

  template <typename T>
  T* GetComponent();

  template <typename T>
  void RemoveComponent();

 private:
  std::unordered_map<std::type_index, std::unique_ptr<Components::IComponent>> components{};

  static int GenerateId();

  const int id{GenerateId()};
  bool active{true};
};

template <typename T, typename... Args>
void Entity::AddComponent(Args&&... args)
{
  // Ensure no duplicate components of the same type
  const auto type = std::type_index(typeid(T));
  assert(!components.contains(type) && "Component already added!");

  // Emplace a new instance of T using perfect forwarding of arguments
  components[type] = std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
T* Entity::GetComponent()
{
  const auto type = std::type_index(typeid(T));

  // Attempt to find the component
  if (const auto it = components.find(type); it != components.end()) {
    return static_cast<T*>(it->second.get());
  }
  return nullptr;
}

template <typename T>
void Entity::RemoveComponent()
{
  const auto type = std::type_index(typeid(T));
  this->components.erase(type);
}

}  // namespace Core::Entity
