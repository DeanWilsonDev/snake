#pragma once

#include <format>
#include <variant>
#include <cstddef>
#include <variant>
#include <cstddef>
#include <string>
#include <string_view>
#include <functional>

namespace Debug {
struct DebugNode;
struct DebugValue;
}  // namespace Debug

namespace Core {
namespace Debug {

class IDebugHUD {
 public:
  virtual ~IDebugHUD() = default;

  virtual void Visit(
      std::function<void(const std::string& key, const ::Debug::DebugNode& node, int depth)>
          callback
  ) const = 0;

  virtual void ClearFrameData() = 0;

  virtual void Set(const std::string_view path, ::Debug::DebugValue value) = 0;

  virtual void Remove(const std::string& path) = 0;

  virtual void ClearAll() = 0;

  virtual void RenderToConsole() const = 0;

  template <typename... Args>
  void FormatPathAndSet(
      std::variant<int, size_t, float, std::string, bool> value,
      const std::format_string<Args...> format, Args&&... args
  );
};
}  // namespace Debug
}  // namespace Core
