//
// Created by Dean Wilson on 12/7/2025.
//

#pragma once
#include <umbra/log.h>
#include <exception>
#include <stdexcept>
#include <functional>
#include <string>
#include <memory>
#include <unordered_map>
#include <typeindex>

namespace Engine {

class DependencyInjector {
 public:
  DependencyInjector() = default;
  ~DependencyInjector();

  template <typename Interface, typename Implementation>
  void Register();

  template <typename Interface>
  void RegisterInstance(const std::shared_ptr<Interface>& instance);

  template <typename Interface, typename Implementation>
  void RegisterSingleton();

  template <typename Interface>
  std::shared_ptr<Interface> Resolve();

  void Teardown();

  template <typename Interface>
  void Unregister();

 private:
  std::unordered_map<std::type_index, std::function<std::shared_ptr<void>()>> factories;
  std::unordered_map<std::type_index, std::shared_ptr<void>> instances;
};

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

template <typename Interface, typename Implementation>
void DependencyInjector::RegisterSingleton()
{
  auto instance = std::make_shared<Implementation>();
  this->instances[std::type_index(typeid(Interface))] = instance;
}

template <typename Interface>
std::shared_ptr<Interface> DependencyInjector::Resolve()
{
  const auto type = std::type_index(typeid(Interface));
  LOG_CORE_TRACE("[DependencyInjector] Resolving {}", type.name());

  // Check if an instance already exists
  if (const auto itInstance = instances.find(type); itInstance != instances.end()) {
    LOG_CORE_TRACE("[DependencyInjector] Instance for type: {} is being invoked", type.name());
    return std::static_pointer_cast<Interface>(itInstance->second);
  }

  // Otherwise create a new instance using the factory
  if (const auto itFactory = factories.find(type); itFactory != factories.end()) {
    try {
      LOG_CORE_TRACE("[DependencyInjector] Factory for type: {} is being invoked", type.name());
      if (!itFactory->second) {
        throw std::runtime_error("[DependencyInjector] Factory function is not callable.");
      }

      const auto rawInstance = itFactory->second();
      if (!rawInstance) {
        throw std::runtime_error(
            "[DependencyInjector] Factory returned nullptr for the requested dependency."
        );
      }
      instances[type] = rawInstance;  // Cache the instance
      return std::static_pointer_cast<Interface>(rawInstance);
    }
    catch (const std::exception& e) {
      throw std::runtime_error(
          std::string("[DependencyInjector] Failed to resolve dependency: ", e.what())
      );
    }
  }

  throw std::runtime_error("[DependencyInjector] Dependency not registered!");
}

template <typename Interface>
void DependencyInjector::Unregister()
{
  const auto type = std::type_index(typeid(Interface));
  instances.erase(type);
  factories.erase(type);
}
}  // namespace Engine
