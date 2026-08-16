//
// Created by Dean Wilson on 29/5/2025.
//
#pragma once

#include "core/components/i-component.hpp"
#include "core/entities/i-entity.hpp"

#include <cassert>
#include <functional>
#include <typeindex>
#include <unordered_map>
#include <memory>

using namespace Core::Entities;

namespace Core {
namespace Spatial {
class ITransform2D;
}
}  // namespace Core

namespace Engine::Spatial::Components {
class TransformComponent2D;
}  // namespace Engine::Spatial::Components

namespace Engine::Entities {

struct EntityParams {
  const bool active = true;
  const Core::Spatial::ITransform2D& transform;

  EntityParams(const Core::Spatial::ITransform2D& transform, const bool active = true)
      : active(active), transform(transform)
  {
  }
};

class Entity : public Core::Entities::IEntity {
 public:
  Engine::Spatial::Components::TransformComponent2D* transform;

  explicit Entity(const EntityParams& params);
  virtual ~Entity() = 0;

  virtual void BeginPlay() override;
  virtual void OnRegistration() override;
  virtual void OnActivate() override;
  virtual void Update(float deltaTime) override;
  virtual void DebugUpdate() const override;
  virtual void DebugRender() const override;

  virtual int GetID() const override;
  virtual bool IsActive() const override;
  virtual void SetActive(const bool active) override;
  virtual const bool& GetActive() const override;

  template <typename T, typename... Args>
  T* AddComponent(Args&&... args);

  template <typename T>
  void RemoveComponent();

  void ForEachComponent(
      std::function<bool(const Core::Components::IComponent*)> visitor
  ) const override;

  void ForEachComponent(std::function<bool(Core::Components::IComponent*)> visitor) override;

 private:
  std::unordered_map<std::type_index, std::unique_ptr<Core::Components::IComponent>> components{};

  static int GenerateId();
  const int id{GenerateId()};
  bool active{true};

  Core::Components::IComponent* GetComponentByType(std::type_index type) const override;
};

template <typename T, typename... Args>
T* Entity::AddComponent(Args&&... args)
{
  // Ensure no duplicate components of the same type
  const auto type = std::type_index(typeid(T));
  assert(!components.contains(type) && "Component already added!");

  // Emplace a new instance of T using perfect forwarding of arguments
  components[type] = std::make_unique<T>(std::forward<Args>(args)...);
  return static_cast<T*>(components[type].get());
}

template <typename T>
void Entity::RemoveComponent()
{
  const auto type = std::type_index(typeid(T));
  this->components.erase(type);
}

}  // namespace Engine::Entities
