//
// Created by Dean Wilson 6th June 2026
//

#pragma once

#include "core/components/i-component.hpp"
#include "core/entities/i-component-dispatcher.hpp"
#include "core/entities/i-entity.hpp"
#include <typeindex>
#include <unordered_map>

namespace Engine {
namespace Entities {

class ComponentDispatcher final : public Core::Entities::IComponentDispatcher {
 public:
  ~ComponentDispatcher() = default;
  virtual void Dispatch(Core::Entities::IEntity*) override;

  template <typename TComponent>
  void RegisterHandler(std::function<void(TComponent*)> handler)
  {
    this->handlers[std::type_index(typeid(TComponent))] =
        [handler](Core::Components::IComponent* component) {
          if (auto* typed = dynamic_cast<TComponent*>(component)) {
            handler(typed);
          }
        };
  }

 private:
  std::unordered_map<std::type_index, std::function<void(Core::Components::IComponent*)>> handlers;
};

}  // namespace Entities
}  // namespace Engine
