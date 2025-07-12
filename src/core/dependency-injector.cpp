//
// Created by Dean Wilson on 12/7/2025.
//

#include "dependency-injector.hpp"

#include "log.h"

#include <core.h>

namespace Core {

DependencyInjector::~DependencyInjector()
{
  Teardown();
}

template <typename Interface, typename Implementation>
void DependencyInjector::Register()
{
  factories[std::type_index(typeid(Interface))] = []() -> std::shared_ptr<void> {
    return std::make_shared<Implementation>();
  };
}

template <typename Interface>
void DependencyInjector::RegisterInstance(const std::shared_ptr<Interface>& instance)
{
  instances[std::type_index(typeid(Interface))] = instance;
}

template <typename Interface>
std::shared_ptr<Interface> DependencyInjector::Resolve()
{
  const auto type = std::type_index(typeid(Interface));

  // Check if an instance already exists
  if (const auto itInstance = instances.find(type); itInstance != instances.end()) {
    LOG_CORE_DEBUG("Instance for type: {} is being invoked", type.name());
    return std::static_pointer_cast<Interface>(itInstance->second);
  }

  // Otherwise create a new instance using the factory
  if (const auto itFactory = factories.find(type); itFactory != factories.end()) {
    try {
      LOG_CORE_DEBUG("Factory for type: {} is being invoked", type.name());
      if (!itFactory->second) {
        throw std::runtime_error("Factory function is not callable.");
      }

      const auto rawInstance = itFactory->second();
      if (!rawInstance) {
        throw std::runtime_error("Factory returned nullptr for the requested dependency.");
      }
      instances[type] = rawInstance;  // Cache the instance
      return std::static_pointer_cast<Interface>(rawInstance);
    }
    catch (const std::exception& e) {
      throw std::runtime_error(std::string("Failed to resolve dependency: ", e.what()));
    }
  }

  throw std::runtime_error("Dependency not registered!");
}

void DependencyInjector::Teardown()
{
  instances.clear();
  factories.clear();
}

template <typename Interface>
void DependencyInjector::Unregister()
{
  const auto type = std::type_index(typeid(Interface));
  instances.erase(type);
  factories.erase(type);
}

}  // namespace Core