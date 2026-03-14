#pragma once

#include <format>
#include <variant>
#include <type_traits>
#include <cstddef>
#include <variant>
#include <string>
#include <string_view>
#include <vector>
#include <cstddef>
#include <functional>
#include "debug-node.hpp"
#include "debug-value.hpp"
#include "core/debug/i-debug-hud.hpp"

namespace Debug {

class DebugHUD : public Core::Debug::IDebugHUD {
 public:
  DebugHUD();
  ~DebugHUD() override;

  void Visit(
      std::function<void(const std::string& key, const DebugNode& node, int depth)> callback
  ) const override;
  void ClearFrameData() override;

  void Set(const std::string_view path, DebugValue value) override;

  void Remove(const std::string& path) override;

  void ClearAll() override;

  void RenderToConsole() const override;

 private:
  DebugMap root;

  static std::vector<std::string> SplitPath(const std::string_view path);

  DebugNode& GetOrCreateNode(const std::vector<std::string>& parts);

  void VisitNode(
      const std::string& key, const DebugNode& node, const int depth, auto& callback
  ) const;

  static void PrintNode(const std::string& key, DebugNode* node, int indent);

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
