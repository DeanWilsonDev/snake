//
// Created by Dean Wilson on 3 May 2026
//
#pragma once

#include "core/debug/i-debugable.hpp"
#include "core/i-updatable.hpp"
#include "core/components/i-component.hpp"
#include <cassert>
#include <typeindex>

namespace Core::Entity {

class IEntity : public Core::Debug::IDebugable, Core::IUpdatable {
 public:
  virtual ~IEntity() = 0;

  virtual void Initialize() = 0;
  virtual void Update([[maybe_unused]] float deltaTime) override = 0;
  virtual void DebugUpdate() const override = 0;
  virtual void DebugRender() const override = 0;
  virtual int GetID() const = 0;
  virtual bool IsActive() const = 0;
  virtual void SetActive(bool active) = 0;
  virtual const bool& GetActive() = 0;
  virtual Core::Components::IComponent* GetComponentByType(std::type_index type) = 0;

  template <typename T>
  T* GetComponent()
  {
    return static_cast<T*>(this->GetComponentByType(typeid(T)));
  };
};
}  // namespace Core::Entity
