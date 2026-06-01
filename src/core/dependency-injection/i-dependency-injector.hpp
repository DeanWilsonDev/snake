//
// Created by Dean Wilson on 15th March 2026
//

#pragma once

#include <memory>
#include <typeindex>
#include <any>
#include <functional>

namespace Core {

class IDependencyInjector {
 public:
  virtual ~IDependencyInjector() = default;

  template <typename TInterface>
  std::shared_ptr<TInterface> Resolve()
  {
    auto any = ResolveImplementation(typeid(TInterface));
    return std::any_cast<std::shared_ptr<TInterface>>(any);
  }

  template <typename TInterface, typename TImplementation>
  void Register()
  {
    return RegisterImplementation(typeid(TInterface), []() -> std::any {
      return std::make_shared<TImplementation>();
    });
  }

  template <typename TInterface>
  void RegisterInstance(const std::shared_ptr<TInterface>& instance)
  {
    return RegisterInstanceImplementation(typeid(TInterface), instance);
  }

  template <typename TInterface, typename TImplementation>
  void RegisterSingleton()
  {
    auto instance = std::make_shared<TImplementation>();
    return RegisterSingletonImplementation(typeid(TInterface), instance);
  }

  virtual void Teardown() = 0;

  template <typename TInterface>
  void Unregister()
  {
    UnregisterImplementation(typeid(TInterface));
  }

 protected:
  virtual std::any ResolveImplementation(std::type_index type) = 0;
  virtual void RegisterImplementation(std::type_index type, std::function<std::any()> factory) = 0;
  virtual void RegisterInstanceImplementation(std::type_index type, std::any instance) = 0;
  virtual void RegisterSingletonImplementation(std::type_index type, std::any instance) = 0;
  virtual void UnregisterImplementation(std::type_index type) = 0;
};

}  // namespace Core
