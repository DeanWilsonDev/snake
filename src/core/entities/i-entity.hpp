//
// Created by Dean Wilson on 3 May 2026
//
#pragma once

#include <cassert>
#include "core/debug/i-debugable.hpp"
#include "core/i-updatable.hpp"
#include <typeindex>

namespace Core {
namespace Components {
class IComponent;
class TransformComponent2D;
}  // namespace Components

namespace Entities {

class IEntity : public Core::IUpdatable, public Core::Debug::IDebugable {
 public:
  virtual ~IEntity() = 0;

  virtual void Initialize() = 0;
  virtual int GetID() const = 0;
  virtual bool IsActive() const = 0;
  virtual void SetActive(bool active) = 0;
  virtual const bool& GetActive() const = 0;
  virtual Components::TransformComponent2D& GetTransformComponent() = 0;
  virtual Core::Components::IComponent* GetComponentByType(std::type_index type) = 0;
  template <typename T>
  T* GetComponent()
  {
    return static_cast<T*>(this->GetComponentByType(typeid(T)));
  };
};
}  // namespace Entities
}  // namespace Core
