//
// Created by Dean Wilson on 12/7/2025.
//

#include "dependency-injector.hpp"

#include "core/logging/log.hpp"

#include <typeindex>
#include <any>
#include <exception>
#include <stdexcept>
#include <functional>
#include <string>
#include <unordered_map>
#include <typeindex>

namespace Engine {

DependencyInjector::~DependencyInjector()
{
  Teardown();
}

std::any DependencyInjector::ResolveImplementation(std::type_index type)
{
  LOG_CORE_TRACE("[DependencyInjector] Resolving {}", type.name());

  // Check if an instance already exists
  if (const auto itInstance = instances.find(type); itInstance != instances.end()) {
    LOG_CORE_TRACE("[DependencyInjector] Instance for type: {} is being invoked", type.name());
    return itInstance->second;
  }

  // Otherwise create a new instance using the factory
  if (const auto itFactory = factories.find(type); itFactory != factories.end()) {
    try {
      LOG_CORE_TRACE("[DependencyInjector] Factory for type: {} is being invoked", type.name());
      if (!itFactory->second) {
        throw std::runtime_error("[DependencyInjector] Factory function is not callable.");
      }

      const auto rawInstance = itFactory->second();
      instances[type] = rawInstance;  // Cache the instance
      return rawInstance;
    }
    catch (const std::exception& e) {
      throw std::runtime_error(
          std::string("[DependencyInjector] Failed to resolve dependency: ", e.what())
      );
    }
  }

  throw std::runtime_error("[DependencyInjector] Dependency not registered!");
}

void DependencyInjector::RegisterImplementation(
    std::type_index type, std::function<std::any()> factory
)
{
  this->factories[type] = factory;
};

void DependencyInjector::RegisterInstanceImplementation(std::type_index type, std::any instance)
{
  instances[type] = instance;
}

void DependencyInjector::RegisterSingletonImplementation(std::type_index type, std::any instance)
{
  this->instances[type] = instance;
}

void DependencyInjector::UnregisterImplementation(std::type_index type)
{
  instances.erase(type);
  factories.erase(type);
}

void DependencyInjector::Teardown()
{
  instances.clear();
  factories.clear();
}

}  // namespace Engine
