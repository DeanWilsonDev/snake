//
// Created by Dean Wilson on 6/7/2025.
//

// REAPER: There are a string of files from this to the window and screen that might not be getting used.

#pragma once
#include <memory>
#include <umbra/log.h>

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
    if (backend == nullptr) {
      LOG_CORE_FATAL("Backend not set!");
      return false;
    }
    return true;
  };

  static std::unique_ptr<TImplementation> backend;
};

template <typename TImplementation>
std::unique_ptr<TImplementation> ImplementationManager<TImplementation>::backend = nullptr;

}  // namespace Core
