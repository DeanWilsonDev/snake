//
// Created by Dean Wilson on 12/7/2025.
//

#pragma once

#include "core/i-dependency-injector.hpp"

#include <typeindex>
#include <any>
#include <functional>
#include <memory>
#include <unordered_map>
#include <typeindex>

namespace Engine {

class DependencyInjector : public Core::IDependencyInjector {
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

  virtual void Teardown() override;

  template <typename Interface>
  void Unregister();

 protected:
  virtual std::any ResolveImplementation(std::type_index type) override;
  virtual void RegisterImplementation(
      std::type_index type, std::function<std::any()> factory
  ) override;
  virtual void RegisterInstanceImplementation(std::type_index type, std::any instance) override;
  virtual void RegisterSingletonImplementation(std::type_index type, std::any instance) override;
  virtual void UnregisterImplementation(std::type_index type) override;

 private:
  std::unordered_map<std::type_index, std::function<std::any()>> factories;
  std::unordered_map<std::type_index, std::any> instances;
};

}  // namespace Engine
