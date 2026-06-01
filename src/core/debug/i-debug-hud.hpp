#pragma once

#include "debug-value.hpp"
#include "debug-node.hpp"
#include <format>
#include <variant>
#include <cstddef>
#include <variant>
#include <cstddef>
#include <string>
#include <string_view>
#include <functional>

namespace Core {
namespace Debug {

class IDebugHUD {
 public:
  virtual ~IDebugHUD() = default;

  virtual void Visit(
      std::function<void(const std::string& key, const DebugNode& node, int depth)> callback
  ) const = 0;

  virtual void ClearFrameData() = 0;

  virtual void Set(const std::string_view path, DebugValue value) = 0;

  virtual void Remove(const std::string& path) = 0;

  virtual void ClearAll() = 0;

  virtual void RenderToConsole() const = 0;

  template <typename... Args>
  void FormatPathAndSet(
      std::variant<int, size_t, float, std::string, bool> value,
      const std::format_string<Args...> format, Args&&... args
  )
  {
    DebugValue debugValue{};
    std::visit(
        [&](const auto& x) {
          using T = std::decay_t<decltype(x)>;
          if constexpr (std::is_same_v<T, int>) {
            debugValue = DebugValue::FromNumber(x);
          }
          if constexpr (std::is_same_v<T, size_t>) {
            debugValue = DebugValue::FromNumber(x);
          }
          if constexpr (std::is_same_v<T, float>) {
            debugValue = DebugValue::FromNumber(x);
          }
          if constexpr (std::is_same_v<T, double>) {
            debugValue = DebugValue::FromNumber(x);
          }
          if constexpr (std::is_same_v<T, std::string>) {
            debugValue = DebugValue::FromString(x);
          }
          if constexpr (std::is_same_v<T, bool>) {
            debugValue = DebugValue::FromBool(x);
          }
        },
        value
    );

    std::string path = std::format(format, std::forward<Args>(args)...);
    this->Set(path, debugValue);
  }
};
}  // namespace Debug
}  // namespace Core
