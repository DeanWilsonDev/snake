//
// Created by Dean Wilson on 29/5/2025.
//
#pragma once

#include "core/components/i-component.hpp"
#include "core/entity/i-entity.hpp"
#include <cassert>
#include <typeindex>
#include <unordered_map>
#include <memory>

namespace Engine::Entity {

struct EntityBaseParams {
  bool active = true;

  EntityBaseParams(bool active = true) : active(active) {}
};

class EntityBase : virtual public Core::Entity::IEntity {
 public:
  explicit EntityBase(const EntityBaseParams& params);
  virtual ~EntityBase() = 0;

  virtual void Initialize() override;
  virtual void Update([[maybe_unused]] float deltaTime) override;
  virtual void DebugUpdate() const override;
  virtual void DebugRender() const override;
  virtual int GetID() const override;
  virtual bool IsActive() const override;
  virtual void SetActive(bool active) override;
  virtual const bool& GetActive() override;
  Core::Components::IComponent* GetComponentByType(std::type_index type) override;

  template <typename T, typename... Args>
  void AddComponent(Args&&... args);

  template <typename T>
  void RemoveComponent();

 private:
  std::unordered_map<std::type_index, std::unique_ptr<Core::Components::IComponent>> components{};

  static int GenerateId();
  const int id{GenerateId()};
  bool active{true};
};

template <typename T, typename... Args>
void EntityBase::AddComponent(Args&&... args)
{
  // Ensure no duplicate components of the same type
  const auto type = std::type_index(typeid(T));
  assert(!components.contains(type) && "Component already added!");

  // Emplace a new instance of T using perfect forwarding of arguments
  components[type] = std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
void EntityBase::RemoveComponent()
{
  const auto type = std::type_index(typeid(T));
  this->components.erase(type);
}

}  // namespace Engine::Entity
