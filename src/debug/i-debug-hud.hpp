#pragma once

#include <string>
#include <functional>
#include "debug-node.hpp"
#include "debug-value.hpp"

namespace Debug {

class IDebugHUD {
  public:
  virtual ~IDebugHUD() = default;

  virtual void Visit(
      std::function<void(const std::string& key, const DebugNode& node, int depth)> callback
  ) const = 0;
  
  virtual void ClearFrameData() = 0;

  virtual void Set(const std::string& path, DebugValue value) = 0;

  virtual void Remove(const std::string& path) = 0;

  virtual void ClearAll() = 0;

  virtual void RenderToConsole() const = 0;
};
}  // namespace Debug
