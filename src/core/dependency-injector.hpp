//
// Created by Dean Wilson on 12/7/2025.
//

#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include <typeindex>

namespace Core {

class DependencyInjector {
 public:
  DependencyInjector() = default;
  ~DependencyInjector();

  template <typename Interface, typename Implementation>
  void Register();

  template <typename Interface>
  void RegisterInstance(const std::shared_ptr<Interface>& instance);

  template <typename Interface>
  std::shared_ptr<Interface> Resolve();

  void Teardown();

  template<typename Interface>
  void Unregister();


 private:
  std::unordered_map<std::type_index, std::function<std::shared_ptr<void>()>> factories;
  std::unordered_map<std::type_index, std::shared_ptr<void>> instances;
};
}  // namespace Core
