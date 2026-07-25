//
// Created by Dean Wilson on 3 May 2026
//
#pragma once

#include <cassert>
#include "core/debug/i-debugable.hpp"
#include "core/life-cycle-hooks/i-begin-play.hpp"
#include "core/life-cycle-hooks/i-on-activate.hpp"
#include "core/life-cycle-hooks/i-on-registration.hpp"
#include "core/life-cycle-hooks/i-updatable.hpp"
#include <functional>
#include <type_traits>
#include <typeindex>
#include <utility>

namespace Core {
namespace Components {
class IComponent;
}  // namespace Components

namespace Spatial {
namespace Components {
class ITransformComponent2D;
}  // namespace Components
}  // namespace Spatial

namespace Entities {

class IEntity : public Core::IBeginPlay,
                public Core::IOnActivate,
                public Core::IOnRegistration,
                public Core::IUpdatable,
                public Core::Debug::IDebugable {
 public:
  virtual ~IEntity() = default;

  virtual int GetID() const = 0;
  virtual bool IsActive() const = 0;
  virtual void SetActive(bool active) = 0;
  virtual const bool& GetActive() const = 0;

  template <typename T>
  T* GetComponent()
  {
    return const_cast<T*>(std::as_const(*this).GetComponent<T>());
  }

  template <typename T>
  const T* GetComponent() const
  {
    if constexpr (std::is_abstract_v<T>) {
      T* result = nullptr;
      this->ForEachComponent([&result](const Core::Components::IComponent* component) {
        if (auto* match = dynamic_cast<const T*>(component)) {
          result = const_cast<T*>(match);
          return false;
        }
        return true;
      });
      return result;
    }
    return static_cast<const T*>(this->GetComponentByType(typeid(T)));
  }

  virtual void ForEachComponent(
      std::function<bool(const Core::Components::IComponent*)> visitor
  ) const = 0;

 private:
  virtual Core::Components::IComponent* GetComponentByType(std::type_index type) const = 0;
};
}  // namespace Entities
}  // namespace Core
