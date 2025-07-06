//
// Created by Dean Wilson on 6/7/2025.
//

#pragma once
#include <memory>

namespace Core {

template <typename TImplementation>
class ImplementationManager {
 public:
  virtual ~ImplementationManager() = default;
  static void SetBackend(std::unique_ptr<TImplementation> impl) { backend = std::move(impl); };

  static TImplementation* GetBackend()
  {
    if (!backend) {
      throw std::runtime_error("Backend not set!");
    }
    return backend.get();
  }

 protected:
  static bool IsInitialized()
  {
    return backend != nullptr || throw std::runtime_error("Backend not set!");
  };

  static std::unique_ptr<TImplementation> backend;
};

template <typename TImplementation>
std::unique_ptr<TImplementation> ImplementationManager<TImplementation>::backend = nullptr;

}  // namespace Core
