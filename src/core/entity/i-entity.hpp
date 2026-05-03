//
// Created by Dean Wilson on 3 May 2026
//
#pragma once

#include "core/debug/i-debugable.hpp"
#include "core/i-updatable.hpp"
#include <cassert>

namespace Core::Entity {

class IEntity : public Core::Debug::IDebugable, Core::IUpdatable {
 public:
  virtual ~IEntity() = 0;

  virtual void Initialize();
  virtual void Update([[maybe_unused]] float deltaTime) override;
  virtual void DebugUpdate() override;
  virtual void DebugRender() override;
  virtual int GetID() const = 0;
  virtual bool IsActive() const = 0;
  virtual void SetActive(bool active) = 0;
  virtual const bool& GetActive() = 0;

  template <typename T, typename... Args>
  void AddComponent(Args&&... args);

  template <typename T>
  T* GetComponent();

  template <typename T>
  void RemoveComponent();
};
}  // namespace Core::Entity
